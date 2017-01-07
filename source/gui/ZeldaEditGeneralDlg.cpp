// ZeldaEditGeneralDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "ZeldaHWLSaveEditorGUI.h"

#include "afxdialogex.h"
#include "ZeldaEditGeneralDlg.h"
#include <atlconv.h>

// CZeldaEditGeneralDlg-Dialogfeld

IMPLEMENT_DYNAMIC(CZeldaEditGeneralDlg, CDialogEx)

CZeldaEditGeneralDlg::CZeldaEditGeneralDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZeldaEditGeneralDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

CZeldaEditGeneralDlg::~CZeldaEditGeneralDlg()
{
}

BOOL CZeldaEditGeneralDlg::OnInitDialog()
{
	//get the save-content
	save = CZeldaHWLSaveEditorGUIApp::save;

	//check, if the static-Map is empty and calculate then
	if (CZeldaHWLSaveEditorGUIApp::mib_disabled_adventure_maps.empty())
	{
		this->calc_disabledState_AmMaps();
	}

	//calculate the disabled-Items and remove the Menu-Entry, if neccessary
	CZeldaHWLSaveEditorGUIApp::calc_disabled_MenuItems(GetMenu()->GetSubMenu(1));
	return CDialogEx::OnInitDialog();
}

void CZeldaEditGeneralDlg::DoDataExchange(CDataExchange* pDX)
{
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//get the save-content
	save = CZeldaHWLSaveEditorGUIApp::save;

	if (save != nullptr)
	{
		for (int i = IDC_EDIT_SAVEFILE_GAME_VERSION; i <= IDC_BUTTON_HELP_UNLOCK_ALL_MATERIALS; i++)
		{
			GetDlgItem(i)->EnableWindow(true);
		}

		this->calc_general();
	}
	else{
		SetDlgItemText(IDC_EDIT_SAVEFILE_GAME_VERSION, L"");
		SetDlgItemText(IDC_RUBY_EDIT, L"");

		for (int i = IDC_EDIT_SAVEFILE_GAME_VERSION; i <= IDC_BUTTON_HELP_UNLOCK_ALL_MATERIALS; i++)
		{
			GetDlgItem(i)->EnableWindow(false);
		}

		CListBox *cl_dlc = (CListBox*)GetDlgItem(IDC_LIST_DLCS);
		cl_dlc->ResetContent();

	}

	CMenu *cm_menu = GetMenu();
	CMenu* cm_submenu = cm_menu->GetSubMenu(1);
	cm_submenu->CheckMenuItem(0, MF_CHECKED | MF_BYPOSITION);

	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZeldaEditGeneralDlg, CDialogEx)
	ON_BN_CLICKED(ID_SAVE, &CZeldaEditGeneralDlg::OnBnClickedSave)
	ON_BN_CLICKED(ID_EXIT, &CZeldaEditGeneralDlg::OnBnClickedExit)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_STATS, &CZeldaEditGeneralDlg::OnMenuEditCharactersStats)
	ON_COMMAND(ID_MENU_ABOUT, &CZeldaEditGeneralDlg::OnMenuAbout)
	ON_EN_CHANGE(IDC_RUBY_EDIT, &CZeldaEditGeneralDlg::OnEnChangeRubyEdit)
	ON_COMMAND(ID_MENU_MAIN_FILE_OPEN, &CZeldaEditGeneralDlg::OnMenuMainFileOpen)
	ON_COMMAND(ID_MENU_MAIN_FILE_CLOSE, &CZeldaEditGeneralDlg::OnMenuMainFileClose)
	ON_COMMAND(ID_MENU_MAIN_EXIT, &CZeldaEditGeneralDlg::OnMenuMainExit)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_BRONZE, &CZeldaEditGeneralDlg::OnMenuEditMaterialsBronze)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_SILVER, &CZeldaEditGeneralDlg::OnMenuEditMaterialsSilver)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_GOLD, &CZeldaEditGeneralDlg::OnMenuEditMaterialsGold)
	ON_COMMAND(ID_MENU_EDIT_FAIRYFOODS, &CZeldaEditGeneralDlg::OnMenuEditFairyfoods)
	ON_COMMAND(ID_MENU_EDIT_AM_AVMAP, &CZeldaEditGeneralDlg::OnMenuEditAmAvmap)
	ON_COMMAND(ID_MENU_EDIT_AM_GSMAP, &CZeldaEditGeneralDlg::OnMenuEditAmGsmap)
	ON_COMMAND(ID_MENU_EDIT_AM_MQMAP, &CZeldaEditGeneralDlg::OnMenuEditAmMqmap)
	ON_COMMAND(ID_MENU_EDIT_GENERAL, &CZeldaEditGeneralDlg::OnMenuEditGeneral)
	ON_BN_CLICKED(IDC_RUBY_MAX, &CZeldaEditGeneralDlg::OnBnClickedRubyMax)
	ON_COMMAND(ID_MENU_EDIT_AM_TLMAP, &CZeldaEditGeneralDlg::OnMenuEditAmTlmap)
	ON_COMMAND(ID_MENU_EDIT_AM_TMMAP, &CZeldaEditGeneralDlg::OnMenuEditAmTmmap)
	ON_COMMAND(ID_MENU_EDIT_FAIRIES, &CZeldaEditGeneralDlg::OnMenuEditFairies)
