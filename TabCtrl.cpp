//TabCtrl.cpp

#include "TabCtrl.h"
#include "OtherNoteForm.h"

BEGIN_MESSAGE_MAP(TabCtrl, CTabCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_PAINT()
	//ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_POPUP_DELETE, OnDeletePageForm)
	ON_COMMAND(ID_POPUP_COPY, OnCopyPageForm)
END_MESSAGE_MAP()

TabCtrl::TabCtrl()
	:CTabCtrl() {
}

TabCtrl::~TabCtrl() {

}

TabCtrl::TabCtrl(const TabCtrl& source)
{

}

TabCtrl& TabCtrl::operator=(const TabCtrl& source) {
	return *this;
}

Long TabCtrl::InsertItem(int nItem, CString name) {
	/*TCITEM item;
	item.mask = TCIF_TEXT;
	
	CString pageName("Page");
	CString pageNumber;
	pageNumber.Format("%d", nItem);
	pageName += pageNumber;*/

	//item.pszText = pageName;
	//pageForm->InsertItem(0, &item);
	//pageForm->InsertItem(1, &item);
	//this->InsertItem(nItem, lpszItem);
	
	//this->InsertItem(nItem, pageName);
	//this->CTabCtrl::InsertItem(nItem, pageName);
	this->CTabCtrl::InsertItem(nItem, name);
	
	return 0;
}

#include "Note.h"
#include "PageForm.h"
void TabCtrl::OnLButtonDown(UINT nFlags, CPoint point) {
	/*CWnd *cWnd = this->FindWindow(NULL, "OtherNote");
	OtherNoteForm *otherNoteForm = static_cast<OtherNoteForm*>(cWnd);
	otherNoteForm->DisplayMemoForm();
	otherNoteForm->RedrawWindow();*/
	
	CTabCtrl::OnLButtonDown(nFlags, point);
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	//1. 현재 페이지를 hide한다.
	PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	pageForm->CleanUpMemoForms();
	pageForm->ShowWindow(SW_HIDE);
	//2. 현재 클릭된 tab 위치를 구한다.
	Long index = this->GetCurSel();
	//3. 선택된 tab으로 변경한다.
	otherNoteForm->SelectTabItem(index);
}

void TabCtrl::OnRButtonDown(UINT nFlags, CPoint point) {
	//Set tabItem of Selected position
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	TC_HITTESTINFO tcHitTestInfo;
	POINT sPoint;
	sPoint.x = point.x;
	sPoint.y = point.y;
	tcHitTestInfo.pt = sPoint;
	tcHitTestInfo.flags = nFlags;
	Long index = this->HitTest(&tcHitTestInfo);
	otherNoteForm->SelectTabItem(index);
	this->SetCurSel(index);

	//Pop-up menu
	CMenu menu;
	menu.LoadMenu(IDR_MENU_POPUP);
	CMenu *popupMenu = menu.GetSubMenu(0);
	CPoint position;
	GetCursorPos(&position);
	popupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, position.x, position.y, this);
	menu.DestroyMenu();
	CTabCtrl::OnRButtonDown(nFlags, point);
}

