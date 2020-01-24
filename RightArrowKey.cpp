//RightArrowKey.cpp

#include "RightArrowKey.h"

RightArrowKey::RightArrowKey(Form *form)
	:KeyAction(form) {

}

RightArrowKey::RightArrowKey(const RightArrowKey& source)
	: KeyAction(source) {

}

RightArrowKey::~RightArrowKey() {

}

RightArrowKey& RightArrowKey::operator=(const RightArrowKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"
void RightArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (dynamic_cast<MemoForm*>(this->form)) {
		Memo *memo = static_cast<Memo*>(this->form->GetContents());
		Line *line = memo->GetLine(memo->GetRow());

		Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();

		if (memo->GetRow() < memo->GetLength() - 1 || line->GetColumn() < line->GetLength()) {
			if (line->GetColumn() < line->GetLength()) {
				line->MoveNextColumn();
				caret->MoveNextCharacter();
			}
			else if (line->GetColumn() == line->GetLength()) {
				memo->MoveNextRow();
				line = memo->GetLine(memo->GetRow());
				line->MoveFirstColumn();
				caret->MoveNextLine();
			}
		}
		dynamic_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
		dynamic_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	}
}