ON_COMMAND(ID_MENU_EDIT_CHARACTERS_WEAPONS, &CZeldaEditGeneralDlg::OnMenuEditCharactersWeapons)
ON_BN_CLICKED(IDC_BUTTON_HELP_UNLOCK_WEAPON_STATES, &CZeldaEditGeneralDlg::OnBnClickedButtonHelpUnlockWeaponStates)
ON_BN_CLICKED(IDC_BUTTON_HELP_UNLOCK_ALL_MATERIALS, &CZeldaEditGeneralDlg::OnBnClickedButtonHelpUnlockAllMaterials)
ON_COMMAND(ID_MENU_CHECKFORUPDATES, &CZeldaEditGeneralDlg::OnMenuCheckforupdates)
ON_COMMAND(ID_MENU_EDIT_AM_MWWMAP, &CZeldaEditGeneralDlg::OnMenuEditAmMwwmap)
ON_COMMAND(ID_MENU_EDIT_AM_KIMAP, &CZeldaEditGeneralDlg::OnMenuEditAmKimap)
ON_COMMAND(ID_MENU_EDIT_AM_GTMAP, &CZeldaEditGeneralDlg::OnMenuEditAmGtmap)
ON_COMMAND(ID_MENU_EDIT_CHARACTERS_OVERVIEW, &CZeldaEditGeneralDlg::OnMenuEditCharactersOverview)
ON_COMMAND(ID_MENU_EDIT_AM_LRMAP, &CZeldaEditGeneralDlg::OnMenuEditAmLrmap)
END_MESSAGE_MAP()


// CZeldaEditGeneralDlg-Meldungshandler

void CZeldaEditGeneralDlg::calc_general()
{
	CString s_game_version_value(save->get_general_things()->get_current_savefile_game_version().c_str());
	SetDlgItemText(IDC_EDIT_SAVEFILE_GAME_VERSION, s_game_version_value);

	CString s_ruby_value;
	s_ruby_value.Format(L"%d", save->get_general_things()->get_rubies());
	SetDlgItemText(IDC_RUBY_EDIT, s_ruby_value);

	CButton *cb_check;
	cb_check = (CButton*)GetDlgItem(IDC_CHECK_GENERAL_UNLOCK_SMITHY);
	cb_check->SetCheck(save->get_general_things()->get_unlocked_smithy_state());

	cb_check = (CButton*)GetDlgItem(IDC_CHECK_GENERAL_UNLOCK_NORMAL_WEAPONS_FOUND);
	cb_check->SetCheck(save->get_general_things()->get_unlocked_normal_weapons_state());

	cb_check = (CButton*)GetDlgItem(IDC_CHECK_GENERAL_UNLOCK_PLUS_WEAPONS_FOUND);
	cb_check->SetCheck(save->get_general_things()->get_unlocked_plus_weapons_state());

	cb_check = (CButton*)GetDlgItem(IDC_CHECK_GENERAL_UNLOCK_ALL_MATERIALS_FOUND);
	cb_check->SetCheck(save->get_general_things()->get_unlocked_all_materials_state());

	CListBox *cl_dlc = (CListBox*)GetDlgItem(IDC_LIST_DLCS);
	cl_dlc->ResetContent();
	for (int i = 0; i < save->get_general_things()->get_dlc_max_available_dlcs(); i++)
	{
		if (save->get_general_things()->get_dlc_installed_state(i))
		{
			//get CString equivalent of DLC-Name and add it to the ListBox
			CString cs_dlc_name(save->get_general_things()->get_dlc_name(i).c_str());
			cl_dlc->AddString(cs_dlc_name);
		}
		
	}

	if (cl_dlc->GetCount() == 0)
		cl_dlc->AddString(L"No DLCs installed");

}

