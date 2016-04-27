// ZeldaEditCharaWeaponsDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZeldaHWLSaveEditorGUI.h"
#include "ZeldaEditCharaWeaponsDlg.h"
#include "afxdialogex.h"


// CZeldaEditCharaWeaponsDlg-Dialogfeld

IMPLEMENT_DYNAMIC(CZeldaEditCharaWeaponsDlg, CDialogEx)

CZeldaEditCharaWeaponsDlg::CZeldaEditCharaWeaponsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZeldaEditCharaWeaponsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->i_chara_id = this->i_weapon_type = this->i_weapon_slot = 0;
}

CZeldaEditCharaWeaponsDlg::~CZeldaEditCharaWeaponsDlg()
{
}

BOOL CZeldaEditCharaWeaponsDlg::OnInitDialog()
{
	//Set te Names of the Skills-Slot 1 to Slot 8
	for (int i = IDC_COMBO_CWEAPON_SKILLS_SLOT_1; i <= IDC_COMBO_CWEAPON_SKILLS_SLOT_8; i++)
	{
		CComboBox *cb_skill = (CComboBox*)GetDlgItem(i);

		for (int j = 0; j < HWLSaveEdit::HWLWeapon::weaponSkillNames.size(); j++)
		{
			CString cs_skill_name(HWLSaveEdit::HWLWeapon::weaponSkillNames[j].c_str());
			cb_skill->InsertString(j,cs_skill_name);
		}
	}

	//Set the Dropdowns for Stars and Level
	CComboBox *cb_stars = (CComboBox*)GetDlgItem(IDC_COMBO_CWEAPON_STARS);
	CComboBox *cb_level = (CComboBox*)GetDlgItem(IDC_COMBO_CWEAPON_LEVEL);

	for (int i = 0; i <= HWLSaveEdit::HWLWeapon::weaponStarsMax; i++)
	{
		CString cs_stars;
		cs_stars.Format(L"%d", i);
		cb_stars->InsertString(i,cs_stars);
	}

	for (int i = 1; i <= HWLSaveEdit::HWLWeapon::weaponLVLMax; i++)
	{
		CString cs_level;
		cs_level.Format(L"%d", i);
		cb_level->InsertString(-1,cs_level);
	}

	this->UpdateData();
	return CDialogEx::OnInitDialog();
}

