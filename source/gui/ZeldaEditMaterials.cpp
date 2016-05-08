// ZeldaEditMaterials.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZeldaHWLSaveEditorGUI.h"
#include "ZeldaEditMaterials.h"
#include "afxdialogex.h"


// CZeldaEditMaterials-Dialogfeld

IMPLEMENT_DYNAMIC(CZeldaEditMaterials, CDialogEx)


CZeldaEditMaterials::CZeldaEditMaterials(CWnd* pParent /*=NULL*/, int i_type)
	: CDialogEx(CZeldaEditMaterials::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->i_type = i_type;
	this->i_page = 1;
}

CZeldaEditMaterials::~CZeldaEditMaterials()
{
}

void CZeldaEditMaterials::DoDataExchange(CDataExchange* pDX)
{
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//menu
	CMenu *cm_menu = GetMenu();
	CMenu* cm_submenu = cm_menu->GetSubMenu(1);
	cm_submenu->CheckMenuItem(2, MF_CHECKED | MF_BYPOSITION);

	//own inits
	save = CZeldaHWLSaveEditorGUIApp::save;

	if (save != nullptr)
	{

		if (this->i_type > -1)
		{
			cm_submenu = cm_submenu->GetSubMenu(2);
			cm_submenu->CheckMenuItem(this->i_type, MF_CHECKED | MF_BYPOSITION);

			switch (this->i_type)
			{
			case 0: {
						this->i_page_max = (HWLSaveEdit::HWLMaterial::vs_bronzeMaterials.size() / this->maxMaterialsShown) + 1;
						CString cs_material_type(save->get_material(0, 0)->get_type(true).c_str());
						SetDlgItemText(IDC_MATERIAL_TYPE, cs_material_type );
						break;
			}

			case 1: {
						this->i_page_max = (HWLSaveEdit::HWLMaterial::vs_silverMaterials.size() / this->maxMaterialsShown) + 1;
						CString cs_material_type(save->get_material(0, 1)->get_type(true).c_str());
						SetDlgItemText(IDC_MATERIAL_TYPE, cs_material_type);
						break;
			}

			case 2: {
						this->i_page_max = (HWLSaveEdit::HWLMaterial::vs_goldMaterials.size() / this->maxMaterialsShown) + 1;
						CString cs_material_type(save->get_material(0, 2)->get_type(true).c_str());
						SetDlgItemText(IDC_MATERIAL_TYPE, cs_material_type);
						break;
			}

			}

			if (this->i_page <= 1)
				GetDlgItem(IDC_MATERIAL_PAGE_PREVIOUS)->EnableWindow(false);
			else
				GetDlgItem(IDC_MATERIAL_PAGE_PREVIOUS)->EnableWindow(true);

			if (this->i_page >= this->i_page_max)
				GetDlgItem(IDC_MATERIAL_PAGE_NEXT)->EnableWindow(false);
			else
				GetDlgItem(IDC_MATERIAL_PAGE_NEXT)->EnableWindow(true);


			for (int i = IDC_EDIT_MATERIAL1; i <= IDC_EDIT_MATERIAL30; i++)
			{
				GetDlgItem(i)->EnableWindow(true);
				GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
			}

			for (int i = IDC_STATIC_MATERIAL1; i <= IDC_STATIC_MATERIAL30; i++)
			{
				GetDlgItem(i)->EnableWindow(true);
				GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
			}


			CString s_page_count;
			s_page_count.Format(L"%d / %d", this->i_page, this->i_page_max);
			SetDlgItemText(IDC_STATIC_PAGE_COUNT, s_page_count);

			this->calc_materials();
		}
	}else
	{
		SetDlgItemText(IDC_MATERIAL_TYPE, L"");

		for (int i = IDC_EDIT_MATERIAL1; i <= IDC_EDIT_MATERIAL30; i++)
		{
			SetDlgItemText(i, L"");
			GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
			GetDlgItem(i)->EnableWindow(false);
		}

		for (int i = IDC_STATIC_MATERIAL1; i <= IDC_STATIC_MATERIAL30; i++)
		{
			SetDlgItemText(i, L"Material");
			GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
		}

		SetDlgItemText(IDC_STATIC_PAGE_COUNT, L"0 / 0");
		GetDlgItem(IDC_MATERIAL_PAGE_PREVIOUS)->EnableWindow(false);
		GetDlgItem(IDC_MATERIAL_PAGE_NEXT)->EnableWindow(false);


	}


	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZeldaEditMaterials, CDialogEx)
	ON_COMMAND(ID_MENU_EDIT_GENERAL, &CZeldaEditMaterials::OnMenuEditGeneral)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_STATS, &CZeldaEditMaterials::OnMenuEditCharactersStats)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_BRONZE, &CZeldaEditMaterials::OnMenuEditMaterialsBronze)
	ON_BN_CLICKED(ID_EXIT, &CZeldaEditMaterials::OnBnClickedExit)
	ON_BN_CLICKED(IDCANCEL, &CZeldaEditMaterials::OnBnClickedCancel)
	ON_BN_CLICKED(ID_SAVE, &CZeldaEditMaterials::OnBnClickedSave)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_EDIT_MATERIAL1, IDC_EDIT_MATERIAL30, &OnEnChangeValueEdit)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_SILVER, &CZeldaEditMaterials::OnMenuEditMaterialsSilver)
	ON_BN_CLICKED(IDC_MATERIAL_PAGE_PREVIOUS, &CZeldaEditMaterials::OnBnClickedMaterialPagePrevious)
	ON_BN_CLICKED(IDC_MATERIAL_PAGE_NEXT, &CZeldaEditMaterials::OnBnClickedMaterialPageNext)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_GOLD, &CZeldaEditMaterials::OnMenuEditMaterialsGold)
	ON_COMMAND(ID_MENU_MAIN_EXIT, &CZeldaEditMaterials::OnMenuMainExit)
	ON_COMMAND(ID_MENU_EDIT_FAIRYFOODS, &CZeldaEditMaterials::OnMenuEditFairyfoods)
	ON_COMMAND(ID_MENU_EDIT_AM_AVMAP, &CZeldaEditMaterials::OnMenuEditAmAvmap)
	ON_COMMAND(ID_MENU_EDIT_AM_GSMAP, &CZeldaEditMaterials::OnMenuEditAmGsmap)
	ON_COMMAND(ID_MENU_EDIT_AM_MQMAP, &CZeldaEditMaterials::OnMenuEditAmMqmap)
	ON_BN_CLICKED(IDC_MATERIAL_MAX_VALUE_ALL, &CZeldaEditMaterials::OnBnClickedMaterialMaxValueAll)
	ON_COMMAND(ID_MENU_EDIT_AM_TLMAP, &CZeldaEditMaterials::OnMenuEditAmTlmap)
	ON_COMMAND(ID_MENU_EDIT_AM_TMMAP, &CZeldaEditMaterials::OnMenuEditAmTmmap)
	ON_COMMAND(ID_MENU_EDIT_FAIRIES, &CZeldaEditMaterials::OnMenuEditFairies)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_WEAPONS, &CZeldaEditMaterials::OnMenuEditCharactersWeapons)