void CZeldaEditGeneralDlg::save_general()
{
	CString s_ruby_value;
	GetDlgItemText(IDC_RUBY_EDIT, s_ruby_value);
	int i_ruby_value = _wtoi(s_ruby_value);
	save->get_general_things()->set_rubies(i_ruby_value);

	CButton *cb_check;
	cb_check = (CButton*)GetDlgItem(IDC_CHECK_GENERAL_UNLOCK_SMITHY);
	save->get_general_things()->set_unlocked_smithy_state((bool)cb_check->GetCheck());

	cb_check = (CButton*)GetDlgItem(IDC_CHECK_GENERAL_UNLOCK_NORMAL_WEAPONS_FOUND);
	save->get_general_things()->set_unlocked_normal_weapons_state((bool)cb_check->GetCheck());

	cb_check = (CButton*)GetDlgItem(IDC_CHECK_GENERAL_UNLOCK_PLUS_WEAPONS_FOUND);
	save->get_general_things()->set_unlocked_plus_weapons_state((bool)cb_check->GetCheck());

	cb_check = (CButton*)GetDlgItem(IDC_CHECK_GENERAL_UNLOCK_ALL_MATERIALS_FOUND);
	save->get_general_things()->set_unlocked_all_materials_state((bool)cb_check->GetCheck());

	save->get_general_things()->save_General();
}

void CZeldaEditGeneralDlg::OnBnClickedSave()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		try
		{
			this->save_general();
			save->save_file();

			CString str("Finish! Saving the current values was successfully.");
			MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
		}
		catch (std::exception &e)
		{
			CString str(e.what());
			MessageBox(str, L"Error", MB_ICONERROR);
		}
	}
	else{
		CString str("There is no SaveFile opened!");
		MessageBox(str, L"Error", MB_ICONERROR);
	}

}


void CZeldaEditGeneralDlg::OnBnClickedExit()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CZeldaEditGeneralDlg::OnOK();

}

void CZeldaEditGeneralDlg::OnEnChangeRubyEdit()
{
	// TODO:  Falls dies ein RICHEDIT-Steuerelement ist, wird das Kontrollelement
	// diese Benachrichtigung nicht senden, es sei denn, Sie überschreiben die CDialogEx::OnInitDialog()-
	// Funktion und rufen CRichEditCtrl().SetEventMask() auf
	// mit dem ENM_CHANGE-Flag ORed in der Eingabe.

	// TODO:  Fügen Sie hier Ihren Code für die Kontrollbenachrichtigungsbehandlung ein.
	if (save != nullptr)
	{
		CString test;
		CEdit *e_test = (CEdit*)GetDlgItem(IDC_RUBY_EDIT);
		CString cs_max_chars;
		cs_max_chars.Format(L"%d", HWLSaveEdit::HWLGeneral::rubyMax);
		e_test->SetLimitText(cs_max_chars.GetLength() + 1);
		GetDlgItemText(IDC_RUBY_EDIT, test);
		int i_test = _wtoi(test);

		if (i_test > HWLSaveEdit::HWLGeneral::rubyMax)
		{
			test.Format(L"%d", HWLSaveEdit::HWLGeneral::rubyMax);
			SetDlgItemText(IDC_RUBY_EDIT, test);
			e_test->SetLimitText(cs_max_chars.GetLength());
		}

		i_test = _wtoi(test);
		save->get_general_things()->set_rubies(i_test);
	}
}


