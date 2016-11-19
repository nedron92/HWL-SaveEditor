
// ZeldaHWLSaveEditorGUI.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "ZeldaAboutDlg.h"
#include "ZeldaCheckForUpdatesDlg.h"
#include "ZeldaEditCharaStatsDlg.h"
#include "ZeldaEditGeneralDlg.h"
#include "ZeldaEditMaterials.h"
#include "ZeldaEditFairyFoods.h"
#include "ZeldaEditAdventureModeMaps.h"
#include "ZeldaEditFairyDlg.h"
#include "ZeldaEditCharaWeaponsDlg.h"
#include "ZeldaEditCharaOverviewDlg.h"
#include "ZeldaConfigWeaponCopyDlg.h"

// CZeldaHWLSaveEditorGUIApp:
// See ZeldaHWLSaveEditorGUI.cpp for the implementation of this class
//

class CZeldaHWLSaveEditorGUIApp : public CWinApp
{
public:
	CZeldaHWLSaveEditorGUIApp();

	static HWLSaveEdit::HWLSaveEditor* save;
	static std::shared_ptr<HWLSaveEdit::HWLWeapon> sp_weapon_copy;

	static map<int, bool> mib_disabled_adventure_maps;
	static map<int, bool> mib_config_copy_weapon_values;

	static void calc_disabled_MenuItems(CMenu *cm_menu_edit);

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CZeldaHWLSaveEditorGUIApp theApp;