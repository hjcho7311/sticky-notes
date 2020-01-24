//OtherNoteForm.cpp

#include "OtherNoteForm.h"
#include "CompositeForm.h"
#include "PageForm.h"
#include "MemoForm.h"
#include "Note.h"
#include "Page.h"
#include "Memo.h"
#include "Line.h"
#include "SingleCharacter.h"
#include "DoubleCharacter.h"
#include "CharacterFaces.h"
#include "Visitor.h"
#include "MakeStringVisitor.h"
//#include "HorizontalScroll.h"
//#include "VerticalScroll.h"
//#include "Caret.h"
//#include "HScrollActionCreator.h"
//#include "VScrollActionCreator.h"
//#include "ScrollAction.h"
#include <afxcmn.h>
#include <WinUser.h>
#include <fstream>
using namespace std;

BEGIN_MESSAGE_MAP(OtherNoteForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	//ON_WM_CHAR()
	//ON_MESSAGE(WM_IME_COMPOSITION, OnImeComposition)
	//ON_WM_KEYDOWN()
	//ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	//ON_WM_HSCROLL()
	//ON_WM_VSCROLL()
	//ON_WM_SETFOCUS()
	ON_COMMAND(ID_MENU_EXIT, &OtherNoteForm::OnMenuExit)
	ON_COMMAND(ID_MENU_LOAD, &OtherNoteForm::OnMenuOpen)
	ON_COMMAND(ID_MENU_SAVE, &OtherNoteForm::OnMenuSave)
END_MESSAGE_MAP()

//void OtherNoteForm::OnLButtonDown(UINT nFlags, CPoint point) {
//	//Mouse mouse(this);
//	//mouse.OnLButtonDown(nFlags, point);
//
//	//
//	PageForm *pageForm=static_cast<PageForm*>(this->GetAt(0));
//	Long current = pageForm->AddMemoForm();
//	MemoForm *memoForm = pageForm->GetMemoForm(current);
//
//	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)GetStockObject(HOLLOW_BRUSH), NULL);
//	memoForm->CreateEx(0, strMyClass, _T("Memo"), WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE, CRect(point.x, point.y, 500, 500), this, 0, NULL);
//	//Long index = CompositeForm::Add(memoForm);
//	memoForm->SetFocus();
//	//
//}

OtherNoteForm::OtherNoteForm(Contents *contents, Long capacity) 
	:CompositeForm(contents, capacity) {
	//this->contents = contents;//new Note;
	this->tabCtrl = new TabCtrl;
}

OtherNoteForm::~OtherNoteForm() 
{
	/*Long i = 0;
	while (i < this->length) {
		if (this->forms.GetAt(i) != 0) {
			delete this->forms.GetAt(i);
		}
		i++;
	}*/
	if (this->contents != 0) {
		delete this->contents;
	}

	if (this->tabCtrl != 0) {
		delete this->tabCtrl;
	}
}

OtherNoteForm::OtherNoteForm(const OtherNoteForm& source) 
	:CompositeForm(source){
	this->tabCtrl = new TabCtrl(*source.tabCtrl);
}

OtherNoteForm& OtherNoteForm::operator=(const OtherNoteForm& source) {
	CompositeForm::operator=(source);
	if (source.tabCtrl != 0) {
		delete source.tabCtrl;
	}
	this->tabCtrl = new TabCtrl(*source.tabCtrl);
	return *this;
}

/*
1. page만들어서 AddPageForm을 호출한다.
1.1. pageForm에 page를 끼워준다.
1.2. tabCtrl에 InsertItem을 해준다.
*/
Long OtherNoteForm::AddPageForm(Page *page, CString pageFormName) {	
	//1. make pageFormName
	if (pageFormName.Compare(CString("")) == 0) {
		CString page("Page");
		pageFormName += page;
		CString pageFormNumber;
		/*this->tabCtrl->InsertItem(this->GetLength());
		this->tabCtrl->InsertItem(this->GetLength());
		int count = this->tabCtrl->GetItemCount();*/
		pageFormNumber.Format("%d", this->GetLength());
		pageFormName += pageFormNumber;
	}	
	
	//2. add pageForm
	Long index = this->CompositeForm::Add(new PageForm(page, 64, (LPCTSTR)pageFormName));	
	PageForm *pageForm = static_cast<PageForm*>(this->CompositeForm::GetAt(index));

	/*CString pageName("Page");
	CString pageNumber;
	pageNumber.Format("%d", this->GetLength() - 1);
	pageName += pageNumber;*/

	//3. insert tab
	//this->tabCtrl->InsertItem(this->GetLength() - 1, pageName);
	this->tabCtrl->InsertItem(this->GetLength(), pageFormName);
	CRect tabRect;
	this->tabCtrl->GetClientRect(&tabRect);
	CRect tabItemRect;
	this->tabCtrl->GetItemRect(0, &tabItemRect);

	CRect noteFormClientRect;
	this->GetClientRect(noteFormClientRect);

	//4. Create pageForm
	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH), NULL);
	//pageForm->CreateEx(0, strMyClass, "Page", WS_BORDER | WS_CHILD | WS_VISIBLE, CRect(noteFormClientRect.left, noteFormClientRect.top + 27, noteFormClientRect.right, noteFormClientRect.bottom), this, 0, NULL);
	pageForm->CreateEx(0, strMyClass, "Page", WS_BORDER | WS_CHILD | WS_VISIBLE, CRect(noteFormClientRect.left, tabItemRect.bottom, noteFormClientRect.right, noteFormClientRect.bottom), this, 0, NULL);
	pageForm->ShowWindow(SW_HIDE);
	//	forms.Store(this->length, new PageForm(page));
	//	this->length++;

	//	CTabCtrl *tab = new CTabCtrl;
	//	CRect rect(10,10,800,800);
	//this->GetClientRect(&rect);

	//	pageForm->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | TCS_TABS, rect, this, 0);
	//	tab->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | TCS_TABS, rect, this, 0);

	//TCITEM item;
	//item.mask = TCIF_TEXT;
	//item.pszText = _T("page1");
	//pageForm->InsertItem(0, &item);
	//pageForm->InsertItem(1, &item);
	//	this->tabCtrl->InsertItem(pageForm->GetLength(), "1");

	//	tab->InsertItem(TVIF_TEXT, &item);

	return index;
}

