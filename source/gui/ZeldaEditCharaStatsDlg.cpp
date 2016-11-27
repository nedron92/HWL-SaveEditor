// ZeldaEditCharaStatsDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZeldaHWLSaveEditorGUI.h"
#include "ZeldaEditCharaStatsDlg.h"
#include "afxdialogex.h"


// CZeldaEditCharaStatsDlg-Dialogfeld

IMPLEMENT_DYNAMIC(CZeldaEditCharaStatsDlg, CDialogEx)

CZeldaEditCharaStatsDlg::CZeldaEditCharaStatsDlg(CWnd* pParent /*=NULL*/, int i_chara_id, int i_skipped_charas)
	: CDialogEx(CZeldaEditCharaStatsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->i_chara_id = i_chara_id;
	this->i_skipped_charas = i_skipped_charas;
}

CZeldaEditCharaStatsDlg::~CZeldaEditCharaStatsDlg()
{
}

BOOL CZeldaEditCharaStatsDlg::OnInitDialog()
{
	//calculate the disabled-Items and remove the Menu-Entry, if neccessary
	CZeldaHWLSaveEditorGUIApp::calc_disabled_MenuItems(GetMenu()->GetSubMenu(1));
	return CDialogEx::OnInitDialog();
}

void CZeldaEditCharaStatsDlg::DoDataExchange(CDataExchange* pDX)
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
	cm_submenu->CheckMenuItem(2, MF_CHECKED | MF_BYPOSITION);

	//get the save-content
	save = CZeldaHWLSaveEditorGUIApp::save;

	
	if (save != nullptr)
	{
		for (int i = IDC_CSTATS_PAGE_PREVIOUS; i <= IDC_BUTTON_CSTATS_EDIT_WEAPONS; i++)
		{
			GetDlgItem(i)->EnableWindow(true);
		}

		if (this->i_chara_id >= HWLSaveEdit::HWLPlayer::vs_players.size() || save->get_player(this->i_chara_id)->get_isDisabled())
		{
			this->i_skipped_charas = 0;
			this->i_chara_id = 0;
		}

		CString s_chara_count;
		s_chara_count.Format(L"%d / %d", (this->i_chara_id + 1) - this->i_skipped_charas, HWLSaveEdit::HWLPlayer::vs_players.size() - HWLSaveEdit::HWLPlayer::get_disabledPlayerCounter());
		SetDlgItemText(IDC_STATIC_CSTATS_PLAYER_COUNT, s_chara_count);

		if (this->i_chara_id <= 0)
			GetDlgItem(IDC_CSTATS_PAGE_PREVIOUS)->EnableWindow(false);

		if ((this->i_chara_id + 1) - this->i_skipped_charas >= HWLSaveEdit::HWLPlayer::vs_players.size() - HWLSaveEdit::HWLPlayer::get_disabledPlayerCounter())
			GetDlgItem(IDC_CSTATS_PAGE_NEXT)->EnableWindow(false);

		this->calc_stats();

	}
	else
	{
		SetDlgItemText(IDC_CSTATS_PLAYERNAME, L"");
		SetDlgItemText(IDC_STATIC_CSTATS_PLAYER_COUNT, L"00 / 99");
		SetDlgItemText(IDC_STATIC_CSTATS_WEAPONTYPES, L"0");
		SetDlgItemText(IDC_STATIC_CSTATS_USED_WEAPONS, L"00 / 99");

		for (int i = IDC_CSTATS_PAGE_PREVIOUS; i <= IDC_BUTTON_CSTATS_EDIT_WEAPONS; i++)
		{
			GetDlgItem(i)->EnableWindow(false);
		}

		for (int i = IDC_EDIT_CSTATS_CHARA_LVL; i <= IDC_EDIT_CSTATS_CHARA_HEARTS; i++)
		{
			SetDlgItemText(i, L"");
		}
	}
	
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZeldaEditCharaStatsDlg, CDialogEx)
	ON_BN_CLICKED(ID_EXIT, &CZeldaEditCharaStatsDlg::OnBnClickedExit)
	ON_BN_CLICKED(ID_SAVE, &CZeldaEditCharaStatsDlg::OnBnClickedSave)
	ON_COMMAND(ID_MENU_ABOUT, &CZeldaEditCharaStatsDlg::OnMenuAbout)
	ON_COMMAND(ID_MENU_EDIT_GENERAL, &CZeldaEditCharaStatsDlg::OnMenuEditGeneral)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_STATS, &CZeldaEditCharaStatsDlg::OnMenuEditCharactersStats)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_BRONZE, &CZeldaEditCharaStatsDlg::OnMenuEditMaterialsBronze)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_SILVER, &CZeldaEditCharaStatsDlg::OnMenuEditMaterialsSilver)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_GOLD, &CZeldaEditCharaStatsDlg::OnMenuEditMaterialsGold)
	ON_COMMAND(ID_MENU_MAIN_EXIT, &CZeldaEditCharaStatsDlg::OnMenuMainExit)
	ON_COMMAND(ID_MENU_EDIT_FAIRYFOODS, &CZeldaEditCharaStatsDlg::OnMenuEditFairyfoods)
	ON_COMMAND(ID_MENU_EDIT_AM_AVMAP, &CZeldaEditCharaStatsDlg::OnMenuEditAmAvmap)
	ON_COMMAND(ID_MENU_EDIT_AM_GSMAP, &CZeldaEditCharaStatsDlg::OnMenuEditAmGsmap)
	ON_COMMAND(ID_MENU_EDIT_AM_MQMAP, &CZeldaEditCharaStatsDlg::OnMenuEditAmMqmap)
	ON_COMMAND(ID_MENU_EDIT_AM_TLMAP, &CZeldaEditCharaStatsDlg::OnMenuEditAmTlmap)
	ON_COMMAND(ID_MENU_EDIT_AM_TMMAP, &CZeldaEditCharaStatsDlg::OnMenuEditAmTmmap)
	ON_COMMAND(ID_MENU_EDIT_FAIRIES, &CZeldaEditCharaStatsDlg::OnMenuEditFairies)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_WEAPONS, &CZeldaEditCharaStatsDlg::OnMenuEditCharactersWeapons)
