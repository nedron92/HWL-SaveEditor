#pragma once


// CZeldaEditFairyDlg-Dialogfeld

class CZeldaEditFairyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZeldaEditFairyDlg)

public:
	CZeldaEditFairyDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CZeldaEditFairyDlg();

// Dialogfelddaten
	enum { IDD = IDD_EDIT_FAIRIES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	HICON m_hIcon;
	HWLSaveEdit::HWLSaveEditor *save;
	int i_fairy;
	int i_fairy_max;

	DECLARE_MESSAGE_MAP()

	//own methods
	void calc_fairy();
	void save_fairy();

public:
	afx_msg void OnMenuEditFairies();
	afx_msg void OnMenuEditGeneral();
	afx_msg void OnMenuEditCharactersStats();
	afx_msg void OnMenuEditMaterialsBronze();
	afx_msg void OnMenuEditMaterialsSilver();
	afx_msg void OnMenuEditMaterialsGold();
	afx_msg void OnMenuEditFairyfoods();
	afx_msg void OnMenuEditAmAvmap();
	afx_msg void OnMenuEditAmGsmap();
	afx_msg void OnMenuEditAmMqmap();
	afx_msg void OnMenuEditAmTlmap();
	afx_msg void OnMenuEditAmTmmap();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedFairyPagePrevious();
	afx_msg void OnBnClickedFairyPageNext();
	afx_msg void OnBnClickedFairyMaxStats();
	afx_msg void OnEnChangeEditFairyLvl();
	afx_msg void OnEnChangeEditFairyTrust();
	afx_msg void OnEnChangeEditFairyIterator();
	afx_msg void OnMenuEditCharactersWeapons();
};
