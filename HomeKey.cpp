//HomeKey.cpp

#include "HomeKey.h"
#include "MemoForm.h"

HomeKey::HomeKey(Form *form)
	:KeyAction(form) {

}

HomeKey::HomeKey(const HomeKey& source)
	: KeyAction(source) {

}

HomeKey::~HomeKey() {

}

HomeKey& HomeKey::operator=(const HomeKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "Memo.h"
#include "Line.h"
#include "Caret.h"
#include "SelectedBuffer.h"
void HomeKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Memo *memo = static_cast<Memo*>(this->form->GetContents());

	Line *line = memo->GetLine(memo->GetRow());
	line->MoveFirstColumn();

	Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();
	caret->MoveFirstCharacter();
	static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
}