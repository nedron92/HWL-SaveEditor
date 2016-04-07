// ZeldaAboutDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZeldaHWLSaveEditorGUI.h"
#include "ZeldaAboutDlg.h"
#include "afxdialogex.h"


// CZeldaAboutDlg-Dialogfeld

IMPLEMENT_DYNAMIC(CZeldaAboutDlg, CDialogEx)

CZeldaAboutDlg::CZeldaAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZeldaAboutDlg::IDD, pParent)
{
}

CZeldaAboutDlg::~CZeldaAboutDlg()
{
}

void CZeldaAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	//Define to CString
	CString cs_app_name_version;
	CString cs_app_name_version_new;

	//Load String from String-Table, Create version CString and
	//Format the other CString to hold both
	cs_app_name_version.LoadString(IDS_APP_NAME_VERSION);
	CString cs_version(HWLSaveEdit::HWLSaveEditorCore::version.c_str());
	cs_app_name_version_new.Format(L"%s%s", cs_app_name_version, cs_version);

	//Set the Dlg item to show the version at the Dialog Box
	SetDlgItemText(IDC_STATIC_APP_NAME, cs_app_name_version_new);

	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZeldaAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CZeldaAboutDlg-Meldungshandler