void CZeldaEditCharaWeaponsDlg::DoDataExchange(CDataExchange* pDX)
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
	cm_submenu->CheckMenuItem(1, MF_CHECKED | MF_BYPOSITION);

	//own inits
	save = CZeldaHWLSaveEditorGUIApp::save;

	if (save != nullptr)
	{
		int i_unused_charas = 0;
		for (int i = 0; i < HWLSaveEdit::HWLPlayer::vs_players.size(); i++)
		{
			CString s_name(save->get_player(i)->get_name().c_str());
			if (s_name == L"???")
			{
				i_unused_charas++;
				continue;
			}
		}

		std::shared_ptr<HWLSaveEdit::HWLWeapon> hwlpw = save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot);

		//Chara-Choose activate
		CString s_chara_count;
		int i_unused_charas_now = 0;
		for (int i = 0; i < this->i_chara_id; i++)
		{
			CString s_name(save->get_player(i)->get_name().c_str());
			if (s_name == L"???")
			{
				i_unused_charas_now++;
			}
		}

		s_chara_count.Format(L"%d / %d", this->i_chara_id + 1 - i_unused_charas_now, HWLSaveEdit::HWLPlayer::vs_players.size() - i_unused_charas);
		SetDlgItemText(IDC_STATIC_CWEAPON_CHARA_COUNT, s_chara_count);
		GetDlgItem(IDC_CWEAPON_CHAR_PAGE_PREVIOUS)->EnableWindow(true);
		GetDlgItem(IDC_CWEAPON_CHAR_PAGE_NEXT)->EnableWindow(true);

		if (this->i_chara_id + 1 <= 1)
			GetDlgItem(IDC_CWEAPON_CHAR_PAGE_PREVIOUS)->EnableWindow(false);
		else
			GetDlgItem(IDC_CWEAPON_CHAR_PAGE_PREVIOUS)->EnableWindow(true);

		if (this->i_chara_id + 1 >= HWLSaveEdit::HWLPlayer::vs_players.size())
			GetDlgItem(IDC_CWEAPON_CHAR_PAGE_NEXT)->EnableWindow(false);
		else
			GetDlgItem(IDC_CWEAPON_CHAR_PAGE_NEXT)->EnableWindow(true);

		//Weapon-Type activate
		CString s_type_count;
		s_type_count.Format(L"%d / %d", this->i_weapon_type + 1, HWLSaveEdit::HWLWeapon::vi_playerWeaponTypeCount[this->i_chara_id]);
		SetDlgItemText(IDC_STATIC_CWEAPON_TYPE_COUNT, s_type_count);
		GetDlgItem(IDC_CWEAPON_TYPE_PAGE_PREVIOUS)->EnableWindow(true);
		GetDlgItem(IDC_CWEAPON_TYPE_PAGE_NEXT)->EnableWindow(true);

		if (this->i_weapon_type + 1 <= 1)
			GetDlgItem(IDC_CWEAPON_TYPE_PAGE_PREVIOUS)->EnableWindow(false);
		else
			GetDlgItem(IDC_CWEAPON_TYPE_PAGE_PREVIOUS)->EnableWindow(true);

		if (this->i_weapon_type + 1 >= HWLSaveEdit::HWLWeapon::vi_playerWeaponTypeCount[this->i_chara_id])
			GetDlgItem(IDC_CWEAPON_TYPE_PAGE_NEXT)->EnableWindow(false);
		else
			GetDlgItem(IDC_CWEAPON_TYPE_PAGE_NEXT)->EnableWindow(true);

		//Weapon-Slot activate
		CString s_weapon_slot_count;
		if (hwlpw->get_id() == HWLSaveEdit::HWLWeapon::vi_playerWeaponTypeHexValues[4] || (this->i_weapon_type == 4 && this->i_chara_id == 0))
			s_weapon_slot_count.Format(L"%d / %d", this->i_weapon_slot + 1, this->i_weapon_slot + 1);
		else
			s_weapon_slot_count.Format(L"%d / %d", this->i_weapon_slot + 1, HWLSaveEdit::HWLPlayer::playerWeaponSlotsMax);

		SetDlgItemText(IDC_STATIC_CWEAPON_SLOT_COUNT, s_weapon_slot_count);
		GetDlgItem(IDC_CWEAPON_SLOT_PAGE_PREVIOUS)->EnableWindow(true);
		GetDlgItem(IDC_CWEAPON_SLOT_PAGE_NEXT)->EnableWindow(true);

		if (this->i_weapon_slot+1 <= 1)
			GetDlgItem(IDC_CWEAPON_SLOT_PAGE_PREVIOUS)->EnableWindow(false);
		else
			GetDlgItem(IDC_CWEAPON_SLOT_PAGE_PREVIOUS)->EnableWindow(true);

		if (hwlpw->get_id() == HWLSaveEdit::HWLWeapon::vi_playerWeaponTypeHexValues[4] || (this->i_weapon_type == 4 && this->i_chara_id == 0))
		{
			GetDlgItem(IDC_CWEAPON_SLOT_PAGE_NEXT)->EnableWindow(false);
		}
		else{
			if (this->i_weapon_slot + 1 >= HWLSaveEdit::HWLPlayer::playerWeaponSlotsMax)
				GetDlgItem(IDC_CWEAPON_SLOT_PAGE_NEXT)->EnableWindow(false);
			else
				GetDlgItem(IDC_CWEAPON_SLOT_PAGE_NEXT)->EnableWindow(true);
		}

		for (int i = IDC_COMBO_CWEAPON_SKILLS_SLOT_1; i <= IDC_COMBO_CWEAPON_SKILLS_SLOT_8; i++)
		{
			CComboBox *cb_skill = (CComboBox*)GetDlgItem(i);
			cb_skill->Clear();
		}

		//Deactivate all changeable weapon-stats, if we have an unused weapon
		if (hwlpw->get_IsUnused())
		{
			//Deactivate Reset-Kills and Reset-Skills
			GetDlgItem(IDC_CWEAPON_RESET_KILLS)->EnableWindow(false);
			GetDlgItem(IDC_CWEAPON_RESET_SKILLS)->EnableWindow(false);

			//Skill-Kills Slot1 to Damage-Base deactivate and set current content to nothing
			for (int i = IDC_EDIT_CWEAPON_KILLS_SLOT_1; i <= IDC_EDIT_CWEAPON_DAMAGE_BASE; i++)
			{
				GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
				GetDlgItem(i)->EnableWindow(false);
			}

			//Deactivate the other Stats
			for (int i = IDC_COMBO_CWEAPON_STARS; i <= IDC_CHECK_CWEAPON_LEGENDARY; i++)
			{
				GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
				GetDlgItem(i)->EnableWindow(false);
			}

			//Deactivate the Skills-Slot 1 to Slot 8
			for (int i = IDC_COMBO_CWEAPON_SKILLS_SLOT_1; i <= IDC_COMBO_CWEAPON_SKILLS_SLOT_8; i++)
			{
				GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
				GetDlgItem(i)->EnableWindow(false);
			}

			//Deactivate Delete-Button and Activate Generate-Button
			GetDlgItem(IDC_CWEAPON_DELETE_WEAPON)->ShowWindow(SW_SHOWNORMAL);
			GetDlgItem(IDC_CWEAPON_DELETE_WEAPON)->EnableWindow(false);
			GetDlgItem(IDC_CWEAPON_DEFAULT_WEAPON)->ShowWindow(SW_SHOWNORMAL);
			GetDlgItem(IDC_CWEAPON_DEFAULT_WEAPON)->EnableWindow(true);
		}else
		{
			//Activate Reset-Kills and Reset-Skills
			GetDlgItem(IDC_CWEAPON_RESET_KILLS)->EnableWindow(true);
			GetDlgItem(IDC_CWEAPON_RESET_SKILLS)->EnableWindow(true);

			//Skill-Kills Slot1 to Damage-Base activate
			for (int i = IDC_EDIT_CWEAPON_KILLS_SLOT_1; i <= IDC_EDIT_CWEAPON_KILLS_SLOT_8; i++)
			{
				GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
				GetDlgItem(i)->EnableWindow(true);
			}

			//Check if we have an legendary weapon, deactivate Damage-Base if yes
			GetDlgItem(IDC_EDIT_CWEAPON_DAMAGE_BASE)->ShowWindow(SW_SHOWNORMAL);
			if (hwlpw->get_state())
				GetDlgItem(IDC_EDIT_CWEAPON_DAMAGE_BASE)->EnableWindow(false);
			else
				GetDlgItem(IDC_EDIT_CWEAPON_DAMAGE_BASE)->EnableWindow(true);

			//Check if we have The Master Sword, and if yes, deactivate some Stats
			if (hwlpw->get_id() == HWLSaveEdit::HWLWeapon::vi_playerWeaponTypeHexValues[4])
			{
				GetDlgItem(IDC_COMBO_CWEAPON_STARS)->EnableWindow(true);

				//Deactivate the other Stats
				for (int i = IDC_COMBO_CWEAPON_LEVEL; i <= IDC_CHECK_CWEAPON_LEGENDARY; i++)
				{
					GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
					GetDlgItem(i)->EnableWindow(false);
				}
			}else
			{
				//Activate the other Stats
				for (int i = IDC_COMBO_CWEAPON_STARS; i <= IDC_CHECK_CWEAPON_LEGENDARY; i++)
				{
					GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
					GetDlgItem(i)->EnableWindow(true);
				}
			}


			//Activate the Skills-Slot 1 to Slot 8
			for (int i = IDC_COMBO_CWEAPON_SKILLS_SLOT_1; i <= IDC_COMBO_CWEAPON_SKILLS_SLOT_8; i++)
			{
				GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
				GetDlgItem(i)->EnableWindow(true);
			}

			//Activate Generate and Delete-Buttons
			GetDlgItem(IDC_CWEAPON_DEFAULT_WEAPON)->ShowWindow(SW_SHOWNORMAL);
			GetDlgItem(IDC_CWEAPON_DEFAULT_WEAPON)->EnableWindow(true);
			GetDlgItem(IDC_CWEAPON_DELETE_WEAPON)->ShowWindow(SW_SHOWNORMAL);
			GetDlgItem(IDC_CWEAPON_DELETE_WEAPON)->EnableWindow(true);

		}

		this->calc_weapon();
	}
	else
	{
		//Chara-Choose deactivate
		SetDlgItemText(IDC_STATIC_CWEAPON_CHARA_COUNT, L"0 / 0");
		GetDlgItem(IDC_CWEAPON_CHAR_PAGE_PREVIOUS)->EnableWindow(false);
		GetDlgItem(IDC_CWEAPON_CHAR_PAGE_NEXT)->EnableWindow(false);

		//Weapon-Type deactivate
		SetDlgItemText(IDC_STATIC_CWEAPON_TYPE_COUNT, L"0 / 0");
		GetDlgItem(IDC_CWEAPON_TYPE_PAGE_PREVIOUS)->EnableWindow(false);
		GetDlgItem(IDC_CWEAPON_TYPE_PAGE_NEXT)->EnableWindow(false);

		//Weapon-Slot Deactivate
		SetDlgItemText(IDC_STATIC_CWEAPON_SLOT_COUNT, L"0 / 0");
		GetDlgItem(IDC_CWEAPON_SLOT_PAGE_PREVIOUS)->EnableWindow(false);
		GetDlgItem(IDC_CWEAPON_SLOT_PAGE_NEXT)->EnableWindow(false);

		SetDlgItemText(IDC_STATIC_CWEAPON_WEAPON_NAME, L"");

		//Deactivate Reset-Kills and Reset-Skills
		GetDlgItem(IDC_CWEAPON_RESET_KILLS)->EnableWindow(false);
		GetDlgItem(IDC_CWEAPON_RESET_SKILLS)->EnableWindow(false);

		//Skill-Kills Slot1 to Damage-Base deactivate and set current content to nothing
		for (int i = IDC_EDIT_CWEAPON_KILLS_SLOT_1; i <= IDC_EDIT_CWEAPON_DAMAGE_BASE; i++)
		{
			SetDlgItemText(i, L"");
			GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
			GetDlgItem(i)->EnableWindow(false);
		}

		//Deactivate the other Stats
		for (int i = IDC_COMBO_CWEAPON_STARS; i <= IDC_CHECK_CWEAPON_LEGENDARY; i++)
		{
			GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
			GetDlgItem(i)->EnableWindow(false);
		}

		//Deactivate the Skills-Slot 1 to Slot 8
		for (int i = IDC_COMBO_CWEAPON_SKILLS_SLOT_1; i <= IDC_COMBO_CWEAPON_SKILLS_SLOT_8; i++)
		{
			GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
			GetDlgItem(i)->EnableWindow(false);
		}

		//Deactivate Generate and Delete-Buttons
		GetDlgItem(IDC_CWEAPON_DEFAULT_WEAPON)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_CWEAPON_DEFAULT_WEAPON)->EnableWindow(false);
		GetDlgItem(IDC_CWEAPON_DELETE_WEAPON)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_CWEAPON_DELETE_WEAPON)->EnableWindow(false);
	}

	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZeldaEditCharaWeaponsDlg, CDialogEx)
	ON_COMMAND(ID_MENU_EDIT_GENERAL, &CZeldaEditCharaWeaponsDlg::OnMenuEditGeneral)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_STATS, &CZeldaEditCharaWeaponsDlg::OnMenuEditCharactersStats)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_WEAPONS, &CZeldaEditCharaWeaponsDlg::OnMenuEditCharactersWeapons)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_BRONZE, &CZeldaEditCharaWeaponsDlg::OnMenuEditMaterialsBronze)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_SILVER, &CZeldaEditCharaWeaponsDlg::OnMenuEditMaterialsSilver)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_GOLD, &CZeldaEditCharaWeaponsDlg::OnMenuEditMaterialsGold)
	ON_COMMAND(ID_MENU_EDIT_FAIRYFOODS, &CZeldaEditCharaWeaponsDlg::OnMenuEditFairyfoods)
	ON_COMMAND(ID_MENU_EDIT_AM_AVMAP, &CZeldaEditCharaWeaponsDlg::OnMenuEditAmAvmap)
	ON_COMMAND(ID_MENU_EDIT_AM_GSMAP, &CZeldaEditCharaWeaponsDlg::OnMenuEditAmGsmap)
	ON_COMMAND(ID_MENU_EDIT_AM_MQMAP, &CZeldaEditCharaWeaponsDlg::OnMenuEditAmMqmap)
	ON_COMMAND(ID_MENU_EDIT_AM_TLMAP, &CZeldaEditCharaWeaponsDlg::OnMenuEditAmTlmap)
	ON_COMMAND(ID_MENU_EDIT_AM_TMMAP, &CZeldaEditCharaWeaponsDlg::OnMenuEditAmTmmap)
	ON_COMMAND(ID_MENU_EDIT_FAIRIES, &CZeldaEditCharaWeaponsDlg::OnMenuEditFairies)
	ON_BN_CLICKED(ID_SAVE, &CZeldaEditCharaWeaponsDlg::OnBnClickedSave)
	ON_BN_CLICKED(ID_EXIT, &CZeldaEditCharaWeaponsDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_CWEAPON_CHAR_PAGE_PREVIOUS, &CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponCharPagePrevious)
	ON_BN_CLICKED(IDC_CWEAPON_CHAR_PAGE_NEXT, &CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponCharPageNext)
	ON_BN_CLICKED(IDC_CWEAPON_TYPE_PAGE_PREVIOUS, &CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponTypePagePrevious)
	ON_BN_CLICKED(IDC_CWEAPON_TYPE_PAGE_NEXT, &CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponTypePageNext)
	ON_BN_CLICKED(IDC_CWEAPON_SLOT_PAGE_PREVIOUS, &CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponSlotPagePrevious)
	ON_BN_CLICKED(IDC_CWEAPON_SLOT_PAGE_NEXT, &CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponSlotPageNext)
	ON_BN_CLICKED(IDC_CWEAPON_DEFAULT_WEAPON, &CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponDefaultWeapon)
	ON_BN_CLICKED(IDC_CWEAPON_DELETE_WEAPON, &CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponDeleteWeapon)
