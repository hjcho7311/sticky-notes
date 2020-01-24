//OtherNoteApp.cpp

#include "OtherNoteApp.h"
#include "OtherNoteForm.h"
#include "Note.h"
#include "PageForm.h"
#include "resource1.h"

BOOL OtherNoteApp::InitInstance() {
	OtherNoteForm *otherNoteForm = new OtherNoteForm(new Note);
	//otherNoteForm->Create(NULL, "OtherNote");
	otherNoteForm->Create(NULL, "OtherNote", WS_OVERLAPPEDWINDOW, CFrameWnd::rectDefault, NULL, (LPCTSTR)IDR_MENU_MAIN, 0, NULL);
	//otherNoteForm->Create(NULL, "OtherNote", WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX, CFrameWnd::rectDefault, NULL, (LPCTSTR)IDR_MENU1, 0, NULL);
	otherNoteForm->ShowWindow(SW_SHOWMAXIMIZED);
	//otherNoteForm->ShowWindow(SW_SHOW);
	
	otherNoteForm->UpdateWindow();
	this->m_pMainWnd = otherNoteForm;
	
	return TRUE;
}

OtherNoteApp otherNoteApp;
