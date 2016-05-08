// ZeldaEditFairyFoods.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZeldaHWLSaveEditorGUI.h"
#include "ZeldaEditFairyFoods.h"
#include "afxdialogex.h"


// CZeldaEditFairyFoods-Dialogfeld

IMPLEMENT_DYNAMIC(CZeldaEditFairyFoods, CDialogEx)

CZeldaEditFairyFoods::CZeldaEditFairyFoods(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZeldaEditFairyFoods::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->i_page = 1;
}

CZeldaEditFairyFoods::~CZeldaEditFairyFoods()
{
}

void CZeldaEditFairyFoods::DoDataExchange(CDataExchange* pDX)
{
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//menu
	CMenu *cm_menu = GetMenu();
	CMenu* cm_submenu = cm_menu->GetSubMenu(1);
	cm_submenu->CheckMenuItem(3, MF_CHECKED | MF_BYPOSITION);

	//own inits
	save = CZeldaHWLSaveEditorGUIApp::save;

	if (save != nullptr)
	{
		this->i_page_max = (HWLSaveEdit::HWLFairyFood::vs_fairyFood.size() / this->maxFairyFoodsShown) + 1;

		if (this->i_page <= 1)
			GetDlgItem(IDC_FAIRYFOOD_PAGE_PREVIOUS)->EnableWindow(false);
		else
			GetDlgItem(IDC_FAIRYFOOD_PAGE_PREVIOUS)->EnableWindow(true);

		if (this->i_page >= this->i_page_max)
			GetDlgItem(IDC_FAIRYFOOD_PAGE_NEXT)->EnableWindow(false);
		else
			GetDlgItem(IDC_FAIRYFOOD_PAGE_NEXT)->EnableWindow(true);


		for (int i = IDC_EDIT_FAIRYFOOD1; i <= IDC_EDIT_FAIRYFOOD30; i++)
		{
			GetDlgItem(i)->EnableWindow(true);
			GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
		}

		for (int i = IDC_STATIC_FAIRYFOOD1; i <= IDC_STATIC_FAIRYFOOD30; i++)
		{
			GetDlgItem(i)->EnableWindow(true);
			GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
		}


		CString s_page_count;
		s_page_count.Format(L"%d / %d", this->i_page, this->i_page_max);
		SetDlgItemText(IDC_STATIC_PAGE_COUNT, s_page_count);

		this->calc_fairyFood();
	}else
	{

		for (int i = IDC_EDIT_FAIRYFOOD1; i <= IDC_EDIT_FAIRYFOOD30; i++)
		{
			SetDlgItemText(i, L"");
			GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
			GetDlgItem(i)->EnableWindow(false);
		}

		for (int i = IDC_STATIC_FAIRYFOOD1; i <= IDC_STATIC_FAIRYFOOD30; i++)
		{
			SetDlgItemText(i, L"Fairy Food");
			GetDlgItem(i)->ShowWindow(SW_SHOWNORMAL);
		}

		SetDlgItemText(IDC_STATIC_PAGE_COUNT, L"0 / 0");
		GetDlgItem(IDC_FAIRYFOOD_PAGE_PREVIOUS)->EnableWindow(false);
		GetDlgItem(IDC_FAIRYFOOD_PAGE_NEXT)->EnableWindow(false);
	}


	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZeldaEditFairyFoods, CDialogEx)
	ON_COMMAND(ID_MENU_ABOUT, &CZeldaEditFairyFoods::OnMenuAbout)
	ON_COMMAND(ID_MENU_EDIT_GENERAL, &CZeldaEditFairyFoods::OnMenuEditGeneral)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_STATS, &CZeldaEditFairyFoods::OnMenuEditCharactersStats)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_BRONZE, &CZeldaEditFairyFoods::OnMenuEditMaterialsBronze)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_SILVER, &CZeldaEditFairyFoods::OnMenuEditMaterialsSilver)
	ON_COMMAND(ID_MENU_EDIT_MATERIALS_GOLD, &CZeldaEditFairyFoods::OnMenuEditMaterialsGold)
	ON_COMMAND(ID_MENU_MAIN_EXIT, &CZeldaEditFairyFoods::OnMenuMainExit)
	ON_COMMAND(ID_MENU_EDIT_FAIRYFOODS, &CZeldaEditFairyFoods::OnMenuEditFairyfoods)
	ON_BN_CLICKED(ID_EXIT, &CZeldaEditFairyFoods::OnBnClickedExit)
	ON_BN_CLICKED(ID_SAVE, &CZeldaEditFairyFoods::OnBnClickedSave)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_EDIT_FAIRYFOOD1, IDC_EDIT_FAIRYFOOD30, &OnEnChangeValueEdit)
	ON_BN_CLICKED(IDC_FAIRYFOOD_PAGE_PREVIOUS, &CZeldaEditFairyFoods::OnBnClickedFairyfoodPagePrevious)
	ON_BN_CLICKED(IDC_FAIRYFOOD_PAGE_NEXT, &CZeldaEditFairyFoods::OnBnClickedFairyfoodPageNext)
	ON_COMMAND(ID_MENU_EDIT_AM_AVMAP, &CZeldaEditFairyFoods::OnMenuEditAmAvmap)
	ON_COMMAND(ID_MENU_EDIT_AM_GSMAP, &CZeldaEditFairyFoods::OnMenuEditAmGsmap)
	ON_COMMAND(ID_MENU_EDIT_AM_MQMAP, &CZeldaEditFairyFoods::OnMenuEditAmMqmap)
	ON_BN_CLICKED(IDC_FAIRYFOOD_MAX_VALUE_PAGE, &CZeldaEditFairyFoods::OnBnClickedFairyfoodMaxValuePage)
	ON_BN_CLICKED(IDC_FAIRYFOOD_MAX_VALUE_ALL, &CZeldaEditFairyFoods::OnBnClickedFairyfoodMaxValueAll)
	ON_BN_CLICKED(IDC_FAIRYFOOD_MAX_VALUE_GRATITUDE, &CZeldaEditFairyFoods::OnBnClickedFairyfoodMaxValueGratitude)
	ON_COMMAND(ID_MENU_EDIT_AM_TLMAP, &CZeldaEditFairyFoods::OnMenuEditAmTlmap)
	ON_COMMAND(ID_MENU_EDIT_AM_TMMAP, &CZeldaEditFairyFoods::OnMenuEditAmTmmap)
	ON_COMMAND(ID_MENU_EDIT_FAIRIES, &CZeldaEditFairyFoods::OnMenuEditFairies)
	ON_COMMAND(ID_MENU_EDIT_CHARACTERS_WEAPONS, &CZeldaEditFairyFoods::OnMenuEditCharactersWeapons)
