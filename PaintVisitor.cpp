//PaintVisitor.cpp

#include "PaintVisitor.h"
#include "Memo.h"
#include "Line.h"
#include "CharacterFaces.h"
#include <afxWin.h>
using namespace std;

//PaintVisitor::PaintVisitor()
//	:Visitor() {
//
//}

//PaintVisitor::PaintVisitor(CDC *dc)
//	: Visitor(), dc(dc) {
//
//}

PaintVisitor::PaintVisitor(CPaintDC *dc, CRect* rect)
	:Visitor() {
	this->dc = dc;
	this->rect = rect;
}

PaintVisitor::PaintVisitor(const PaintVisitor& source)
	: Visitor(source) {
	this->dc = source.dc;
	this->rect = source.rect;
}

PaintVisitor::~PaintVisitor() {

}

PaintVisitor& PaintVisitor::operator=(const PaintVisitor& source) {
	Visitor::operator=(source);
	this->dc = source.dc;
	this->rect = source.rect;

	return *this;
}

void PaintVisitor::Visit(Note *note) {
	
}

#include "MakeStringVisitor.h"
#include "Page.h"
void PaintVisitor::Visit(Page *page) {
	//MakeStringVisitor makeStringVisitor;
	//page->Accept(&makeStringVisitor);

	//CharacterFaces *characterFaces = CharacterFaces::Instance(this->dc);
	//CFont font;
	//font.CreatePointFont(characterFaces->GetFontSize(), characterFaces->GetFontFamily().c_str());
	//this->dc->SelectObject(&font);

	////	this->dc->TabbedTextOut(0, 0, makeStringVisitor.GetCompleteString().c_str(), 8, 0, 0);
	////	this->dc->TextOut(0,0, makeStringVisitor.GetCompleteString().c_str());
	//this->dc->DrawText(CString(makeStringVisitor.GetCompleteString().c_str()), this->rect, DT_EDITCONTROL | DT_WORDBREAK | DT_LEFT | DT_EXPANDTABS);
	MakeStringVisitor makeStringVisitor;
	Memo *memo;
	Long i = 0;
	while (i < page->GetLength()) {
		memo = page->GetMemo(i);
		memo->Accept(&makeStringVisitor);
		this->dc->DrawText(CString(makeStringVisitor.GetCompleteString().c_str()), this->rect, DT_EDITCONTROL | DT_WORDBREAK | DT_LEFT | DT_EXPANDTABS);
		i++;
	}
}

#include "MakeStringVisitor.h"
void PaintVisitor::Visit(Memo *memo) {
	this->dc->FillSolidRect(rect, RGB(230, 230, 250));

	this->dc->SetBkMode(TRANSPARENT);
	//CRect wndRect;
	//this->GetWindowRect(&wndRect);

	CRect clientRect(this->rect->left, this->rect->top + 20, this->rect->right, this->rect->bottom);
	this->dc->FillSolidRect(this->rect->left, this->rect->top, this->rect->right, this->rect->top + 20, RGB(123, 104, 238));
	MakeStringVisitor makeStringVisitor;
	memo->Accept(&makeStringVisitor);

	CharacterFaces *characterFaces = CharacterFaces::Instance(this->dc);
	CFont font;
	font.CreatePointFont(characterFaces->GetFontSize(), characterFaces->GetFontFamily().c_str());
	this->dc->SelectObject(&font);

//	this->dc->TabbedTextOut(0, 0, makeStringVisitor.GetCompleteString().c_str(), 8, 0, 0);
//	this->dc->TextOut(0,0, makeStringVisitor.GetCompleteString().c_str());
	this->dc->DrawText(CString(makeStringVisitor.GetCompleteString().c_str()), CRect(clientRect.left+15, clientRect.top+7, clientRect.right, clientRect.bottom), DT_EDITCONTROL | DT_WORDBREAK | DT_LEFT | DT_EXPANDTABS);
}

void PaintVisitor::Visit(Line *line) {

}

void PaintVisitor::Visit(SingleCharacter *singleCharacter) {

}

void PaintVisitor::Visit(DoubleCharacter *doubleCharacter) {

}

void PaintVisitor::Visit(Character *character) {
	
}