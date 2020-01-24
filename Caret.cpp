////Caret.cpp
//
//#include "Caret.h"
//#include "MemoForm.h"
//#include "Memo.h"
//#include "Line.h"
//#include "SingleCharacter.h"
//#include "DoubleCharacter.h"
//#include "CharacterFaces.h"
//#include "CharacterSize.h"
//
////Caret* Caret::_instance = 0;
//
//Caret::Caret(MemoForm *memoForm) {
//	this->memoFormLink = memoForm;
//
//	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
////	CharacterFaces *characterFaces = CharacterFaces::Instance(this->memoFormLink->GetDC());
//	CharacterSize characterSize = characterFaces->GetCharacterSize(95);
//	
//	this->width = 5;
//	this->height = characterSize.GetHeight();
//	//this->memoFormLink->CWnd::CreateSolidCaret(this->width, this->height);
//	
//	this->xPosition = 0;
//	this->yPosition = 0;
//	//this->memoFormLink->CWnd::SetCaretPos(CPoint(xPosition, yPosition));
//	
////	this->memoFormLink->CWnd::ShowCaret();
//}
//
//Caret::~Caret() {
////	_instance = 0;
//}
//
////Caret::Caret(const Caret& source) {
////
////}
//
////Caret* Caret::Instance(MemoForm *memoForm) {
////	if (_instance == 0) {
////		_instance = new Caret(memoForm);
////	}
////
////	return _instance;
////}
//
////void SetCaretPosition(NoteBookForm *noteBookForm, Long xPosition, Long yPosition) {
//////	noteBookForm->CreateSolidCaret(5, 50);
////
////	noteBookForm->SetCaretPos(*(noteBookForm->point));
////
////	//noteBookForm->ShowCaret();
////}
//
//void Caret::Move(Long xPos, Long yPos) {
//	this->xPosition = xPos;
//	this->yPosition = yPos;
//
//	CWnd::SetCaretPos(CPoint(xPosition, yPosition));
//
//}
//
//void Caret::MoveNextCharacter() {
//	Memo *memo = static_cast<Memo*>(this->memoFormLink->GetContents());
//	Line *line = memo->GetLine(memo->GetRow());
//	Character *character = line->GetCharacter(line->GetColumn() - 1);
//	Long moveWidth;
//
//	//if (dynamic_cast<SingleCharacter*>(character)) {
//	//	char value = dynamic_cast<SingleCharacter*>(character)->GetValue();
//	//	if (value == '\t') {
//	//		CharacterFaces *characterFaces = CharacterFaces::Instance(noteBookFormLink->GetDC());
//	//		Long tabWidth = characterFaces->GetCharacterSize(97).GetWidth() * 8;	//ASCII a:97
//	//		moveWidth = tabWidth - (xPosition%tabWidth);
//	//	}
//	//	else {
//	//		moveWidth = character->GetWidth();
//	//	}
//	//}
//	//else if (dynamic_cast<DoubleCharacter*>(character)) {
//	moveWidth = character->GetWidth();
////	}
//
//	this->xPosition += moveWidth;
//	
//	CWnd::SetCaretPos(CPoint(xPosition, yPosition));
//}
//
//void Caret::MovePreviousCharacter() {
//	Memo *memo = static_cast<Memo*>(this->memoFormLink->GetContents());
//	Line *line = memo->GetLine(memo->GetRow());
//	Character *character = line->GetCharacter(line->GetColumn() - 1);
//	Long moveWidth = character->GetWidth();
//
//	this->xPosition -= moveWidth;
//
//	CWnd::SetCaretPos(CPoint(xPosition, yPosition));
//}
//
//void Caret::MoveNextLine() {
////	Memo *memo = this->noteBookFormLink->GetMemo();
////	Line *line = memo->GetLine(memo->GetRow() - 1);
//	//Character *character = line->GetCharacter(line->GetColumn() - 1);
//	//Long moveHeight = character->GetHeight();
//
////	this->yPosition += moveHeight;
//	this->yPosition += this->height;
//	this->xPosition = 0;
//	//line = memo->GetLine(memo->GetRow());
//	//Long moveWidth;
//	//xPosition = 0;
//	//Long i = 0;
//	//while (i < line->GetColumn()) {
//	//	character = line->GetCharacter(line->GetColumn());
//	//	moveWidth = character->GetWidth();
//	//	xPosition += moveWidth;
//	//	i++;
//	//}
//
//
//	CWnd::SetCaretPos(CPoint(xPosition, yPosition));
//}
//
//void Caret::MovePreviousLine() {
////	Memo *memo = this->noteBookFormLink->GetMemo();
////	Line *line = memo->GetLine(memo->GetRow());
//	
//	//Character *character = line->GetCharacter(line->GetColumn() - 1);
//	//Long moveHeight = character->GetHeight();
//
////	yPosition -= moveHeight;
//	this->xPosition = 0;
//	this->yPosition -= height;
//	/*
//	line = memo->GetLine(memo->GetRow() - 1);
//	Long moveWidth;
//	xPosition = 0;
//	Long i = 0;
//	while (i < line->GetColumn()) {
//		character = line->GetCharacter(line->GetColumn());
//		moveWidth = character->GetWidth();
//		xPosition += moveWidth;
//		i++;
//	}
//	*/
//	CWnd::SetCaretPos(CPoint(xPosition, yPosition));
//}
//
//bool Caret::ChangeImeCaret() {
//	DestroyCaret();
//
//	//Memo *memo = noteBookFormLink->GetMemo();
//	//Line *line = memo->GetLine(memo->GetRow());
//	//Character *character = line->GetCharacter(line->GetColumn()-1);
//	//
//	//width = character->GetWidth();
//	//height = character->GetHeight();
//
////	CharacterFaces *characterFaces = CharacterFaces::Instance(this->memoFormLink->GetDC());
//	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
//	//CharacterSize characterSize(characterFaces->GetCharacterSize(127));
//	//width = characterSize.GetWidth();
//	//height = characterSize.GetHeight();
//
//	this->width = characterFaces->GetCharacterSize(127).GetWidth();
//	this->height = characterFaces->GetCharacterSize(127).GetHeight();
//
//	memoFormLink->CWnd::CreateSolidCaret(this->width, this->height);
//
//	memoFormLink->CWnd::ShowCaret();
//
//	return true;
//}
//
//bool Caret::ChangeCaret() {
//	DestroyCaret();
//
//	Memo *memo = static_cast<Memo*>(this->memoFormLink->GetContents());
//	Line *line = memo->GetLine(memo->GetRow());
//	Character *character = line->GetCharacter(line->GetColumn() - 1);
//
//	width = 5;
//	height = character->GetHeight();
//
//	memoFormLink->CWnd::CreateSolidCaret(width, height);
//
//	memoFormLink->CWnd::ShowCaret();
//
//	return true;
//}
//
//void Caret::MoveNextTab() {
//	CharacterFaces *characterFaces = CharacterFaces::Instance(memoFormLink->GetDC());
//
//	Long tabWidth = characterFaces->GetCharacterSize(97).GetWidth()*8;
//
//	Long moveWidth = tabWidth - (xPosition%tabWidth);
//	xPosition += moveWidth;
//
//	CWnd::SetCaretPos(CPoint(xPosition, yPosition));
//}
//
//void Caret::MovePreviousTab() {
//
//}
//
//void Caret::ShowCaret() {
//	this->memoFormLink->CWnd::CreateSolidCaret(this->width, this->height);
//	this->memoFormLink->CWnd::SetCaretPos(CPoint(this->xPosition, this->yPosition));
//	this->memoFormLink->CWnd::ShowCaret();
//}






