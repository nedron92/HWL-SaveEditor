#pragma once


// CZeldaAboutDlg-Dialogfeld

class CZeldaAboutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZeldaAboutDlg)

public:
	CZeldaAboutDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CZeldaAboutDlg();

// Dialogfelddaten
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
};
