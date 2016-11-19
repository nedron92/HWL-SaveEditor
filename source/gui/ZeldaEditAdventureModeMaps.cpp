// CZeldaEditAdventureModeMaps.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZeldaHWLSaveEditorGUI.h"
#include "ZeldaEditAdventureModeMaps.h"
#include "afxdialogex.h"


// CZeldaEditAdventureModeMaps-Dialogfeld

IMPLEMENT_DYNAMIC(CZeldaEditAdventureModeMaps, CDialogEx)

CZeldaEditAdventureModeMaps::CZeldaEditAdventureModeMaps(CWnd* pParent /*=NULL*/, int i_map)
: CDialogEx(CZeldaEditAdventureModeMaps::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->i_map = i_map;
	this->i_skipped_maps = 0;
}

CZeldaEditAdventureModeMaps::~CZeldaEditAdventureModeMaps()
{
}

BOOL CZeldaEditAdventureModeMaps::OnInitDialog()
{
	//calculate the disabled-Items and remove the Menu-Entry, if neccessary
	CZeldaHWLSaveEditorGUIApp::calc_disabled_MenuItems(GetMenu()->GetSubMenu(1));
	return CDialogEx::OnInitDialog();
}

void CZeldaEditAdventureModeMaps::DoDataExchange(CDataExchange* pDX)
{
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//menu
	CMenu *cm_menu = GetMenu();
	CMenu* cm_submenu = cm_menu->GetSubMenu(1);
	cm_submenu->CheckMenuItem(4, MF_CHECKED | MF_BYPOSITION);

	//get the save-content
	save = CZeldaHWLSaveEditorGUIApp::save;

	
	if (save != nullptr)
	{
		if (this->i_map > -1)
		{
			if (this->i_map >= save->get_adventureMode_maxMaps() || save->get_amMap(this->i_map)->get_isDisabled())
			{
				this->i_skipped_maps = 0;
				this->i_map = 0;
			}

			cm_submenu = cm_submenu->GetSubMenu(4);

			for (int i = 0; i < save->get_adventureMode_maxMaps(); i++)
			{
				cm_submenu->CheckMenuItem(i, MF_UNCHECKED | MF_BYPOSITION);
			}
			
			cm_submenu->CheckMenuItem(this->i_map, MF_CHECKED | MF_BYPOSITION);
			CString cs_amMap_MapName(save->get_amMap(this->i_map)->get_name().c_str());
			SetDlgItemText(IDC_AM_MAPNAME, cs_amMap_MapName);
			

			if (this->i_map <= 0)
				GetDlgItem(IDC_AMMAP_PAGE_PREVIOUS)->EnableWindow(false);
			else
				GetDlgItem(IDC_AMMAP_PAGE_PREVIOUS)->EnableWindow(true);

			if (this->i_map + 1 >= save->get_adventureMode_maxMaps() - HWLSaveEdit::HWLAdventureModeMaps::get_disabledMapCounter())
				GetDlgItem(IDC_AMMAP_PAGE_NEXT)->EnableWindow(false);
			else
				GetDlgItem(IDC_AMMAP_PAGE_NEXT)->EnableWindow(true);
			
			
			for (int i = IDC_EDIT_AMITEM1; i <= IDC_EDIT_AMITEM12; i++)
			{
				GetDlgItem(i)->EnableWindow(true);
				GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
			}

			for (int i = IDC_STATIC_AMITEM1; i <= IDC_STATIC_AMITEM12; i++)
			{
				GetDlgItem(i)->EnableWindow(true);
				GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
			}
			

			CString s_map_count;
			s_map_count.Format(L"%d / %d", (this->i_map - this->i_skipped_maps) + 1, save->get_adventureMode_maxMaps() - HWLSaveEdit::HWLAdventureModeMaps::get_disabledMapCounter());
			SetDlgItemText(IDC_STATIC_MAP_COUNT, s_map_count);
			
			this->calc_amItems();
		}
	}else
	{
		SetDlgItemText(IDC_AM_MAPNAME, L"");

		for (int i = IDC_EDIT_AMITEM1; i <= IDC_EDIT_AMITEM12; i++)
		{
			SetDlgItemText(i, L"");
			GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
			GetDlgItem(i)->EnableWindow(false);
		}

		for (int i = IDC_STATIC_AMITEM1; i <= IDC_STATIC_AMITEM12; i++)
		{
			SetDlgItemText(i, L"AM-Items");
			GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
		}

		SetDlgItemText(IDC_STATIC_MAP_COUNT, L"0 / 0");
		GetDlgItem(IDC_AMMAP_PAGE_PREVIOUS)->EnableWindow(false);
		GetDlgItem(IDC_AMMAP_PAGE_NEXT)->EnableWindow(false);
	}


	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZeldaEditAdventureModeMaps, CDialogEx)
	ON_COMMAND(ID_MENU_MAIN_EXIT, &CZeldaEditAdventureModeMaps::OnMenuMainExit)
	ON_COMMAND(ID_MENU_EDIT_GENERAL, &CZeldaEditAdventureModeMaps::OnMenuEditGeneral)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_STATS, &CZeldaEditAdventureModeMaps::OnMenuEditCharactersStats)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_BRONZE, &CZeldaEditAdventureModeMaps::OnMenuEditMaterialsBronze)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_SILVER, &CZeldaEditAdventureModeMaps::OnMenuEditMaterialsSilver)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_GOLD, &CZeldaEditAdventureModeMaps::OnMenuEditMaterialsGold)
	ON_COMMAND(ID_MENU_EDIT_FAIRYFOODS, &CZeldaEditAdventureModeMaps::OnMenuEditFairyfoods)
	ON_BN_CLICKED(ID_SAVE, &CZeldaEditAdventureModeMaps::OnBnClickedSave)
	ON_BN_CLICKED(ID_EXIT, &CZeldaEditAdventureModeMaps::OnBnClickedExit)
	ON_BN_CLICKED(IDC_AMITEM_PAGE_PREVIOUS, &CZeldaEditAdventureModeMaps::OnBnClickedAMItemPagePrevious)
	ON_BN_CLICKED(IDC_AMITEM_PAGE_NEXT, &CZeldaEditAdventureModeMaps::OnBnClickedAMItemPageNext)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_EDIT_AMITEM1, IDC_EDIT_AMITEM12, &OnEnChangeValueEdit)
	ON_COMMAND(ID_MENU_EDIT_AM_AVMAP, &CZeldaEditAdventureModeMaps::OnMenuEditAmAvmap)
	ON_COMMAND(ID_MENU_EDIT_AM_GSMAP, &CZeldaEditAdventureModeMaps::OnMenuEditAmGsmap)
	ON_COMMAND(ID_MENU_EDIT_AM_MQMAP, &CZeldaEditAdventureModeMaps::OnMenuEditAmMqmap)
	ON_BN_CLICKED(IDC_AMITEM_MAX_VALUE_MAP, &CZeldaEditAdventureModeMaps::OnBnClickedAmitemMaxValueMap)
	ON_COMMAND(ID_MENU_EDIT_AM_TLMAP, &CZeldaEditAdventureModeMaps::OnMenuEditAmTlmap)
	ON_COMMAND(ID_MENU_EDIT_AM_TMMAP, &CZeldaEditAdventureModeMaps::OnMenuEditAmTmmap)
	ON_COMMAND(ID_MENU_EDIT_FAIRIES, &CZeldaEditAdventureModeMaps::OnMenuEditFairies)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_WEAPONS, &CZeldaEditAdventureModeMaps::OnMenuEditCharactersWeapons)
	ON_COMMAND(ID_MENU_EDIT_AM_MWWMAP, &CZeldaEditAdventureModeMaps::OnMenuEditAmMwwmap)
	ON_COMMAND(ID_MENU_EDIT_AM_KIMAP, &CZeldaEditAdventureModeMaps::OnMenuEditAmKimap)
	ON_COMMAND(ID_MENU_EDIT_AM_GTMAP, &CZeldaEditAdventureModeMaps::OnMenuEditAmGtmap)
	ON_BN_CLICKED(IDC_AMMAP_MAX_VALUE_ALL, &CZeldaEditAdventureModeMaps::OnBnClickedAmmapMaxValueAll)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_OVERVIEW, &CZeldaEditAdventureModeMaps::OnMenuEditCharactersOverview)
