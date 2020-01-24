#pragma once
//PageForm.h

#ifndef _PAGEFORM_H
#define _PAGEFORM_H

#include "CompositeForm.h"
#include <afxwin.h>
#include <string>
using namespace std;
typedef signed long int Long;

class Visitor;
class Contents;
class MemoForm;
class Memo;
class PageForm :public CWnd, public CompositeForm {
public:
	PageForm(Contents *contents=0,Long capacity = 64, string pageFormName = "");
	virtual ~PageForm();
	PageForm(const PageForm& source);
	PageForm& operator=(const PageForm& source);
	//Long AddMemoForm(Memo *memo);
	//Long AddMemoForm(Memo *memo, CPoint point);
	Long AddMemoForm(Memo *memo, CRect rect);
	Long AddMemoForm(MemoForm *memoForm);
	Long RemoveMemoForm(Long index);
	MemoForm* GetMemoForm(Long index);
	MemoForm* operator[](Long index);
	string& GetPageFormName() const;
	void SetPageFormName(const string& pageFormName);
	virtual Form* Clone() const;
	virtual void Accept(Visitor* visitor);
	virtual ArrayIterator<Form*>* CreateIterator() const;
	afx_msg void OnClose();
	bool CleanUpMemoForms();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	//afx_msg void OnSelChanging();
	//afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	DECLARE_MESSAGE_MAP()

private:
	string pageFormName;
};

inline string& PageForm::GetPageFormName() const {
	return const_cast<string&>(this->pageFormName);
}

inline void PageForm::SetPageFormName(const string& pageFormName) {
	this->pageFormName = pageFormName;
}
#endif	//_MEMO_H