Long OtherNoteForm::AddPageForm(PageForm *pageForm) {
	//1. make pageFormName
	CString pageFormName;
	pageFormName = pageForm->GetPageFormName().c_str();
	pageFormName += "Copy";
	pageForm->SetPageFormName((LPCTSTR)pageFormName);

	//2. add pageForm
	Long index = this->CompositeForm::Add(pageForm);
	
	//3. insert tab
	this->tabCtrl->InsertItem(this->GetLength(), pageFormName);
	CRect tabRect;
	this->tabCtrl->GetClientRect(&tabRect);
	CRect tabItemRect;
	this->tabCtrl->GetItemRect(0, &tabItemRect);

	CRect noteFormClientRect;
	this->GetClientRect(noteFormClientRect);

	//4. Create pageForm
	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH), NULL);
	pageForm->CreateEx(0, strMyClass, "Page", WS_BORDER | WS_CHILD | WS_VISIBLE, CRect(noteFormClientRect.left, tabItemRect.bottom, noteFormClientRect.right, noteFormClientRect.bottom), this, 0, NULL);
	pageForm->ShowWindow(SW_HIDE);
	
	return index;
}

PageForm* OtherNoteForm::GetPageForm(Long index) {
	return static_cast<PageForm*>(CompositeForm::GetAt(index));
}

Long OtherNoteForm::RemovePageForm(Long index) {
	this->tabCtrl->DeleteItem(index);
	return CompositeForm::Remove(index);
}

PageForm* OtherNoteForm::operator[](Long index) {
	return static_cast<PageForm*>(this->forms[index]);
}

Form* OtherNoteForm::Clone() const{
	return new OtherNoteForm(*this);
}

