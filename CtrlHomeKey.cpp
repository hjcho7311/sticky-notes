//CtrlHomeKey.cpp

#include "CtrlHomeKey.h"

CtrlHomeKey::CtrlHomeKey(Form *form)
	:KeyAction(form) {

}

CtrlHomeKey::CtrlHomeKey(const CtrlHomeKey& source)
	: KeyAction(source) {

}

CtrlHomeKey::~CtrlHomeKey() {

}

CtrlHomeKey& CtrlHomeKey::operator=(const CtrlHomeKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"
void CtrlHomeKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (dynamic_cast<MemoForm*>(this->form)) {
		Memo *memo = static_cast<Memo*>(this->form->GetContents());
		memo->MoveFirstRow();

		Line *line = memo->GetLine(memo->GetRow());
		line->MoveFirstColumn();

		Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();
		caret->MoveFirstLine();
		dynamic_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
	}
}