ON_COMMAND(ID_MENU_EDIT_AM_MWWMAP, &CZeldaEditCharaStatsDlg::OnMenuEditAmMwwmap)
ON_COMMAND(ID_MENU_EDIT_AM_KIMAP, &CZeldaEditCharaStatsDlg::OnMenuEditAmKimap)
ON_COMMAND(ID_MENU_EDIT_AM_GTMAP, &CZeldaEditCharaStatsDlg::OnMenuEditAmGtmap)
ON_COMMAND(ID_MENU_EDIT_CHARACTERS_OVERVIEW, &CZeldaEditCharaStatsDlg::OnMenuEditCharactersOverview)
ON_BN_CLICKED(IDC_BUTTON_CSTATS_EDIT_WEAPONS, &CZeldaEditCharaStatsDlg::OnBnClickedButtonCstatsEditWeapons)
ON_BN_CLICKED(IDC_BUTTON_CSTATS_MAX_STATS_USED_WEAPONS, &CZeldaEditCharaStatsDlg::OnBnClickedButtonCstatsMaxStatsUsedWeapons)
ON_BN_CLICKED(IDC_CSTATS_CHARA_MAX_STATS, &CZeldaEditCharaStatsDlg::OnBnClickedCstatsCharaMaxStats)
ON_BN_CLICKED(IDC_CSTATS_PAGE_PREVIOUS, &CZeldaEditCharaStatsDlg::OnBnClickedCstatsPagePrevious)
ON_BN_CLICKED(IDC_CSTATS_PAGE_NEXT, &CZeldaEditCharaStatsDlg::OnBnClickedCstatsPageNext)
ON_EN_CHANGE(IDC_EDIT_CSTATS_CHARA_LVL, &CZeldaEditCharaStatsDlg::OnEnChangeEditCstatsCharaLvl)
ON_EN_CHANGE(IDC_EDIT_CSTATS_CHARA_EXP, &CZeldaEditCharaStatsDlg::OnEnChangeEditCstatsCharaExp)
ON_EN_CHANGE(IDC_EDIT_CSTATS_CHARA_ATK, &CZeldaEditCharaStatsDlg::OnEnChangeEditCstatsCharaAtk)
ON_EN_CHANGE(IDC_EDIT_CSTATS_CHARA_HEARTS, &CZeldaEditCharaStatsDlg::OnEnChangeEditCstatsCharaHearts)
ON_BN_CLICKED(IDC_CHECK_CSTATS_CHARA_UNLOCK, &CZeldaEditCharaStatsDlg::OnBnClickedCheckCstatsCharaUnlock)
ON_COMMAND(ID_MENU_EDIT_AM_LRMAP, &CZeldaEditCharaStatsDlg::OnMenuEditAmLrmap)
END_MESSAGE_MAP()


