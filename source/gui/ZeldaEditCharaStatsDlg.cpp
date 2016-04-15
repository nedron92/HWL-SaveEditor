// ZeldaEditCharaStatsDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZeldaHWLSaveEditorGUI.h"
#include "afxdialogex.h"
#include "ZeldaEditCharaStatsDlg.h"


// CZeldaEditCharaStatsDlg-Dialogfeld

IMPLEMENT_DYNAMIC(CZeldaEditCharaStatsDlg, CDialogEx)

CZeldaEditCharaStatsDlg::CZeldaEditCharaStatsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZeldaEditCharaStatsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CZeldaEditCharaStatsDlg::~CZeldaEditCharaStatsDlg()
{
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
	cm_submenu->CheckMenuItem(0, MF_CHECKED | MF_BYPOSITION);

	//own inits
	save = CZeldaHWLSaveEditorGUIApp::save;

	if (save != nullptr)
	{
		for (int i = IDC_EDIT_CHARA_LVL1; i <= IDC_EDIT_CHARA_LVL24; i++)
		{
			GetDlgItem(i)->EnableWindow(true);
		}

		for (int i = IDC_EDIT_CHARA_EXP1; i <= IDC_EDIT_CHARA_EXP24; i++)
		{
			GetDlgItem(i)->EnableWindow(true);
		}

		for (int i = IDC_EDIT_CHARA_ATK1; i <= IDC_EDIT_CHARA_ATK24; i++)
		{
			GetDlgItem(i)->EnableWindow(true);
		}

		for (int i = IDC_CHECK_CHARA_UNLOCK1; i <= IDC_CHECK_CHARA_UNLOCK24; i++)
		{
			GetDlgItem(i)->EnableWindow(true);
		}

		this->calc_players();

	}
	else
	{

		for (int i = IDC_STATIC_CHARA1; i <= IDC_STATIC_CHARA24; i++)
		{
			SetDlgItemText(i, L"Chara");
		}

		for (int i = IDC_EDIT_CHARA_LVL1; i <= IDC_EDIT_CHARA_LVL24; i++)
		{
			SetDlgItemText(i, L"");
			GetDlgItem(i)->EnableWindow(false);
		}

		for (int i = IDC_EDIT_CHARA_EXP1; i <= IDC_EDIT_CHARA_EXP24; i++)
		{
			SetDlgItemText(i, L"");
			GetDlgItem(i)->EnableWindow(false);
		}	

		for (int i = IDC_EDIT_CHARA_ATK1; i <= IDC_EDIT_CHARA_ATK24; i++)
		{
			SetDlgItemText(i, L"");
			GetDlgItem(i)->EnableWindow(false);
		}

		for (int i = IDC_CHECK_CHARA_UNLOCK1; i <= IDC_CHECK_CHARA_UNLOCK24; i++)
		{
			((CButton*)GetDlgItem(i))->SetCheck(0);
			GetDlgItem(i)->EnableWindow(false);
		}

	}

	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZeldaEditCharaStatsDlg, CDialogEx)
	ON_BN_CLICKED(ID_EXIT, &CZeldaEditCharaStatsDlg::OnBnClickedExit)
	ON_BN_CLICKED(ID_SAVE, &CZeldaEditCharaStatsDlg::OnBnClickedSave)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_EDIT_CHARA_LVL1, IDC_EDIT_CHARA_LVL24, &OnEnChangeLVLEdit)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_EDIT_CHARA_EXP1, IDC_EDIT_CHARA_EXP24, &OnEnChangeEXPEdit)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_EDIT_CHARA_ATK1, IDC_EDIT_CHARA_ATK24, &OnEnChangeATKEdit)
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
	ON_BN_CLICKED(IDC_CHARA_MAX_EXP_ALL, &CZeldaEditCharaStatsDlg::OnBnClickedCharaMaxExpAll)
	ON_BN_CLICKED(IDC_CHARA_MAX_ATK_ALL, &CZeldaEditCharaStatsDlg::OnBnClickedCharaMaxAtkAll)
	ON_BN_CLICKED(IDC_CHARA_UNLOCK_ALL, &CZeldaEditCharaStatsDlg::OnBnClickedCharaUnlockAll)
	ON_COMMAND(ID_MENU_EDIT_AM_TLMAP, &CZeldaEditCharaStatsDlg::OnMenuEditAmTlmap)
	ON_COMMAND(ID_MENU_EDIT_AM_TMMAP, &CZeldaEditCharaStatsDlg::OnMenuEditAmTmmap)
	ON_COMMAND(ID_MENU_EDIT_FAIRIES, &CZeldaEditCharaStatsDlg::OnMenuEditFairies)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_WEAPONS, &CZeldaEditCharaStatsDlg::OnMenuEditCharactersWeapons)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHECK_CHARA_UNLOCK1, IDC_CHECK_CHARA_UNLOCK24, &OnBnClickedUnlockCheck)
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
			this->save_players();
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

