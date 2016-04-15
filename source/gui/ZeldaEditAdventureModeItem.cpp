// ZeldaEditAdventureModeItem.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZeldaHWLSaveEditorGUI.h"
#include "ZeldaEditAdventureModeItem.h"
#include "afxdialogex.h"


// CZeldaEditAdventureModeItem-Dialogfeld

IMPLEMENT_DYNAMIC(CZeldaEditAdventureModeItem, CDialogEx)

CZeldaEditAdventureModeItem::CZeldaEditAdventureModeItem(CWnd* pParent /*=NULL*/, int i_type)
	: CDialogEx(CZeldaEditAdventureModeItem::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->i_type = i_type;
	this->i_map = i_type+1;
}

CZeldaEditAdventureModeItem::~CZeldaEditAdventureModeItem()
{
}

void CZeldaEditAdventureModeItem::DoDataExchange(CDataExchange* pDX)
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

	//own inits
	save = CZeldaHWLSaveEditorGUIApp::save;

	if (save != nullptr)
	{
		if (this->i_type > -1)
		{
			cm_submenu = cm_submenu->GetSubMenu(4);

			for (int i = 0; i < save->get_adventureMode_maxItemCount(); i++)
			{
				cm_submenu->CheckMenuItem(i, MF_UNCHECKED | MF_BYPOSITION);
			}

			cm_submenu->CheckMenuItem(this->i_type, MF_CHECKED | MF_BYPOSITION);
			this->i_map_max = save->get_adventureMode_maxItemCount();
			CString cs_amItem_type(save->get_amItem(0,this->i_type)->get_type(true).c_str());
			cs_amItem_type.Replace(L" Item", L"");
			SetDlgItemText(IDC_AM_MAPNAME, cs_amItem_type);


			if (this->i_map <= 1)
				GetDlgItem(IDC_AMITEM_PAGE_PREVIOUS)->EnableWindow(false);
			else
				GetDlgItem(IDC_AMITEM_PAGE_PREVIOUS)->EnableWindow(true);

			if (this->i_map >= this->i_map_max)
				GetDlgItem(IDC_AMITEM_PAGE_NEXT)->EnableWindow(false);
			else
				GetDlgItem(IDC_AMITEM_PAGE_NEXT)->EnableWindow(true);


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
			s_map_count.Format(L"%d / %d", this->i_map, this->i_map_max);
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
		GetDlgItem(IDC_AMITEM_PAGE_PREVIOUS)->EnableWindow(false);
		GetDlgItem(IDC_AMITEM_PAGE_NEXT)->EnableWindow(false);
	}


	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZeldaEditAdventureModeItem, CDialogEx)
	ON_COMMAND(ID_MENU_MAIN_EXIT, &CZeldaEditAdventureModeItem::OnMenuMainExit)
	ON_COMMAND(ID_MENU_EDIT_GENERAL, &CZeldaEditAdventureModeItem::OnMenuEditGeneral)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_STATS, &CZeldaEditAdventureModeItem::OnMenuEditCharactersStats)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_BRONZE, &CZeldaEditAdventureModeItem::OnMenuEditMaterialsBronze)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_SILVER, &CZeldaEditAdventureModeItem::OnMenuEditMaterialsSilver)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_GOLD, &CZeldaEditAdventureModeItem::OnMenuEditMaterialsGold)
	ON_COMMAND(ID_MENU_EDIT_FAIRYFOODS, &CZeldaEditAdventureModeItem::OnMenuEditFairyfoods)
	ON_BN_CLICKED(ID_SAVE, &CZeldaEditAdventureModeItem::OnBnClickedSave)
	ON_BN_CLICKED(ID_EXIT, &CZeldaEditAdventureModeItem::OnBnClickedExit)
	ON_BN_CLICKED(IDC_AMITEM_PAGE_PREVIOUS, &CZeldaEditAdventureModeItem::OnBnClickedAMItemPagePrevious)
	ON_BN_CLICKED(IDC_AMITEM_PAGE_NEXT, &CZeldaEditAdventureModeItem::OnBnClickedAMItemPageNext)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_EDIT_AMITEM1, IDC_EDIT_AMITEM12, &OnEnChangeValueEdit)
	ON_COMMAND(ID_MENU_EDIT_AM_AVMAP, &CZeldaEditAdventureModeItem::OnMenuEditAmAvmap)
	ON_COMMAND(ID_MENU_EDIT_AM_GSMAP, &CZeldaEditAdventureModeItem::OnMenuEditAmGsmap)
	ON_COMMAND(ID_MENU_EDIT_AM_MQMAP, &CZeldaEditAdventureModeItem::OnMenuEditAmMqmap)
	ON_BN_CLICKED(IDC_AMITEM_MAX_VALUE_MAP, &CZeldaEditAdventureModeItem::OnBnClickedAmitemMaxValueMap)
	ON_COMMAND(ID_MENU_EDIT_AM_TLMAP, &CZeldaEditAdventureModeItem::OnMenuEditAmTlmap)
	ON_COMMAND(ID_MENU_EDIT_AM_TMMAP, &CZeldaEditAdventureModeItem::OnMenuEditAmTmmap)
	ON_COMMAND(ID_MENU_EDIT_FAIRIES, &CZeldaEditAdventureModeItem::OnMenuEditFairies)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_WEAPONS, &CZeldaEditAdventureModeItem::OnMenuEditCharactersWeapons)
