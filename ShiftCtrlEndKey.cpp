//ShiftCtrlEndKey.cpp

#include "ShiftCtrlEndKey.h"
#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"
#include "SelectedBuffer.h"

ShiftCtrlEndKey::ShiftCtrlEndKey(Form *form)
	:KeyAction(form) {
}

ShiftCtrlEndKey::ShiftCtrlEndKey(const ShiftCtrlEndKey& source)
	: KeyAction(source) {
}

ShiftCtrlEndKey::~ShiftCtrlEndKey() {

}

ShiftCtrlEndKey& ShiftCtrlEndKey::operator=(const ShiftCtrlEndKey& source) {
	KeyAction::operator=(source);

	return *this;
}

void ShiftCtrlEndKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	MemoForm *memoForm = static_cast<MemoForm*>(this->form);
	Memo *memo = static_cast<Memo*>(memoForm->GetContents());
	Line *line = memo->GetLine(memo->GetRow());
	Caret *caret = static_cast<MemoForm*>(this->form)->GetCaret();

	//1. store a caret of starting position
	if (memoForm->GetSelectedBuffer()->GetIsSelecting() == false) {
		memoForm->GetSelectedBuffer()->SetInitialPosition(memo->GetRow(), line->GetColumn());
	}

	//2. same caret logic
	if (memo->GetRow() < memo->GetLength() - 1 || line->GetColumn() < line->GetLength()) {
		caret->MoveLastLine();
		caret->MoveLastCharacter();
		memo->MoveLastRow();
		//������ �ѹ� �������� ������ ĳ�� ���� �߻�
		line = memo->GetLine(memo->GetRow());
		line->MoveLastColumn();
	}
	
	//3. copy to buffer for selectedbuffer
	memoForm->GetSelectedBuffer()->CopyToBuffer(memo->GetRow(), line->GetColumn());
	
	//4. fixed shift button clicked a caret of the starting position
	memoForm->GetSelectedBuffer()->SetIsSelecting(true);
	dynamic_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}