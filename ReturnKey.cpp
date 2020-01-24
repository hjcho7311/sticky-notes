//ReturnKey.cpp

#include "ReturnKey.h"

ReturnKey::ReturnKey(Form *form)
	:KeyAction(form) {

}

ReturnKey::ReturnKey(const ReturnKey& source)
	: KeyAction(source) {

}

ReturnKey::~ReturnKey() {

}

ReturnKey& ReturnKey::operator=(const ReturnKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"
#include "SelectedBuffer.h"
void ReturnKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (dynamic_cast<MemoForm*>(this->form)) {
		Memo *memo = static_cast<Memo*>(this->form->GetContents());
		Line *line = memo->GetLine(memo->GetRow());

		Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();
		memo->InsertLine();
		Line *newLine = memo->GetLine(memo->GetRow());

		while (line->GetColumn() < line->GetLength()) {
			newLine->Add(line->GetCharacter(line->GetColumn())->Clone());
			newLine->MoveNextColumn();

			line->MoveNextColumn();
			line->Erase();
		}
		newLine->MoveFirstColumn();

		caret->MoveNextLine();
		dynamic_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
	}
}