void TabCtrl::OnPaint() {
	CTabCtrl::OnPaint();
	//CWindowDC parentDC(this->GetParent());
	//Long captionHeight = GetSystemMetrics(SM_CYCAPTION);
	//Long menuHeight = GetSystemMetrics(SM_CYMENU);

	//CPen newParentBGPen(PS_SOLID, 5, RGB(255, 0, 0));
	////CPen newPen(PS_SOLID, 1, RGB(0, 120, 215));
	//CPen *pOldPen = parentDC.SelectObject(&newParentBGPen);

	//CRect wndRect;
	//this->GetWindowRect(wndRect);

	///*dc.MoveTo(0, captionHeight + menuHeight + 12);
	//dc.LineTo(wndRect.right, captionHeight + menuHeight + 12);*/
	//parentDC.SelectObject(newParentBGPen);

	//parentDC.MoveTo(0, captionHeight + menuHeight + 11);
	//parentDC.LineTo(wndRect.right, captionHeight + menuHeight + 11);
	//parentDC.SelectObject(pOldPen);

	//CWindowDC dc(this);
	//CPen newBGPen(PS_SOLID, 5, RGB(255, 255, 255));
	////CPen newBGPen(PS_SOLID, 5, RGB(192, 0, 0));
	////CPen newPen(PS_SOLID, 1, RGB(0, 120, 215));
	////CPen *pOldPen = dc.SelectObject(&newBGPen);
	//pOldPen = dc.SelectObject(&newBGPen);

	////CRect wndRect;
	////this->GetWindowRect(wndRect);

	///*dc.MoveTo(0, captionHeight + menuHeight + 12);
	//dc.LineTo(wndRect.right, captionHeight + menuHeight + 12);*/
	//dc.SelectObject(newBGPen);

	//dc.MoveTo(0, 0);
	//dc.LineTo(wndRect.right, 0);
	//dc.SelectObject(pOldPen);

	//CPen newBlackPen(PS_SOLID, 2, RGB(0, 120, 215));
	//dc.SelectObject(newBlackPen);
	//dc.MoveTo(0, 2);
	//dc.LineTo(wndRect.right, 2);

	//dc.SelectObject(pOldPen);
}

void TabCtrl::OnDeletePageForm() {
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	//1. 현재 페이지를 삭제한다.
	PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	pageForm->OnClose();
	//2. 현재 클릭된 tab 위치를 구한다.
	Long index = this->GetCurSel();
	//3. 현재 tabitem을 제거한다.
	this->DeleteItem(index);
	//4. tab item의 개수를 구한다.
	Long count = this->GetItemCount();
	//5. 마지막tab으로 설정한다.
	this->SetCurSel(count - 1);
	if (count >= 1) {
		otherNoteForm->SelectTabItem(count - 1);
	}
	else {
		/*PageForm *pageForm = this->GetPageForm(static_cast<Note*>(this->contents)->GetCurrent());
		pageForm->ShowWindow(SW_HIDE);*/
		Long index = static_cast<Note*>(otherNoteForm->GetContents())->AddPage();
		Page *page = static_cast<Note*>(otherNoteForm->GetContents())->GetPage(index);
		index = otherNoteForm->AddPageForm(page);
		pageForm = otherNoteForm->GetPageForm(index);
		pageForm->ShowWindow(SW_SHOW);
		otherNoteForm->GetTabCtrl()->SetCurSel(index);
		pageForm->SetFocus();
	}
}

#include "CopyVisitor.h"
#include "MemoForm.h"
#include "Page.h"
void TabCtrl::OnCopyPageForm() {
	//1. 클릭했던 tab에서 page를 알아온다.
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	PageForm *oldPageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	oldPageForm->ShowWindow(SW_HIDE);

	//2. AddPageForm(pageForm)
	Page *newPage = new Page(*static_cast<Page*>(oldPageForm->GetContents()));
	static_cast<Note*>(otherNoteForm->GetContents())->AddPage();

	CString pageFormName;
	pageFormName = oldPageForm->GetPageFormName().c_str();

	PageForm *newPageForm = new PageForm(newPage, 64, (LPCTSTR)pageFormName);
	Long index = otherNoteForm->AddPageForm(newPageForm);

	//3. create memoform
	Long i = 0;
	while (i < newPage->GetLength()) {
		MemoForm *newMemoForm = new MemoForm(*oldPageForm->GetMemoForm(i));
		newMemoForm->SetContents(newPage->GetMemo(i));
		newPageForm->AddMemoForm(newMemoForm);
		i++;
	}

	//4. pageForm을 Show해준다.
	newPageForm->ShowWindow(SW_SHOW);

	//5. 복사된 tab으로 변경한다.
	this->SetCurSel(index);
	otherNoteForm->SelectTabItem(index);
	newPageForm->SetFocus();

	newPageForm->GetMemoForm(static_cast<Page*>(newPageForm->GetContents())->GetCurrent())->HideCaret();
}