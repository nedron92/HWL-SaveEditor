#pragma once


// CZeldaConfigWeaponCopyDlg-Dialogfeld

class CZeldaConfigWeaponCopyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZeldaConfigWeaponCopyDlg)

public:
	CZeldaConfigWeaponCopyDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CZeldaConfigWeaponCopyDlg();

// Dialogfelddaten
	enum { IDD = IDD_CONFIG_WEAPONCOPY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