ArrayIterator<Form*>* OtherNoteForm::CreateIterator() const{
	return const_cast<ArrayIterator<Form*>*>(new ArrayIterator<Form*>(&this->forms));
}

void OtherNoteForm::Accept(Visitor *visitor) {
	visitor->Visit(this);
}

//To do
int OtherNoteForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);

	//this->menu.LoadMenu(IDR_MENU1);
	//SetMenu(&this->menu);
	//if (CFrameWnd::OnCreate(lpCreateStruct) != -1) {
	//this->menu.LoadMenu(IDR_MENU1);
	//this->SetMenu(&this->menu);
	//}
	/*this->menu.LoadMenu(IDR_MENU1);
	ASSERT(this->menu);
	SetMenu(NULL);
	::DestroyMenu(m_hMenuDefault);
	SetMenu(&this->menu);
	m_hMenuDefault = this->menu.GetSafeHmenu();*/


	//Long heightOfMenu = GetSystemMetrics(SM_CYMENU);

	CRect rect;
	this->GetClientRect(&rect);
	//rect.top += heightOfMenu;
	this->tabCtrl->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | TCS_TABS, rect, this, 0);

	/*CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)GetStockObject(HOLLOW_BRUSH), NULL);
	CWnd *wnd = new CWnd;
	wnd->CreateEx(0, strMyClass, _T("child"), WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE, CRect(10, 10, 300, 300), this, 0, NULL);
	*/
	
	//Page *page = static_cast<Note*>(this->contents)->GetPage(static_cast<Note*>(this->contents)->GetCurrent());
	/*Long index = static_cast<Note*>(this->contents)->AddPage();
	this->AddPageForm(static_cast<Page*>(static_cast<Note*>(this->contents)->GetAt(index)));*/

	//Page *page = static_cast<Note*>(this->contents)->GetPage(static_cast<Note*>(this->contents)->GetCurrentPage());
	//Long currentMemo = page->AddMemo();
	//Memo *memo = page->GetMemo(currentMemo);


	//Long formIndex = this->AddMemoForm(memo);
	//MemoForm *memoForm = static_cast<MemoForm*>(this->forms.GetAt(formIndex));
	//memoForm->SetFocus();

	//this->memo = new Memo;
	
	//load file
	//this->contents = new Note;/////제거
	//CPaintDC dc(this);
	//CharacterFaces *characterFaces = CharacterFaces::Instance(&dc);

	this->Load();
	if (this->GetLength() == 0) {
		CPaintDC dc(this);
		CharacterFaces *characterFaces = CharacterFaces::Instance(&dc);
		Long index = static_cast<Note*>(this->contents)->AddPage();
		this->AddPageForm(static_cast<Page*>(static_cast<Note*>(this->contents)->GetAt(index)));
	}

	static_cast<Note*>(this->contents)->SetCurrent(0);

	////memoForm create
	//PageForm *pageForm = this->GetPageForm(0);
	//MemoForm *memoForm;
	//Long i = 0;
	//while (i < pageForm->GetLength()) {
	//	memoForm = pageForm->GetMemoForm(i);
	//	//Memo *memo = memoForm->GetContents();
	//	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)GetStockObject(HOLLOW_BRUSH), NULL);
	//	memoForm->CreateEx(0, strMyClass, _T("Memo"), WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE, CRect(memoForm->GetPositionX(), memoForm->GetPositionY(), memoForm->GetPositionX() + 300, memoForm->GetPositionY() + 200), pageForm, 0, NULL);
	//	i++;
	//}

	//Caret *caret = Caret::Instance(this);

	static_cast<PageForm*>(this->GetPageForm(0))->ShowWindow(SW_SHOW);

	this->RedrawWindow();

	//return FALSE;
	return 0;
}


