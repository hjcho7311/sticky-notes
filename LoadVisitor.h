// LoadVisitor.h

#ifndef _LOADVISITOR_H
#define _LOADVISITOR_H

#include "Visitor.h"
#include <fstream>
using namespace std;

class LoadVisitor : public Visitor {
public:
	LoadVisitor();
	LoadVisitor(const LoadVisitor& source);
	~LoadVisitor();
	LoadVisitor& operator=(const LoadVisitor& source);
	
	virtual void Visit(Note *note);
	virtual void Visit(Page *page);
	virtual void Visit(Memo *memo);
	virtual void Visit(Line *line);
	virtual void Visit(Character *character);
	virtual void Visit(SingleCharacter *singleCharacter);
	virtual void Visit(DoubleCharacter *doubleCharaceter);

	virtual void Visit(OtherNoteForm *otherNoteForm);
	virtual void Visit(PageForm *pageForm);
	virtual void Visit(MemoForm *memoForm);

	fstream& Getfstream() const; // 6.19 üũ �ʿ�
private:
	fstream fs;
	//bool isEof;
	//bool isBad;
};

inline fstream& LoadVisitor::Getfstream() const {
	return const_cast<fstream&>(this->fs);
}

#endif //_LOADVISITOR_H