ON_CBN_SELCHANGE(IDC_COMBO_CWEAPON_LEVEL, &CZeldaEditCharaWeaponsDlg::OnCbnSelchangeComboCweaponLevel)
ON_EN_CHANGE(IDC_EDIT_CWEAPON_DAMAGE_BASE, &CZeldaEditCharaWeaponsDlg::OnEnChangeEditCweaponDamageBase)
ON_EN_KILLFOCUS(IDC_EDIT_CWEAPON_DAMAGE_BASE, &CZeldaEditCharaWeaponsDlg::OnEnKillfocusEditCweaponDamageBase)
ON_BN_CLICKED(IDC_CHECK_CWEAPON_LEGENDARY, &CZeldaEditCharaWeaponsDlg::OnBnClickedCheckCweaponLegendary)
ON_BN_CLICKED(IDC_CWEAPON_RESET_KILLS, &CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponResetKills)
ON_BN_CLICKED(IDC_CWEAPON_RESET_SKILLS, &CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponResetSkills)
ON_CONTROL_RANGE(EN_CHANGE, IDC_EDIT_CWEAPON_KILLS_SLOT_1, IDC_EDIT_CWEAPON_KILLS_SLOT_8, &OnEnChangeKillSlotEdit)
ON_CBN_SELCHANGE(IDC_COMBO_CWEAPON_STARS, &CZeldaEditCharaWeaponsDlg::OnCbnSelchangeComboCweaponStars)
END_MESSAGE_MAP()

