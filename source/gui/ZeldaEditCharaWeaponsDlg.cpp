// ZeldaEditCharaWeaponsDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZeldaHWLSaveEditorGUI.h"
#include "ZeldaEditCharaWeaponsDlg.h"
#include "afxdialogex.h"


// CZeldaEditCharaWeaponsDlg-Dialogfeld

IMPLEMENT_DYNAMIC(CZeldaEditCharaWeaponsDlg, CDialogEx)

CZeldaEditCharaWeaponsDlg::CZeldaEditCharaWeaponsDlg(CWnd* pParent /*=NULL*/, int i_chara_id, int i_skipped_charas)
	: CDialogEx(CZeldaEditCharaWeaponsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->i_chara_id = i_chara_id;
	this->i_skipped_charas = i_skipped_charas;

	this->i_weapon_type = this->i_weapon_slot = this->i_skipped_weaponTypes = 0;
	this->i_disabledWeaponSkillsCounter = HWLSaveEdit::HWLWeapon::get_WeaponSkillDisabledCounter();

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
		int i_skipped_skills = 0;

		for (int j = 0; j < HWLSaveEdit::HWLWeapon::weaponSkillNames.size(); j++)
		{
			if (HWLSaveEdit::HWLWeapon::get_isWeaponSkillDisabled(j))
			{
				i_skipped_skills++;
				continue;
			}

			CString cs_skill_name(HWLSaveEdit::HWLWeapon::weaponSkillNames[j].c_str());
			cb_skill->InsertString(j - i_skipped_skills, cs_skill_name);
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

	//calculate the disabled-Items and remove the Menu-Entry, if neccessary
	CZeldaHWLSaveEditorGUIApp::calc_disabled_MenuItems(GetMenu()->GetSubMenu(1));

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
	cm_submenu->CheckMenuItem(3, MF_CHECKED | MF_BYPOSITION);

	//get the save-content
	save = CZeldaHWLSaveEditorGUIApp::save;

	if (save != nullptr)
	{

		if (this->i_chara_id >= HWLSaveEdit::HWLPlayer::vs_players.size() || save->get_player(this->i_chara_id)->get_isDisabled())
		{
			this->i_skipped_charas = 0;
			this->i_chara_id = 0;
		}

		if (this->i_weapon_type >= save->get_player(this->i_chara_id)->get_weapon_type_count() || save->get_player(this->i_chara_id)->get_isWeaponTypeDisabled(this->i_weapon_type))
		{
			this->i_skipped_weaponTypes = 0;
			this->i_weapon_type = 0;
		}

		if (this->i_disabledWeaponSkillsCounter != HWLSaveEdit::HWLWeapon::get_WeaponSkillDisabledCounter())
		{
			CZeldaEditCharaWeaponsDlg dlg(NULL, this->i_chara_id, this->i_skipped_charas);
			EndDialog(this->IDD);
			dlg.DoModal();
		}

		std::shared_ptr<HWLSaveEdit::HWLWeapon> hwlpw = save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot);

		//Chara-Choose activate
		CString s_chara_count; 
		s_chara_count.Format(L"%d / %d", (this->i_chara_id + 1) - this->i_skipped_charas, HWLSaveEdit::HWLPlayer::vs_players.size() - HWLSaveEdit::HWLPlayer::get_disabledPlayerCounter());
		SetDlgItemText(IDC_STATIC_CWEAPON_CHARA_COUNT, s_chara_count);
		GetDlgItem(IDC_CWEAPON_CHAR_PAGE_PREVIOUS)->EnableWindow(true);
		GetDlgItem(IDC_CWEAPON_CHAR_PAGE_NEXT)->EnableWindow(true);

		if (this->i_chara_id <= 0)
			GetDlgItem(IDC_CWEAPON_CHAR_PAGE_PREVIOUS)->EnableWindow(false);
		else
			GetDlgItem(IDC_CWEAPON_CHAR_PAGE_PREVIOUS)->EnableWindow(true);

		if ((this->i_chara_id + 1) - this->i_skipped_charas >= HWLSaveEdit::HWLPlayer::vs_players.size() - HWLSaveEdit::HWLPlayer::get_disabledPlayerCounter())
			GetDlgItem(IDC_CWEAPON_CHAR_PAGE_NEXT)->EnableWindow(false);
		else
			GetDlgItem(IDC_CWEAPON_CHAR_PAGE_NEXT)->EnableWindow(true);

		//Weapon-Type activate
		CString s_type_count;
		s_type_count.Format(L"%d / %d", (this->i_weapon_type + 1) - this->i_skipped_weaponTypes, save->get_player(this->i_chara_id)->get_weapon_type_count() - save->get_player(this->i_chara_id)->get_disabledWeaponTypeCounter() );
		SetDlgItemText(IDC_STATIC_CWEAPON_TYPE_COUNT, s_type_count);
		GetDlgItem(IDC_CWEAPON_TYPE_PAGE_PREVIOUS)->EnableWindow(true);
		GetDlgItem(IDC_CWEAPON_TYPE_PAGE_NEXT)->EnableWindow(true);

		if (this->i_weapon_type <= 0)
			GetDlgItem(IDC_CWEAPON_TYPE_PAGE_PREVIOUS)->EnableWindow(false);
		else
			GetDlgItem(IDC_CWEAPON_TYPE_PAGE_PREVIOUS)->EnableWindow(true);

		if (this->i_weapon_type + 1 >= save->get_player(this->i_chara_id)->get_weapon_type_count() - save->get_player(this->i_chara_id)->get_disabledWeaponTypeCounter() )
			GetDlgItem(IDC_CWEAPON_TYPE_PAGE_NEXT)->EnableWindow(false);
		else
			GetDlgItem(IDC_CWEAPON_TYPE_PAGE_NEXT)->EnableWindow(true);

		//Weapon-Slot activate
		CString s_weapon_slot_count;
		s_weapon_slot_count.Format(L"%d / %d", this->i_weapon_slot + 1, HWLSaveEdit::HWLPlayer::playerWeaponSlotsMax);


		SetDlgItemText(IDC_STATIC_CWEAPON_SLOT_COUNT, s_weapon_slot_count);
		GetDlgItem(IDC_CWEAPON_SLOT_PAGE_PREVIOUS)->EnableWindow(true);
		GetDlgItem(IDC_CWEAPON_SLOT_PAGE_NEXT)->EnableWindow(true);

		if (this->i_weapon_slot+1 <= 1)
			GetDlgItem(IDC_CWEAPON_SLOT_PAGE_PREVIOUS)->EnableWindow(false);
		else
			GetDlgItem(IDC_CWEAPON_SLOT_PAGE_PREVIOUS)->EnableWindow(true);

		if (this->i_weapon_slot + 1 >= HWLSaveEdit::HWLPlayer::playerWeaponSlotsMax)
			GetDlgItem(IDC_CWEAPON_SLOT_PAGE_NEXT)->EnableWindow(false);
		else
			GetDlgItem(IDC_CWEAPON_SLOT_PAGE_NEXT)->EnableWindow(true);

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

			//Deactivate Copy/Paste Buttons
			GetDlgItem(IDC_CWEAPON_COPY_VALUES)->EnableWindow(false);
			GetDlgItem(IDC_CWEAPON_PASTE_VALUES)->EnableWindow(false);

			//Skill-Kills Slot1 to Damage-Base deactivate and set current content to nothing
			for (int i = IDC_EDIT_CWEAPON_KILLS_SLOT_1; i <= IDC_EDIT_CWEAPON_DAMAGE_BASE; i++)
			{
				GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
				GetDlgItem(i)->EnableWindow(false);
			}

			//Deactivate the other Stats
			for (int i = IDC_COMBO_CWEAPON_STARS; i <= IDC_CHECK_CWEAPON_MULTIELEMENT; i++)
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

			//Deactivate Copy/Paste Buttons
			GetDlgItem(IDC_CWEAPON_COPY_VALUES)->EnableWindow(true);
			GetDlgItem(IDC_CWEAPON_PASTE_VALUES)->EnableWindow(true);

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
				for (int i = IDC_COMBO_CWEAPON_LEVEL; i <= IDC_CHECK_CWEAPON_MULTIELEMENT; i++)
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

				//Check if we have a Multi-ElementWeapon of that type, deactiate CheckBox if not (and also LVL)
				if (hwlpw->get_multi_element_hex() != 0x00)
				{
					GetDlgItem(IDC_CHECK_CWEAPON_MULTIELEMENT)->ShowWindow(SW_SHOWNORMAL);
					GetDlgItem(IDC_CHECK_CWEAPON_MULTIELEMENT)->EnableWindow(true);
				}
				else  
				{
					GetDlgItem(IDC_CHECK_CWEAPON_MULTIELEMENT)->ShowWindow(SW_SHOWNORMAL);
					GetDlgItem(IDC_CHECK_CWEAPON_MULTIELEMENT)->EnableWindow(false);
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

		//Deactivate Copy/Paste Buttons
		GetDlgItem(IDC_CWEAPON_COPY_VALUES)->EnableWindow(false);
		GetDlgItem(IDC_CWEAPON_PASTE_VALUES)->EnableWindow(false);

		//Skill-Kills Slot1 to Damage-Base deactivate and set current content to nothing
		for (int i = IDC_EDIT_CWEAPON_KILLS_SLOT_1; i <= IDC_EDIT_CWEAPON_DAMAGE_BASE; i++)
		{
			SetDlgItemText(i, L"");
			GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
			GetDlgItem(i)->EnableWindow(false);
		}

		//Deactivate the other Stats
		for (int i = IDC_COMBO_CWEAPON_STARS; i <= IDC_CHECK_CWEAPON_MULTIELEMENT; i++)
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
ON_COMMAND(ID_MENU_EDIT_AM_MWWMAP, &CZeldaEditCharaWeaponsDlg::OnMenuEditAmMwwmap)
ON_COMMAND(ID_MENU_EDIT_AM_KIMAP, &CZeldaEditCharaWeaponsDlg::OnMenuEditAmKimap)
ON_COMMAND(ID_MENU_EDIT_AM_GTMAP, &CZeldaEditCharaWeaponsDlg::OnMenuEditAmGtmap)
ON_BN_CLICKED(IDC_CHECK_CWEAPON_MULTIELEMENT, &CZeldaEditCharaWeaponsDlg::OnBnClickedCheckCweaponMultielement)
ON_COMMAND(ID_MENU_MAIN_EXIT, &CZeldaEditCharaWeaponsDlg::OnMenuMainExit)
ON_COMMAND(ID_MENU_EDIT_CHARACTERS_OVERVIEW, &CZeldaEditCharaWeaponsDlg::OnMenuEditCharactersOverview)
ON_BN_CLICKED(IDC_CWEAPON_COPY_VALUES, &CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponCopyValues)
ON_BN_CLICKED(IDC_CWEAPON_PASTE_VALUES, &CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponPasteValues)
ON_COMMAND(ID_MENU_EDIT_AM_LRMAP, &CZeldaEditCharaWeaponsDlg::OnMenuEditAmLrmap)
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
	CZeldaEditAdventureModeMaps dlg(NULL, 0);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditAmGsmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditAmMqmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditAmTlmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 3);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditAmTmmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 4);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditCharaWeaponsDlg::OnMenuEditAmMwwmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps dlg(NULL, 5);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditAmKimap()
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


void CZeldaEditCharaWeaponsDlg::OnMenuEditAmGtmap()
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

void CZeldaEditCharaWeaponsDlg::OnMenuEditAmLrmap()
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


void CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponCharPageNext()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_weapon();

	this->i_weapon_slot = 0;
	this->i_weapon_type = 0;

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


void CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponTypePagePrevious()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_weapon();

	this->i_weapon_slot = 0;

	int i_old_weaponType_id = this->i_weapon_type;
	for (int i = this->i_weapon_type - 1; i > 0; i--)
	{
		if (save->get_player(this->i_chara_id)->get_isWeaponTypeDisabled(i))
		{
			if (this->i_skipped_weaponTypes > 0)
				this->i_skipped_weaponTypes--;
			continue;
		}
		else
		{
			this->i_weapon_type = i;
			break;
		}
	}

	if (this->i_weapon_type == i_old_weaponType_id)
		this->i_weapon_type = 0;

	this->UpdateData();
}


void CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponTypePageNext()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_weapon();

	this->i_weapon_slot = 0;

	int i_old_weaponType_id = this->i_weapon_type;
	for (int i = this->i_weapon_type + 1; i < save->get_player(this->i_chara_id)->get_weapon_type_count(); i++)
	{
		if (save->get_player(this->i_chara_id)->get_isWeaponTypeDisabled(i))
		{
			this->i_skipped_weaponTypes++;
			continue;
		}
		else
		{
			this->i_weapon_type = i;
			break;
		}
	}

	if (this->i_weapon_type == i_old_weaponType_id)
		this->i_weapon_type = 0;

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
	
	if (save->get_player(this->i_chara_id)->get_weapon_count(this->i_weapon_type) > HWLSaveEdit::HWLPlayer::playerWeaponSlotsMaxIngame)
	{
		CString cs_info;
		cs_info.Format(L"You add more Weapons then the game allowed you to take (Max: %d) so you have to sell %d Weapon(s) at the start of the game itself.",
			HWLSaveEdit::HWLPlayer::playerWeaponSlotsMaxIngame, 
			save->get_player(this->i_chara_id)->get_weapon_count(this->i_weapon_type) - HWLSaveEdit::HWLPlayer::playerWeaponSlotsMaxIngame);
		MessageBox(cs_info, L"Information", MB_OK | MB_ICONINFORMATION);
	}

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
	CString s_weapon_multiElement_addition = L"";
	if (hwlpw->get_IsMultiElement())
		s_weapon_multiElement_addition = L"+";

	if (hwlpw->get_id() == HWLSaveEdit::HWLWeapon::vi_playerWeaponTypeHexValues[4])
		s_weapon_name.Format(L"%s", s_weapon_name_tmp);
	else
		s_weapon_name.Format(L"%s LVL-%d%s", s_weapon_name_tmp, hwlpw->get_lvl(), s_weapon_multiElement_addition);



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

	//Get current MultiElement-state and set it
	CButton *cb_check_MultiElement_state = (CButton*)GetDlgItem(IDC_CHECK_CWEAPON_MULTIELEMENT);
	cb_check_MultiElement_state->SetCheck(hwlpw->get_IsMultiElement());

	if (hwlpw->get_IsMultiElement())
	{
		GetDlgItem(IDC_COMBO_CWEAPON_LEVEL)->ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_COMBO_CWEAPON_LEVEL)->EnableWindow(false);
	}

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
	
		//Get current legendary-state and change the state
		CButton *cb_check_legendary_state = (CButton*)GetDlgItem(IDC_CHECK_CWEAPON_LEGENDARY);
		bool b_is_legendary = cb_check_legendary_state->GetCheck();
		hwlpw->change_legendary_state(b_is_legendary);

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

	bool b_dlc_safety_checks = stoi(save->get_config()->get_param_value("DlcSafetyCheck", save->get_config()->get_sectionID("General")));

	if (i_lvl == HWLSaveEdit::HWLWeapon::weaponLVLMax && this->i_chara_id == 26 && this->i_weapon_type == 0 
		&& save->get_general_things()->get_current_savefile_game_version() != "1.0.0"
		&& save->get_general_things()->get_current_savefile_game_version() != "1.2.0"
		&& save->get_general_things()->get_dlc_installed_dlcs_value() == 0)
	{
		if (b_dlc_safety_checks)
		{
			save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->change_lvl(i_lvl - 1);

			CString cs_info;
			cs_info.Format
				(L"Due to a security reason and because the game doesn't recognize LVL-%d Weapons of %s without a DLC. \nSo this Weapon is set to LVL-%d instead."
				, i_lvl, CString(save->get_player(this->i_chara_id)->get_name().c_str()), i_lvl - 1);
			MessageBox(cs_info, L"Information", MB_OK | MB_ICONINFORMATION);
		}
		else{
			save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->change_lvl(i_lvl);
		}


	}else
		save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->change_lvl(i_lvl);


	save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->save_weapon();

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
		save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->save_weapon();

	}
}

