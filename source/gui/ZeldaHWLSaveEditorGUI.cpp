
// ZeldaHWLSaveEditorGUI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ZeldaHWLSaveEditorGUI.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CZeldaHWLSaveEditorGUIApp

BEGIN_MESSAGE_MAP(CZeldaHWLSaveEditorGUIApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CZeldaHWLSaveEditorGUIApp construction

CZeldaHWLSaveEditorGUIApp::CZeldaHWLSaveEditorGUIApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CZeldaHWLSaveEditorGUIApp object

CZeldaHWLSaveEditorGUIApp theApp;


// CZeldaHWLSaveEditorGUIApp initialization
//initialize the static-member
HWLSaveEdit::HWLSaveEditor *CZeldaHWLSaveEditorGUIApp::save = nullptr;
std::shared_ptr<HWLSaveEdit::HWLWeapon> CZeldaHWLSaveEditorGUIApp::sp_weapon_copy = nullptr;

map<int, bool> CZeldaHWLSaveEditorGUIApp::mib_disabled_adventure_maps;
map<int, bool> CZeldaHWLSaveEditorGUIApp::mib_config_copy_weapon_values;

BOOL CZeldaHWLSaveEditorGUIApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	//SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CZeldaEditGeneralDlg dlg;
	bool b_is_update_check = false;
	INT_PTR nResponse;

	//get the current command-line parameter
	CString cs_cmd_param = theApp.m_lpCmdLine;

	//check if we have to disable the auto-trim function or not
	if (cs_cmd_param == L"--disable-auto-trim")
	{
		HWLSaveEdit::HWLSaveEditor::enable_auto_trim(false);
	}

	//check if we have only to check for updates
	if (cs_cmd_param == L"--check-updates")
	{
		b_is_update_check = true;
	}

	//check if we have to try to create a new default-config-file
	if (cs_cmd_param == L"--create-default-config")
	{
		HWLSaveEdit::HWLConfig hwlc_tmp_config = HWLSaveEdit::HWLConfig(false);

		try
		{
			hwlc_tmp_config.write_config();
			MessageBox(dlg, CString("A new default-config was created successfully."), L"Information", MB_OK | MB_ICONINFORMATION);
			return FALSE;
		}
		catch (HWLSaveEdit::HWLException &e)
		{
			CString str(e.what());
			CString str2(to_string(e.get_code()).c_str());

			str = L"Error: \nCode:" + str2 + L"\n\nMessage: " + str;
			MessageBox(dlg, str, L"Error", MB_OK | MB_ICONWARNING);
			return FALSE;
		}
	}

	//check if we have to try to create a new config-file with all params + changed ones
	if (cs_cmd_param == L"--create-config")
	{
		HWLSaveEdit::HWLConfig hwlc_tmp_config = HWLSaveEdit::HWLConfig();

		try
		{
			hwlc_tmp_config.write_config();
			MessageBox(dlg, CString("A new config, with all current parameters, was created successfully."), L"Information", MB_OK | MB_ICONINFORMATION);
			return FALSE;
		}
		catch (HWLSaveEdit::HWLException &e)
		{
			CString str(e.what());
			CString str2(to_string(e.get_code()).c_str());

			str = L"Error: \nCode:" + str2 + L"\n\nMessage: " + str;
			MessageBox(dlg, str, L"Error", MB_OK | MB_ICONWARNING);
			return FALSE;
		}
	}

	//check if we have NOT the commnad-line for update-checking
	if (!b_is_update_check)
	{
		//own initialization
		try
		{
			this->save = new HWLSaveEdit::HWLSaveEditor();

			if (stoi(this->save->get_config()->get_param_value("openLastSaveFileOnStart", this->save->get_config()->get_sectionID("General"))) == 0)
			{
				if (MessageBox(dlg, L"Found a 'zmha.bin' within this dir. Open it?", L"Information", MB_YESNO | MB_ICONASTERISK) == IDNO)
					this->save = nullptr;
			}

		}
		catch (HWLSaveEdit::HWLException &e)
		{

			CString str(e.what());
			str = L"An error occured: \n" + str + L"\n\nShould Application start with no SaveFile opened?";

			if (MessageBox(dlg, str, L"Information", MB_YESNO | MB_ICONASTERISK) == IDNO)
				return FALSE;
		}

		if (save != nullptr && save->get_update_message() != "")
			MessageBox(dlg, CString(save->get_update_message().c_str()), L"Information", MB_OK | MB_ICONINFORMATION);

		m_pMainWnd = &dlg;
		nResponse = dlg.DoModal();

	}
	else{
		CZeldaCheckForUpdatesDlg dlg_update;
		m_pMainWnd = &dlg_update;
		nResponse = dlg_update.DoModal();

	}

	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CZeldaHWLSaveEditorGUIApp::calc_disabled_MenuItems(CMenu *cm_menu_edit)
{
	//check if the static map is empty
	if (!mib_disabled_adventure_maps.empty())
	{
		//get the ID of the first MAP->Menu-Item
		int i_first_map_id = ID_MENU_EDIT_AM_AVMAP;
		
		//get the AM-SubeMenu
		CMenu *cm_menu_edit_am_maps = cm_menu_edit->GetSubMenu(4);

		//iterate over the static-map
		for (int i = 0; i < mib_disabled_adventure_maps.size(); i++)
		{
			//check, if the map is disabled and remove the Item, if its TRUE
			if (mib_disabled_adventure_maps[i])
				cm_menu_edit_am_maps->EnableMenuItem(i_first_map_id + i, MF_GRAYED | MF_BYCOMMAND);
			else
				cm_menu_edit_am_maps->EnableMenuItem(i_first_map_id + i, MF_ENABLED | MF_BYCOMMAND);

		}
	}
}