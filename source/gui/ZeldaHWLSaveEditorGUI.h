
// ZeldaHWLSaveEditorGUI.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "ZeldaAboutDlg.h"
#include "ZeldaEditCharaStatsDlg.h"
#include "ZeldaEditGeneralDlg.h"
#include "ZeldaEditMaterials.h"

// CZeldaHWLSaveEditorGUIApp:
// See ZeldaHWLSaveEditorGUI.cpp for the implementation of this class
//

class CZeldaHWLSaveEditorGUIApp : public CWinApp
{
public:
	CZeldaHWLSaveEditorGUIApp();

	static HWLSaveEdit::HWLSaveEditor* save;

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CZeldaHWLSaveEditorGUIApp theApp;