void OtherNoteForm::OnSize(UINT nType, int cx, int cy) {
	/*this->horizontalScroll = new HorizontalScroll(this);
	this->verticalScroll = new VerticalScroll(this);*/
	/*CRect rect;
	this->GetClientRect(&rect);

	CRect tabRect;
	this->GetTabCtrl()->GetClientRect(&tabRect);
	
	if (this->tabCtrl->GetSafeHwnd()) {
		this->tabCtrl->AdjustRect(TRUE, &rect);
		this->tabCtrl->MoveWindow(&rect, TRUE);

		this->tabCtrl->AdjustRect(FALSE, &rect);
		this->tabCtrl->MoveWindow(&rect, TRUE);
	}*/

	//CMenu 때문에 뻑나서 주석처리함.
	//CFrameWnd::OnSize(nType, cx, cy);
	//this->tabCtrl->MoveWindow(0, 0, cx, cy, true);
	//CRect tabItemRect;
	//this->tabCtrl->GetItemRect(0, &tabItemRect);
	//Long i = 0;
	//while (i < static_cast<Note*>(this->GetContents())->GetLength()) {
	//	this->GetPageForm(i)->MoveWindow(tabItemRect.left, tabItemRect.bottom, cx, cy, true);
	//	i++;
	//}
	CFrameWnd::OnSize(nType, cx, cy);

	CRect noteClientRect;
	this->GetClientRect(&noteClientRect);
	
	//get height of menu
	//Long heightOfMenu = GetSystemMetrics(SM_CYMENU);
	//this->tabCtrl->MoveWindow(0, 0, noteClientRect.Width(), noteClientRect.Height() - heightOfMenu, true);
	this->tabCtrl->MoveWindow(0, 0, noteClientRect.Width(), noteClientRect.Height(), true);
	
	CRect tabItemRect;
	this->tabCtrl->GetItemRect(0, &tabItemRect);
	Long i = 0;
	while (i < static_cast<Note*>(this->GetContents())->GetLength()) {
		//this->GetPageForm(i)->MoveWindow(0, heightOfMenu + tabItemRect.bottom, noteClientRect.Width(), noteClientRect.Height() - 27, true);
		this->GetPageForm(i)->MoveWindow(0, tabItemRect.bottom, noteClientRect.Width(), noteClientRect.Height() - tabItemRect.bottom, true);
		i++;
	}
}

//To do
void OtherNoteForm::OnClose() {
	//Caret *caret = Caret::Instance(this);
	//if (caret != 0) {
	//	delete caret;
	//}
	this->SetFocus();
	this->Save();
	/*Long i = 0;
	while (i < this->length) {
		if (this->forms.GetAt(i) != 0) {
			delete this->forms.GetAt(i);
		}
		i++;
	}*/

	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	if (characterFaces != 0) {
		delete characterFaces;
	}

	/*if (this->memo != 0) {/////제거
		delete this->memo;
	}*/

	//if (this->tabCtrl != 0) {
	//	delete this->tabCtrl;
	//}

	//destructor에서 할일로 보임
	/*while (this->length > 0) {
		static_cast<Note*>(this->contents)->SetCurrent(0);
		this->RemovePageForm(0);
	}*/
	
	CFrameWnd::OnClose();
}

#include "PaintVisitor.h"
#include "ArrayIterator.h"

//To do
void OtherNoteForm::OnPaint() {
	//CPaintDC dc(this);
	//SCROLLINFO scrinfo;
	//SCROLLINFO vScrinfo;
	//this->horizontalScroll->GetScrollBar()->GetScrollInfo(&scrinfo);
	//this->verticalScroll->GetScrollBar()->GetScrollInfo(&vScrinfo);
	//
	//CScrollBar *csb=this->hScroll->GetScroll();
	//csb->GetScrollBarInfo();
	//
	//CRect rect;
	//this->GetClientRect(&rect);
	//CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	//CRect rrect(-(scrinfo.nPos), -(vScrinfo.nPos), 10000, 10000);
	//PaintVisitor paintVisitor(&dc, &rect);	
	//this->memo->Accept(&paintVisitor);/////제거
//	static_cast<Note*>(this->contents)->GetPage(static_cast<Note*>(this->contents)->GetCurrentPage())->Accept(&paintVisitor);
	CFrameWnd::OnPaint();
	//CWindowDC dc(this);
	//Long captionHeight = GetSystemMetrics(SM_CYCAPTION);
	//Long menuHeight = GetSystemMetrics(SM_CYMENU);

	//CPen newBGPen(PS_SOLID, 5, RGB(255, 255, 255));
	////CPen newPen(PS_SOLID, 1, RGB(0, 120, 215));
	//CPen *pOldPen = dc.SelectObject(&newBGPen);

	//CRect wndRect;
	//this->GetWindowRect(wndRect);

	///*dc.MoveTo(0, captionHeight + menuHeight + 12);
	//dc.LineTo(wndRect.right, captionHeight + menuHeight + 12);*/
	//dc.SelectObject(newBGPen);

	//dc.MoveTo(0, captionHeight + menuHeight + 11);
	//dc.LineTo(wndRect.right, captionHeight + menuHeight + 11);
	//dc.SelectObject(pOldPen);
}

