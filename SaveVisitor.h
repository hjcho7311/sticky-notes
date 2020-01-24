// SaveVisitor.h

#ifndef _SAVEVISITOR_H
#define _SAVEVISITOR_H

#include "Visitor.h"
#include <fstream>
using namespace std;

class SaveVisitor : public Visitor {
public:
	SaveVisitor();
	SaveVisitor(const SaveVisitor& source);
	virtual ~SaveVisitor();
	SaveVisitor& operator=(const SaveVisitor& source);

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
};

// 6.19 üũ �ʿ�
inline fstream& SaveVisitor::Getfstream() const {
	return const_cast<fstream&>(this->fs);
}

#endif //_SAVEVISITOR_H