void CZeldaEditCharaStatsDlg::calc_players()
{
	int unused_charas = 0;


	for (int i = 0; i < save->vs_players.size(); i++)
	{
		CString s_player_name(save->get_player(i)->get_name().c_str());

		CString s_player_lvl;
		s_player_lvl.Format(L"%d", save->get_player(i)->get_lvl());

		CString s_player_exp;
		s_player_exp.Format(L"%d", save->get_player(i)->get_exp());

		CString s_player_atk;
		s_player_atk.Format(L"%d", save->get_player(i)->get_atk());

		bool b_player_is_unlock = save->get_player(i)->get_isUnlock();
		CButton *cb_check;


		if (s_player_name == L"???")
		{
			unused_charas++;
			continue;
		}

		SetDlgItemText((IDC_STATIC_CHARA1 + i - unused_charas), s_player_name + L": ");
		SetDlgItemText((IDC_EDIT_CHARA_LVL1 + i - unused_charas), s_player_lvl);
		SetDlgItemText((IDC_EDIT_CHARA_EXP1 + i - unused_charas), s_player_exp);
		SetDlgItemText((IDC_EDIT_CHARA_ATK1 + i - unused_charas), s_player_atk);
		cb_check = (CButton*)GetDlgItem((IDC_CHECK_CHARA_UNLOCK1 + i - unused_charas));
		cb_check->SetCheck(b_player_is_unlock);

		CEdit *e_test = (CEdit*)GetDlgItem((IDC_EDIT_CHARA_LVL1 + i - unused_charas));
		CString cs_max_chars;
		cs_max_chars.Format(L"%d", HWLSaveEdit::HWLPlayer::playerLVLMax);
		e_test->SetLimitText(cs_max_chars.GetLength() + 1);

		e_test = (CEdit*)GetDlgItem((IDC_EDIT_CHARA_EXP1 + i - unused_charas));
		cs_max_chars.Format(L"%d", HWLSaveEdit::HWLPlayer::playerEXPMax);
		e_test->SetLimitText(cs_max_chars.GetLength() + 1);

		e_test = (CEdit*)GetDlgItem((IDC_EDIT_CHARA_ATK1 + i - unused_charas));
		cs_max_chars.Format(L"%d", HWLSaveEdit::HWLPlayer::playerATKMax);
		e_test->SetLimitText(cs_max_chars.GetLength() + 1);
	}

}