END_MESSAGE_MAP()


// CZeldaEditFairyFoods-Meldungshandler

void CZeldaEditFairyFoods::OnMenuAbout()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaAboutDlg about;
	about.DoModal();
}


void CZeldaEditFairyFoods::OnMenuEditGeneral()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditGeneralDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditFairyFoods::OnMenuEditCharactersStats()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaStatsDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyFoods::OnMenuEditMaterialsBronze()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 0);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyFoods::OnMenuEditMaterialsSilver()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyFoods::OnMenuEditMaterialsGold()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditMaterials dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyFoods::OnMenuMainExit()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyFoods::OnOK();

}


void CZeldaEditFairyFoods::OnMenuEditFairyfoods()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
}


void CZeldaEditFairyFoods::OnBnClickedExit()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CZeldaEditFairyFoods::OnOK();

}


void CZeldaEditFairyFoods::OnBnClickedSave()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		try
		{
			this->save_fairyFood();
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

void CZeldaEditFairyFoods::calc_fairyFood()
{
	int i_size = HWLSaveEdit::HWLFairyFood::vs_fairyFood.size();
	int i_diff = i_size - ((this->i_page - 1) * this->maxFairyFoodsShown);

	for (int i = 0; i < this->maxFairyFoodsShown; i++)
	{
		if (i < i_diff)
		{
			int i_fairyFood_id = i + ((this->i_page - 1) * this->maxFairyFoodsShown);
			CString s_fairyFood_name(save->get_fairyFood(i_fairyFood_id)->get_name().c_str());
			CString s_fairyFood_value;
			s_fairyFood_value.Format(L"%d", save->get_fairyFood(i_fairyFood_id)->get_value());

			SetDlgItemText((IDC_STATIC_FAIRYFOOD1 + i), s_fairyFood_name + L": ");
			SetDlgItemText((IDC_EDIT_FAIRYFOOD1 + i), s_fairyFood_value);

			CEdit *e_test = (CEdit*)GetDlgItem((IDC_EDIT_FAIRYFOOD1 + i));
			CString cs_max_chars;
			cs_max_chars.Format(L"%d", HWLSaveEdit::HWLFairyFood::fairyFoodlValueMax);
			e_test->SetLimitText(cs_max_chars.GetLength() + 1);
		}
		else{
			if (GetDlgItem(IDC_STATIC_FAIRYFOOD1 + i)->IsWindowVisible())
				GetDlgItem(IDC_STATIC_FAIRYFOOD1 + i)->ShowWindow(SW_HIDE);

			if (GetDlgItem(IDC_EDIT_FAIRYFOOD1 + i)->IsWindowVisible())
				GetDlgItem(IDC_EDIT_FAIRYFOOD1 + i)->ShowWindow(SW_HIDE);

		}

	}
}

void CZeldaEditFairyFoods::save_fairyFood()
{


	int i_size = HWLSaveEdit::HWLFairyFood::vs_fairyFood.size();
	int i_diff = i_size - ((this->i_page - 1) * this->maxFairyFoodsShown);

	for (int i = 0; i < this->maxFairyFoodsShown; i++)
	{
		if (i < i_diff)
		{
			int i_fairyFood_id = i + ((this->i_page - 1) * this->maxFairyFoodsShown);
			CString s_fairyFood_value;

			GetDlgItemText((IDC_EDIT_FAIRYFOOD1 + i), s_fairyFood_value);
			int i_fairyFood_value = _wtof(s_fairyFood_value);

			save->get_fairyFood(i_fairyFood_id)->set_value(i_fairyFood_value);
			save->get_fairyFood(i_fairyFood_id)->save_FairyFood();
		}
	}
}

void CZeldaEditFairyFoods::OnEnChangeValueEdit(UINT nID)
{
	if (SendDlgItemMessage(nID, EM_GETMODIFY, 0, 0))
	{
		if (save != nullptr)
		{
			CString test;
			CEdit *e_test = (CEdit*)GetDlgItem(nID);
			CString cs_max_chars;
			cs_max_chars.Format(L"%d", HWLSaveEdit::HWLFairyFood::fairyFoodlValueMax);
			e_test->SetLimitText(cs_max_chars.GetLength() + 1);
			GetDlgItemText(nID, test);
			int i_test = _wtoi(test);

			if (i_test > HWLSaveEdit::HWLFairyFood::fairyFoodlValueMax)
			{
				test.Format(L"%d", HWLSaveEdit::HWLFairyFood::fairyFoodlValueMax);
				SetDlgItemText(nID, test);
				e_test->SetLimitText(cs_max_chars.GetLength());
			}

		}
	}
}

void CZeldaEditFairyFoods::OnBnClickedFairyfoodPagePrevious()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_fairyFood();
	this->i_page--;
	this->UpdateData();
}


