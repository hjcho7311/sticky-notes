// HighLightVisitor.cpp

#include "HighLightVisitor.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"
#include "CharacterFaces.h"
#include "SingleCharacter.h"
#include "DoubleCharacter.h"

HighLightVisitor::HighLightVisitor(CDC *dc)
	:Visitor() {
	this->dc = dc;
}

HighLightVisitor::HighLightVisitor(const HighLightVisitor& source)
	: Visitor(source) {
}

HighLightVisitor::~HighLightVisitor() {

}

HighLightVisitor& HighLightVisitor::operator=(const HighLightVisitor& source) {
	Visitor::operator=(source);

	return *this;
}

void HighLightVisitor::Visit(Note *note) {

}

void HighLightVisitor::Visit(Page *page) {

}

void HighLightVisitor::Visit(Memo *memo) {
	//Memo *memo = static_cast<Memo*>(this->GetContents());
	Line *line = memo->GetLine(0);
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	CharacterSize characterSize = characterFaces->GetCharacterSize(97);
	Long characterHeight = characterSize.GetHeight();
	
	//�츮��Ʈ�� �°� �ٽ� ��������
	CFont font;
	font.CreatePointFont(characterFaces->GetFontSize(), characterFaces->GetFontFamily().c_str());
	
	this->dc->SelectObject(&font);
	this->dc->SetBkMode(OPAQUE);
	this->dc->SetBkColor(RGB(255, 255, 102));
	this->dc->SetTextColor(RGB(0, 0, 0));
	
	if (line->GetLength() > 0) {
		Long xPos = 0;
		Long yPos = 20;
		Long i = 0;
		Long begin_xPos;
		bool highLight = false;
		bool isDraw = false;

		while (i < memo->GetLength()) {
			line = memo->GetLine(i);
			Long j = 0;
			xPos = 0;
			begin_xPos = -1;
			
			CString str;
			
			while (j < line->GetLength()) {
				if (line->GetCharacter(j)->GetHighLight() == true) {
					if (begin_xPos == -1) {
						begin_xPos = xPos;
						highLight = true;
					}
					if (dynamic_cast<SingleCharacter*>(line->GetCharacter(j))) {
						str += CString(dynamic_cast<SingleCharacter*>(line->GetCharacter(j))->GetValue());
					}
					else {
						string composition;
						composition += dynamic_cast<DoubleCharacter*>(line->GetCharacter(j))->GetValue()[0];
						composition += dynamic_cast<DoubleCharacter*>(line->GetCharacter(j))->GetValue()[1];
						str += composition.c_str();
					}
				}
				else {
					if (highLight == true) {
						highLight = false;
						isDraw = true;
					}
				}
				if (isDraw == true || j == line->GetLength()-1) {
					this->dc->TextOutA(begin_xPos, yPos, str);
					str = "";
					begin_xPos = -1;
					isDraw = false;
				}
				xPos += line->GetCharacter(j)->GetWidth();
				j++;
			}
			yPos += characterHeight;
			i++;
		}
	}
}

void HighLightVisitor::Visit(Line *line) {

}
void HighLightVisitor::Visit(Character *character) {

}
void HighLightVisitor::Visit(SingleCharacter *singleCharacter) {

}
void HighLightVisitor::Visit(DoubleCharacter *doubleCharacter) {

}

