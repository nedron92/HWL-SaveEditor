// ZeldaEditCharaOverview.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZeldaHWLSaveEditorGUI.h"
#include "ZeldaEditCharaOverviewDlg.h"
#include "afxdialogex.h"


// CZeldaEditCharaOverviewDlg-Dialogfeld

IMPLEMENT_DYNAMIC(CZeldaEditCharaOverviewDlg, CDialogEx)

CZeldaEditCharaOverviewDlg::CZeldaEditCharaOverviewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZeldaEditCharaOverviewDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

CZeldaEditCharaOverviewDlg::~CZeldaEditCharaOverviewDlg()
{
}

BOOL CZeldaEditCharaOverviewDlg::OnInitDialog()
{
	//calculate the disabled-Items and remove the Menu-Entry, if neccessary
	CZeldaHWLSaveEditorGUIApp::calc_disabled_MenuItems(GetMenu()->GetSubMenu(1));
	return CDialogEx::OnInitDialog();
}

void CZeldaEditCharaOverviewDlg::DoDataExchange(CDataExchange* pDX)
{
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//menu
	CMenu *cm_menu = GetMenu();
	CMenu* cm_submenu = cm_menu->GetSubMenu(1);
	cm_submenu->CheckMenuItem(1, MF_CHECKED | MF_BYPOSITION);

	cm_submenu = cm_submenu->GetSubMenu(1);
	cm_submenu->CheckMenuItem(0, MF_CHECKED | MF_BYPOSITION);

	//get the save-content
	save = CZeldaHWLSaveEditorGUIApp::save;

	if (save != nullptr)
	{
		for (int i = IDC_CHECK_CHARA_UNLOCK1; i <= IDC_CHECK_CHARA_UNLOCK29; i++)
		{
			GetDlgItem(i)->EnableWindow(true);
		}

		for (int i = IDC_BUTTON_CHARA_EDIT1; i <= IDC_BUTTON_CHARA_EDIT29; i++)
		{
			GetDlgItem(i)->EnableWindow(true);
		}

		this->calc_players();

	}
	else
	{
		for (int i = IDC_STATIC_CHARA1; i <= IDC_STATIC_CHARA29; i++)
		{
			SetDlgItemText(i, L"Chara");
		}

		for (int i = IDC_CHECK_CHARA_UNLOCK1; i <= IDC_CHECK_CHARA_UNLOCK29; i++)
		{
			((CButton*)GetDlgItem(i))->SetCheck(0);
			GetDlgItem(i)->EnableWindow(false);
		}

		for (int i = IDC_BUTTON_CHARA_EDIT1; i <= IDC_BUTTON_CHARA_EDIT29; i++)
		{
			GetDlgItem(i)->EnableWindow(false);
		}
	}
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZeldaEditCharaOverviewDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_CHARA_EDIT1, IDC_BUTTON_CHARA_EDIT29, &OnBnClickedEditButton)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHECK_CHARA_UNLOCK1, IDC_CHECK_CHARA_UNLOCK29, &OnBnClickedUnlockCheck)
	ON_BN_CLICKED(ID_SAVE, &CZeldaEditCharaOverviewDlg::OnBnClickedSave)
	ON_BN_CLICKED(ID_EXIT, &CZeldaEditCharaOverviewDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_CHARA_MAX_STATS_ALL, &CZeldaEditCharaOverviewDlg::OnBnClickedCharaMaxStatsAll)
	ON_BN_CLICKED(IDC_CHARA_UNLOCK_ALL, &CZeldaEditCharaOverviewDlg::OnBnClickedCharaUnlockAll)
	ON_COMMAND(ID_MENU_MAIN_EXIT, &CZeldaEditCharaOverviewDlg::OnMenuMainExit)
	ON_COMMAND(ID_MENU_EDIT_GENERAL, &CZeldaEditCharaOverviewDlg::OnMenuEditGeneral)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_OVERVIEW, &CZeldaEditCharaOverviewDlg::OnMenuEditCharactersOverview)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_STATS, &CZeldaEditCharaOverviewDlg::OnMenuEditCharactersStats)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_WEAPONS, &CZeldaEditCharaOverviewDlg::OnMenuEditCharactersWeapons)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_BRONZE, &CZeldaEditCharaOverviewDlg::OnMenuEditMaterialsBronze)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_SILVER, &CZeldaEditCharaOverviewDlg::OnMenuEditMaterialsSilver)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_GOLD, &CZeldaEditCharaOverviewDlg::OnMenuEditMaterialsGold)
	ON_COMMAND(ID_MENU_EDIT_FAIRYFOODS, &CZeldaEditCharaOverviewDlg::OnMenuEditFairyfoods)
	ON_COMMAND(ID_MENU_EDIT_AM_AVMAP, &CZeldaEditCharaOverviewDlg::OnMenuEditAmAvmap)
	ON_COMMAND(ID_MENU_EDIT_AM_GSMAP, &CZeldaEditCharaOverviewDlg::OnMenuEditAmGsmap)
	ON_COMMAND(ID_MENU_EDIT_AM_MQMAP, &CZeldaEditCharaOverviewDlg::OnMenuEditAmMqmap)
	ON_COMMAND(ID_MENU_EDIT_AM_TLMAP, &CZeldaEditCharaOverviewDlg::OnMenuEditAmTlmap)
	ON_COMMAND(ID_MENU_EDIT_AM_TMMAP, &CZeldaEditCharaOverviewDlg::OnMenuEditAmTmmap)
	ON_COMMAND(ID_MENU_EDIT_AM_MWWMAP, &CZeldaEditCharaOverviewDlg::OnMenuEditAmMwwmap)
	ON_COMMAND(ID_MENU_EDIT_AM_KIMAP, &CZeldaEditCharaOverviewDlg::OnMenuEditAmKimap)
	ON_COMMAND(ID_MENU_EDIT_AM_GTMAP, &CZeldaEditCharaOverviewDlg::OnMenuEditAmGtmap)
	ON_COMMAND(ID_MENU_EDIT_FAIRIES, &CZeldaEditCharaOverviewDlg::OnMenuEditFairies)
	ON_COMMAND(ID_MENU_EDIT_AM_LRMAP, &CZeldaEditCharaOverviewDlg::OnMenuEditAmLrmap)
