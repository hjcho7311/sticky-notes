//ShiftUpArrowKey.cpp

#include "ShiftUpArrowKey.h"
#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"
#include "SelectedBuffer.h"

ShiftUpArrowKey::ShiftUpArrowKey(Form *form)
	:KeyAction(form) {

}

ShiftUpArrowKey::ShiftUpArrowKey(const ShiftUpArrowKey& source)
	: KeyAction(source) {

}

ShiftUpArrowKey::~ShiftUpArrowKey() {

}

ShiftUpArrowKey& ShiftUpArrowKey::operator=(const ShiftUpArrowKey& source) {
	KeyAction::operator=(source);

	return *this;
}

void ShiftUpArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	MemoForm *memoForm = static_cast<MemoForm*>(this->form);
	Memo *memo = static_cast<Memo*>(memoForm->GetContents());
	Line *line = memo->GetLine(memo->GetRow());
	Caret *caret = static_cast<MemoForm*>(this->form)->GetCaret();

	//1. store a caret of starting position
	if (memoForm->GetSelectedBuffer()->GetIsSelecting() == false) {
		memoForm->GetSelectedBuffer()->SetInitialPosition(memo->GetRow(), line->GetColumn());
	}

	//2. same caret logic
	if (memo->GetRow() > 0) {
		Long originalXPosition = caret->GetXPosition();

		caret->MovePreviousLine();
		memo->MovePreviousRow();

		line = memo->GetLine(memo->GetRow());
		line->MoveFirstColumn();

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
	//3. copy to buffer for selectedbuffer
	memoForm->GetSelectedBuffer()->CopyToBuffer(memo->GetRow(), line->GetColumn());

	//4. fixed shift button clicked a caret of the starting position
	memoForm->GetSelectedBuffer()->SetIsSelecting(true);
	dynamic_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}