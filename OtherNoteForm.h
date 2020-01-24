//OtherNoteForm.h

#ifndef _OTHERNOTEFORM_H
#define _OTHERNOTEFORM_H

#include "CompositeForm.h"
#include "TabCtrl.h"
#include "resource1.h"
#include <afxwin.h>
//using namespace std;

//class HorizontalScroll;
//class VerticalScroll;
class Form;
class PageForm;
class Visitor;
class CTabCtrl;
class Page;
class OtherNoteForm :public CFrameWnd, public CompositeForm{
public:
	OtherNoteForm(Contents *contents = 0, Long capacity = 64);
	~OtherNoteForm();
	OtherNoteForm(const OtherNoteForm& source);
	OtherNoteForm& operator=(const OtherNoteForm& source);

	//Long AddPageForm(Page *page);
	Long AddPageForm(Page *page, CString pageFormName = "");
	Long AddPageForm(PageForm *pageForm);
	Long RemovePageForm(Long index);
	PageForm* GetPageForm(Long index);
	PageForm* operator[](Long index);

	virtual Form* Clone() const;
	virtual ArrayIterator<Form*>* CreateIterator() const;
	virtual void Accept(Visitor *visitor);

	//void Detach(Contents *contents);
	//void DisplayMemoForm(Long index);
	void SelectTabItem(Long index);

	TabCtrl* GetTabCtrl() const;

	void Load();
	void Save();
	//HorizontalScroll* GetHorizontalScroll() const;
	//VerticalScroll* GetVerticalScroll() const;
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnPaint();
	//afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//afx_msg LRESULT OnImeComposition(WPARAM wParam, LPARAM lParam);
	//afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMenuExit();
	afx_msg void OnMenuOpen();
	afx_msg void OnMenuSave();
	DECLARE_MESSAGE_MAP()
private:
	TabCtrl *tabCtrl;
	CMenu menu;
};

inline TabCtrl* OtherNoteForm::GetTabCtrl() const {
	return const_cast<TabCtrl*>(this->tabCtrl);
}

//inline HorizontalScroll* OtherNoteForm::GetHorizontalScroll() const {
//	return const_cast<HorizontalScroll*>(this->horizontalScroll);
//}
//
//inline VerticalScroll* OtherNoteForm::GetVerticalScroll() const {
//	return const_cast<VerticalScroll*>(this->verticalScroll);
//}

#endif	//_OTHERNOTEFORM_H