// CZeldaEditCharaStatsDlg-Meldungshandler
void CZeldaEditCharaStatsDlg::OnBnClickedExit()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CZeldaEditCharaStatsDlg::OnOK();
}


void CZeldaEditCharaStatsDlg::OnBnClickedSave()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		try
		{
			this->save_stats();
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

void CZeldaEditCharaStatsDlg::calc_stats()
{
	if (save->get_player(this->i_chara_id)->get_isDisabled())
		this->i_chara_id = 0;

	shared_ptr<HWLSaveEdit::HWLPlayer> hwlp = save->get_player(this->i_chara_id);
	
	CString s_player_name(hwlp->get_name().c_str());

	CString s_player_lvl;
	s_player_lvl.Format(L"%d", hwlp->get_lvl());

	CString s_player_exp;
	s_player_exp.Format(L"%d", hwlp->get_exp());

	CString s_player_atk;
	s_player_atk.Format(L"%d", hwlp->get_atk());

	CString s_player_hearts;
	s_player_hearts.Format(L"%d", hwlp->get_hearts());

	bool b_player_is_unlock = hwlp->get_isUnlock();

	CString s_player_weaponTypes;
	s_player_weaponTypes.Format(L"%d", hwlp->get_weapon_type_count() - hwlp->get_disabledWeaponTypeCounter());

	CString s_player_usedWeapons;

	int i_usedWeapons = 0;
	int i_usedWeaponsMax = 0;
	for (int i = 0; i < hwlp->get_weapon_type_count(); i++)
	{
		if (hwlp->get_isWeaponTypeDisabled(i))
			continue;

		i_usedWeapons += hwlp->get_weapon_count(i);
		i_usedWeaponsMax += HWLSaveEdit::HWLPlayer::playerWeaponSlotsMax;
	}

	s_player_usedWeapons.Format(L"%d / %d", i_usedWeapons, i_usedWeaponsMax);

	//Setting
	CButton *cb_check;

	SetDlgItemText(IDC_CSTATS_PLAYERNAME, s_player_name);
	SetDlgItemText(IDC_EDIT_CSTATS_CHARA_LVL, s_player_lvl);
	SetDlgItemText(IDC_EDIT_CSTATS_CHARA_EXP, s_player_exp);
	SetDlgItemText(IDC_EDIT_CSTATS_CHARA_ATK, s_player_atk);
	SetDlgItemText(IDC_EDIT_CSTATS_CHARA_HEARTS, s_player_hearts);

	cb_check = (CButton*)GetDlgItem(IDC_CHECK_CSTATS_CHARA_UNLOCK);
	cb_check->SetCheck(b_player_is_unlock);

	SetDlgItemText(IDC_STATIC_CSTATS_WEAPONTYPES, s_player_weaponTypes);
	SetDlgItemText(IDC_STATIC_CSTATS_USED_WEAPONS, s_player_usedWeapons);

	//Set Max Chara-Input
	CEdit *e_test = (CEdit*)GetDlgItem(IDC_EDIT_CSTATS_CHARA_LVL);
	CString cs_max_chars;
	cs_max_chars.Format(L"%d", HWLSaveEdit::HWLPlayer::get_max_stati_value("LVL"));
	e_test->SetLimitText(cs_max_chars.GetLength() + 1);

	e_test = (CEdit*)GetDlgItem(IDC_EDIT_CSTATS_CHARA_EXP);
	cs_max_chars.Format(L"%d", HWLSaveEdit::HWLPlayer::get_max_stati_value("EXP"));
	e_test->SetLimitText(cs_max_chars.GetLength() + 1);

	e_test = (CEdit*)GetDlgItem(IDC_EDIT_CSTATS_CHARA_ATK);
	cs_max_chars.Format(L"%d", HWLSaveEdit::HWLPlayer::get_max_stati_value("ATK"));
	e_test->SetLimitText(cs_max_chars.GetLength() + 1);

	e_test = (CEdit*)GetDlgItem(IDC_EDIT_CSTATS_CHARA_HEARTS);
	cs_max_chars.Format(L"%d", HWLSaveEdit::HWLPlayer::get_max_stati_value("HEARTS"));
	e_test->SetLimitText(cs_max_chars.GetLength() + 1);
}

void CZeldaEditCharaStatsDlg::save_stats()
{
	if (save != nullptr)
	{
		CString s_player_lvl, s_player_exp, s_player_atk, s_player_hearts;

		GetDlgItemText(IDC_EDIT_CSTATS_CHARA_LVL, s_player_lvl);
		int i_player_lvl = _wtof(s_player_lvl);

		GetDlgItemText(IDC_EDIT_CSTATS_CHARA_EXP, s_player_exp);
		int i_player_exp = _wtof(s_player_exp);

		GetDlgItemText(IDC_EDIT_CSTATS_CHARA_ATK, s_player_atk);
		int i_player_atk = _wtof(s_player_atk);

		GetDlgItemText(IDC_EDIT_CSTATS_CHARA_HEARTS, s_player_hearts);
		int i_player_hearts = _wtof(s_player_hearts);

		CButton *cb_check = (CButton*)GetDlgItem(IDC_CHECK_CSTATS_CHARA_UNLOCK);
		bool b_player_is_unlock = cb_check->GetCheck();

		save->get_player(this->i_chara_id)->set_lvl(i_player_lvl);
		save->get_player(this->i_chara_id)->set_exp(i_player_exp);
		save->get_player(this->i_chara_id)->set_atk(i_player_atk);
		save->get_player(this->i_chara_id)->set_hearts(i_player_hearts);
		save->get_player(this->i_chara_id)->set_isUnlock(b_player_is_unlock);
		save->get_player(this->i_chara_id)->save_Player();

	}

}


void CZeldaEditCharaStatsDlg::OnMenuAbout()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaAboutDlg about;
	about.DoModal();
}


