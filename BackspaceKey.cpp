//BackspaceKey.cpp

#include "BackspaceKey.h"
#include "MemoForm.h"
#include "Memo.h"
#include "Line.h"
#include "Caret.h"
#include "Character.h"
#include "SelectedBuffer.h"

BackspaceKey::BackspaceKey(Form *form)
	:KeyAction(form) {
}

BackspaceKey::BackspaceKey(const BackspaceKey& source)
	:KeyAction(source) {
}

BackspaceKey::~BackspaceKey() {

}

BackspaceKey& BackspaceKey::operator=(const BackspaceKey& source) {
	KeyAction::operator=(source);

	return *this;
}

void BackspaceKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (dynamic_cast<MemoForm*>(this->form)) {
		Memo *memo = static_cast<Memo*>(this->form->GetContents());
		Line *line;

		Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();

		MemoForm *memoForm = dynamic_cast<MemoForm*>(this->form);
		Long count = 0;
		if (memoForm->GetSelectedBuffer()->GetIsSelecting() == true) {
			SelectedBuffer *selectedBuffer = memoForm->GetSelectedBuffer();
			Memo *buffer = selectedBuffer->GetBuffer();
			Long i = 0;
			while (i < buffer->GetLength()) {
				line = buffer->GetLine(i);
				count += line->GetLength();
				count++;
				i++;
			}
			count--;

			memo->SetRow(selectedBuffer->GetEndRow());
			line = memo->GetLine(memo->GetRow());
			line->SetColumn(selectedBuffer->GetEndColumn());
		}
		else {
			count = 1;
		}

		Long j = 0;
		while (j < count) {
			line = memo->GetLine(memo->GetRow());
			if (line->GetLength() != 0 && line->GetColumn() != 0) {
				caret->MovePreviousCharacter();
				line->Erase();
			}
			else if (memo->GetRow() != 0) {
				if (line->GetLength() == 0) {
					caret->MovePreviousLine();
					memo->RemoveLine();
					memo->GetLine(memo->GetRow())->MoveLastColumn();
					caret->MoveLastCharacter();
				}
				else {
					Line *lineToCopy = memo->GetLine(memo->MovePreviousRow());

					caret->MovePreviousLine();
					lineToCopy->MoveLastColumn();
					caret->MoveLastCharacter();

					Long i = 0;
					while (i < line->GetLength()) {
						Contents *contents = line->GetCharacter(i)->Clone();
						lineToCopy->Add(contents);
						i++;
					}
					memo->MoveNextRow();
					memo->RemoveLine();
				}
			}
			j++;
		}
		
		if (memoForm->GetSelectedBuffer()->GetIsSelecting() == true) {
			Long xPos = 0;
			Long yPos = 0;
			memoForm->CalculatePosition(&xPos, &yPos);
			yPos += 20;
			caret->Move(xPos, yPos);
		}
		
		dynamic_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
		dynamic_cast<MemoForm*>(this->form)->ReSizeWindow();
		dynamic_cast<MemoForm*>(this->form)->RedrawWindow();
	}
}