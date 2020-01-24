// LoadVisitor.cpp

#include "LoadVisitor.h"
#include "CharacterFaces.h"
#include "Note.h"
#include "Page.h"
#include "Memo.h"
#include "Line.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "MemoForm.h"
#include <afxwin.h>
#include <string>
#include <stdlib.h>
//#define BUFFERSIZE 256
#define BUFFERSIZE 2048
using namespace std;

typedef signed long int Long;


LoadVisitor::LoadVisitor()
	:fs("OtherNote.txt", ios::in) {
	//this->isEof = false;
	//this->isBad = false;
	//if(!(this->fs.bad())){
	//	this->isBad = true;
	//}
}

LoadVisitor::LoadVisitor(const LoadVisitor& source)
	:fs("OtherNote.txt", ios::in) {
}

LoadVisitor::~LoadVisitor() {
	this->fs.close();
}

LoadVisitor& LoadVisitor::operator=(const LoadVisitor& source) {
	return *this;
}

void LoadVisitor::Visit(Note *note) {
	/*char buffer[BUFFERSIZE];
	
	this->fs.getline(buffer, sizeof(buffer));
	Long count = stoi(buffer);

	Long i = 0;
	while (i < count) {
		Page *page = note->GetPage(i);
		page->Accept(this);
		note->AddPage();
		i++;
	}*/
}

void LoadVisitor::Visit(Page *page) {
	//char buffer[BUFFERSIZE];

	//if (!this->fs.fail()) {

	//	//1. Iterate line(s)
	//	this->fs.getline(buffer, sizeof(buffer));
	//	Long count = stoi(buffer);

	//	Long i = 0;
	//	while (i < count) {
	//		Memo *memo = page->GetMemo(i);
	//		memo->Accept(this);
	//		page->AddMemo();
	//		i++;
	//	}
	//	//memo->RemoveLine();
	//}
}

void LoadVisitor::Visit(Memo *memo) {
//	char buffer[BUFFERSIZE];
//
//	if (!this->fs.fail()) {
//
//		CharacterFaces *characterFaces = CharacterFaces::Instance(0);
//		characterFaces->SetFontFamily(static_cast<string>(buffer));
//
//		this->fs.getline(buffer, sizeof(buffer));
//		
//		Long fontSize = atoi(buffer);
//		characterFaces->SetFontSize(fontSize);
//		
//		Long j;
//		Long i = 0;
////		this->fs.getline(buffer, sizeof(buffer));
//		while (!this->fs.eof()) {
//			Line *line = memo->GetLine(i);
//			line->Accept(this);
//			j = memo->AddLine();
//			i++;
//		}
//		//memo->RemoveLine(j); //06/19
//		memo->RemoveLine();
//	}
	char buffer[BUFFERSIZE];

	if (!this->fs.fail()) {

		//1. get number of line(s)
		this->fs.getline(buffer, sizeof(buffer));
		Long count = stoi(buffer);

		//2. Iterate line(s)
		Long i = 0;
		while (i < count) {
			/*Line *line = memo->GetLine(i);
			line->Accept(this);
			memo->AddLine();*/
			Long index = memo->AddLine();
			Line *line = memo->GetLine(index);
			line->Accept(this);
			i++;
		}
		//memo->RemoveLine();
	}
}

void LoadVisitor::Visit(Line *line) {

	char buffer[BUFFERSIZE];

	this->fs.getline(buffer, sizeof(buffer));

//	if(!this->fs.eof()) {
		Long length = CString(buffer).GetLength();
	
		char doubleCharacter[2];

		Long i = 0;
		//while(i < length-1) {
		while (i < length) {
			if(buffer[i] >= 0 && buffer[i] < 130){
			//if (buffer[i] >= 'NUL' && buffer[i] < 'DEL') {
				line->Write(buffer[i]);
			}
			else {
				doubleCharacter[0] = buffer[i];
				doubleCharacter[1] = buffer[i+1];
				i++;
				line->Write(doubleCharacter);
			}
			i++;
		}

//		this->fs.getline(buffer, sizeof(buffer));

//	}
	//else {
	//	this->isEof = true;
	//}
}

void LoadVisitor::Visit(Character *character) {

}

void LoadVisitor::Visit(SingleCharacter *singleCharacter) {

}

void LoadVisitor::Visit(DoubleCharacter *doubleCharacter) {

}