void CZeldaEditCharaStatsDlg::OnMenuEditGeneral()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditGeneralDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditCharaStatsDlg::OnMenuEditCharactersStats()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
}


void CZeldaEditCharaStatsDlg::OnMenuEditMaterialsBronze()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 0);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaStatsDlg::OnMenuEditMaterialsSilver()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaStatsDlg::OnMenuEditMaterialsGold()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaStatsDlg::OnMenuMainExit()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaStatsDlg::OnOK();
}


void CZeldaEditCharaStatsDlg::OnMenuEditFairyfoods()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyFoods dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaStatsDlg::OnMenuEditAmAvmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 0);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaStatsDlg::OnMenuEditAmGsmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaStatsDlg::OnMenuEditAmMqmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditCharaStatsDlg::OnMenuEditAmTlmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 3);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditCharaStatsDlg::OnMenuEditAmTmmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 4);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditCharaStatsDlg::OnMenuEditAmMwwmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 5);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditCharaStatsDlg::OnMenuEditAmKimap()
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


void CZeldaEditCharaStatsDlg::OnMenuEditAmGtmap()
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

void CZeldaEditCharaStatsDlg::OnMenuEditAmLrmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 8);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditCharaStatsDlg::OnMenuEditFairies()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaStatsDlg::OnMenuEditCharactersWeapons()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaWeaponsDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditCharaStatsDlg::OnMenuEditCharactersOverview()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaOverviewDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditCharaStatsDlg::OnBnClickedButtonCstatsEditWeapons()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CZeldaEditCharaWeaponsDlg dlg(NULL, this->i_chara_id, this->i_skipped_charas);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaStatsDlg::OnBnClickedButtonCstatsMaxStatsUsedWeapons()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		for (int i = 0; i < save->get_player(this->i_chara_id)->get_weapon_type_count(); i++)
		{
			if (save->get_player(this->i_chara_id)->get_isWeaponTypeDisabled(i))
				continue;

			int i_weapon_count = save->get_player(this->i_chara_id)->get_weapon_count(i);

			for (int j = 0; j < i_weapon_count; j++)
			{
				std::shared_ptr<HWLSaveEdit::HWLWeapon> hwlpw_tmp = save->get_player(this->i_chara_id)->get_weapon_slot(i, j);

				if (hwlpw_tmp->get_id() != HWLSaveEdit::HWLWeapon::vi_playerWeaponTypeHexValues[4])
				{
					hwlpw_tmp->change_lvl(HWLSaveEdit::HWLWeapon::weaponLVLMax);
					hwlpw_tmp->change_multi_element_state(true);
					hwlpw_tmp->change_damage_base(HWLSaveEdit::HWLWeapon::weaponDamageBaseMax);
					hwlpw_tmp->change_stars(HWLSaveEdit::HWLWeapon::weaponStarsMax);
					hwlpw_tmp->save_weapon();
				}else{
					hwlpw_tmp->change_stars(HWLSaveEdit::HWLWeapon::weaponStarsMax);
					hwlpw_tmp->save_weapon();
				}
			}

			save->get_player(this->i_chara_id)->save_Player();
		}

		CString str("Finish! All needed Values are updated.");
		MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
	}
}