// CZeldaEditCharaWeaponsDlg-Meldungshandler


void CZeldaEditCharaWeaponsDlg::OnMenuEditGeneral()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditGeneralDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditCharactersStats()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaStatsDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditCharactersWeapons()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditMaterialsBronze()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 0);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditMaterialsSilver()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditMaterialsGold()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditFairyfoods()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyFoods dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditAmAvmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 0);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditAmGsmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditAmMqmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditAmTlmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 3);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditAmTmmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 4);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditFairies()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnBnClickedSave()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		try
		{
			this->save_weapon();
			save->save_file();
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


void CZeldaEditCharaWeaponsDlg::OnBnClickedExit()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CZeldaEditCharaWeaponsDlg::OnOK();

}


void CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponCharPagePrevious()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_weapon();

	this->i_weapon_slot = 0;
	this->i_weapon_type = 0;
	this->i_chara_id--;

	while (1)
	{
		CString s_name(save->get_player(i_chara_id)->get_name().c_str());
		if (s_name == L"???")
		{
			this->i_chara_id--;
		}
		else{
			break;
		}
	}
	this->UpdateData();
}


void CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponCharPageNext()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_weapon();

	this->i_weapon_slot = 0;
	this->i_weapon_type = 0;
	this->i_chara_id++;

	while (1)
	{
		CString s_name(save->get_player(i_chara_id)->get_name().c_str());
		if (s_name == L"???")
		{
			this->i_chara_id++;
		}
		else{
			break;
		}
	}
	this->UpdateData();
}


void CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponTypePagePrevious()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_weapon();

	this->i_weapon_slot = 0;
	this->i_weapon_type--;
	this->UpdateData();
}


void CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponTypePageNext()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_weapon();

	this->i_weapon_slot = 0;
	this->i_weapon_type++;
	this->UpdateData();
}


void CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponSlotPagePrevious()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_weapon();

	this->i_weapon_slot--;
	this->UpdateData();
}


void CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponSlotPageNext()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_weapon();

	this->i_weapon_slot++;
	this->UpdateData();
}


void CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponDefaultWeapon()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->generate_default_weapon();
	this->UpdateData();
}


void CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponDeleteWeapon()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (this->i_weapon_type == 0)
	{
		if (save->get_player(this->i_chara_id)->get_weapon_count(this->i_weapon_type) != 1)
		{
			save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->delete_weapon();
			this->UpdateData();
		}
		else{
			CString str("You are going to delete the last weapon of the first weapon-type of this character?\n"
				"This can be a dangerous operation for your save and can result in a unstable state of your savegame.\n"
				"Make sure, that you lock this character after that to avoid such problems. \n"
				"Do you really want to delete this last weapon?");
			if (MessageBox(str, L"Dangerous Operation", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES)
			{
				save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->delete_weapon();
				this->UpdateData();
			}
		}
	}
	else{
		save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->delete_weapon();
		this->UpdateData();
	}


}