END_MESSAGE_MAP()


void CZeldaEditCharaOverviewDlg::calc_players()
{
	int i_current_disabled_count = 0;
	int i_last_IDC_id = 0;

	for (int i = 0; i < HWLSaveEdit::HWLPlayer::vs_players.size(); i++)
	{
		if (save->get_player(i)->get_isDisabled())
		{
			i_current_disabled_count++;
			continue;
		}

		CString s_player_name(save->get_player(i)->get_name().c_str());

		bool b_player_is_unlock = save->get_player(i)->get_isUnlock();
		CButton *cb_check;

		SetDlgItemText(IDC_STATIC_CHARA1 + i - i_current_disabled_count, s_player_name + L": ");
		GetDlgItem(IDC_STATIC_CHARA1 + i - i_current_disabled_count)->EnableWindow(true);

		cb_check = (CButton*)GetDlgItem((IDC_CHECK_CHARA_UNLOCK1 + i - i_current_disabled_count));
		cb_check->SetCheck(b_player_is_unlock);

		i_last_IDC_id = IDC_STATIC_CHARA1 + i - i_current_disabled_count;
	}

	int i_to_disabled_charas = IDC_STATIC_CHARA29 - i_last_IDC_id;

	for (int i = 0; i < i_to_disabled_charas; i++)
	{
		SetDlgItemText(IDC_STATIC_CHARA29 - i, L"Chara: ");
		CButton *cb_check = (CButton*)GetDlgItem((IDC_CHECK_CHARA_UNLOCK29 - i));
		cb_check->SetCheck(0);

		GetDlgItem(IDC_STATIC_CHARA29 - i)->EnableWindow(false);
		GetDlgItem(IDC_CHECK_CHARA_UNLOCK29 - i)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_CHARA_EDIT29 - i)->EnableWindow(false);
	}
}