void CZeldaEditCharaStatsDlg::OnBnClickedCstatsCharaMaxStats()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		save->get_player(this->i_chara_id)->set_lvl(HWLSaveEdit::HWLPlayer::get_max_stati_value("LVL"));
		save->get_player(this->i_chara_id)->set_exp(HWLSaveEdit::HWLPlayer::get_max_stati_value("EXP"));
		save->get_player(this->i_chara_id)->set_atk(HWLSaveEdit::HWLPlayer::get_max_stati_value("ATK"));
		save->get_player(this->i_chara_id)->set_hearts(HWLSaveEdit::HWLPlayer::get_max_stati_value("HEARTS"));
		save->get_player(this->i_chara_id)->set_isUnlock(true);
		save->get_player(this->i_chara_id)->save_Player();

		this->UpdateData();

		CString str("Finish! All needed Values are updated.");
		MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
	}
}


void CZeldaEditCharaStatsDlg::OnBnClickedCstatsPagePrevious()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_stats();

	int i_old_chara_id = this->i_chara_id;
	for (int i = this->i_chara_id - 1; i > 0; i--)
	{
		if (save->get_player(i)->get_isDisabled())
		{
			if (this->i_skipped_charas > 0)
				this->i_skipped_charas--;
			continue;
		}
		else
		{
			this->i_chara_id = i;
			break;
		}
	}

	if (this->i_chara_id == i_old_chara_id)
		this->i_chara_id = 0;

	this->UpdateData();
}


