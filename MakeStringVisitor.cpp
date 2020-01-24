// MakeStringVisitor.cpp

#include "MakeStringVisitor.h"
#include "Memo.h"
#include "Line.h"
#include "SingleCharacter.h"
#include "DoubleCharacter.h"
#include "ArrayIterator.h"

MakeStringVisitor::MakeStringVisitor(){
	this->completeString = "";
}

MakeStringVisitor::MakeStringVisitor(const MakeStringVisitor& source){
	this->completeString = source.completeString;
}

MakeStringVisitor::~MakeStringVisitor(){

}

MakeStringVisitor& MakeStringVisitor::operator=(const MakeStringVisitor& source){
	this->completeString = source.completeString;
	
	return *this;
}

void MakeStringVisitor::Visit(Note *note) {

}

void MakeStringVisitor::Visit(Page *page) {
	/*ArrayIterator<Contents*> *memoIterator = memo->CreateIterator();

	memoIterator->First();
	while (!memoIterator->IsDone()) {
		MakeStringVisitor makeStringVisitor;
		static_cast<Line*>(memoIterator->CurrentItem())->Accept(&makeStringVisitor);

		this->completeString += makeStringVisitor.GetCompleteString();
		this->completeString += "\r\n";

		memoIterator->Next();
	}

	if (memoIterator != 0) {
		delete memoIterator;
		memoIterator = 0;
	}*/
}

void MakeStringVisitor::Visit(Memo *memo) {
	ArrayIterator<Contents*> *memoIterator = memo->CreateIterator();
	
	memoIterator->First();
	while (!memoIterator->IsDone()) {
		MakeStringVisitor makeStringVisitor;
		static_cast<Line*>(memoIterator->CurrentItem())->Accept(&makeStringVisitor);

		this->completeString += makeStringVisitor.GetCompleteString();
		this->completeString += "\r\n";

		memoIterator->Next();
	}

	if (memoIterator != 0) {
		delete memoIterator;
		memoIterator = 0;
	}
}

void MakeStringVisitor::Visit(Line *line) {
	ArrayIterator<Contents*> *lineIterator = line->CreateIterator();
	
	lineIterator->First();
	while (!lineIterator->IsDone()) {
		Character *characterLink = static_cast<Character*>(lineIterator->CurrentItem());
		if (dynamic_cast<SingleCharacter*>(characterLink)) {
			this->completeString += dynamic_cast<SingleCharacter*>(characterLink)->GetValue();
		}
		else if (dynamic_cast<DoubleCharacter*>(characterLink)) {
			this->completeString += dynamic_cast<DoubleCharacter*>(characterLink)->GetValue()[0];
			this->completeString += dynamic_cast<DoubleCharacter*>(characterLink)->GetValue()[1];
		}
		lineIterator->Next();
	}
	
	if (lineIterator != 0) {
		delete lineIterator;
		lineIterator = 0;
	}
}

void MakeStringVisitor::Visit(SingleCharacter *singleCharacter) {
}

void MakeStringVisitor::Visit(DoubleCharacter *doubleCharacter) {
}

void MakeStringVisitor::Visit(Character *character) {
	if (dynamic_cast<SingleCharacter*>(character)) {
		this->completeString += dynamic_cast<SingleCharacter*>(character)->GetValue();
	}
	else if (dynamic_cast<DoubleCharacter*>(character)) {
		this->completeString += dynamic_cast<DoubleCharacter*>(character)->GetValue()[0];
		this->completeString += dynamic_cast<DoubleCharacter*>(character)->GetValue()[1];
	}
}