void CZeldaEditGeneralDlg::OnMenuMainFileOpen()
{
	CMenu *test = GetMenu();
	GetActiveWindow()->ShowWindow(SW_MINIMIZE);

	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	TCHAR szFilters[] = _T("Hyrule Warriors Legends SaveGame (zmha.bin)|*.bin||");
	CFileDialog fileDlg(TRUE, _T(""), _T(""),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters, GetActiveWindow());

	if (fileDlg.DoModal() == IDOK)
	{
		CString cs_filepath = fileDlg.GetPathName();
		CT2CA pszConvertedAnsiString(cs_filepath);
		std::string s_filepath(pszConvertedAnsiString);

		if (cs_filepath != L"")
		{
			GetActiveWindow()->ShowWindow(SW_MAXIMIZE);
			GetActiveWindow()->ShowWindow(SW_SHOWNORMAL);

			delete CZeldaHWLSaveEditorGUIApp::save;
			try
			{
				CZeldaHWLSaveEditorGUIApp::save = new HWLSaveEdit::HWLSaveEditor(s_filepath, true);
				save = CZeldaHWLSaveEditorGUIApp::save;
				GetActiveWindow()->UpdateData();

				CZeldaHWLSaveEditorGUIApp::mib_disabled_adventure_maps.clear();
				this->calc_disabledState_AmMaps();
				CZeldaHWLSaveEditorGUIApp::calc_disabled_MenuItems(GetActiveWindow()->GetMenu()->GetSubMenu(1));

				int i_active_window_id = this->get_active_window_id();

				if (i_active_window_id == this->IDD)
				{
					CString str;
					str.Format(L"%d", save->get_general_things()->get_rubies());
					SetDlgItemText(IDC_RUBY_EDIT, str);
				}
				else
				
				{
					/*
					switch (i_active_window_id)
					{
					case IDD_EDIT_CHARA_STATS:
					{
												 CZeldaEditCharaStatsDlg *cdlg_tmp = (CZeldaEditCharaStatsDlg*)GetActiveWindow();
												 cdlg_tmp->calc_players();

												 break;
					}

					default:
						break;

					}
					*/
				}

			}
			catch (HWLSaveEdit::HWLException &e)
			{
				CZeldaHWLSaveEditorGUIApp::save = nullptr;
				save = CZeldaHWLSaveEditorGUIApp::save;
				GetActiveWindow()->UpdateData();

				CString str(e.what());
				str = L"An error occured: \n" + str + L"\n\nIf you have had opened a SaveFile, then it's closed now.";

				MessageBoxA(GetActiveWindow()->m_hWnd, CStringA(str), "Error", MB_OK | MB_ICONWARNING);

				GetActiveWindow()->ShowWindow(SW_MAXIMIZE);
				GetActiveWindow()->ShowWindow(SW_SHOWNORMAL);
			}
		}
	}
}


void CZeldaEditGeneralDlg::calc_disabledState_AmMaps()
{
	if (save != nullptr)
	{
		for (int i = 0; i < save->get_adventureMode_maxMaps(); i++)
		{
			if (save->get_amMap(i)->get_isDisabled())
				CZeldaHWLSaveEditorGUIApp::mib_disabled_adventure_maps[i] = true;
			else
				CZeldaHWLSaveEditorGUIApp::mib_disabled_adventure_maps[i] = false;
		}
	}
	else{
		int i_counter = 0;
		for (int i = ID_MENU_EDIT_AM_AVMAP; i <= ID_MENU_EDIT_AM_LRMAP; i++)
		{
			if (i_counter >= 5)
				CZeldaHWLSaveEditorGUIApp::mib_disabled_adventure_maps[i_counter] = true;
			else
				CZeldaHWLSaveEditorGUIApp::mib_disabled_adventure_maps[i_counter] = false;

			i_counter++;
		}
	}


}


int CZeldaEditGeneralDlg::get_active_window_id()
{
	CWnd *cw_active_window = GetActiveWindow();
	CRuntimeClass crc_runtime;
	CString cs_active_window_class_name(cw_active_window->GetRuntimeClass()->m_lpszClassName);

	if (cs_active_window_class_name == this->GetRuntimeClass()->m_lpszClassName)
		return this->IDD;

	if (cs_active_window_class_name == L"CZeldaEditCharaStatsDlg")
		return ( (CZeldaEditCharaStatsDlg*)crc_runtime.FromName(cs_active_window_class_name) )->IDD;


	return 0;
}

