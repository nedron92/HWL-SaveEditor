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
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZeldaAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CZeldaAboutDlg-Meldungshandler