void CZeldaEditCharaStatsDlg::OnEnChangeLVLEdit(UINT nID)
{

	if (SendDlgItemMessage(nID, EM_GETMODIFY, 0, 0))
	{
		if (save != nullptr)
		{
			CString test;
			CEdit *e_test = (CEdit*)GetDlgItem(nID);
			CString cs_max_chars;
			cs_max_chars.Format(L"%d", HWLSaveEdit::HWLPlayer::playerLVLMax);
			e_test->SetLimitText(cs_max_chars.GetLength() + 1);
			GetDlgItemText(nID, test);
			int i_test = _wtoi(test);

			if (i_test > HWLSaveEdit::HWLPlayer::playerLVLMax)
			{
				test.Format(L"%d", HWLSaveEdit::HWLPlayer::playerLVLMax);
				SetDlgItemText(nID, test);
				e_test->SetLimitText(cs_max_chars.GetLength());
			}

		}
	}

}

void CZeldaEditCharaStatsDlg::OnEnChangeEXPEdit(UINT nID)
{

	if (SendDlgItemMessage(nID, EM_GETMODIFY, 0, 0))
	{
		if (save != nullptr)
		{
			CString test;
			CEdit *e_test = (CEdit*)GetDlgItem(nID);
			CString cs_max_chars;
			cs_max_chars.Format(L"%d", HWLSaveEdit::HWLPlayer::playerEXPMax);
			e_test->SetLimitText(cs_max_chars.GetLength() + 1);
			GetDlgItemText(nID, test);
			int i_test = _wtoi(test);

			if (i_test > HWLSaveEdit::HWLPlayer::playerEXPMax)
			{
				test.Format(L"%d", HWLSaveEdit::HWLPlayer::playerEXPMax);
				SetDlgItemText(nID, test);
				e_test->SetLimitText(cs_max_chars.GetLength());
			}

		}
	}

}

void CZeldaEditCharaStatsDlg::OnEnChangeATKEdit(UINT nID)
{

	if (SendDlgItemMessage(nID, EM_GETMODIFY, 0, 0))
	{
		if (save != nullptr)
		{
			CString test;
			CEdit *e_test = (CEdit*)GetDlgItem(nID);
			CString cs_max_chars;
			cs_max_chars.Format(L"%d", HWLSaveEdit::HWLPlayer::playerATKMax);
			e_test->SetLimitText(cs_max_chars.GetLength() + 1);
			GetDlgItemText(nID, test);
			int i_test = _wtoi(test);

			if (i_test > HWLSaveEdit::HWLPlayer::playerATKMax)
			{
				test.Format(L"%d", HWLSaveEdit::HWLPlayer::playerATKMax);
				SetDlgItemText(nID, test);
				e_test->SetLimitText(cs_max_chars.GetLength());
			}

		}
	}

}

void CZeldaEditCharaStatsDlg::OnBnClickedUnlockCheck(UINT nID)
{
	if (save != nullptr)
	{
		CButton *cb_check = (CButton*)GetDlgItem(nID);
		bool b_player_is_unlock = cb_check->GetCheck();

		if (b_player_is_unlock)
		{
			int unused_charas = 0;
			int i_unused_last_id = 0;
			for (int i = 0; i < save->vs_players.size(); i++)
			{
				CString s_player_name(save->get_player(i)->get_name().c_str());

				if (s_player_name == L"???")
				{
					i_unused_last_id = i;
					unused_charas++;
					continue;
				}
			}

			int i_unused_first_id = i_unused_last_id - (unused_charas - 1);
			int i_diff_to_first_chara = nID - IDC_CHECK_CHARA_UNLOCK1;
			int i_current_chara_id = 0;

			if (i_diff_to_first_chara >= i_unused_first_id)
				i_current_chara_id = i_diff_to_first_chara + unused_charas;
			else
				i_current_chara_id = i_diff_to_first_chara;

			if (save->get_player(i_current_chara_id)->get_weapon_count(0) == 0)
			{
				save->generate_default_weapon(i_current_chara_id, 0, 0);
				save->get_player(i_current_chara_id)->get_weapon_slot(0, 0)->save_weapon();

				CString cs_info("This character hasn't a default weapon, so maybe he wasn't "
					"unlocked within the story yet. \n"
					"To really unlock this character, a default weapon was added automatically.");
				MessageBox(cs_info, L"Information", MB_OK | MB_ICONINFORMATION);
			}
		}
	}
}

