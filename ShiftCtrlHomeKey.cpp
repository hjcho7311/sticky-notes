//ShiftCtrlHomeKey.cpp

#include "ShiftCtrlHomeKey.h"
#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"
#include "SelectedBuffer.h"

ShiftCtrlHomeKey::ShiftCtrlHomeKey(Form *form)
	:KeyAction(form) {
}

ShiftCtrlHomeKey::ShiftCtrlHomeKey(const ShiftCtrlHomeKey& source)
	: KeyAction(source) {
}

ShiftCtrlHomeKey::~ShiftCtrlHomeKey() {

}

ShiftCtrlHomeKey& ShiftCtrlHomeKey::operator=(const ShiftCtrlHomeKey& source) {
	KeyAction::operator=(source);

	return *this;
}

//Todo
void ShiftCtrlHomeKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	MemoForm *memoForm = static_cast<MemoForm*>(this->form);
	Memo *memo = static_cast<Memo*>(memoForm->GetContents());
	Line *line = memo->GetLine(memo->GetRow());
	Caret *caret = static_cast<MemoForm*>(this->form)->GetCaret();

	//1. store a caret of starting position
	if (memoForm->GetSelectedBuffer()->GetIsSelecting() == false) {
		memoForm->GetSelectedBuffer()->SetInitialPosition(memo->GetRow(), line->GetColumn());
	}

	//2. same caret logic
	if (memo->GetRow() > 0 || line->GetColumn() > 0) {
		memo->MoveFirstRow();
		
		//line을 다시 구해야 한다. 그렇지 않으면 캐럿오동작 발생함
		line = memo->GetLine(memo->GetRow());
		line->MoveFirstColumn();
		
		caret->MoveFirstLine();
		caret->MoveFirstCharacter();
	}

	//3. copy to buffer for selectedbuffer
	memoForm->GetSelectedBuffer()->CopyToBuffer(memo->GetRow(), line->GetColumn());

	//4. fixed shift button clicked a caret of the starting position
	memoForm->GetSelectedBuffer()->SetIsSelecting(true);
	dynamic_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}