//Caret.cpp

#include "Caret.h"
#include "MemoForm.h"
#include "Memo.h"
#include "Line.h"
#include "SingleCharacter.h"
#include "DoubleCharacter.h"
#include "CharacterFaces.h"
#include "CharacterSize.h"

#define CARETWIDTH 2;

//Caret* Caret::_instance = 0;

Caret::Caret(MemoForm *memoForm) {
	this->memoFormLink = memoForm;

	CharacterFaces *characterFaces = CharacterFaces::Instance(this->memoFormLink->GetDC());
	CharacterSize characterSize = characterFaces->GetCharacterSize(97);

	this->width = CARETWIDTH;
	this->height = characterSize.GetHeight();
	//this->memoFormLink->CWnd::CreateSolidCaret(this->width, this->height);

	this->xPosition = 0 +15; //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@2
	this->yPosition = 20+7;
	//this->memoFormLink->CWnd::SetCaretPos(CPoint(xPosition, yPosition));

	//this->memoFormLink->CWnd::CreateSolidCaret(this->width, this->height);

	//	this->memoFormLink->CWnd::ShowCaret();
}

Caret::~Caret() {
	//	_instance = 0;
}

//Caret* Caret::Instance(MemoForm *memoForm) {
//	if (_instance == 0) {
//		_instance = new Caret(memoForm);
//	}
//
//	return _instance;
//}