void CZeldaEditCharaWeaponsDlg::calc_weapon()
{
	//Get current name of Character and print it out
	CString s_chara_name(save->get_player(this->i_chara_id)->get_name().c_str());
	SetDlgItemText(IDC_EDIT_CWEAPON_CHARA_NAME, s_chara_name);

	//Get current weapon-type of choosen chara and print it out
	int i_weapon_count = 0;
	for (int i = 0; i < this->i_chara_id; i++)
	{
		i_weapon_count = i_weapon_count + HWLSaveEdit::HWLWeapon::vi_playerWeaponTypeCount[i];
	}
	
	CString s_weapon_type_name(HWLSaveEdit::HWLWeapon::vs_playerWeaponTypeNames[i_weapon_count + this->i_weapon_type].c_str());
	SetDlgItemText(IDC_EDIT_CWEAPON_WEAPON_TYPE, s_weapon_type_name);

	//Get current Weapon-Name of chosen chara and type and print it out (with LVL-added, but no, if we have the Master Sword)
	std::shared_ptr<HWLSaveEdit::HWLWeapon> hwlpw = save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot);
	CString s_weapon_name, s_weapon_name_tmp(hwlpw->get_name().c_str());
	if (hwlpw->get_id() == HWLSaveEdit::HWLWeapon::vi_playerWeaponTypeHexValues[4])
		s_weapon_name.Format(L"%s", s_weapon_name_tmp);
	else
		s_weapon_name.Format(L"%s LVL-%d", s_weapon_name_tmp, hwlpw->get_lvl());

	SetDlgItemText(IDC_STATIC_CWEAPON_WEAPON_NAME, s_weapon_name);

	//Get current Kills for all Skills and set them
	int i_slot_counter = 0;
	for (int i = IDC_EDIT_CWEAPON_KILLS_SLOT_1; i <= IDC_EDIT_CWEAPON_KILLS_SLOT_8; i++)
	{
		CString s_kill_value;
		s_kill_value.Format(L"%d", hwlpw->get_skill_slot_kill(i_slot_counter));
		SetDlgItemText(i, s_kill_value);
		i_slot_counter++;
	}

	//Get the current Damage and set it
	CString cs_damage;
	cs_damage.Format(L"%d", hwlpw->get_damage());
	SetDlgItemText(IDC_EDIT_CWEAPON_DAMAGE, cs_damage);

	//Get current damage-base and set it
	CString cs_damage_base;
	cs_damage_base.Format(L"%d", hwlpw->get_damage_base());
	SetDlgItemText(IDC_EDIT_CWEAPON_DAMAGE_BASE, cs_damage_base);

	//Get current stars and level and set them
	CComboBox *cb_stars = (CComboBox*)GetDlgItem(IDC_COMBO_CWEAPON_STARS);
	CComboBox *cb_level = (CComboBox*)GetDlgItem(IDC_COMBO_CWEAPON_LEVEL);
	cb_stars->SetCurSel(hwlpw->get_stars());
	cb_level->SetCurSel(hwlpw->get_lvl() - 1);

	//Get current Skills and set them
	int i_slot_counter2 = 0;
	for (int i = IDC_COMBO_CWEAPON_SKILLS_SLOT_1; i <= IDC_COMBO_CWEAPON_SKILLS_SLOT_8; i++)
	{
		CComboBox *cb_skill = (CComboBox*)GetDlgItem(i);

		int i_skill_value = hwlpw->get_skill_slot(i_slot_counter2);
		if (i_skill_value != HWLSaveEdit::HWLWeapon::weaponSkillValueNoSkill)
		{
			cb_skill->SetCurSel(i_skill_value);
		}
		else
		{
			int i_last_item_index = cb_skill->GetCount() - 1;
			if (i_last_item_index >= 0 && i_last_item_index < cb_skill->GetCount())
				cb_skill->SetCurSel(i_last_item_index);
		}

		i_slot_counter2++;
	}

	//Get current legendary-state and set it
	CButton *cb_check_legendary_state = (CButton*)GetDlgItem(IDC_CHECK_CWEAPON_LEGENDARY);
	cb_check_legendary_state->SetCheck(hwlpw->get_state());

	//Get the current isUnused-State and set it
	CButton *cb_check_is_unused = (CButton*)GetDlgItem(IDC_CHECK_CWEAPON_FREE_SLOT);
	cb_check_is_unused->SetCheck(hwlpw->get_IsUnused());
}

