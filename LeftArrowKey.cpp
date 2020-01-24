//LeftArrowKey.cpp

#include "LeftArrowKey.h"

LeftArrowKey::LeftArrowKey(Form *form)
	:KeyAction(form) {

}

LeftArrowKey::LeftArrowKey(const LeftArrowKey& source)
	: KeyAction(source) {

}

LeftArrowKey::~LeftArrowKey() {

}

LeftArrowKey& LeftArrowKey::operator=(const LeftArrowKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"
void LeftArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	
	if (dynamic_cast<MemoForm*>(this->form)) {
		Memo *memo = static_cast<Memo*>(this->form->GetContents());
		Line *line = memo->GetLine(memo->GetRow());

		Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();
	
		if (memo->GetRow() > 0 || line->GetColumn() > 0) {
			if (line->GetColumn() > 0) {
				caret->MovePreviousCharacter();
				line->MovePreviousColumn();
			}
			else if (line->GetColumn() == 0) {
				caret->MovePreviousLine();

				memo->MovePreviousRow();
				line = memo->GetLine(memo->GetRow());

				line->MoveLastColumn();
				caret->MoveLastCharacter();
			}
		}
		dynamic_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
		dynamic_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	}
}