END_MESSAGE_MAP()


// CZeldaEditMaterials-Meldungshandler


void CZeldaEditMaterials::OnMenuEditGeneral()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditGeneralDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditMaterials::OnMenuEditCharactersStats()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaStatsDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditMaterials::OnBnClickedExit()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CZeldaEditMaterials::OnOK();
}


void CZeldaEditMaterials::OnBnClickedCancel()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CDialogEx::OnCancel();
}


void CZeldaEditMaterials::OnBnClickedSave()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		try
		{
			this->save_materials();
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

void CZeldaEditMaterials::calc_materials()
{
	int i_size;
	switch (this->i_type)
	{
	case 0: {
				i_size = HWLSaveEdit::HWLMaterial::vs_bronzeMaterials.size();
				break;
	}

	case 1: {
				i_size = HWLSaveEdit::HWLMaterial::vs_silverMaterials.size();
				break;
	}

	case 2: {
				i_size = HWLSaveEdit::HWLMaterial::vs_goldMaterials.size();
				break;
	}

	}

	int i_diff = i_size - ((this->i_page - 1) * this->maxMaterialsShown);

	for (int i = 0; i < this->maxMaterialsShown; i++)
	{
		if (i < i_diff)
		{
			int i_material_id = i + ((this->i_page - 1) * this->maxMaterialsShown);
			CString s_material_name(save->get_material(i_material_id, this->i_type)->get_name().c_str());
			CString s_material_value;
			s_material_value.Format(L"%d", save->get_material(i_material_id, this->i_type)->get_value());

			SetDlgItemText((IDC_STATIC_MATERIAL1 + i), s_material_name + L": ");
			SetDlgItemText((IDC_EDIT_MATERIAL1 + i), s_material_value);

			CEdit *e_test = (CEdit*)GetDlgItem((IDC_EDIT_MATERIAL1 + i));
			CString cs_max_chars;
			cs_max_chars.Format(L"%d", HWLSaveEdit::HWLMaterial::materialValueMax);
			e_test->SetLimitText(cs_max_chars.GetLength() + 1);
		}
		else{
			if (GetDlgItem(IDC_STATIC_MATERIAL1 + i)->IsWindowVisible() || this->i_type == 0)
				GetDlgItem(IDC_STATIC_MATERIAL1 + i)->ShowWindow(SW_HIDE);

			if (GetDlgItem(IDC_EDIT_MATERIAL1 + i)->IsWindowVisible() || this->i_type == 0)
				GetDlgItem(IDC_EDIT_MATERIAL1 + i)->ShowWindow(SW_HIDE);

		}

	}
}

void CZeldaEditMaterials::save_materials()
{


	int i_size;
	switch (this->i_type)
	{
	case 0: {
				i_size = HWLSaveEdit::HWLMaterial::vs_bronzeMaterials.size();
				break;
	}

	case 1: {
				i_size = HWLSaveEdit::HWLMaterial::vs_silverMaterials.size();
				break;
	}

	case 2: {
				i_size = HWLSaveEdit::HWLMaterial::vs_goldMaterials.size();
				break;
	}

	}

	int i_diff = i_size - ((this->i_page - 1) * this->maxMaterialsShown);

	for (int i = 0; i < this->maxMaterialsShown; i++)
	{
		if (i < i_diff)
		{
			int i_material_id = i + ((this->i_page - 1) * this->maxMaterialsShown);
			CString s_material_value;

			GetDlgItemText((IDC_EDIT_MATERIAL1 + i), s_material_value);
			int i_material_value = _wtof(s_material_value);

			save->get_material(i_material_id, this->i_type)->set_value(i_material_value);
			save->get_material(i_material_id, this->i_type)->save_Material();
		}
	}
}


void CZeldaEditMaterials::OnEnChangeValueEdit(UINT nID)
{
	if (SendDlgItemMessage(nID, EM_GETMODIFY, 0, 0))
	{
		if (save != nullptr)
		{
			CString test;
			CEdit *e_test = (CEdit*)GetDlgItem(nID);
			CString cs_max_chars;
			cs_max_chars.Format(L"%d", HWLSaveEdit::HWLMaterial::materialValueMax);
			e_test->SetLimitText(cs_max_chars.GetLength() + 1);
			GetDlgItemText(nID, test);
			int i_test = _wtoi(test);

			if (i_test > HWLSaveEdit::HWLMaterial::materialValueMax)
			{
				test.Format(L"%d", HWLSaveEdit::HWLMaterial::materialValueMax);
				SetDlgItemText(nID, test);
				e_test->SetLimitText(cs_max_chars.GetLength());
			}

		}
	}
}

void CZeldaEditMaterials::OnMenuEditMaterialsBronze()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	if (this->i_type != 0)
	{
		CZeldaEditMaterials dlg(NULL, 0);
		EndDialog(this->IDD);
		dlg.DoModal();
	}
}


