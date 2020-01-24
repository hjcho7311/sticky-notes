//CtrlEndKey.cpp

#include "CtrlEndKey.h"

CtrlEndKey::CtrlEndKey(Form *form)
	:KeyAction(form) {

}

CtrlEndKey::CtrlEndKey(const CtrlEndKey& source)
	: KeyAction(source) {

}

CtrlEndKey::~CtrlEndKey() {

}

CtrlEndKey& CtrlEndKey::operator=(const CtrlEndKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"
void CtrlEndKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (dynamic_cast<MemoForm*>(this->form)) {
		Memo *memo = static_cast<Memo*>(this->form->GetContents());
		memo->MoveLastRow();

		Line *line = memo->GetLine(memo->GetRow());
		line->MoveLastColumn();

		Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();

		caret->MoveLastLine();
		caret->MoveLastCharacter();
		dynamic_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
	}
}