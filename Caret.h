//#pragma once
////Caret.h
//
//#ifndef _CARET_H
//#define _CARET_H
//
////#include <afxwin.h>
////using namespace std;
//
//typedef signed long int Long;
//
//class MemoForm;
//class Caret {
//public:
//	~Caret();
////	static Caret* Instance(MemoForm *memoForm);
//	void Move(Long xPos, Long yPos);
//	void MoveNextCharacter();
//	void MovePreviousCharacter();
//	void MoveNextLine();
//	void MovePreviousLine();
//	bool ChangeCaret();
//	bool ChangeImeCaret();
//	void MoveNextTab();
//	void MovePreviousTab();
//	//static void SetCaretPosition(NoteBookForm *noteBookForm, Long xPosition, Long yPosition);
//	Long GetWidth() const;
//	Long GetHeight() const;
//	Long GetXPosition() const;
//	Long GetYPosition() const;
//	//
//	void ShowCaret();
//	//
////protected:
//	Caret(MemoForm *memoForm);
//	//Caret(const Caret& source);
//	//Caret& operator=(const Caret& source);
//
////public:
////	static Long width;
////	static Long height;
////	static Long xPosition;
////	static Long yPosition;
//
//private:
//	Long width;
//	Long height;
//	Long xPosition;
//	Long yPosition;
//	MemoForm *memoFormLink;
//
////	static Caret *_instance;
////	static NoteBookForm *noteBookFormLink;
//	
//};
//
//inline Long Caret::GetWidth() const {
//	return this->width;
//}
//
//inline Long Caret::GetHeight() const {
//	return this->height;
//}
//
//inline Long Caret::GetXPosition() const {
//	return this->xPosition;
//}
//
//inline Long Caret::GetYPosition() const {
//	return this->yPosition;
//}
//
//#endif	//_CARET_H

#pragma once
//Caret.h

#ifndef _CARET_H
#define _CARET_H

//#include <afxwin.h>
//using namespace std;

typedef signed long int Long;

class MemoForm;
class Caret {
public:
	~Caret();
	//	static Caret* Instance(MemoForm *memoForm);
	void Move(Long xPos, Long yPos);
	void MoveFirstCharacter();
	void MovePreviousCharacter();
	void MoveNextCharacter();
	void MoveLastCharacter();
	void MoveFirstLine();
	void MovePreviousLine();
	void MoveNextLine();
	void MoveLastLine();
	bool ChangeCaret();
	bool ChangeImeCaret();
	void MoveNextTab();
	void MovePreviousTab();
	//static void SetCaretPosition(NoteBookForm *noteBookForm, Long xPosition, Long yPosition);
	Long GetWidth() const;
	Long GetHeight() const;
	Long GetXPosition() const;
	Long GetYPosition() const;
	//
	void ShowCaret();
	//void HideCaret();
	//
	//protected:
	Caret(MemoForm *memoForm);
	Caret(const Caret& source);
	Caret& operator=(const Caret& source);

	//public:
	//	static Long width;
	//	static Long height;
	//	static Long xPosition;
	//	static Long yPosition;

private:
	Long width;
	Long height;
	Long xPosition;
	Long yPosition;
	MemoForm *memoFormLink;

	//	static Caret *_instance;
	//	static NoteBookForm *noteBookFormLink;

};

inline Long Caret::GetWidth() const {
	return this->width;
}

inline Long Caret::GetHeight() const {
	return this->height;
}

inline Long Caret::GetXPosition() const {
	return this->xPosition;
}

inline Long Caret::GetYPosition() const {
	return this->yPosition;
}

#endif	//_CARET_H