void CZeldaEditMaterials::OnMenuEditMaterialsSilver()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	if (this->i_type != 1)
	{
		CZeldaEditMaterials dlg(NULL, 1);
		EndDialog(this->IDD);
		dlg.DoModal();
	}
}

void CZeldaEditMaterials::OnMenuEditMaterialsGold()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	if (this->i_type != 2)
	{
		CZeldaEditMaterials dlg(NULL, 2);
		EndDialog(this->IDD);
		dlg.DoModal();
	}
}


void CZeldaEditMaterials::OnBnClickedMaterialPagePrevious()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_materials();
	this->i_page--;
	this->UpdateData();
}


void CZeldaEditMaterials::OnBnClickedMaterialPageNext()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_materials();
	this->i_page++;
	this->UpdateData();
}




void CZeldaEditMaterials::OnMenuMainExit()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials::OnOK();
}


void CZeldaEditMaterials::OnMenuEditFairyfoods()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyFoods dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditMaterials::OnMenuEditAmAvmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 0);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditMaterials::OnMenuEditAmGsmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditMaterials::OnMenuEditAmMqmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditMaterials::OnMenuEditAmTlmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 3);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditMaterials::OnMenuEditAmTmmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 4);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditMaterials::OnBnClickedMaterialMaxValueAll()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		int i_size;
		switch (this->i_type)
		{
		case 0: {
					i_size = HWLSaveEdit::HWLMaterial::vs_bronzeMaterials.size();
					break;
		}

		case 1: {
					i_size = HWLSaveEdit::HWLMaterial::vs_silverMaterials.size();
					break;
		}

		case 2: {
					i_size = HWLSaveEdit::HWLMaterial::vs_goldMaterials.size();
					break;
		}

		}

		for (int i = 0; i < i_size; i++)
		{
			save->get_material(i, this->i_type)->set_value(HWLSaveEdit::HWLMaterial::materialValueMax);
			save->get_material(i, this->i_type)->save_Material();
		}

		this->UpdateData();

		CString str("Finish! All needed Values are updated.");
		MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
	}

}



void CZeldaEditMaterials::OnMenuEditFairies()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditMaterials::OnMenuEditCharactersWeapons()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaWeaponsDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}
