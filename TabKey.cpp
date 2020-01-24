//TabKey.cpp

#include "TabKey.h"
#include "OtherNoteForm.h"

TabKey::TabKey(Form *form)
	:KeyAction(form) {

}

TabKey::TabKey(const TabKey& source)
	: KeyAction(source) {

}

TabKey::~TabKey() {

}

TabKey& TabKey::operator=(const TabKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
//#include "Character.h"
#include "CharacterFaces.h"
#include "SelectedBuffer.h"
void TabKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (dynamic_cast<MemoForm*>(this->form)) {
		Memo *memo = static_cast<Memo*>(this->form->GetContents());
		Line *line = memo->GetLine(memo->GetRow());

		CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		Long tabWidth = characterFaces->GetCharacterSize(97).GetWidth() * 8;


		Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();

		Long xPosition = caret->GetXPosition();
		Long height = caret->GetYPosition();

		Long width = tabWidth - (xPosition%tabWidth);
				
		line->Write('\t', width, height);

		caret->MoveNextCharacter();
		dynamic_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
	}
}