void CZeldaEditCharaStatsDlg::OnBnClickedCstatsPageNext()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_stats();

	int i_old_chara_id = this->i_chara_id;
	for (int i = this->i_chara_id + 1; i < HWLSaveEdit::HWLPlayer::vs_players.size(); i++)
	{
		if (save->get_player(i)->get_isDisabled())
		{
			this->i_skipped_charas++;
			continue;
		}
		else
		{
			this->i_chara_id = i;
			break;
		}
	}

	if (this->i_chara_id == i_old_chara_id)
		this->i_chara_id = 0;

	this->UpdateData();
}


void CZeldaEditCharaStatsDlg::OnEnChangeEditCstatsCharaLvl()
{
	// TODO:  Falls dies ein RICHEDIT-Steuerelement ist, wird das Kontrollelement
	// diese Benachrichtigung nicht senden, es sei denn, Sie überschreiben die CDialogEx::OnInitDialog()-
	// Funktion und rufen CRichEditCtrl().SetEventMask() auf
	// mit dem ENM_CHANGE-Flag ORed in der Eingabe.

	// TODO:  Fügen Sie hier Ihren Code für die Kontrollbenachrichtigungsbehandlung ein.
	if (save != nullptr)
	{
		CString test;
		CEdit *e_test = (CEdit*)GetDlgItem(IDC_EDIT_CSTATS_CHARA_LVL);
		CString cs_max_chars;
		cs_max_chars.Format(L"%d", HWLSaveEdit::HWLPlayer::get_max_stati_value("LVL"));
		e_test->SetLimitText(cs_max_chars.GetLength() + 1);
		GetDlgItemText(IDC_EDIT_CSTATS_CHARA_LVL, test);
		int i_test = _wtoi(test);

		if (i_test > HWLSaveEdit::HWLPlayer::get_max_stati_value("LVL"))
		{
			test.Format(L"%d", HWLSaveEdit::HWLPlayer::get_max_stati_value("LVL"));
			SetDlgItemText(IDC_EDIT_CSTATS_CHARA_LVL, test);
			e_test->SetLimitText(cs_max_chars.GetLength());
		}

		save->get_player(this->i_chara_id)->set_lvl(i_test);
		save->get_player(this->i_chara_id)->save_Player();
	}
}


void CZeldaEditCharaStatsDlg::OnEnChangeEditCstatsCharaExp()
{
	// TODO:  Falls dies ein RICHEDIT-Steuerelement ist, wird das Kontrollelement
	// diese Benachrichtigung nicht senden, es sei denn, Sie überschreiben die CDialogEx::OnInitDialog()-
	// Funktion und rufen CRichEditCtrl().SetEventMask() auf
	// mit dem ENM_CHANGE-Flag ORed in der Eingabe.

	// TODO:  Fügen Sie hier Ihren Code für die Kontrollbenachrichtigungsbehandlung ein.
	if (save != nullptr)
	{
		CString test;
		CEdit *e_test = (CEdit*)GetDlgItem(IDC_EDIT_CSTATS_CHARA_EXP);
		CString cs_max_chars;
		cs_max_chars.Format(L"%d", HWLSaveEdit::HWLPlayer::get_max_stati_value("EXP"));
		e_test->SetLimitText(cs_max_chars.GetLength() + 1);
		GetDlgItemText(IDC_EDIT_CSTATS_CHARA_EXP, test);
		int i_test = _wtoi(test);

		if (i_test > HWLSaveEdit::HWLPlayer::get_max_stati_value("EXP"))
		{
			test.Format(L"%d", HWLSaveEdit::HWLPlayer::get_max_stati_value("EXP"));
			SetDlgItemText(IDC_EDIT_CSTATS_CHARA_EXP, test);
			e_test->SetLimitText(cs_max_chars.GetLength());
		}

		save->get_player(this->i_chara_id)->set_exp(i_test);
		save->get_player(this->i_chara_id)->save_Player();
	}
}