void CZeldaEditGeneralDlg::OnMenuMainFileClose()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	delete CZeldaHWLSaveEditorGUIApp::save;
	CZeldaHWLSaveEditorGUIApp::save = nullptr;
	save = CZeldaHWLSaveEditorGUIApp::save;

	CZeldaHWLSaveEditorGUIApp::mib_disabled_adventure_maps.clear();
	this->calc_disabledState_AmMaps();
	CZeldaHWLSaveEditorGUIApp::calc_disabled_MenuItems(GetActiveWindow()->GetMenu()->GetSubMenu(1));

	GetActiveWindow()->UpdateData();
}


void CZeldaEditGeneralDlg::OnMenuMainExit()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditGeneralDlg::OnOK();

}

void CZeldaEditGeneralDlg::OnMenuAbout()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaAboutDlg about;
	about.DoModal();

}


void CZeldaEditGeneralDlg::OnMenuCheckforupdates()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaCheckForUpdatesDlg updates;
	updates.DoModal();
}


void CZeldaEditGeneralDlg::OnMenuEditCharactersOverview()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaOverviewDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditGeneralDlg::OnMenuEditCharactersStats()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaStatsDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();

}

void CZeldaEditGeneralDlg::OnMenuEditMaterialsBronze()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL,0);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditGeneralDlg::OnMenuEditMaterialsSilver()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditGeneralDlg::OnMenuEditMaterialsGold()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditGeneralDlg::OnMenuEditFairyfoods()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyFoods dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditGeneralDlg::OnMenuEditAmAvmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 0);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditGeneralDlg::OnMenuEditAmGsmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditGeneralDlg::OnMenuEditAmMqmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditGeneralDlg::OnMenuEditAmTlmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 3);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditGeneralDlg::OnMenuEditAmTmmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 4);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditGeneralDlg::OnMenuEditAmMwwmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 5);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditGeneralDlg::OnMenuEditAmKimap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	int i_map_id = 6;
	int i_skipped_maps = 0;

	for (int i = i_map_id - 1; i < i_map_id; i++)
	{
		if (save->get_amMap(i)->get_isDisabled())
			i_skipped_maps++;
	}

	CZeldaEditAdventureModeMaps dlg(NULL, i_map_id, i_skipped_maps);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditGeneralDlg::OnMenuEditAmGtmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	int i_map_id = 7;
	int i_skipped_maps = 0;

	for (int i = i_map_id - 2; i < i_map_id; i++)
	{
		if (save->get_amMap(i)->get_isDisabled())
			i_skipped_maps++;
	}

	CZeldaEditAdventureModeMaps dlg(NULL, i_map_id, i_skipped_maps);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditGeneralDlg::OnMenuEditAmLrmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	int i_map_id = 8;
	int i_skipped_maps = 0;

	for (int i = i_map_id - 3; i < i_map_id; i++)
	{
		if (save->get_amMap(i)->get_isDisabled())
			i_skipped_maps++;
	}

	CZeldaEditAdventureModeMaps dlg(NULL, i_map_id, i_skipped_maps);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditGeneralDlg::OnMenuEditFairies()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditGeneralDlg::OnMenuEditGeneral()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	
}


void CZeldaEditGeneralDlg::OnBnClickedRubyMax()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		CString cs_ruby_value;

		save->get_general_things()->set_rubies(HWLSaveEdit::HWLGeneral::rubyMax);
		cs_ruby_value.Format(L"%d", save->get_general_things()->get_rubies());
		SetDlgItemText(IDC_RUBY_EDIT, cs_ruby_value);

		CString str("Finish! All needed Values are updated.");
		MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
	}
}

void CZeldaEditGeneralDlg::OnMenuEditCharactersWeapons()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaWeaponsDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditGeneralDlg::OnBnClickedButtonHelpUnlockWeaponStates()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CString cs_info("If you activate those check-boxes, then you don't have more weapons\n"
		"then before, but the game wil believe that you collect them all.\n"
		"If you have the Master Sword, then please check the Skills ingame ;) ");
	MessageBox(cs_info, L"Information", MB_OK | MB_ICONINFORMATION);
}


void CZeldaEditGeneralDlg::OnBnClickedButtonHelpUnlockAllMaterials()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CString cs_info("If you activate this check-box, then you don't have more materials\n"
		"then before, but the game wil believe that you collect them all.\n");
	MessageBox(cs_info, L"Information", MB_OK | MB_ICONINFORMATION);
}