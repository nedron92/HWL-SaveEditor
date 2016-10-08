// ZeldaCheckForUpdatesDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZeldaHWLSaveEditorGUI.h"
#include "ZeldaCheckForUpdatesDlg.h"
#include "afxdialogex.h"


// CZeldaCheckForUpdatesDlg-Dialogfeld

IMPLEMENT_DYNAMIC(CZeldaCheckForUpdatesDlg, CDialogEx)

CZeldaCheckForUpdatesDlg::CZeldaCheckForUpdatesDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CZeldaCheckForUpdatesDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

CZeldaCheckForUpdatesDlg::~CZeldaCheckForUpdatesDlg()
{
}

BOOL CZeldaCheckForUpdatesDlg::OnInitDialog()
{
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//get the current save-object
	save = CZeldaHWLSaveEditorGUIApp::save;

	CString cs_current_version;
	CString cs_latest_stable_version;
	CString cs_latest_nightly_version;
	CString cs_stable_release_url;
	CString cs_nightly_release_url;
	CString cs_update_information_detail;

	GetDlgItemText(IDC_STATIC_CURRENT_VERSION, cs_current_version);
	cs_current_version += HWLSaveEdit::HWLSaveEditorCore::version.c_str();
	SetDlgItemText(IDC_STATIC_CURRENT_VERSION, cs_current_version);

	GetDlgItemText(IDC_STATIC_LATEST_STABLE_VERSION, cs_latest_stable_version);
	cs_latest_stable_version += save->get_http_object()->get_current_version().c_str();
	SetDlgItemText(IDC_STATIC_LATEST_STABLE_VERSION, cs_latest_stable_version);

	GetDlgItemText(IDC_STATIC_LATEST_NIGHTLY_VERSION, cs_latest_nightly_version);
	cs_latest_nightly_version += save->get_http_object()->get_current_nightly_version().c_str();
	SetDlgItemText(IDC_STATIC_LATEST_NIGHTLY_VERSION, cs_latest_nightly_version);

	cs_stable_release_url = save->get_http_object()->latestURL.c_str();
	SetDlgItemText(IDC_EDIT_STABLE_URL, cs_stable_release_url);

	cs_nightly_release_url = save->get_http_object()->nightlyURL.c_str();
	SetDlgItemText(IDC_EDIT_NIGHTLY_URL, cs_nightly_release_url);
	
	cs_update_information_detail = save->get_http_object()->compare_with_current_version().c_str();
	cs_update_information_detail += "\n AND \n";
	cs_update_information_detail += save->get_http_object()->compare_with_current_version(true).c_str();
	SetDlgItemText(IDC_STATIC_UPDATE_INFORMATION_DETAIL, cs_update_information_detail);

	this->UpdateData();
	return CDialogEx::OnInitDialog();
}

void CZeldaCheckForUpdatesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZeldaCheckForUpdatesDlg, CDialogEx)
END_MESSAGE_MAP()