void CZeldaEditCharaStatsDlg::OnEnChangeEditCstatsCharaAtk()
{
	// TODO:  Falls dies ein RICHEDIT-Steuerelement ist, wird das Kontrollelement
	// diese Benachrichtigung nicht senden, es sei denn, Sie überschreiben die CDialogEx::OnInitDialog()-
	// Funktion und rufen CRichEditCtrl().SetEventMask() auf
	// mit dem ENM_CHANGE-Flag ORed in der Eingabe.

	// TODO:  Fügen Sie hier Ihren Code für die Kontrollbenachrichtigungsbehandlung ein.
	if (save != nullptr)
	{
		CString test;
		CEdit *e_test = (CEdit*)GetDlgItem(IDC_EDIT_CSTATS_CHARA_ATK);
		CString cs_max_chars;
		cs_max_chars.Format(L"%d", HWLSaveEdit::HWLPlayer::get_max_stati_value("ATK"));
		e_test->SetLimitText(cs_max_chars.GetLength() + 1);
		GetDlgItemText(IDC_EDIT_CSTATS_CHARA_ATK, test);
		int i_test = _wtoi(test);

		if (i_test > HWLSaveEdit::HWLPlayer::get_max_stati_value("ATK"))
		{
			test.Format(L"%d", HWLSaveEdit::HWLPlayer::get_max_stati_value("ATK"));
			SetDlgItemText(IDC_EDIT_CSTATS_CHARA_ATK, test);
			e_test->SetLimitText(cs_max_chars.GetLength());
		}

		save->get_player(this->i_chara_id)->set_atk(i_test);
		save->get_player(this->i_chara_id)->save_Player();
	}
}


void CZeldaEditCharaStatsDlg::OnEnChangeEditCstatsCharaHearts()
{
	// TODO:  Falls dies ein RICHEDIT-Steuerelement ist, wird das Kontrollelement
	// diese Benachrichtigung nicht senden, es sei denn, Sie überschreiben die CDialogEx::OnInitDialog()-
	// Funktion und rufen CRichEditCtrl().SetEventMask() auf
	// mit dem ENM_CHANGE-Flag ORed in der Eingabe.

	// TODO:  Fügen Sie hier Ihren Code für die Kontrollbenachrichtigungsbehandlung ein.
	if (save != nullptr)
	{
		CString test;
		CEdit *e_test = (CEdit*)GetDlgItem(IDC_EDIT_CSTATS_CHARA_HEARTS);
		CString cs_max_chars;
		cs_max_chars.Format(L"%d", HWLSaveEdit::HWLPlayer::get_max_stati_value("HEARTS"));
		e_test->SetLimitText(cs_max_chars.GetLength() + 1);
		GetDlgItemText(IDC_EDIT_CSTATS_CHARA_HEARTS, test);
		int i_test = _wtoi(test);

		if (i_test > HWLSaveEdit::HWLPlayer::get_max_stati_value("HEARTS"))
		{
			test.Format(L"%d", HWLSaveEdit::HWLPlayer::get_max_stati_value("HEARTS"));
			SetDlgItemText(IDC_EDIT_CSTATS_CHARA_HEARTS, test);
			e_test->SetLimitText(cs_max_chars.GetLength());
		}

		save->get_player(this->i_chara_id)->set_hearts(i_test);
		save->get_player(this->i_chara_id)->save_Player();
	}
}


void CZeldaEditCharaStatsDlg::OnBnClickedCheckCstatsCharaUnlock()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		save->get_player(this->i_chara_id)->set_isUnlock(true);

		//Check if the character hasn't a default weapon
		if (save->get_player(this->i_chara_id)->get_weapon_count(0) == 0)
		{
			save->get_player(this->i_chara_id)->get_weapon_slot(0, 0)->generate_default_weapon();
			save->get_player(this->i_chara_id)->get_weapon_slot(0, 0)->save_weapon();

			CString cs_info("This character hasen't a default weapon, so maybe it wasn't "
				"unlocked within the story yet. \n"
				"To really unlock this character, a default weapon was added automatically.");
			MessageBox(cs_info, L"Information", MB_OK | MB_ICONINFORMATION);
		}

		save->get_player(this->i_chara_id)->save_Player();
		this->UpdateData();
	}
}