END_MESSAGE_MAP()


// CZeldaEditAdventureModeMaps-Meldungshandler
void CZeldaEditAdventureModeMaps::OnMenuMainExit()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeMaps::OnOK();
}

void CZeldaEditAdventureModeMaps::OnMenuEditGeneral()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditGeneralDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditAdventureModeMaps::OnMenuEditCharactersStats()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaStatsDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditAdventureModeMaps::OnMenuEditMaterialsBronze()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 0);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditAdventureModeMaps::OnMenuEditMaterialsSilver()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditAdventureModeMaps::OnMenuEditMaterialsGold()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditAdventureModeMaps::OnMenuEditFairyfoods()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyFoods dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditAdventureModeMaps::OnBnClickedSave()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		try
		{
			this->save_amItems();
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

void CZeldaEditAdventureModeMaps::OnBnClickedExit()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CZeldaEditAdventureModeMaps::OnOK();
}

void CZeldaEditAdventureModeMaps::OnBnClickedAMItemPagePrevious()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_amItems();

	int i_old_map_id = this->i_map;
	for (int i = this->i_map - 1; i > 0; i--)
	{
		if (save->get_amMap(i)->get_isDisabled())
		{
			if (this->i_skipped_maps > 0)
				this->i_skipped_maps--;
			continue;
		}
		else
		{
			this->i_map = i;
			break;
		}
	}

	if (this->i_map == i_old_map_id)
		this->i_map = 0;

	this->UpdateData();
}