void CZeldaEditCharaOverviewDlg::save_players()
{
	if (save != nullptr)
	{
		int i_current_disabled_count = 0;
		for (int i = 0; i < HWLSaveEdit::HWLPlayer::vs_players.size(); i++)
		{
			if (save->get_player(i)->get_isDisabled())
			{
				i_current_disabled_count++;
				continue;
			}

			CButton *cb_check = (CButton*)GetDlgItem((IDC_CHECK_CHARA_UNLOCK1 + i - i_current_disabled_count));
			bool b_player_is_unlock = cb_check->GetCheck();

			save->get_player(i)->set_isUnlock(b_player_is_unlock);
			save->get_player(i)->save_Player();
		}

	}
}


void CZeldaEditCharaOverviewDlg::OnBnClickedEditButton(UINT nID)
{
	if (save != nullptr)
	{
		CButton *cb_edit = (CButton*)GetDlgItem(nID);
		
		int i_chara_id = nID - IDC_BUTTON_CHARA_EDIT1;
		int i_skipped_charas = 0;
		bool b_failure = false;

		if (i_chara_id >= 19)
		{
			i_skipped_charas += 2;
			i_chara_id += 2;

			if (save->get_player(i_chara_id)->get_isDisabled())
			{
				int i_old_chara_id = i_chara_id;
				i_skipped_charas++;

				for (int i = i_chara_id + 1; i < HWLSaveEdit::HWLPlayer::vs_players.size(); i++)
				{
					if (save->get_player(i)->get_isDisabled())
					{
						i_skipped_charas++;
						continue;
					}
					else
					{
						i_chara_id = i;
						break;
					}
				}

				if (i_old_chara_id == i_chara_id)
				{
					CString cs_info("This character is disabled, that mean you don't have the right Update/DLC installed to edit "
						"this character.");
					MessageBox(cs_info, L"Information", MB_OK | MB_ICONINFORMATION);
					b_failure = true;
				}
			}else
			{
				for (int i = 21; i < i_chara_id; i++)
				{
					if (save->get_player(i)->get_isDisabled())
					{
						i_skipped_charas++;
						i_chara_id++;
					}
				}
			}
		}


		if (!b_failure)
		{
			CZeldaEditCharaStatsDlg dlg(NULL, i_chara_id, i_skipped_charas);
			EndDialog(this->IDD);
			dlg.DoModal();
		}

	}
}

void CZeldaEditCharaOverviewDlg::OnBnClickedUnlockCheck(UINT nID)
{
	if (save != nullptr)
	{
		CButton *cb_check = (CButton*)GetDlgItem(nID);
		bool b_player_is_unlock = cb_check->GetCheck();

		if (b_player_is_unlock)
		{
			int i_chara_id = nID - IDC_CHECK_CHARA_UNLOCK1;
			bool b_failure = false;

			if (i_chara_id >= 19)
				i_chara_id += 2;

			if (save->get_player(i_chara_id)->get_isDisabled())
			{
				int i_old_chara_id = i_chara_id;

				for (int i = i_chara_id + 1; i < HWLSaveEdit::HWLPlayer::vs_players.size(); i++)
				{
					if (save->get_player(i)->get_isDisabled())
						continue;
					else
						i_chara_id = i;
					break;
				}

				if (i_old_chara_id == i_chara_id)
				{
					CString cs_info("This character is disabled, that mean you don't have the right Update/DLC installed to unlock "
						"this character.");
					MessageBox(cs_info, L"Information", MB_OK | MB_ICONINFORMATION);
					b_failure = true;
				}
			}

			if (!b_failure)
			{
				if (save->get_player(i_chara_id)->get_weapon_count(0) == 0)
				{
					save->get_player(i_chara_id)->get_weapon_slot(0, 0)->generate_default_weapon();
					save->get_player(i_chara_id)->get_weapon_slot(0, 0)->save_weapon();

					CString cs_info("This character hasn't a default weapon, so maybe he wasn't "
						"unlocked within the story yet. \n"
						"To really unlock this character, a default weapon was added automatically.");
					MessageBox(cs_info, L"Information", MB_OK | MB_ICONINFORMATION);
				}
			}
		}
	}
}