void CZeldaEditCharaWeaponsDlg::save_weapon()
{
	if (save != nullptr)
	{
		std::shared_ptr<HWLSaveEdit::HWLWeapon> hwlpw = save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot);

		//Get current Kills for all Skills and set to the object
		int i_slot_counter = 0;
		for (int i = IDC_EDIT_CWEAPON_KILLS_SLOT_1; i <= IDC_EDIT_CWEAPON_KILLS_SLOT_8; i++)
		{
			CString s_kill_value;
			GetDlgItemText(i, s_kill_value);
			int i_kill_value = _wtof(s_kill_value);
			hwlpw->set_skill_slot_kill(i_slot_counter, i_kill_value);
			i_slot_counter++;
		}

		//Get current damage-base and set to the object
		CString cs_damage_base;
		GetDlgItemText(IDC_EDIT_CWEAPON_DAMAGE_BASE, cs_damage_base);
		int i_damage_base = _wtof(cs_damage_base);
		hwlpw->set_damage_base(i_damage_base);

		//Get current stars and set to the object
		CComboBox *cb_stars = (CComboBox*)GetDlgItem(IDC_COMBO_CWEAPON_STARS);
		int i_stars = cb_stars->GetCurSel();
		hwlpw->set_stars(i_stars);
	
		//Get current legendary-sate and check if we have the unique master sword or not
		if (hwlpw->get_id() != HWLSaveEdit::HWLWeapon::vi_playerWeaponTypeHexValues[4])
		{
			CButton *cb_check_legendary_state = (CButton*)GetDlgItem(IDC_CHECK_CWEAPON_LEGENDARY);
			bool b_is_legendary = cb_check_legendary_state->GetCheck();
			
			if (b_is_legendary)
				hwlpw->set_state(HWLSaveEdit::HWLWeapon::weaponStateValuesHex[1]);
			else
				hwlpw->set_state(HWLSaveEdit::HWLWeapon::weaponStateValuesHex[0]);
		}
		else{
			hwlpw->set_state(HWLSaveEdit::HWLWeapon::weaponStateValuesHex[2]);
		}

		//Get current Skills and set to the object
		int i_slot_counter2 = 0;
		for (int i = IDC_COMBO_CWEAPON_SKILLS_SLOT_1; i <= IDC_COMBO_CWEAPON_SKILLS_SLOT_8; i++)
		{
			CComboBox *cb_skill = (CComboBox*)GetDlgItem(i);

			int i_skill_value = cb_skill->GetCurSel();
			int i_last_item_index = cb_skill->GetCount() - 1;

			if (i_skill_value != i_last_item_index)
			{
				hwlpw->set_skill_slot(i_slot_counter2, i_skill_value);
			}
			else
			{
				hwlpw->set_skill_slot(i_slot_counter2, HWLSaveEdit::HWLWeapon::weaponSkillValueNoSkill);
			}

			i_slot_counter2++;
		}

		hwlpw->save_weapon();
		save->get_player(this->i_chara_id)->set_weapon_slot(this->i_weapon_type, this->i_weapon_slot, hwlpw);
	}

}

void CZeldaEditCharaWeaponsDlg::OnCbnSelchangeComboCweaponLevel()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	//Get current stars and set to the object
	CComboBox *cb_lvl = (CComboBox*)GetDlgItem(IDC_COMBO_CWEAPON_LEVEL);
	int i_lvl = cb_lvl->GetCurSel() + 1;
	save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->change_lvl(i_lvl);

	this->UpdateData();
}


void CZeldaEditCharaWeaponsDlg::OnEnChangeEditCweaponDamageBase()
{
	// TODO:  Fügen Sie hier Ihren Code für die Kontrollbenachrichtigungsbehandlung ein.
	if (save != nullptr)
	{
		CString test;
		CEdit *e_test = (CEdit*)GetDlgItem(IDC_EDIT_CWEAPON_DAMAGE_BASE);
		CString cs_max_chars;
		cs_max_chars.Format(L"%d", HWLSaveEdit::HWLWeapon::weaponDamageBaseMax);
		e_test->SetLimitText(cs_max_chars.GetLength() + 1);
		GetDlgItemText(IDC_EDIT_CWEAPON_DAMAGE_BASE, test);
		int i_test = _wtoi(test);

		if (i_test > HWLSaveEdit::HWLWeapon::weaponDamageBaseMax)
		{
			i_test = HWLSaveEdit::HWLWeapon::weaponDamageBaseMax;
			test.Format(L"%d", i_test);
			SetDlgItemText(IDC_EDIT_CWEAPON_DAMAGE_BASE, test);
			e_test->SetLimitText(cs_max_chars.GetLength());
		}

		save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->change_damage_base(i_test);
		this->UpdateData();
	}
}