void CZeldaEditCharaStatsDlg::save_players()
{
	if (save != nullptr)
	{
		int unused_charas = 0;

		for (int i = 0; i < save->vs_players.size(); i++)
		{
			CString s_player_name(save->get_player(i)->get_name().c_str());
			CString s_player_lvl;
			CString s_player_exp;
			CString s_player_atk;
			CButton *cb_check;

			if (s_player_name == L"???")
			{
				unused_charas++;
				continue;
			}

			GetDlgItemText((IDC_EDIT_CHARA_LVL1 + i - unused_charas), s_player_lvl);
			int i_player_lvl = _wtof(s_player_lvl);

			GetDlgItemText((IDC_EDIT_CHARA_EXP1 + i - unused_charas), s_player_exp);
			int i_player_exp = _wtof(s_player_exp);

			GetDlgItemText((IDC_EDIT_CHARA_ATK1 + i - unused_charas), s_player_atk);
			int i_player_atk = _wtof(s_player_atk);

			cb_check = (CButton*)GetDlgItem((IDC_CHECK_CHARA_UNLOCK1 + i - unused_charas));
			bool b_player_is_unlock = cb_check->GetCheck();

			save->get_player(i)->set_lvl(i_player_lvl);
			save->get_player(i)->set_exp(i_player_exp);
			save->get_player(i)->set_atk(i_player_atk);
			save->get_player(i)->set_isUnlock(b_player_is_unlock);
			save->get_player(i)->save_Player();
		}

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
	CZeldaEditAdventureModeItem dlg(NULL, 0);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaStatsDlg::OnMenuEditAmGsmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaStatsDlg::OnMenuEditAmMqmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditCharaStatsDlg::OnMenuEditAmTlmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 3);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditCharaStatsDlg::OnMenuEditAmTmmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 4);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditCharaStatsDlg::OnBnClickedCharaMaxExpAll()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.

	if (save != nullptr)
	{
		int unused_charas = 0;

		for (int i = 0; i < save->vs_players.size(); i++)
		{
			CString s_player_name(save->get_player(i)->get_name().c_str());

			if (s_player_name == L"???")
			{
				unused_charas++;
				continue;
			}

			save->get_player(i)->set_exp(HWLSaveEdit::HWLPlayer::playerEXPMax);
			save->get_player(i)->save_Player();
		}

		this->UpdateData();

		CString str("Finish! All needed Values are updated.");
		MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
	}

}


void CZeldaEditCharaStatsDlg::OnBnClickedCharaMaxAtkAll()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.

	if (save != nullptr)
	{
		int unused_charas = 0;

		for (int i = 0; i < save->vs_players.size(); i++)
		{
			CString s_player_name(save->get_player(i)->get_name().c_str());

			if (s_player_name == L"???")
			{
				unused_charas++;
				continue;
			}

			save->get_player(i)->set_atk(HWLSaveEdit::HWLPlayer::playerATKMax);
			save->get_player(i)->save_Player();
		}

		this->UpdateData();

		CString str("Finish! All needed Values are updated.");
		MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);

	}
}


void CZeldaEditCharaStatsDlg::OnBnClickedCharaUnlockAll()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.

	if (save != nullptr)
	{
		int unused_charas = 0;
		bool b_no_weapon = false;
		for (int i = 0; i < save->vs_players.size(); i++)
		{
			CString s_player_name(save->get_player(i)->get_name().c_str());
			CButton *cb_check;

			if (s_player_name == L"???")
			{
				unused_charas++;
				continue;
			}

			save->get_player(i)->set_isUnlock(true);

			//Check if the character hasn't a default weapon
			if (save->get_player(i)->get_weapon_count(0) == 0)
			{
				b_no_weapon = true;
				save->generate_default_weapon(i, 0, 0);
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
