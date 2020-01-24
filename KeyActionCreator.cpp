//KeyActionCreator.cpp

#include "KeyActionCreator.h"
#include "LeftArrowKey.h"
#include "UpArrowKey.h"
#include "DownArrowKey.h"
#include "RightArrowKey.h"
#include "CtrlLeftArrowKey.h"
#include "CtrlRightArrowKey.h"
#include "CtrlCKey.h"
#include "CtrlVKey.h"
#include "CtrlXKey.h"
#include "ShiftLeftArrowKey.h"
#include "ShiftRightArrowKey.h"
#include "ShiftUpArrowKey.h"
#include "ShiftDownArrowKey.h"
#include "ShiftHomeKey.h"
#include "ShiftEndKey.h"
#include "ShiftCtrlHomeKey.h"
#include "ShiftCtrlEndKey.h"
//#include "CtrlShiftLeftArrowKey.h"
//#include "CtrlShiftRightArrowKey.h"
#include "TabKey.h"
#include "ReturnKey.h"
#include "BackspaceKey.h"
#include "DeleteKey.h"
#include "HomeKey.h"
#include "EndKey.h"
#include "CtrlHomeKey.h"
#include "CtrlEndKey.h"


KeyActionCreator::KeyActionCreator() {

}

KeyActionCreator::KeyActionCreator(const KeyActionCreator& source) {

}

KeyActionCreator::~KeyActionCreator() {

}

KeyActionCreator& KeyActionCreator::operator=(const KeyActionCreator& source) {
	return *this;
}

KeyAction* KeyActionCreator::Create(Form *form, UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_LEFT && GetKeyState(VK_CONTROL) < 0) {
		return new CtrlLeftArrowKey(form);
	}
	else if (nChar == VK_RIGHT && GetKeyState(VK_CONTROL) < 0) {
		return new CtrlRightArrowKey(form);
	}
	else if ((nChar == 'C'|| nChar == 'c') && GetKeyState(VK_CONTROL) < 0) {
		return new CtrlCKey(form);
	}
	else if ((nChar == 'V' || nChar == 'v') && GetKeyState(VK_CONTROL) < 0) {
		return new CtrlVKey(form);
	}
	else if ((nChar == 'X' || nChar == 'x') && GetKeyState(VK_CONTROL) < 0) {
		return new CtrlXKey(form);
	}
	else if (nChar == VK_HOME && GetKeyState(VK_SHIFT) < 0 && GetKeyState(VK_CONTROL) < 0) {
		return new ShiftCtrlHomeKey(form);
	}
	else if (nChar == VK_END && GetKeyState(VK_SHIFT) < 0 && GetKeyState(VK_CONTROL) < 0) {//todo
		return new ShiftCtrlEndKey(form);
	}
	else if (nChar == VK_HOME && GetKeyState(VK_CONTROL) < 0) {
		return new CtrlHomeKey(form);
	}
	else if (nChar == VK_END && GetKeyState(VK_CONTROL) < 0) {
		return new CtrlEndKey(form);
	}
	else if (nChar == VK_LEFT && GetKeyState(VK_SHIFT) < 0) {
		return new ShiftLeftArrowKey(form);
	}
	else if (nChar == VK_RIGHT && GetKeyState(VK_SHIFT) < 0) {
		return new ShiftRightArrowKey(form);
	}
	else if (nChar == VK_UP && GetKeyState(VK_SHIFT) < 0) {
		return new ShiftUpArrowKey(form);
	}
	else if (nChar == VK_DOWN && GetKeyState(VK_SHIFT) < 0) {
		return new ShiftDownArrowKey(form);
	}
	else if (nChar == VK_HOME && GetKeyState(VK_SHIFT) < 0) {
		return new ShiftHomeKey(form);
	}
	else if (nChar == VK_END && GetKeyState(VK_SHIFT) < 0) {
		return new ShiftEndKey(form);
	}
	else if (nChar == VK_END && GetKeyState(VK_SHIFT) < 0) {
		return new ShiftEndKey(form);
	}
	else if (nChar == VK_LEFT) {
		return new LeftArrowKey(form);
	}
	else if (nChar == VK_UP) {
		return new UpArrowKey(form);
	}
	else if (nChar == VK_DOWN) {
		return new DownArrowKey(form);
	}
	else if (nChar == VK_RIGHT) {
		return new RightArrowKey(form);
	}
	else if (nChar == VK_TAB) {
		return new TabKey(form);
	}
	else if (nChar == VK_RETURN) {
		return new ReturnKey(form);
	}
	else if (nChar == VK_BACK) {
		return new BackspaceKey(form);
	}
	else if (nChar == VK_DELETE) {
		return new DeleteKey(form);
	}
	else if (nChar == VK_HOME) {
		return new HomeKey(form);
	}
	else if (nChar == VK_END) {
		return new EndKey(form);
	}
	return 0;
}

//KeyAction* KeyActionCreator::Create(OtherNoteForm *otherNoteForm, UINT nChar, UINT nRepCnt, UINT nFlags) {
//	
//	if (nChar == VK_LEFT && GetKeyState(VK_CONTROL) < 0) {
//		return new CtrlLeftArrowKey(otherNoteForm);
//	}
//	else if (nChar == VK_RIGHT && GetKeyState(VK_CONTROL) < 0) {
//		return new CtrlRightArrowKey(otherNoteForm);
//	}
//
//	else if (nChar == VK_LEFT && GetKeyState(VK_SHIFT) < 0) {
//		return new ShiftLeftArrowKey(otherNoteForm);
//	}
//	else if (nChar == VK_UP && GetKeyState(VK_SHIFT) < 0) {
//		return new ShiftUpArrowKey(otherNoteForm);
//	}
//	else if (nChar == VK_DOWN && GetKeyState(VK_SHIFT) < 0) {
//		return new ShiftDownArrowKey(otherNoteForm);
//	}
//	else if (nChar == VK_RIGHT && GetKeyState(VK_SHIFT) < 0) {
//		return new ShiftRightArrowKey(otherNoteForm);
//	}
//
//	else if (nChar == VK_HOME && GetKeyState(VK_CONTROL) < 0) {
//		return new CtrlHomeKey(otherNoteForm);
//	}
//	else if (nChar == VK_END && GetKeyState(VK_CONTROL) < 0) {
//		return new CtrlEndKey(otherNoteForm);
//	}
//	else if ((nChar == 'C' || nChar=='c') && GetKeyState(VK_CONTROL) < 0) {
//		return new CtrlCKey(otherNoteForm);
//	}
//	else if ((nChar == 'V' || nChar == 'v') && GetKeyState(VK_CONTROL) < 0) {
//		return new CtrlVKey(otherNoteForm);
//	}
//
//	else if (nChar == VK_LEFT) {
//		return new LeftArrowKey(otherNoteForm);
//	}
//	else if (nChar == VK_UP) {
//		return new UpArrowKey(otherNoteForm);
//	}
//	else if (nChar == VK_DOWN) {
//		return new DownArrowKey(otherNoteForm);
//	}
//	else if (nChar == VK_RIGHT) {
//		return new RightArrowKey(otherNoteForm);
//	}
//	
//	
//	else if (nChar == VK_TAB) {
//		return new TabKey(otherNoteForm);
//	}
//	else if (nChar == VK_RETURN) {
//		return new ReturnKey(otherNoteForm);
//	}
//	else if (nChar == VK_BACK) {
//	if (nChar == VK_BACK) {
//		return new BackspaceKey(otherNoteForm);
//	}
//	else if (nChar == VK_DELETE) {
//		return new DeleteKey(otherNoteForm);
//	}
//	
//	return 0;
//}