//#include "KeyActionCreator.h"
//#include "KeyAction.h"
//void OtherNoteForm::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
//	KeyActionCreator keyActionCreator;
//	KeyAction *keyAction = keyActionCreator.Create(this, nChar, nRepCnt, nFlags);
//	if (keyAction != 0) {
//		keyAction->OnKeyDown(nChar, nRepCnt, nFlags);
//		delete keyAction;
//		keyAction = 0;
//	}
//}

//#include "Mouse.h"
//void OtherNoteForm::OnMouseMove(UINT nFlags, CPoint point) {
//	//UNREFERENCED_PARAMETER(nFlags);
//	//UNREFERENCED_PARAMETER(point);
//
//	Mouse mouse(this);
//	mouse.OnMouseMove(nFlags, point);
//
//}

//void OtherNoteForm::OnLButtonDown(UINT nFlags, CPoint point) {
//	Mouse mouse(this);
//	mouse.OnLButtonDown(nFlags, point);
//
//}

//void OtherNoteForm::OnLButtonUp(UINT nFlags, CPoint point) {
//	//CRect rect(20, 20, 210, 210);
//	//Invalidate();
//	//this->UpdateWindow();
//
//}

#include "LoadVisitor.h"
void OtherNoteForm::Load() {
	/*fstream fs("aha.txt", ios::in);
	if (!fs.fail()) {
		char buffer[10000];
		fs.getline(buffer, sizeof(buffer));
		CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		characterFaces->SetFontFamily(buffer);
		fs.getline(buffer, sizeof(buffer));
		string temp(buffer);
		Long fontSize = stoi(temp);
		characterFaces->SetFontSize(fontSize);
		Line *line;
		char doubleCharacter[2];
		Long j = 0;
		fs.getline(buffer, sizeof(buffer));
		while (!fs.eof()) {
			line = this->memo->GetLine(j);
			Long length = string(buffer).length();
			Long i = 0;
			while (i < length - 1) {
				if (buffer[i] >= 0 && buffer[i] <= 127) {
					line->Write(buffer[i]);
				}
				else {
					doubleCharacter[0] = buffer[i];
					doubleCharacter[1] = buffer[i + 1];
					i++;
					line->Write(doubleCharacter);
				}
				i++;
			}
			this->memo->AddLine();
			j++;
			fs.getline(buffer, sizeof(buffer));
		}
		this->memo->RemoveLine(this->memo->GetLength() - 1);
		fs.close();
	}
	this->memo->SetRow(0);
	this->memo->GetLine(0)->SetColumn(0);*/
	LoadVisitor loadVisitor;
	this->Accept(&loadVisitor);
}

#include "SaveVisitor.h"
void OtherNoteForm::Save() {
	/*fstream fs("aha.txt", ios::out | ios::trunc);
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	fs << characterFaces->GetFontFamily() << "\r\n" << characterFaces->GetFontSize() << "\r\n";
	Line *line;
	Long i = 0;
	while (i < this->memo->GetLength()) {
		line = this->memo->GetLine(i);
		MakeStringVisitor makeStringVisitor;
		line->Accept(&makeStringVisitor);
		fs << makeStringVisitor.GetCompleteString().c_str() << "\r\n";
		i++;
	}
	fs.close();*/
	SaveVisitor saveVisitor;
	this->Accept(&saveVisitor);
}


