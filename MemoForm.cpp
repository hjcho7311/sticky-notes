//MemoForm.cpp

#include "MemoForm.h"
#include "Form.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"
#include "Visitor.h"
#include "CharacterFaces.h"
#include "PaintVisitor.h"
#include "ArrayIterator.h"
#include "Caret.h"
#include "SelectedBuffer.h"
#include "MakeStringVisitor.h"
#include "HighLightVisitor.h"
//#include "Mouse.h"

BEGIN_MESSAGE_MAP(MemoForm, CWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_MESSAGE(WM_IME_COMPOSITION, OnImeComposition)
	ON_WM_KEYDOWN()
	//ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEACTIVATE()
	ON_WM_NCHITTEST()
	ON_WM_MOVE()
	ON_WM_NCLBUTTONDOWN()
	//ON_WM_MOUSEHOVER()
	//ON_WM_MOUSEMOVE()
	//ON_WM_SIZE()
	//ON_COMMAND(ID_MEMOFORM_HIGHLIGHT, OnSetHighLight)
	ON_COMMAND(ID_MEMOFORM_HIGHLIGHT, OnHighLight)
	ON_COMMAND(ID_MEMOFORM_UNHIGHLIGHT, OnUnHighLight)
END_MESSAGE_MAP()

MemoForm::MemoForm(Contents* contents, Long positionX, Long positionY, Long width, Long height, Long highLightCapacity)
	:Form(contents), highLights(highLightCapacity) {
	this->endComposition = true;
	this->positionX = positionX;
	this->positionY = positionY;
	//this->caret = new Caret(this);
	this->caret = 0;
	this->selectedBuffer = 0;
	this->maxWidth = width;
	this->maxHeight = height;
	this->isCaption = false;
	this->highLightCapacity = 100;
	this->highLightLength = 0;
	this->state = 1;
}

#include "OtherNoteForm.h"
MemoForm::~MemoForm() {
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)CWnd::FindWindow("#32770", "OtherNote");
	//otherNoteForm->Detach(this->contents);
	/*if (this->caret != 0) {
		delete this->caret;
	}*/
	if (this->caret != 0) {
		delete this->caret;
	}

	if (this->selectedBuffer != 0) {
		delete this->selectedBuffer;
	}
}

MemoForm::MemoForm(const MemoForm& source)
	:Form(source), highLights(source.highLightCapacity) {
	this->endComposition = source.endComposition;
	this->positionX = source.positionX;
	this->positionY = source.positionY;
	this->caret = 0;
	this->selectedBuffer = 0;
	this->maxWidth = source.maxWidth;
	this->maxHeight = source.maxHeight;
	this->isCaption = source.isCaption;

	Long i = 0;
	while (i < this->highLightLength) {
		this->highLights.Store(i, (const_cast<MemoForm&>(source)).highLights.GetAt(i));
		i++;
	}
	this->highLightCapacity = source.highLightCapacity;
	this->highLightLength = source.highLightLength;
}

MemoForm& MemoForm::operator = (const MemoForm& source) {
	this->endComposition = source.endComposition;
	this->positionX = source.positionX;
	this->positionY = source.positionY;
	this->caret = 0;
	this->selectedBuffer = 0;
	this->maxWidth = source.maxWidth;
	this->maxHeight = source.maxHeight;
	this->isCaption = source.isCaption;

	Long i = 0;
	while (i < this->highLightLength) {
		if (this->highLights.GetAt(i) != 0) {
			delete this->highLights.GetAt(i);
		}
		i++;
	}
	this->highLights = source.highLights;
	i = 0;
	while (i < source.highLightLength) {
		this->highLights.Modify(i, (const_cast<MemoForm&>(source)).highLights.GetAt(i));
		i++;
	}
	this->highLightCapacity = source.highLightCapacity;
	this->highLightLength = source.highLightLength;

	return *this;
}

Form* MemoForm::Clone() const {
	return new MemoForm(*this);
}

void MemoForm::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

int MemoForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct);
	
	//CPaintDC dc(this);
	//CharacterFaces *characterFaces = CharacterFaces::Instance(&dc);
	
	//Caret *caret = Caret::Instance(this);
	if (this->caret == 0) {
		this->caret = new Caret(this);
	}

	if (this->selectedBuffer == 0) {
		//Memo *memo = static_cast<Memo*>(this->GetContents());
		//this->selectedBuffer = new SelectedBuffer(this, static_cast<Memo*>(this->GetContents())->GetRow(), static_cast<Memo*>(this->GetContents())->GetLine(static_cast<Memo*>(contents)->GetRow())->GetColumn());
		//this->selectedBuffer = new SelectedBuffer(this, static_cast<Memo*>(this->GetContents())->AddLine(), static_cast<Memo*>(this->GetContents())->GetLine(static_cast<Memo*>(contents)->GetRow())->GetColumn());
		this->selectedBuffer = new SelectedBuffer(this, 0, 0);
	}


	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	this->caret->ShowCaret();
	return 0;
}

void MemoForm::SetSelectedBuffer(SelectedBuffer* selectedBuffer) {
	this->selectedBuffer = selectedBuffer;
}

#include "PageForm.h"
#include "Page.h"
#include "Note.h"
void MemoForm::OnClose() {
	CWnd::OnClose();
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	Note *note = (Note*)(otherNoteForm->GetContents());
	PageForm *pageForm = otherNoteForm->GetPageForm(note->GetCurrent());
	Page *page = static_cast<Page*>(pageForm->GetContents());
	Long i = 0;
	while (page->GetMemo(i) != static_cast<Memo*>(this->contents)) {
		i++;
	}

	page->SetCurrent(i);
	pageForm->RemoveMemoForm(page->GetCurrent());
	page->RemoveMemo();
}

#include "PaintHighLightVisitor.h"
#include "SelectedBuffer.h"
#include "PaintSelectionVisitor.h"
#include "SingleCharacter.h"
#include "DoubleCharacter.h"
void MemoForm::OnPaint() {
	CPaintDC dc(this);
	CRect rect;
	this->GetClientRect(&rect);
	
	PaintVisitor paintVisitor(&dc, &rect);
	this->contents->Accept(&paintVisitor);
	HighLightVisitor highLightVisitor(&dc);
	this->GetContents()->Accept(&highLightVisitor);
	PaintSelectionVisitor paintSelectionVisitor(&dc);
	this->Accept(&paintSelectionVisitor);
	
	//if(this->state == 2) {
	//	CPen pen;
	//	pen.CreatePen( PS_SOLID, 5, RGB(0,0,0) );    // 빨간색 펜 생성
	//	CPen* oldPen = dc.SelectObject( &pen );
	//	dc.MoveTo(0, 20);
	//	dc.LineTo(0, rect.bottom);
	//	dc.MoveTo(0, rect.bottom);
	//	dc.LineTo(rect.right, rect.bottom);
	//	dc.MoveTo(rect.right, rect.bottom);
	//	dc.LineTo(rect.right, 20);
	//	dc.SelectObject( oldPen );
	//}

	CWnd::OnPaint();
}

void MemoForm::CalculatePosition(Long *xPos, Long *yPos) {
	//Caret *caret = Caret::Instance(this);
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	CharacterSize characterSize = characterFaces->GetCharacterSize(127);
	*xPos = 0;
	*yPos = 0;

	Long beginRow = this->selectedBuffer->GetBeginRow();
	Long i = 0;
	while (i < beginRow) {
		*yPos += characterSize.GetHeight();
		i++;
	}
	Line *beginLine = static_cast<Memo*>(this->GetContents())->GetLine(beginRow);
	Long beginColumn = this->selectedBuffer->GetBeginColumn();
	Long j = 0;
	while (j < beginColumn) {
		*xPos += beginLine->GetCharacter(j)->GetWidth();
		j++;
	}
}