void CZeldaEditAdventureModeMaps::OnBnClickedAMItemPageNext()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_amItems();

	int i_old_map_id = this->i_map;
	for (int i = this->i_map + 1; i < save->get_adventureMode_maxMaps(); i++)
	{
		if (save->get_amMap(i)->get_isDisabled())
		{
			this->i_skipped_maps++;
			continue;
		}
		else
		{
			this->i_map = i;
			break;
		}
	}

	if (this->i_map == i_old_map_id)
		this->i_map = 0;

	this->UpdateData();
}

void CZeldaEditAdventureModeMaps::OnMenuEditAmAvmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	if (this->i_map != 0)
	{
		CZeldaEditAdventureModeMaps dlg(NULL, 0);
		EndDialog(this->IDD);
		dlg.DoModal();
	}
}


void CZeldaEditAdventureModeMaps::OnMenuEditAmGsmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	if (this->i_map != 1)
	{
		CZeldaEditAdventureModeMaps dlg(NULL, 1);
		EndDialog(this->IDD);
		dlg.DoModal();
	}

}


void CZeldaEditAdventureModeMaps::OnMenuEditAmMqmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	if (this->i_map != 2)
	{
		CZeldaEditAdventureModeMaps dlg(NULL, 2);
		EndDialog(this->IDD);
		dlg.DoModal();
	}

}

void CZeldaEditAdventureModeMaps::OnMenuEditAmTlmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	if (this->i_map != 3)
	{
		CZeldaEditAdventureModeMaps dlg(NULL, 3);
		EndDialog(this->IDD);
		dlg.DoModal();
	}

}

void CZeldaEditAdventureModeMaps::OnMenuEditAmTmmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	if (this->i_map != 4)
	{
		CZeldaEditAdventureModeMaps dlg(NULL, 4);
		EndDialog(this->IDD);
		dlg.DoModal();
	}
}

void CZeldaEditAdventureModeMaps::OnMenuEditAmMwwmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	if (this->i_map != 5)
	{
		CZeldaEditAdventureModeMaps dlg(NULL, 5);
		EndDialog(this->IDD);
		dlg.DoModal();
	}
}

void CZeldaEditAdventureModeMaps::OnMenuEditAmKimap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	if (this->i_map != 6)
	{
		CZeldaEditAdventureModeMaps dlg(NULL, 6);
		EndDialog(this->IDD);
		dlg.DoModal();
	}
}


void CZeldaEditAdventureModeMaps::OnMenuEditAmGtmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	if (this->i_map != 7)
	{
		CZeldaEditAdventureModeMaps dlg(NULL, 7);
		EndDialog(this->IDD);
		dlg.DoModal();
	}
}