#include <afxwin.h>
void LoadVisitor::Visit(OtherNoteForm *otherNoteForm) {
	char buffer[BUFFERSIZE];

	if (!this->fs.fail()) {
		//1. Set fontFamily
		//CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		CPaintDC dc(otherNoteForm);
		CharacterFaces *characterFaces = CharacterFaces::Instance(&dc);

		this->fs.getline(buffer, sizeof(buffer));
		characterFaces->SetFontFamily(static_cast<string>(buffer));

		//2. Set fontSize
		this->fs.getline(buffer, sizeof(buffer));
		Long fontSize = stoi(buffer);
		characterFaces->SetFontSize(fontSize);

		//3. iterate  
		this->fs.getline(buffer, sizeof(buffer));
		Long pageCount = stoi(buffer);
		Long i = 0;
		while (i < pageCount) {
			//3.1. get pageFormName
			this->fs.getline(buffer, sizeof(buffer));
			
			//3.2 add Page & add PageForm
			Long index = static_cast<Note*>(otherNoteForm->GetContents())->AddPage();
			Long pageIndex = otherNoteForm->AddPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetPage(index), buffer);

			//3.3. set PageFormName
			otherNoteForm->GetPageForm(index)->SetPageFormName(buffer);

			
			//3.4. load pageForm
			otherNoteForm->GetPageForm(pageIndex)->Accept(this);

			i++;
		}
	}
}

void LoadVisitor::Visit(PageForm *pageForm) {
	char buffer[BUFFERSIZE];

	if (!this->fs.fail()) {
		//1. set pageFormName
		/*this->fs.getline(buffer, sizeof(buffer));
		pageForm->SetPageFormName(buffer);*/

		//2. get number of memo(s)
		this->fs.getline(buffer, sizeof(buffer));
		Long memoCount = stoi(buffer);

		//3. 
		Long i = 0;
		while (i < memoCount) {
			CPoint point;
			//1. Get positionX
			this->fs.getline(buffer, sizeof(buffer));
			point.x = stoi(buffer);
			
			//2. Get positionY
			this->fs.getline(buffer, sizeof(buffer));
			point.y = stoi(buffer);

			//3. Get width
			this->fs.getline(buffer, sizeof(buffer));
			Long width = stoi(buffer);

			//4. Get height
			this->fs.getline(buffer, sizeof(buffer));
			Long height = stoi(buffer);

			//5.1. add memo
			Long index = static_cast<Page*>(pageForm->GetContents())->AddMemo();
			CRect rect;
			rect.left = point.x;
			rect.top = point.y;
			rect.right = rect.left + width;
			rect.bottom = rect.top + height;
			//Long memoIndex = pageForm->AddMemoForm(static_cast<Page*>(pageForm->GetContents())->GetMemo(index), point);
			Long memoIndex = pageForm->AddMemoForm(static_cast<Page*>(pageForm->GetContents())->GetMemo(index), rect);

			pageForm->GetMemoForm(memoIndex)->Accept(this);
			i++;
		}

		//3. load page
		//pageForm->GetContents()->Accept(this);
	}
}

void LoadVisitor::Visit(MemoForm *memoForm) {
	//char buffer[BUFFERSIZE];

	if (!this->fs.fail()) {
		
		////1. Get positionX
		//this->fs.getline(buffer, sizeof(buffer));
		//Long positionX = stoi(buffer);
		//memoForm->SetPositionX(positionX);

		////2. Get positionY
		//this->fs.getline(buffer, sizeof(buffer));
		//Long positionY = stoi(buffer);
		//memoForm->SetPositionY(positionY);

		/*CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		characterFaces->SetFontFamily(static_cast<string>(buffer));*/

		//3. load memo
		memoForm->GetContents()->Accept(this);

		//3. Get count(s)
		/*this->fs.getline(buffer, sizeof(buffer));
		Long count = stoi(buffer);*/

		//4. Iterate line(s)
		//Memo *memo = static_cast<Memo*>(memoForm->GetContents());
		//memo->Accept(this);
		
		//Long i = 0;
		//while (i < count) {
		//	//4.1. get line from file
		//	this->fs.getline(buffer, sizeof(buffer));
		//	//4.2. add line
		//	Long index = memo->AddLine();
		//	Line *line = memo->GetLine(index);
		//	//4.3. 
		//	line->Accept(this);
		//	memo->AddLine();
		//	i++;
		//}
		//memo->RemoveLine();
	}
}