void CZeldaEditFairyFoods::OnBnClickedFairyfoodPageNext()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	this->save_fairyFood();
	this->i_page++;
	this->UpdateData();
}


void CZeldaEditFairyFoods::OnMenuEditAmAvmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 0);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyFoods::OnMenuEditAmGsmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 1);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyFoods::OnMenuEditAmMqmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 2);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditFairyFoods::OnMenuEditAmTlmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 3);
	EndDialog(this->IDD);
	dlg.DoModal();
}

void CZeldaEditFairyFoods::OnMenuEditAmTmmap()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditAdventureModeItem dlg(NULL, 4);
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyFoods::OnBnClickedFairyfoodMaxValuePage()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		int i_size = HWLSaveEdit::HWLFairyFood::vs_fairyFood.size();
		int i_diff = i_size - ((this->i_page - 1) * this->maxFairyFoodsShown);

		for (int i = 0; i < this->maxFairyFoodsShown; i++)
		{
			if (i < i_diff)
			{
				int i_fairyFood_id = i + ((this->i_page - 1) * this->maxFairyFoodsShown);

				save->get_fairyFood(i_fairyFood_id)->set_value(HWLSaveEdit::HWLFairyFood::fairyFoodlValueMax);
				save->get_fairyFood(i_fairyFood_id)->save_FairyFood();
			}
		}

		this->UpdateData();

		CString str("Finish! All needed Values are updated.");
		MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
	}
}


void CZeldaEditFairyFoods::OnBnClickedFairyfoodMaxValueAll()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		for (int i = 0; i < HWLSaveEdit::HWLFairyFood::vs_fairyFood.size(); i++)
		{
			save->get_fairyFood(i)->set_value(HWLSaveEdit::HWLFairyFood::fairyFoodlValueMax);
			save->get_fairyFood(i)->save_FairyFood();
		}

		this->UpdateData();

		CString str("Finish! All needed Values are updated.");
		MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
	}
}


void CZeldaEditFairyFoods::OnBnClickedFairyfoodMaxValueGratitude()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (save != nullptr)
	{
		for (int i = HWLSaveEdit::HWLFairyFood::fairyGratitudeCrystalIDBegin; i <= HWLSaveEdit::HWLFairyFood::fairyGratitudeCrystalIDEnd; i++)
		{
			save->get_fairyFood(i)->set_value(HWLSaveEdit::HWLFairyFood::fairyFoodlValueMax);
			save->get_fairyFood(i)->save_FairyFood();
		}

		this->UpdateData();

		CString str("Finish! All needed Values are updated.");
		MessageBox(str, L"Information", MB_OK | MB_ICONINFORMATION);
	}
}


void CZeldaEditFairyFoods::OnMenuEditFairies()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditFairyDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}


void CZeldaEditFairyFoods::OnMenuEditCharactersWeapons()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CZeldaEditCharaWeaponsDlg dlg;
	EndDialog(this->IDD);
	dlg.DoModal();
}
