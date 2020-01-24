#pragma once
//TabCtrl.h

#ifndef _TABCTRL_H
#define _TABCTRL_H

#include <afxwin.h>
#include <afxcmn.h>
#include <Windows.h>
#include "resource1.h"
typedef signed long int Long;

class TabCtrl :public CTabCtrl {
public:
	TabCtrl();
	~TabCtrl();
	TabCtrl(const TabCtrl& source);
	TabCtrl& operator=(const TabCtrl& source);
	//Long InsertItem(int nItem, LPCTSTR lpszItem);
	//Long InsertItem(int nItem);
	Long InsertItem(int nItem, CString name);
	
protected:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);
	afx_msg void OnCopyPageForm();
	afx_msg void OnDeletePageForm();
	DECLARE_MESSAGE_MAP()
};

#endif	//_TABCTRL_H