END_MESSAGE_MAP()


// CZeldaEditAdventureModeItem-Meldungshandler
void CZeldaEditAdventureModeItem::OnMenuMainExit()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem::OnOK();
}

void CZeldaEditAdventureModeItem::OnMenuEditGeneral()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditGeneralDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditAdventureModeItem::OnMenuEditCharactersStats()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaStatsDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditAdventureModeItem::OnMenuEditMaterialsBronze()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 0);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditAdventureModeItem::OnMenuEditMaterialsSilver()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditAdventureModeItem::OnMenuEditMaterialsGold()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditAdventureModeItem::OnMenuEditFairyfoods()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyFoods dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditAdventureModeItem::OnBnClickedSave()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		try
		{
			this->save_amItems();
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

void CZeldaEditAdventureModeItem::OnBnClickedExit()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CZeldaEditAdventureModeItem::OnOK();
}

void CZeldaEditAdventureModeItem::OnBnClickedAMItemPagePrevious()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_amItems();
	this->i_map--;
	this->i_type--;
	this->UpdateData();
}


void CZeldaEditAdventureModeItem::OnBnClickedAMItemPageNext()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_amItems();
	this->i_map++;
	this->i_type++;
	this->UpdateData();
}

void CZeldaEditAdventureModeItem::OnMenuEditAmAvmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	if (this->i_type != 0)
	{
		CZeldaEditAdventureModeItem dlg(NULL, 0);
		EndDialog(this->IDD);
		dlg.DoModal();
	}
}


void CZeldaEditAdventureModeItem::OnMenuEditAmGsmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	if (this->i_type != 1)
	{
		CZeldaEditAdventureModeItem dlg(NULL, 1);
		EndDialog(this->IDD);
		dlg.DoModal();
	}

}


void CZeldaEditAdventureModeItem::OnMenuEditAmMqmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	if (this->i_type != 2)
	{
		CZeldaEditAdventureModeItem dlg(NULL, 2);
		EndDialog(this->IDD);
		dlg.DoModal();
	}

}

void CZeldaEditAdventureModeItem::OnMenuEditAmTlmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	if (this->i_type != 3)
	{
		CZeldaEditAdventureModeItem dlg(NULL, 3);
		EndDialog(this->IDD);
		dlg.DoModal();
	}

}

void CZeldaEditAdventureModeItem::OnMenuEditAmTmmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	if (this->i_type != 4)
	{
		CZeldaEditAdventureModeItem dlg(NULL, 4);
		EndDialog(this->IDD);
		dlg.DoModal();
	}
}



void CZeldaEditAdventureModeItem::calc_amItems()
{
	for (int i = 0; i < this->maxAMItemsShown; i++)
	{
		CString s_amItem_name(save->get_amItem(i, this->i_type)->get_name().c_str());
		CString s_amItem_value;
		s_amItem_value.Format(L"%d", save->get_amItem(i, this->i_type)->get_value());

		SetDlgItemText((IDC_STATIC_AMITEM1 + i), s_amItem_name + L": ");
		SetDlgItemText((IDC_EDIT_AMITEM1 + i), s_amItem_value);

		CEdit *e_test = (CEdit*)GetDlgItem((IDC_EDIT_AMITEM1 + i));
		CString cs_max_chars;
		cs_max_chars.Format(L"%d", HWLSaveEdit::HWLAdventureModeItems::amItemValueMax);
		e_test->SetLimitText(cs_max_chars.GetLength() + 1);
	}
}

void CZeldaEditAdventureModeItem::save_amItems()
{
	for (int i = 0; i < this->maxAMItemsShown; i++)
	{
		CString s_amItem_value;

		GetDlgItemText((IDC_EDIT_AMITEM1 + i), s_amItem_value);
		int i_amItem_value = _wtof(s_amItem_value);

		save->get_amItem(i, this->i_type)->set_value(i_amItem_value);
		save->get_amItem(i, this->i_type)->save_AMItem();
	}
}

void CZeldaEditAdventureModeItem::OnEnChangeValueEdit(UINT nID)
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

void CZeldaEditAdventureModeItem::OnBnClickedAmitemMaxValueMap()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		for (int i = 0; i < this->maxAMItemsShown; i++)
		{
			save->get_amItem(i, this->i_type)->set_value(HWLSaveEdit::HWLAdventureModeItems::amItemValueMax);
			save->get_amItem(i, this->i_type)->save_AMItem();
		}

		this->UpdateData();

		CString str("Finish! All needed Values are updated.");
		MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
	}

}



void CZeldaEditAdventureModeItem::OnMenuEditFairies()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditAdventureModeItem::OnMenuEditCharactersWeapons()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaWeaponsDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}