void CZeldaEditCharaWeaponsDlg::OnEnKillfocusEditCweaponDamageBase()
{
	/*
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
	*/
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

	save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->change_legendary_state(b_is_legendary);
	save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->save_weapon();

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

			int i_kill_slot_id = nID - IDC_EDIT_CWEAPON_KILLS_SLOT_1;
			save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->set_skill_slot_kill(i_kill_slot_id, i_test);
			save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->save_weapon();
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

		save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->set_skill_slot_kill(i_slot_counter, 0);
		i_slot_counter++;
	}

	save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->save_weapon();
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

		save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->set_skill_slot(i_slot_counter, i_skill_value);
		i_slot_counter++;
	}

	save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->save_weapon();
	CString str("Finish! All needed Values are updated.");
	MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
}


void CZeldaEditCharaWeaponsDlg::OnCbnSelchangeComboCweaponStars()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CComboBox *cb_stars = (CComboBox*)GetDlgItem(IDC_COMBO_CWEAPON_STARS);
	int i_stars = cb_stars->GetCurSel();
	save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->change_stars(i_stars);
	save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->save_weapon();

	this->UpdateData();
}

void CZeldaEditCharaWeaponsDlg::OnBnClickedCheckCweaponMultielement()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CButton *cb_check_multiElement_state = (CButton*)GetDlgItem(IDC_CHECK_CWEAPON_MULTIELEMENT);
	bool b_is_multiElement = cb_check_multiElement_state->GetCheck();

	bool b_dlc_safety_checks = stoi(save->get_config()->get_param_value("DlcSafetyCheck", save->get_config()->get_sectionID("General")));

	if (save->get_general_things()->get_current_savefile_game_version() != "1.0.0"
		&& save->get_general_things()->get_current_savefile_game_version() != "1.2.0"
		&& save->get_general_things()->get_current_savefile_game_version() != "1.3.0"
		&& (save->get_general_things()->get_dlc_installed_state(1) || save->get_general_things()->get_dlc_installed_state(2) || save->get_general_things()->get_dlc_installed_state(3)))
	{
		save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->change_multi_element_state(b_is_multiElement);
		save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->save_weapon();
	}
	else{
		if (b_dlc_safety_checks || save->get_general_things()->get_current_savefile_game_version() == "1.0.0"
			|| save->get_general_things()->get_current_savefile_game_version() == "1.2.0"
			|| save->get_general_things()->get_current_savefile_game_version() == "1.3.0")
		{
			CString cs_info;
			cs_info.Format
				(L"This option is only available, if you on GameVersion '1.4.0' or higher \nand if you have one of the following DLCs installed:\n\n%s\n%s\n%s"
				, CString(save->get_general_things()->get_dlc_name(1).c_str()), CString(save->get_general_things()->get_dlc_name(2).c_str()), CString(save->get_general_things()->get_dlc_name(3).c_str()));
			MessageBox(cs_info, L"Information", MB_OK | MB_ICONINFORMATION);
		}
		else{
			save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->change_multi_element_state(b_is_multiElement);
			save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot)->save_weapon();
		}



	}




	this->UpdateData();

}


