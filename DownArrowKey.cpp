//DownArrowKey.cpp

#include "DownArrowKey.h"

DownArrowKey::DownArrowKey(Form *form)
	:KeyAction(form) {

}

DownArrowKey::DownArrowKey(const DownArrowKey& source)
	: KeyAction(source) {

}

DownArrowKey::~DownArrowKey() {

}

DownArrowKey& DownArrowKey::operator=(const DownArrowKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"
#include "SelectedBuffer.h"
void DownArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (dynamic_cast<MemoForm*>(this->form)) {
		Memo *memo = static_cast<Memo*>(this->form->GetContents());

		Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();

		if (memo->GetRow() < memo->GetLength() - 1) {
			Long originalXPosition = caret->GetXPosition();

			caret->MoveNextLine();
			memo->MoveNextRow();
			Line *line = memo->GetLine(memo->GetRow());
			line->MoveFirstColumn();

			//Long previousWidth = -1;
			Long previousWidth = 0;
			Long currentWidth = 0;
			while (currentWidth < originalXPosition && line->GetColumn() < line->GetLength()) {
				previousWidth = currentWidth;
				currentWidth += line->GetCharacter(line->GetColumn())->GetWidth();
				line->MoveNextColumn();
			}

			Long resultWidth;
			if (currentWidth - originalXPosition <= originalXPosition - previousWidth) {
				resultWidth = currentWidth;
			}
			else {
				resultWidth = previousWidth;
				line->MovePreviousColumn();
			}

			caret->Move(resultWidth, caret->GetYPosition());
		}
		dynamic_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
		dynamic_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	}
}