void CZeldaEditCharaWeaponsDlg::OnEnKillfocusEditCweaponDamageBase()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		CString test;
		CEdit *e_test = (CEdit*)GetDlgItem(IDC_EDIT_CWEAPON_DAMAGE_BASE);
		CString cs_max_chars;
		cs_max_chars.Format(L"%d", HWLSaveEdit::HWLWeapon::weaponDamageBaseMax);
		e_test->SetLimitText(cs_max_chars.GetLength() + 1);
		GetDlgItemText(IDC_EDIT_CWEAPON_DAMAGE_BASE, test);
		int i_test = _wtoi(test);

		if (i_test < HWLSaveEdit::HWLWeapon::vi_damage_base_defaults[0])
		{
			i_test = HWLSaveEdit::HWLWeapon::vi_damage_base_defaults[0];
			test.Format(L"%d", i_test);
			SetDlgItemText(IDC_EDIT_CWEAPON_DAMAGE_BASE, test);
			e_test->SetLimitText(cs_max_chars.GetLength());
		}

		save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->change_damage_base(i_test);
		this->UpdateData();
	}
}


void CZeldaEditCharaWeaponsDlg::OnBnClickedCheckCweaponLegendary()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CButton *cb_check_legendary_state = (CButton*)GetDlgItem(IDC_CHECK_CWEAPON_LEGENDARY);
	bool b_is_legendary = cb_check_legendary_state->GetCheck();

	if (b_is_legendary)
	{
		GetDlgItem(IDC_EDIT_CWEAPON_DAMAGE_BASE)->EnableWindow(false);

		CString cs_info("This weapon was a non-legendary one before. So if you really want to have a legendary weapon you need the legendary skill.\n"
			"So don't forget to set an Skill-Slot to this special Skill. Only set this flag or the skill is useless.");
		MessageBox(cs_info, L"Information", MB_OK | MB_ICONINFORMATION);
	}
	else
		GetDlgItem(IDC_EDIT_CWEAPON_DAMAGE_BASE)->EnableWindow(true);
}

void CZeldaEditCharaWeaponsDlg::OnEnChangeKillSlotEdit(UINT nID)
{
	if (SendDlgItemMessage(nID, EM_GETMODIFY, 0, 0))
	{
		if (save != nullptr)
		{
			CString test;
			CEdit *e_test = (CEdit*)GetDlgItem(nID);
			CString cs_max_chars;
			cs_max_chars.Format(L"%d", HWLSaveEdit::HWLWeapon::weaponSkillSlotKillMax);
			e_test->SetLimitText(cs_max_chars.GetLength() + 1);
			GetDlgItemText(nID, test);
			int i_test = _wtoi(test);

			if (i_test > HWLSaveEdit::HWLWeapon::weaponSkillSlotKillMax)
			{
				test.Format(L"%d", HWLSaveEdit::HWLWeapon::weaponSkillSlotKillMax);
				SetDlgItemText(nID, test);
				e_test->SetLimitText(cs_max_chars.GetLength());
			}

		}
	}
}

void CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponResetKills()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	//Set all Kills for all Skills to zero
	int i_slot_counter = 0;
	for (int i = IDC_EDIT_CWEAPON_KILLS_SLOT_1; i <= IDC_EDIT_CWEAPON_KILLS_SLOT_8; i++)
	{
		CString s_kill_value;
		s_kill_value.Format(L"%d", 0);
		SetDlgItemText(i, s_kill_value);
		i_slot_counter++;
	}
	CString str("Finish! All needed Values are updated.");
	MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
}


void CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponResetSkills()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	//Set Skill 1 to an Open Slot and all others to Non-Slot
	int i_slot_counter = 0;
	for (int i = IDC_COMBO_CWEAPON_SKILLS_SLOT_1; i <= IDC_COMBO_CWEAPON_SKILLS_SLOT_8; i++)
	{
		CComboBox *cb_skill = (CComboBox*)GetDlgItem(i);
		int i_skill_value;

		if (i_slot_counter == 0)
			i_skill_value = 0x00;
		else
			i_skill_value = HWLSaveEdit::HWLWeapon::weaponSkillValueNoSkill;

		if (i_skill_value != HWLSaveEdit::HWLWeapon::weaponSkillValueNoSkill)
		{
			cb_skill->SetCurSel(i_skill_value);
		}
		else
		{
			int i_last_item_index = cb_skill->GetCount() - 1;
			if (i_last_item_index >= 0 && i_last_item_index < cb_skill->GetCount())
				cb_skill->SetCurSel(i_last_item_index);
		}

		i_slot_counter++;
	}
	CString str("Finish! All needed Values are updated.");
	MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
}


void CZeldaEditCharaWeaponsDlg::OnCbnSelchangeComboCweaponStars()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CComboBox *cb_stars = (CComboBox*)GetDlgItem(IDC_COMBO_CWEAPON_STARS);
	int i_stars = cb_stars->GetCurSel();
	save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->change_stars(i_stars);

	this->UpdateData();
}
