#pragma once
//MemoForm.h

#ifndef _MEMOFORM_H
#define _MEMOFROM_H

#include "Form.h"
#include "HighLight.h"
#include "Array.h"
//#include "ArrayIterator.h"
#include "resource1.h"
#include <afxwin.h>
#include <afxcmn.h>

class Contents;
class Visitor;
class Caret;
class SelectedBuffer;
class MemoForm : public CWnd, public Form {
public :
	MemoForm(Contents *contents = 0, Long positionX = 0, Long positionY = 0, Long width = 300, Long height = 200, Long highLightCapacity = 100);
	~MemoForm();
	MemoForm(const MemoForm& source);
	MemoForm& operator = (const MemoForm& source);
	
	virtual Form* Clone() const;
	virtual void Accept(Visitor* visitor);

	bool GetEndComposition() const;
	Long GetPositionX() const;
	Long GetPositionY() const;
	void SetPositionX(Long positionX);
	void SetPositionY(Long positionY);
	Caret* GetCaret() const;
	void SetIsCaption(bool isCaption);
	bool GetIsCaption() const;
	void SetSelectedBuffer(SelectedBuffer* selectedBuffer);
	SelectedBuffer* GetSelectedBuffer() const;
	void CalculatePosition(Long *xPos, Long *yPos);
	void ReSizeWindow();
	Long GetMaxWidth() const;
	Long GetMaxHeight() const;
	void SetMaxWidth(Long width);
	void SetMaxHeight(Long height);
	Long UpdateMaxWidth();
	Long UpdateMaxHeight();
	void PaintHighLights(CPaintDC &dc);
	void Accept(MemoForm *memoForm);
	afx_msg void OnClose();

protected :
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnImeComposition(WPARAM wParam, LPARAM lParam);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg int OnMouseActivate(CWnd *pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnMove(int x,int y);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetHighLight();
	afx_msg void OnHighLight();
	afx_msg void OnUnHighLight();
	//afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
private :
	Caret *caret;
	bool endComposition;
	Long positionX;
	Long positionY;
	bool isCaption;
	Long maxWidth;
	Long maxHeight;
	SelectedBuffer *selectedBuffer;
	Long highLightCapacity;
	Long highLightLength;
	Array<HighLight*> highLights;
	Long state;
};

inline bool MemoForm::GetEndComposition() const {
	return this->endComposition;
}

inline Long MemoForm::GetPositionX() const {
	return this->positionX;
}

inline Long MemoForm::GetPositionY() const {
	return this->positionY;
}

inline Caret* MemoForm::GetCaret() const {
	return const_cast<Caret*>(this->caret);
}

inline bool MemoForm::GetIsCaption() const {
	return this->isCaption;
}

inline SelectedBuffer* MemoForm::GetSelectedBuffer() const {
	return const_cast<SelectedBuffer*>(this->selectedBuffer);
}

inline Long MemoForm::GetMaxWidth() const {
	return this->maxWidth;
}
inline Long MemoForm::GetMaxHeight() const {
	return this->maxHeight;
}

#endif	//_MEMOFORM_H