#include "DeleteKey.h"
void MemoForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	//if (this->isCaption == false) {
		if (nChar >= 32 && nChar <= 126) {
			//
			if (this->selectedBuffer->GetIsSelecting() == true) {
				DeleteKey deleteKey = DeleteKey(this);
				deleteKey.OnKeyDown(nChar, nRepCnt, nFlags);
				this->selectedBuffer->SetIsSelecting(false);
			}

			Line *line = static_cast<Memo*>(this->contents)->GetLine(static_cast<Memo*>(this->contents)->GetRow());
			line->Write(nChar);
			//Caret *caret = Caret::Instance(this);
			this->caret->MoveNextCharacter();
		}
		//temp to be deleted
		/*else if (nChar == 13) {
			Memo *memo = static_cast<Memo*>(this->contents);
			Line *line = static_cast<Memo*>(this->contents)->GetLine(static_cast<Memo*>(this->contents)->GetRow());

			memo->InsertLine();
			Line *newLine = memo->GetLine(memo->GetRow());

			newLine->MoveFirstColumn();
		}*/

		this->ReSizeWindow();
		this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	//}
}

Long MemoForm::UpdateMaxWidth() {
	Memo *memo = static_cast<Memo*>(this->GetContents());
	Long widthOfLine = 0;
	this->maxWidth = 300;
	Long i = 0;
	while (i < memo->GetLength()) {
		widthOfLine = 35;
		Line *line = memo->GetLine(i);
		Long j = 0;
		while (j < line->GetLength()) {
			widthOfLine += line->GetCharacter(j)->GetWidth();
			j++;
		}
		if (this->maxWidth < widthOfLine) {
			this->maxWidth = widthOfLine;
		}
		i++;
	}
	if (this->maxWidth < 300) {
		this->maxWidth = 300;
	}

	return this->maxWidth;
}

Long MemoForm::UpdateMaxHeight() {
	Memo *memo = static_cast<Memo*>(this->GetContents());
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	Long heightOfMemoForm = characterFaces->GetCharacterSize(97).GetHeight() + 25;
	this->maxHeight = 200;
	Long i = 0;
	while (i < memo->GetLength()) {
		heightOfMemoForm += characterFaces->GetCharacterSize(97).GetHeight();
		i++;
	}
	if (this->maxHeight < heightOfMemoForm) {
		this->maxHeight = heightOfMemoForm;
	}
	if (this->maxHeight < 200) {
		this->maxHeight = 200;
	}
	return this->maxHeight;
}

void MemoForm::ReSizeWindow() {
	this->UpdateMaxWidth();
	this->UpdateMaxHeight();
	this->SetWindowPos(&wndBottom, this->GetPositionX(), this->GetPositionY(), this->maxWidth, this->maxHeight, SWP_NOMOVE);
}

//void MemoForm::OnSize(UINT nType, int cx, int cy) {
//	CWnd::OnSize(nType, cx, cy);
//
//	this->MoveWindow(this->GetPositionX(), this->GetPositionY(), cx, cy);
//}

LRESULT MemoForm::OnImeComposition(WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	//if (this->isCaption == false) {
		if (this->selectedBuffer->GetIsSelecting() == true) {
			DeleteKey deleteKey = DeleteKey(this);
			deleteKey.OnKeyDown(0, 0, 0);
			this->selectedBuffer->SetIsSelecting(false);
		}

		char composition[2];
		composition[0] = HIBYTE(wParam);
		composition[1] = LOBYTE(wParam);

		Line *lineLink = static_cast<Memo*>(this->contents)->GetLine(static_cast<Memo*>(this->contents)->GetRow());

		//Caret *caret = Caret::Instance(0);
		this->caret->ChangeImeCaret();

		if (lParam & GCS_COMPSTR) {
			if (this->endComposition == false) {
				lineLink->Erase();
			}
			this->endComposition = false;

			if (!(composition[1] == '\x1b' && composition[0] == '\0')) {
				lineLink->Write(composition);
			}
			else {
				this->endComposition = true;
				this->caret->ChangeCaret();
			}
		}
		if (lParam & GCS_RESULTSTR) {
			this->endComposition = true;
			lineLink->Erase();
			lineLink->Write(composition);
			this->caret->MoveNextCharacter();
			this->caret->ChangeCaret();
		}
		this->ReSizeWindow();
		//this->RedrawWindow();
		this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	//}
	return 0;
}