//void SetCaretPosition(NoteBookForm *noteBookForm, Long xPosition, Long yPosition) {
////	noteBookForm->CreateSolidCaret(5, 50);
//
//	noteBookForm->SetCaretPos(*(noteBookForm->point));
//
//	//noteBookForm->ShowCaret();
//}

void Caret::Move(Long xPos, Long yPos) {
	this->xPosition = xPos + 15;
	this->yPosition = yPos + 7;  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	CWnd::SetCaretPos(CPoint(xPosition, yPosition));

}

void Caret::MoveFirstCharacter() {
	this->xPosition = 0 + 15; //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	CWnd::SetCaretPos(CPoint(this->xPosition, this->yPosition));
}

void Caret::MoveNextCharacter() {
	Memo *memo = static_cast<Memo*>(this->memoFormLink->GetContents());
	Line *line = memo->GetLine(memo->GetRow());
	Character *character = line->GetCharacter(line->GetColumn() - 1);
	Long moveWidth;

	moveWidth = character->GetWidth();

	this->xPosition += moveWidth;

	CWnd::SetCaretPos(CPoint(xPosition, yPosition));
}

void Caret::MovePreviousCharacter() {
	Memo *memo = static_cast<Memo*>(this->memoFormLink->GetContents());
	Line *line = memo->GetLine(memo->GetRow());
	Character *character = line->GetCharacter(line->GetColumn() - 1);
	Long moveWidth = character->GetWidth();

	this->xPosition -= moveWidth;

	CWnd::SetCaretPos(CPoint(xPosition, yPosition));
}

void Caret::MoveLastCharacter() {
	Memo *memo = static_cast<Memo*>(this->memoFormLink->GetContents());
	Line *line = memo->GetLine(memo->GetRow());

	Long moveWidth = 0 + 15;  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	Long i = 0;
	while (i < line->GetLength()) {
		moveWidth += line->GetCharacter(i)->GetWidth();
		i++;
	}
	this->xPosition = moveWidth;

	CWnd::SetCaretPos(CPoint(this->xPosition, this->yPosition));
}

void Caret::MoveFirstLine() {
	this->xPosition = 0 + 15; //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	this->yPosition = 20 + 7;

	CWnd::SetCaretPos(CPoint(this->xPosition, this->yPosition));
}

void Caret::MoveNextLine() {
	//	Memo *memo = this->noteBookFormLink->GetMemo();
	//	Line *line = memo->GetLine(memo->GetRow() - 1);
	//Character *character = line->GetCharacter(line->GetColumn() - 1);
	//Long moveHeight = character->GetHeight();

	//	this->yPosition += moveHeight;
	this->yPosition += this->height;
	this->xPosition = 0 + 15; //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//line = memo->GetLine(memo->GetRow());
	//Long moveWidth;
	//xPosition = 0;
	//Long i = 0;
	//while (i < line->GetColumn()) {
	//	character = line->GetCharacter(line->GetColumn());
	//	moveWidth = character->GetWidth();
	//	xPosition += moveWidth;
	//	i++;
	//}


	CWnd::SetCaretPos(CPoint(xPosition, yPosition));
}

