//PaintSelectionVisitor.cpp

#include "PaintSelectionVisitor.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"
#include "CharacterFaces.h"
#include "Caret.h"
#include "SelectedBuffer.h"
#include <afxWin.h>
using namespace std;

PaintSelectionVisitor::PaintSelectionVisitor(CDC *dc)
	:Visitor() {
	this->dc = dc;
//	this->selectedBuffer = selectedBuffer;
	//this->xPosition = xPosition;
	//this->yPosition = yPosition;

	//Long beginRow = this->selectedBuffer->GetBeginRow();
	//Long i = 0;
	//while (i < beginRow) {
	//	this->yPosition += caret->GetHeight();
	//	i++;
	//}
	//Line *beginLine = this->selectedBuffer->GetBuffer()->GetLine(beginRow);
	//Long beginColumn = this->selectedBuffer->GetBeginColumn();
	//this->xPosition = 0;
	//Long j = 0;
	//while (j < beginColumn) {
	//	this->xPosition += beginLine->GetCharacter(j)->GetWidth();
	//	j++;
	//}	
}

PaintSelectionVisitor::PaintSelectionVisitor(const PaintSelectionVisitor& source)
	: Visitor(source) {
	this->dc = source.dc;
//	this->selectedBuffer = source.selectedBuffer;
	this->xPosition = source.xPosition;
	this->yPosition = source.yPosition;
}

PaintSelectionVisitor::~PaintSelectionVisitor() {

}

PaintSelectionVisitor& PaintSelectionVisitor::operator=(const PaintSelectionVisitor& source) {
	Visitor::operator=(source);
	this->dc = source.dc;
//	this->selectedBuffer = source.selectedBuffer;
	this->xPosition = source.xPosition;
	this->yPosition = source.yPosition;
	
	return *this;
}

#include "MakeStringVisitor.h"
void PaintSelectionVisitor::Visit(Note *note) {

}

void PaintSelectionVisitor::Visit(Page *page) {

}


void PaintSelectionVisitor::Visit(Memo *memo) {
	//Caret *caret = Caret::Instance(0);
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	CharacterSize characterSize = characterFaces->GetCharacterSize(127);

	Long i = 0;
	Line *line = memo->GetLine(i);
	line->Accept(this);
	i++;
	while (i < memo->GetLength()) {
		this->xPosition = 0 + 15;  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//this->yPosition += caret->GetHeight();
		this->yPosition += characterSize.GetHeight();
		Line *line = memo->GetLine(i);
		line->Accept(this);
		i++;
	}
}

void PaintSelectionVisitor::Visit(Line *line) {
	MakeStringVisitor makeStringVisitor;
	//makeStringVisitor.SetCompleteString("");
	line->Accept(&makeStringVisitor);

	this->dc->TabbedTextOut(this->xPosition, this->yPosition, makeStringVisitor.GetCompleteString().c_str(), 8, 0, 0);
}  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void PaintSelectionVisitor::Visit(SingleCharacter *singleCharacter) {

}

void PaintSelectionVisitor::Visit(DoubleCharacter *doubleCharacter) {

}

void PaintSelectionVisitor::Visit(Character *character) {

}
#include "MemoForm.h"
void PaintSelectionVisitor::Visit(MemoForm *memoForm) {
	if (memoForm->GetSelectedBuffer()->GetIsSelecting() == true) {		//this->selectedBuffer->GetBuffer()!=0
		//CDC *dc = memoForm->GetDC();
		CharacterFaces *characterFaces = CharacterFaces::Instance(this->dc);
		CFont font;
		font.CreatePointFont(characterFaces->GetFontSize(), characterFaces->GetFontFamily().c_str());
		this->dc->SelectObject(&font);
		this->dc->SetBkMode(OPAQUE);
		this->dc->SetBkColor(RGB(51, 153, 255));
		this->dc->SetTextColor(RGB(255, 255, 255));
		Memo *bufferMemo = memoForm->GetSelectedBuffer()->GetBuffer();
		Line *bufferLine = bufferMemo->GetLine(bufferMemo->GetRow());
		Long xPos = 0;
		Long yPos = 0;
		memoForm->CalculatePosition(&xPos, &yPos);
		this->xPosition = xPos + 15;
		this->yPosition = yPos +20 + 7;   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//PaintSelectionVisitor paintSelectionVisitor(dc, memoForm->GetSelectedBuffer(), xPos, yPos + 20);

		bufferMemo->Accept(this);
	}

}