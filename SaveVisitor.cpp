// SaveVisitor.cpp
#include "SaveVisitor.h"
#include "MakeStringVisitor.h"
#include "CharacterFaces.h"
#include "Note.h"
#include "Page.h"
#include "Memo.h"
#include "Line.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "MemoForm.h"

SaveVisitor::SaveVisitor()
	:fs("OtherNote.txt", ios::out | ios::trunc) {
}

SaveVisitor::SaveVisitor(const SaveVisitor& source)
	:fs("OtherNote.txt", ios::out | ios::trunc) {
}

SaveVisitor::~SaveVisitor(){
	this->fs.close();
}

SaveVisitor& SaveVisitor::operator=(const SaveVisitor& source) {
	return *this;
}

void SaveVisitor::Visit(Note *note) {
	Long i = 0;
	while (i < note->GetLength()) {
		Page *page = note->GetPage(i);
		page->Accept(this);
		this->fs << "\n";
		i++;
	}
}

void SaveVisitor::Visit(Page *page) {
	Long i = 0;
	while (i < page->GetLength()) {
		Memo *memo = page->GetMemo(i);
		memo->Accept(this);
		this->fs << "\n";
		i++;
	}
}

void SaveVisitor::Visit(Memo *memo) {
	/*CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	this->fs << characterFaces->GetFontFamily().c_str() << "\r\n";
	this->fs<<characterFaces->GetFontSize()<<"\r\n";*/

	Long i = 0;
	while (i < memo->GetLength()) {
		Line *line = memo->GetLine(i);
		line->Accept(this);
		this->fs<<"\n";
		i++;
	}
}

void SaveVisitor::Visit(Line *line) {
	MakeStringVisitor makeStringVisitor;
	line->Accept(&makeStringVisitor);	
	this->fs<<makeStringVisitor.GetCompleteString().c_str();
}

void SaveVisitor::Visit(Character *character) {

}

void SaveVisitor::Visit(SingleCharacter *singleCharacter) {
}

void SaveVisitor::Visit(DoubleCharacter *doubleCharacter) {
}

void SaveVisitor::Visit(OtherNoteForm *otherNoteForm) {
	//1. Write File name
	//To do 

	//2. Write font family
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	this->fs << characterFaces->GetFontFamily().c_str() << "\n";
	
	//3. Write font size
	this->fs << characterFaces->GetFontSize() << "\n";

	//4. Write count of page(s)
	this->fs << static_cast<Note*>(otherNoteForm->GetContents())->GetLength() << "\n";

	//5. Iterate pageForm(s)
	//otherNoteForm->GetContents()->Accept(this);
	Long i = 0;
	//while (i < 2) {
	while (i < otherNoteForm->GetLength()) {
	//while (i < static_cast<Note*>(otherNoteForm->GetContents())->GetLength()) {
		PageForm *pageForm = otherNoteForm->GetPageForm(i);
		pageForm->Accept(this);
		//this->fs << "\r\n";
		i++;
	}
}

void SaveVisitor::Visit(PageForm *pageForm) {
	//1. Write Page name
	this->fs << pageForm->GetPageFormName() << "\n";

	//2. Write count of Memo(s)
	this->fs << static_cast<Page*>(pageForm->GetContents())->GetLength() << "\n";

	//3. Iterate memoForm(s)
	//pageForm->GetContents()->Accept(this);
	Long i = 0;
	while (i < pageForm->GetLength()) {
		MemoForm *memoForm = pageForm->GetMemoForm(i);
		memoForm->Accept(this);
		//this->fs << "\r\n";
		i++;
	}
}

void SaveVisitor::Visit(MemoForm *memoForm) {
	//1. Write Position of MemoForm
	this->fs << memoForm->GetPositionX() << "\n";
	this->fs << memoForm->GetPositionY() << "\n";

	//2. Write width, height of MemoForm
	this->fs << memoForm->GetMaxWidth() << "\n";
	this->fs << memoForm->GetMaxHeight() << "\n";

	//2. Write count of Line(s)
	this->fs << static_cast<Memo*>(memoForm->GetContents())->GetLength() << "\n";

	//3. Iterate line(s)
	//memoForm->GetContents()->Accept(this);
	Long i = 0;
	while (i < static_cast<Memo*>(memoForm->GetContents())->GetLength()) {
		Line *line = static_cast<Memo*>(memoForm->GetContents())->GetLine(i);
		line->Accept(this);
		this->fs << "\n";
		i++;
	}
}