//CtrlVKey.cpp

#include "CtrlVKey.h"
#include "MemoForm.h"

CtrlVKey::CtrlVKey(Form *form)
	:KeyAction(form) {

}

CtrlVKey::CtrlVKey(const CtrlVKey& source)
	: KeyAction(source) {

}

CtrlVKey::~CtrlVKey() {

}

CtrlVKey& CtrlVKey::operator=(const CtrlVKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"
void CtrlVKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	//SelectedBuffer *selectedBuffer = this->otherNoteForm->selectedBuffer;
	//if (selectedBuffer->GetIsCopy()) {
	//	selectedBuffer->Paste();
	//}
	static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->PasteToMemoForm();
	dynamic_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
}