// CZeldaEditCharaOverviewDlg-Meldungshandler


void CZeldaEditCharaOverviewDlg::OnBnClickedSave()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		try
		{
			this->save_players();
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


void CZeldaEditCharaOverviewDlg::OnBnClickedExit()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CZeldaEditCharaOverviewDlg::OnOK();

}


void CZeldaEditCharaOverviewDlg::OnBnClickedCharaMaxStatsAll()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		for (int i = 0; i < HWLSaveEdit::HWLPlayer::vs_players.size(); i++)
		{
			if (save->get_player(i)->get_isDisabled())
				continue;


			save->get_player(i)->set_lvl(HWLSaveEdit::HWLPlayer::get_max_stati_value("LVL"));
			save->get_player(i)->set_exp(HWLSaveEdit::HWLPlayer::get_max_stati_value("EXP"));
			save->get_player(i)->set_atk(HWLSaveEdit::HWLPlayer::get_max_stati_value("ATK"));
			save->get_player(i)->set_hearts(HWLSaveEdit::HWLPlayer::get_max_stati_value("Hearts"));

			save->get_player(i)->save_Player();
		}

		this->UpdateData();

		CString str("Finish! All needed Values are updated.");
		MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
	}

}


void CZeldaEditCharaOverviewDlg::OnBnClickedCharaUnlockAll()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		bool b_no_weapon = false;
		for (int i = 0; i < HWLSaveEdit::HWLPlayer::vs_players.size(); i++)
		{
			if (save->get_player(i)->get_isDisabled())
				continue;

			save->get_player(i)->set_isUnlock(true);

			//Check if the character hasn't a default weapon
			if (save->get_player(i)->get_weapon_count(0) == 0)
			{
				b_no_weapon = true;
				save->get_player(i)->get_weapon_slot(0, 0)->generate_default_weapon();
				save->get_player(i)->get_weapon_slot(0, 0)->save_weapon();
			}

			save->get_player(i)->save_Player();
		}

		if (b_no_weapon)
		{

			CString cs_info("One or more characters haven't a default weapon, so maybe they wasn't "
				"unlocked within the story yet. \n"
				"To really unlock those characters, a default weapon was added automatically.");
			MessageBox(cs_info, L"Information", MB_OK | MB_ICONINFORMATION);
		}

		this->UpdateData();

		CString str("Finish! All needed Values are updated.");
		MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);

	}
}


void CZeldaEditCharaOverviewDlg::OnMenuMainExit()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaOverviewDlg::OnOK();

}


void CZeldaEditCharaOverviewDlg::OnMenuEditGeneral()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditGeneralDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaOverviewDlg::OnMenuEditCharactersOverview()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
}


void CZeldaEditCharaOverviewDlg::OnMenuEditCharactersStats()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaStatsDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaOverviewDlg::OnMenuEditCharactersWeapons()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaWeaponsDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaOverviewDlg::OnMenuEditMaterialsBronze()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 0);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaOverviewDlg::OnMenuEditMaterialsSilver()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaOverviewDlg::OnMenuEditMaterialsGold()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaOverviewDlg::OnMenuEditFairyfoods()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyFoods dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaOverviewDlg::OnMenuEditAmAvmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 0);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaOverviewDlg::OnMenuEditAmGsmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaOverviewDlg::OnMenuEditAmMqmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaOverviewDlg::OnMenuEditAmTlmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 3);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaOverviewDlg::OnMenuEditAmTmmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 4);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaOverviewDlg::OnMenuEditAmMwwmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 5);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaOverviewDlg::OnMenuEditAmKimap()
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


void CZeldaEditCharaOverviewDlg::OnMenuEditAmGtmap()
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

void CZeldaEditCharaOverviewDlg::OnMenuEditAmLrmap()
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


void CZeldaEditCharaOverviewDlg::OnMenuEditFairies()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}