void CZeldaEditAdventureModeMaps::calc_amItems()
{
	
	for (int i = 0; i < HWLSaveEdit::HWLAdventureModeMaps::amm_MaxItemsPerMap; i++)
	{
		CString s_amItem_name( save->get_amMap(this->i_map)->get_amItem(i)->get_name().c_str() );
		CString s_amItem_value;
		s_amItem_value.Format(L"%d", save->get_amMap(this->i_map)->get_amItem(i)->get_value());

		SetDlgItemText((IDC_STATIC_AMITEM1 + i), s_amItem_name + L": ");
		SetDlgItemText((IDC_EDIT_AMITEM1 + i), s_amItem_value);

		CEdit *e_test = (CEdit*)GetDlgItem((IDC_EDIT_AMITEM1 + i));
		CString cs_max_chars;
		cs_max_chars.Format(L"%d", HWLSaveEdit::HWLAdventureModeItems::amItemValueMax);
		e_test->SetLimitText(cs_max_chars.GetLength() + 1);
	}
	
}

void CZeldaEditAdventureModeMaps::save_amItems()
{
	
	for (int i = 0; i < HWLSaveEdit::HWLAdventureModeMaps::amm_MaxItemsPerMap; i++)
	{
		CString s_amItem_value;

		GetDlgItemText((IDC_EDIT_AMITEM1 + i), s_amItem_value);
		int i_amItem_value = _wtof(s_amItem_value);

		save->get_amMap(this->i_map)->get_amItem(i)->set_value(i_amItem_value);
		save->get_amMap(this->i_map)->get_amItem(i)->save_AMItem();
	}
	
}

void CZeldaEditAdventureModeMaps::OnEnChangeValueEdit(UINT nID)
{
	if (SendDlgItemMessage(nID, EM_GETMODIFY, 0, 0))
	{
		if (save != nullptr)
		{
			CString test;
			CEdit *e_test = (CEdit*)GetDlgItem(nID);
			CString cs_max_chars;
			cs_max_chars.Format(L"%d", HWLSaveEdit::HWLAdventureModeItems::amItemValueMax);
			e_test->SetLimitText(cs_max_chars.GetLength()+1);
			GetDlgItemText(nID, test);
			int i_test = _wtoi(test);

			if (i_test > HWLSaveEdit::HWLAdventureModeItems::amItemValueMax)
			{
				test.Format(L"%d", HWLSaveEdit::HWLAdventureModeItems::amItemValueMax);
				SetDlgItemText(nID, test);
				e_test->SetLimitText(cs_max_chars.GetLength());
			}

		}
	}
}

void CZeldaEditAdventureModeMaps::OnBnClickedAmitemMaxValueMap()
{
	
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		for (int i = 0; i < HWLSaveEdit::HWLAdventureModeMaps::amm_MaxItemsPerMap; i++)
		{
			save->get_amMap(this->i_map)->get_amItem(i)->set_value(HWLSaveEdit::HWLAdventureModeItems::amItemValueMax);
			save->get_amMap(this->i_map)->get_amItem(i)->save_AMItem();
		}

		this->UpdateData();

		CString str("Finish! All needed Values are updated.");
		MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
	}
	
}

void CZeldaEditAdventureModeMaps::OnBnClickedAmmapMaxValueAll()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		for (int i = 0; i < save->get_adventureMode_maxMaps(); i++)
		{
			if (save->get_amMap(i)->get_isDisabled())
				continue;

			for (int j = 0; j < HWLSaveEdit::HWLAdventureModeMaps::amm_MaxItemsPerMap; j++)
			{
				save->get_amMap(i)->get_amItem(j)->set_value(HWLSaveEdit::HWLAdventureModeItems::amItemValueMax);
				save->get_amMap(i)->get_amItem(j)->save_AMItem();
			}
		}



		this->UpdateData();

		CString str("Finish! All needed Values are updated.");
		MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
	}
}


void CZeldaEditAdventureModeMaps::OnMenuEditFairies()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditAdventureModeMaps::OnMenuEditCharactersWeapons()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaWeaponsDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}



void CZeldaEditAdventureModeMaps::OnMenuEditCharactersOverview()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaOverviewDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}