//void OtherNoteForm::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
//	HScrollActionCreator hScrollActionCreator;
//	ScrollAction *scrollAction = hScrollActionCreator.Create(this->horizontalScroll, nSBCode, nPos, pScrollBar);
//
//	if(scrollAction != 0) {
//		scrollAction->Action(nSBCode, nPos, pScrollBar);
//	}
//}
//
//void OtherNoteForm::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
//	VScrollActionCreator vScrollActionCreator;
//	ScrollAction *scrollAction = vScrollActionCreator.Create(this->verticalScroll, nSBCode, nPos, pScrollBar);
//	
//	if(scrollAction != 0) {
//		scrollAction->Action(nSBCode, nPos, pScrollBar);
//	}
//}


//void OtherNoteForm::DisplayMemoForm(Long index) {
//	//memoForm create
//	PageForm *pageForm = this->GetPageForm(index);
//	MemoForm *memoForm;
//	Long i = 0;
//	//while (i < pageForm->GetLength()) {
//	//	memoForm = pageForm->GetMemoForm(i);
//	//	//Memo *memo = memoForm->GetContents();
//	//	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)GetStockObject(HOLLOW_BRUSH), NULL);
//	//	memoForm->CreateEx(0, strMyClass, _T("Memo"), WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE, CRect(memoForm->GetPositionX(), memoForm->GetPositionY(), memoForm->GetPositionX() + 300, memoForm->GetPositionY() + 200), pageForm, 0, NULL);
//	//	i++;
//	//}
//	
//	pageForm->ShowWindow(SW_SHOW);
//}

void OtherNoteForm::OnLButtonDblClk(UINT nFlags, CPoint point) {
	PageForm *pageForm = this->GetPageForm(static_cast<Note*>(this->contents)->GetCurrent());
	pageForm->ShowWindow(SW_HIDE);
	Long index = static_cast<Note*>(this->contents)->AddPage();
	Page *page = static_cast<Note*>(this->contents)->GetPage(index);
	index = this->AddPageForm(page);
	pageForm = this->GetPageForm(index);
	pageForm->ShowWindow(SW_SHOW);
	this->tabCtrl->SetCurSel(index);
	pageForm->SetFocus();
	CFrameWnd::OnLButtonDblClk(nFlags, point);
}

void OtherNoteForm::SelectTabItem(Long index) {
	/*PageForm *pageForm = this->GetPageForm(static_cast<Note*>(this->contents)->GetCurrent());
	pageForm->ShowWindow(SW_HIDE);
	pageForm = this->GetPageForm(index);
	pageForm->ShowWindow(SW_SHOW);
	static_cast<Note*>(this->contents)->SetCurrent(index);
	pageForm->SetFocus();*/
	
	//1. page 위치를 설정해준다.
	static_cast<Note*>(this->contents)->SetCurrent(index);
	//2. page 위치의 for을 가져온다.
	PageForm *pageForm = this->GetPageForm(index);
	//3. page폼를 보여준다.
	pageForm->ShowWindow(SW_SHOW);
	//4. page폼에 포커스를 설정한다.
	pageForm->SetFocus();
}

#include <afxdlgs.h>
void OtherNoteForm::OnMenuExit() {
	this->OnClose();
}

//Not Use
//void OtherNoteForm::OnSetFocus(CWnd* pOldWnd) {
//	CFrameWnd::OnSetFocus(pOldWnd);
//	this->RedrawWindow();
//}

void OtherNoteForm::OnMenuOpen()
{///////////////////////////////////////////////////////////////////////////////////////////
	CString fileName = "";
	CFileDialog fileDialog(TRUE, ".txt", "OtherNote.txt");
	OPENFILENAME& ofn = fileDialog.GetOFN();
	//ofn.Flags |= OFN_ALLOWMULTISELECT;
	//ofn.lpstrFile = p;
	//ofn.nMaxFile = FILE_LIST_BUFFER_SIZE;

	fileDialog.DoModal();
	fileName.ReleaseBuffer();
}


void OtherNoteForm::OnMenuSave()
{
	
}