void CZeldaEditCharaWeaponsDlg::OnMenuMainExit()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaWeaponsDlg::OnOK();
}


void CZeldaEditCharaWeaponsDlg::OnMenuEditCharactersOverview()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaOverviewDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponCopyValues()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		CZeldaConfigWeaponCopyDlg weapon_config;
		weapon_config.DoModal();

		if (CZeldaHWLSaveEditorGUIApp::sp_weapon_copy == nullptr)
			CZeldaHWLSaveEditorGUIApp::sp_weapon_copy = make_shared<HWLSaveEdit::HWLWeapon>(0, -1, false, true);

		*(CZeldaHWLSaveEditorGUIApp::sp_weapon_copy) = *(this->save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot));

		this->UpdateData();
	}

}


void CZeldaEditCharaWeaponsDlg::OnBnClickedCweaponPasteValues()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.

	if (save != nullptr)
	{
		std::shared_ptr<HWLSaveEdit::HWLWeapon> sp_hwl_current_weapon = this->save->get_player(this->i_chara_id)->get_weapon_slot(this->i_weapon_type, this->i_weapon_slot);
		std::shared_ptr<HWLSaveEdit::HWLWeapon> sp_hwl_copy_weapon = CZeldaHWLSaveEditorGUIApp::sp_weapon_copy;
		bool b_is_current_weapon_master_sword = false;

		if (sp_hwl_current_weapon->get_id() == HWLSaveEdit::HWLWeapon::vi_playerWeaponTypeHexValues[4])
			b_is_current_weapon_master_sword = true;

		if (sp_hwl_copy_weapon != nullptr)
		{
			if (!sp_hwl_current_weapon->get_IsUnused())
			{
				for (int i = 0; i < CZeldaHWLSaveEditorGUIApp::mib_config_copy_weapon_values.size(); i++)
				{
					bool b_current_config_value = CZeldaHWLSaveEditorGUIApp::mib_config_copy_weapon_values[i];

					switch (i)
					{
					case 0:
						if (b_current_config_value && !b_is_current_weapon_master_sword)
							sp_hwl_current_weapon->change_legendary_state(sp_hwl_copy_weapon->get_state());
						break;

					case 1:
						if (b_current_config_value && !b_is_current_weapon_master_sword)
							sp_hwl_current_weapon->change_lvl(sp_hwl_copy_weapon->get_lvl());
						break;

					case 2:
						if (b_current_config_value && !b_is_current_weapon_master_sword)
							sp_hwl_current_weapon->change_multi_element_state(sp_hwl_copy_weapon->get_IsMultiElement());
						break;

					case 3:
						if (b_current_config_value && !b_is_current_weapon_master_sword && !sp_hwl_current_weapon->get_state())
							sp_hwl_current_weapon->change_damage_base(sp_hwl_copy_weapon->get_damage_base());
						break;

					case 4:
						if (b_current_config_value)
							sp_hwl_current_weapon->change_stars(sp_hwl_copy_weapon->get_stars());
						break;

					case 5:
						if (b_current_config_value)
							sp_hwl_current_weapon->set_skill_kills(sp_hwl_copy_weapon->get_skill_kills());
						break;

					case 6:
						if (b_current_config_value)
							sp_hwl_current_weapon->set_skills(sp_hwl_copy_weapon->get_skills());
						break;

					default:
						break;
					}

				}

				sp_hwl_current_weapon->save_weapon();
				this->UpdateData();

			}else
			{
				CString str("You can't paste values to this weapon, because it's an unused one.\n"
					"Please generate a default weapon first.");
				MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
			}
		}else
		{
			CString str("You haven't copied any values yet!");
			MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
		}

	}
}
