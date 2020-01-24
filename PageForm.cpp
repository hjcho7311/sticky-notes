//PageForm.cpp

#include "PageForm.h"
#include "MemoForm.h"
#include "Contents.h"
#include "Page.h"
#include "Memo.h"
#include "Visitor.h"
#include "ArrayIterator.h"

BEGIN_MESSAGE_MAP(PageForm, CWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	//ON_NOTIFY(TCN_SELCHANGING, 0, OnSelChanging)
	//ON_WM_KEYDOWN()
	//ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//ON_WM_LBUTTONUP()
	//ON_WM_HSCROLL()
	//ON_WM_VSCROLL()
END_MESSAGE_MAP()

PageForm::PageForm(Contents *contents, Long capacity, string pageFormName)
	:CompositeForm(contents, capacity) {
	this->pageFormName = pageFormName;
}

PageForm::PageForm(const PageForm& source)
	: CompositeForm(source) {
	this->pageFormName = source.pageFormName;
}

PageForm::~PageForm() {
	
}

PageForm& PageForm::operator=(const PageForm& source) {
	CompositeForm::operator=(source);
	this->pageFormName = source.pageFormName;
	return *this;
}

int PageForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct);
	
	this->RedrawWindow();
	
	return 0;
}
#include "OtherNoteForm.h"
#include "Note.h"
void PageForm::OnClose() {
//	CTabCtrl::OnClose();
	CWnd::OnClose();
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	Long i = 0;
	while (otherNoteForm->GetPageForm(i) != this) {
		i++;
	}
	Note *note = (Note*)(otherNoteForm->GetContents());
	note->SetCurrent(i);
	otherNoteForm->RemovePageForm(note->GetCurrent());
	note->RemovePage();
	//여기까지 페이지 제거
	//이후 커런트가 -1일 때 length>0이면 current++, length==0이면 페이지, 페이지폼 추가 (후 커런트 옮기고 show해줌->페이지폼 추가에 포함돼있음)
}

void PageForm::OnPaint() {
	CWnd::OnPaint();
//	CTabCtrl::OnPaint();
	//CPaintDC dc(this);
}

//수정필요
//void PageForm::OnSize(UINT nType, int cx, int cy) {
//	CRect rect;
//	this->GetClientRect(&rect);
//	rect.right = cx;
//	rect.bottom = cy;
//	this->MoveWindow(&rect, TRUE);
//
//	//this->ShowWindow(SW_SHOWMAXIMIZED);
//
//	CRect tabRect;
//	this->GetTabCtrl()->GetClientRect(&tabRect);
//	this->tabCtrl->AdjustRect(TRUE, &rect);
//	this->tabCtrl->MoveWindow(&rect, TRUE);
//
//	this->tabCtrl->AdjustRect(FALSE, &rect);
//	this->tabCtrl->MoveWindow(&rect, TRUE);
//}

//Long PageForm::AddMemoForm(Memo *memo, CPoint point) {
Long PageForm::AddMemoForm(Memo *memo, CRect rect) {
	Long current = CompositeForm::Add(new MemoForm(memo, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top));
	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH), NULL);
	MemoForm *memoForm = this->GetMemoForm(current);
	//memoForm->CreateEx(0, strMyClass, _T("Memo"), WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE, CRect(point.x, point.y, point.x + 300, point.y + 200), this, 0, NULL);
	memoForm->CreateEx(0, strMyClass, _T("Memo"), WS_CHILD | WS_VISIBLE, rect, this, 0, NULL);
	memoForm->SetWindowPos(&wndTop, 0, 0, rect.right - rect.left, rect.bottom - rect. top, SWP_NOMOVE);

	return current;
}

Long PageForm::AddMemoForm(MemoForm *memoForm) {
	Long current = CompositeForm::Add(memoForm);
	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH), NULL);
	//memoForm = this->GetMemoForm(current);
	//memoForm->CreateEx(0, strMyClass, _T("Memo"), WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE, CRect(point.x, point.y, point.x + 300, point.y + 200), this, 0, NULL);
	CRect rect;
	rect.left = memoForm->GetPositionX();
	rect.right = rect.left + memoForm->GetMaxWidth();
	rect.top = memoForm->GetPositionY();
	rect.bottom = rect.top + memoForm->GetMaxHeight();
	memoForm->CreateEx(0, strMyClass, _T("Memo"), WS_CHILD | WS_VISIBLE, rect, this, 0, NULL);
	//memoForm->SetWindowPos(&wndTop, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE);
	//memoForm->ShowWindow(SW_HIDE);
	return current;
}

void PageForm::OnLButtonDown(UINT nFlags, CPoint point) {
	CWnd::OnLButtonDown(nFlags, point);
	//Mouse mouse(this);
	//mouse.OnLButtonDown(nFlags, point);
	
	//빈 메모폼들을 정리해주는 부분 추가
	//this->CleanUpMemoForms();

	Long index = static_cast<Page*>(this->contents)->AddMemo();
	//Memo *memo = static_cast<Page*>(this->contents)->GetMemo(static_cast<Page*>(this->contents)->GetCurrentMemo());
	Memo *memo = static_cast<Page*>(this->contents)->GetMemo(index);
	memo->AddLine();
	//Long current = this->AddMemoForm(memo, point);
	CRect rect;
	rect.left = point.x;
	rect.top = point.y;
	rect.right = rect.left + 300;
	rect.bottom = rect.top + 200;
	Long current = this->AddMemoForm(memo, rect);
	MemoForm *memoForm = this->GetMemoForm(current);
	memoForm->SetFocus();
	//CWnd::OnLButtonDown(nFlags, point);
}

Long PageForm::RemoveMemoForm(Long index) {
	return CompositeForm::Remove(index);
}

MemoForm* PageForm::GetMemoForm(Long index) {
	return static_cast<MemoForm*>(CompositeForm::GetAt(index));
}

MemoForm* PageForm::operator[](Long index) {
	return static_cast<MemoForm*>(CompositeForm::GetAt(index));
}

Form* PageForm::Clone() const {
	return new PageForm(*this);
}

void PageForm::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

ArrayIterator<Form*>* PageForm::CreateIterator() const {
	return const_cast<ArrayIterator<Form*>*>(new ArrayIterator<Form*>(&this->forms));
}

#include "Line.h"
bool PageForm::CleanUpMemoForms(){
	bool ret = false;
	//1. 페이지폼의 페이지를 가져온다.
	Page *page = static_cast<Page*>(this->GetContents());

	//2. 빈메모를 찾는다.
	Memo *memo;
	Long i = 0;
	while (i < page->GetLength()) {
		memo = page->GetMemo(i);
		Line *line;
		line = memo->GetLine(0);
		//3. 빈메모를 지운다.
		if (memo->GetLength() == 1 && line->GetLength() == 0) {
			ret = true;
			this->GetMemoForm(i)->OnClose();
		}
		i++;
	}
	return ret;
}