//void MemoForm::OnMouseMove(UINT nFlags, CPoint point) {
	//UNREFERENCED_PARAMETER(nFlags);
	//UNREFERENCED_PARAMETER(point);

	//Mouse mouse(this);
	//mouse.OnMouseMove(nFlags, point);
//}

#include "Character.h"
#include "PageForm.h"
#include "Page.h"
void MemoForm::OnLButtonDown(UINT nFlags, CPoint point) {
	/*Mouse mouse(this);
	mouse.OnLButtonDown(nFlags, point);*/
	//this->SetFocus();	
	CWnd::OnLButtonDown(nFlags, point);
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	Note *note = (Note*)(otherNoteForm->GetContents());
	PageForm *pageForm = otherNoteForm->GetPageForm(note->GetCurrent());
	//pageForm->CleanUpMemoForms();
	Long i = 0;
	while (pageForm->GetMemoForm(i) != this) {
		i++;
	}
	Page *page = static_cast<Page*>(pageForm->GetContents());
	page->SetCurrent(i);
	//this->SetFocus();

	Memo *memo = static_cast<Memo*>(this->contents);
	memo->MoveFirstRow();
	Long height = 20 + 7;//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	while (height < (point.y - this->caret->GetHeight()) && memo->GetRow() < memo->GetLength() - 1) {
		memo->MoveNextRow();
		height += this->caret->GetHeight();
	}

	Line *line = memo->GetLine(memo->GetRow());
	line->MoveFirstColumn();
	Long previousWidth = 0+15 ;//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	Long currentWidth = 0+15 ;//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@2
	while (currentWidth < point.x && line->GetColumn() < line->GetLength()) {
		previousWidth = currentWidth;
		currentWidth += line->GetCharacter(line->GetColumn())->GetWidth();
		line->MoveNextColumn();
	}
	
	if (currentWidth - point.x < point.x - previousWidth) {
		this->caret->Move(currentWidth-15, height-7);//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	}
	else {
		line->MovePreviousColumn();
		this->caret->Move(previousWidth-15, height-7); //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	}
	this->isCaption = false;
	this->caret->ShowCaret();
	this->selectedBuffer->SetIsSelecting(false);
	this->SetWindowPos(&wndBottom, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	this->SetFocus();	
	this->RedrawWindow();
}

//void MemoForm::OnLButtonUp(UINT nFlags, CPoint point) {
//	//CRect rect(20, 20, 210, 210);
//	//Invalidate();
//	//this->UpdateWindow();
//	
//	/*if (point.x != this->GetPositionX()) {
//		this->SetPositionX(point.x);
//	}
//	if (point.y != this->GetPositionY()) {
//		this->SetPositionY(point.y);
//	}*/
//}

void MemoForm::OnSetFocus(CWnd *pOldWnd) {
	//if (dynamic_cast<MemoForm*>(pOldWnd)) {
	//	pOldWnd->HideCaret();
	//	//static_cast<MemoForm*>(pOldWnd)->GetCaret()->HideCaret();
	//}
	//pOldWnd->RedrawWindow();
	//if (this->isCaption == FALSE) {
		//this->caret->ShowCaret();
	//}
	//else {
		//this->caret->HideCaret();
		//DestroyCaret();
	//}
	CWnd::OnSetFocus(pOldWnd);
	this->caret->ShowCaret();	
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}

void MemoForm::OnKillFocus(CWnd* pNewWnd) {
	CWnd::OnKillFocus(pNewWnd);
	this->selectedBuffer->SetIsSelecting(false);
	//this->HideCaret();
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	Note *note = (Note*)(otherNoteForm->GetContents());
	PageForm *pageForm = otherNoteForm->GetPageForm(note->GetCurrent());
	Long lines = static_cast<Memo*>(this->GetContents())->GetLength();
	Long characters = static_cast<Memo*>(this->GetContents())->GetLine(0)->GetLength();
	if (lines == 1 && characters == 0) {
		pageForm->CleanUpMemoForms();
	}
}

int MemoForm::OnMouseActivate(CWnd *pDesktopWnd, UINT nHitTest, UINT message) {
	//this->caret = new Caret(this);
	this->SetFocus();
	
	return MA_ACTIVATE;
}

#include "KeyActionCreator.h"
#include "KeyAction.h"
void MemoForm::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	KeyActionCreator keyActionCreator;
	KeyAction *keyAction = keyActionCreator.Create(this, nChar, nRepCnt, nFlags);

	if (keyAction != 0) {
		keyAction->OnKeyDown(nChar, nRepCnt, nFlags);
		delete keyAction;
		keyAction = 0;
	}
}

void MemoForm::SetPositionX(Long positionX) {
	this->positionX = positionX;
}

void MemoForm::SetPositionY(Long poisitionY) {
	this->positionY = positionY;
}

LRESULT MemoForm::OnNcHitTest(CPoint point) {
	CWnd::OnNcHitTest(point);
	CRect wndRect;
	this->GetWindowRect(&wndRect);
	//CRect clientRect;
	//this->GetClientRect(&clientRect);
	if (point.y < wndRect.top + 20 && point.y > wndRect.top) {
		//this->OnLButtonDown(0, point);
		/*if(this->focus == false) {
		this->RedrawWindow();
		this->focus = true;
		}*/
		/*	if(this->focus == false) {
		this->SetFocus();
		this->focus = true;
		}*/
		
		/*this->SetIsCaption(1);
		this->HideCaret();*/
		return HTCAPTION;
	}
	/*this->SetIsCaption(0);
	this->ShowCaret();*/

	return HTCLIENT;
}

void MemoForm::SetIsCaption(bool isCaption) {
	this->isCaption = isCaption;
}

void MemoForm::OnMove(int x, int y) {
	if (this->positionX != x) {
		this->positionX = x;
	}

	if (this->positionY != y) {
		this->positionY = y;
	}
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}

void MemoForm::SetMaxWidth(Long width) {
	this->maxWidth = width;
}

void MemoForm::SetMaxHeight(Long height) {
	this->maxHeight = height;
}

void MemoForm::OnNcLButtonDown(UINT nHitTest, CPoint point) {
	CWnd::OnNcLButtonDown(nHitTest, point);

	/*OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	Note *note = (Note*)(otherNoteForm->GetContents());
	PageForm *pageForm = otherNoteForm->GetPageForm(note->GetCurrent());
	pageForm->CleanUpMemoForms();*/

	this->SetIsCaption(true);
	
	//this->HideCaret();
	this->selectedBuffer->SetInitialPosition(0, 0);
	
	//자료구조 끝 계산
	Long endRow;
	Long endColumn;
	endRow = static_cast<Memo*>(this->GetContents())->GetLength() - 1;
	endColumn = static_cast<Memo*>(this->GetContents())->GetLine(endRow)->GetLength();
	
	//영역 복사해서 buffer에 저장
	this->selectedBuffer->CopyToBuffer(endRow, endColumn);
	//영역체크 유효화(선택보여주기)
	this->selectedBuffer->SetIsSelecting(true);

	//zorder 이슈 호출해준 부분
	this->SetWindowPos(&wndBottom, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

	//캐럿을 나중에 출력하기 위해서 제일 마지막에 둔다
	this->SetFocus();
	this->caret->MoveLastLine();
	this->caret->MoveLastCharacter();
}

void MemoForm::OnRButtonDown(UINT nFlags, CPoint point) {
	//Pop-up menu
	if (this->selectedBuffer->GetIsSelecting() == true) {
		CMenu menu;
		menu.LoadMenu(IDR_MENU_MEMOFORM);
		CMenu *popupMenu = menu.GetSubMenu(0);
		CPoint position;
		GetCursorPos(&position);
		popupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, position.x, position.y, this);
		menu.DestroyMenu();
		CWnd::OnRButtonDown(nFlags, point);
	}	
}

//#include "HighLight.h"
void MemoForm::OnSetHighLight() {
	HighLight *highLight = new HighLight(this, this->selectedBuffer->GetBeginRow(), this->selectedBuffer->GetBeginColumn(), this->selectedBuffer->GetEndRow(), this->selectedBuffer->GetEndColumn());
	highLight->CopyToHighLightBuffer();

	Long index;
	if (this->highLightCapacity > this->highLightLength) {
		index = this->highLights.Store(this->highLightLength, highLight);
	}
	else {
		index = this->highLights.AppendFromRear(highLight);
		this->highLightCapacity++;
	}
	this->highLightLength++;
	//return index;
	this->RedrawWindow();
}

#include "PaintHighLightVisitor.h"
void MemoForm::PaintHighLights(CPaintDC &dc) {
	//CPaintDC dc(this);
	Long i = 0;
	while (i < this->highLightLength) {
		dc.SetBkMode(OPAQUE);
		dc.SetBkColor(RGB(255, 255, 102));
		dc.SetTextColor(RGB(0, 0, 0));
		HighLight *highLight = this->highLights.GetAt(i);
		Memo *highLightBufferMemo = highLight->GetHighLightBuffer();
		Line *highLightBufferLine = highLightBufferMemo->GetLine(highLightBufferMemo->GetRow());
		Long xPos = 0;
		Long yPos = 0;
		this->CalculatePosition(&xPos, &yPos);
		PaintHighLightVisitor paintHighLightVisitor(&dc, highLight, xPos, yPos + 20);
		highLightBufferMemo->Accept(&paintHighLightVisitor);
		i++;
	}
	dc.SetBkMode(TRANSPARENT);
	CWnd::OnPaint();
}

void MemoForm::OnHighLight() {
	Long startColumn = this->selectedBuffer->GetBeginColumn();
	Long startRow = this->selectedBuffer->GetBeginRow();
	Long endColumn = this->selectedBuffer->GetEndColumn();
	Long endRow = this->selectedBuffer->GetEndRow();

	static_cast<Memo*>(this->contents)->SetHighLightMode(startRow, startColumn, endRow, endColumn, true);

	//to be deleteed
	//this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	//CPaintDC dc(this);
	CDC *dc = this->GetDC();
	HighLightVisitor highLightVisitor(dc);
	this->GetContents()->Accept(&highLightVisitor);
	ReleaseDC(dc);
	/*1. 강조하기 이후에 선택영역이 사라지지 않는다 - done
	2. 강조하기 위로는 선택영역 표시가 나타나지 않는다*/
}


#include "UnHighLightVisitor.h"
void MemoForm::OnUnHighLight() {
	Long startColumn = this->selectedBuffer->GetBeginColumn();
	Long startRow = this->selectedBuffer->GetBeginRow();
	Long endColumn = this->selectedBuffer->GetEndColumn();
	Long endRow = this->selectedBuffer->GetEndRow();

	static_cast<Memo*>(this->contents)->SetHighLightMode(startRow, startColumn, endRow, endColumn, false);

	CDC *dc = this->GetDC();
	UnHighLightVisitor unHighLightVisitor(dc);
	this->GetContents()->Accept(&unHighLightVisitor);
	ReleaseDC(dc);
	/*1. 강조하기 이후에 선택영역이 사라지지 않는다 - done
	2. 강조하기 위로는 선택영역 표시가 나타나지 않는다*/
}

//BOOL m_bTrackMouse = FALSE;
//void MemoForm::OnMouseHover(UINT nFlags, CPoint point) {
//	//m_bTrackMouse = FALSE;
//	if(this->state == 1) {
//		this->state = 2;
//	}
//	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
//	
//	CWnd::OnMouseHover(nFlags, point);
//}
//
//void MemoForm::OnMouseMove(UINT nFlags, CPoint point) {
//	if(!m_bTrackMouse)
//
//	{
//
//		TRACKMOUSEEVENT tme;
//
//		tme.cbSize = sizeof(tme);
//
//		tme.hwndTrack = m_hWnd;
//
//		tme.dwFlags = TME_LEAVE|TME_HOVER;
//
//		tme.dwHoverTime = 1;
//
//		if(TrackMouseEvent(&tme))
//		{
//			m_bTrackMouse = TRUE;
//		}
//		m_bTrackMouse = FALSE;
//	}
//	//CButton::OnMouseMove(nFlags, point);
//}