void Caret::MovePreviousLine() {
	//	Memo *memo = this->noteBookFormLink->GetMemo();
	//	Line *line = memo->GetLine(memo->GetRow());

	//Character *character = line->GetCharacter(line->GetColumn() - 1);
	//Long moveHeight = character->GetHeight();

	//	yPosition -= moveHeight;
	this->xPosition = 0 + 15;  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	this->yPosition -= height;
	/*
	line = memo->GetLine(memo->GetRow() - 1);
	Long moveWidth;
	xPosition = 0;
	Long i = 0;
	while (i < line->GetColumn()) {
	character = line->GetCharacter(line->GetColumn());
	moveWidth = character->GetWidth();
	xPosition += moveWidth;
	i++;
	}
	*/
	CWnd::SetCaretPos(CPoint(xPosition, yPosition));
}

void Caret::MoveLastLine() {
	Memo *memo = static_cast<Memo*>(this->memoFormLink->GetContents());
	//0808에 캡션클릭시 캐럿이 마지막줄로 이동을 못하는 이슈로 인해서 추가함
	memo->SetRow(memo->GetLength() - 1);
	Line *line = memo->GetLine(memo->GetRow());

	this->xPosition = 0 + 15;  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	this->yPosition = this->height * memo->GetRow() + 20 + 7;

	CWnd::SetCaretPos(CPoint(this->xPosition, this->yPosition));
}

bool Caret::ChangeImeCaret() {
	DestroyCaret();

	//Memo *memo = noteBookFormLink->GetMemo();
	//Line *line = memo->GetLine(memo->GetRow());
	//Character *character = line->GetCharacter(line->GetColumn()-1);
	//
	//width = character->GetWidth();
	//height = character->GetHeight();

	CharacterFaces *characterFaces = CharacterFaces::Instance(this->memoFormLink->GetDC());
	//CharacterSize characterSize(characterFaces->GetCharacterSize(127));
	//width = characterSize.GetWidth();
	//height = characterSize.GetHeight();

	this->width = characterFaces->GetCharacterSize(127).GetWidth();
	this->height = characterFaces->GetCharacterSize(127).GetHeight();

	memoFormLink->CWnd::CreateSolidCaret(this->width, this->height);

	memoFormLink->CWnd::ShowCaret();

	return true;
}

bool Caret::ChangeCaret() {
	DestroyCaret();

	Memo *memo = static_cast<Memo*>(this->memoFormLink->GetContents());
	Line *line = memo->GetLine(memo->GetRow());
	Character *character = line->GetCharacter(line->GetColumn() - 1);

	width = CARETWIDTH;
	height = character->GetHeight();

	memoFormLink->CWnd::CreateSolidCaret(width, height);

	memoFormLink->CWnd::ShowCaret();

	return true;
}

void Caret::MoveNextTab() {
	CharacterFaces *characterFaces = CharacterFaces::Instance(memoFormLink->GetDC());

	Long tabWidth = characterFaces->GetCharacterSize(97).GetWidth() * 8;

	Long moveWidth = tabWidth - (xPosition%tabWidth);
	xPosition += moveWidth;

	CWnd::SetCaretPos(CPoint(xPosition, yPosition));
}

void Caret::MovePreviousTab() {
	CharacterFaces *characterFaces = CharacterFaces::Instance(memoFormLink->GetDC());

	Long tabWidth = characterFaces->GetCharacterSize(97).GetWidth() * 8;

	Long moveWidth = xPosition%tabWidth;
	xPosition -= moveWidth;

	CWnd::SetCaretPos(CPoint(xPosition, yPosition));
}

void Caret::ShowCaret() {
	this->memoFormLink->CWnd::CreateSolidCaret(this->width, this->height);
	this->memoFormLink->CWnd::SetCaretPos(CPoint(this->xPosition, this->yPosition));
	this->memoFormLink->CWnd::ShowCaret();
}

//void Caret::HideCaret() {
//	//this->memoFormLink->CWnd::HideCaret();
//	//DestroyCaret();
//}