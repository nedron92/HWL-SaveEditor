// ZeldaConfigWeaponCopyDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZeldaHWLSaveEditorGUI.h"
#include "ZeldaConfigWeaponCopyDlg.h"
#include "afxdialogex.h"


// CZeldaConfigWeaponCopyDlg-Dialogfeld

IMPLEMENT_DYNAMIC(CZeldaConfigWeaponCopyDlg, CDialogEx)

CZeldaConfigWeaponCopyDlg::CZeldaConfigWeaponCopyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZeldaConfigWeaponCopyDlg::IDD, pParent)
{

}

CZeldaConfigWeaponCopyDlg::~CZeldaConfigWeaponCopyDlg()
{
}

void CZeldaConfigWeaponCopyDlg::DoDataExchange(CDataExchange* pDX)
{
	if (!CZeldaHWLSaveEditorGUIApp::mib_config_copy_weapon_values.empty())
	{
		for (int i = 0; i < CZeldaHWLSaveEditorGUIApp::mib_config_copy_weapon_values.size(); i++)
		{
			CButton *cb_check_config_value = (CButton*)GetDlgItem(IDC_CHECK_COPY_LEGENDARY + i);
			cb_check_config_value->SetCheck(CZeldaHWLSaveEditorGUIApp::mib_config_copy_weapon_values[i]);
		}
	}else
	{
		for (int i = IDC_CHECK_COPY_LEGENDARY; i <= IDC_CHECK_COPY_SKILLS; i++)
		{
			CButton *cb_check_config_value = (CButton*)GetDlgItem(i);
			cb_check_config_value->SetCheck(true);
		}
	}

	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZeldaConfigWeaponCopyDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CZeldaConfigWeaponCopyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CZeldaConfigWeaponCopyDlg-Meldungshandler


void CZeldaConfigWeaponCopyDlg::OnBnClickedOk()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (!CZeldaHWLSaveEditorGUIApp::mib_config_copy_weapon_values.empty())
	{
		for (int i = 0; i < CZeldaHWLSaveEditorGUIApp::mib_config_copy_weapon_values.size(); i++)
		{
			CButton *cb_check_config_value = (CButton*)GetDlgItem(IDC_CHECK_COPY_LEGENDARY + i);
			bool b_check_config_value = cb_check_config_value->GetCheck();
			CZeldaHWLSaveEditorGUIApp::mib_config_copy_weapon_values[i] = b_check_config_value;
		}
	}else
	{
		for (int i = IDC_CHECK_COPY_LEGENDARY; i <= IDC_CHECK_COPY_SKILLS; i++)
		{
			CButton *cb_check_config_value = (CButton*)GetDlgItem(i);
			bool b_check_config_value = cb_check_config_value->GetCheck();
			CZeldaHWLSaveEditorGUIApp::mib_config_copy_weapon_values[i - IDC_CHECK_COPY_LEGENDARY] = b_check_config_value;
		}
	}


	CDialogEx::OnOK();
}
