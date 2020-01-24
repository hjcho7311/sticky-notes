//EndKey.cpp

#include "EndKey.h"
#include "MemoForm.h"

EndKey::EndKey(Form *form)
	:KeyAction(form) {

}

EndKey::EndKey(const EndKey& source)
	: KeyAction(source) {

}

EndKey::~EndKey() {

}

EndKey& EndKey::operator=(const EndKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "Memo.h"
#include "Line.h"
#include "Caret.h"
#include "SelectedBuffer.h"
void EndKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Memo *memo = static_cast<Memo*>(this->form->GetContents());

	Line *line = memo->GetLine(memo->GetRow());
	line->MoveLastColumn();

	Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();
	caret->MoveLastCharacter();
	static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
}