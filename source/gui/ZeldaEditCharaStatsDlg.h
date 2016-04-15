#pragma once


// CZeldaEditCharaStatsDlg-Dialogfeld

class CZeldaEditCharaStatsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZeldaEditCharaStatsDlg)

public:
	CZeldaEditCharaStatsDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CZeldaEditCharaStatsDlg();

// Dialogfelddaten
	enum { IDD = IDD_EDIT_CHARA_STATS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	HICON m_hIcon;

	HWLSaveEdit::HWLSaveEditor *save;

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedSave();
	afx_msg void OnEnChangeLVLEdit(UINT nID);
	afx_msg void OnEnChangeEXPEdit(UINT nID);
	afx_msg void OnEnChangeATKEdit(UINT nID);
	afx_msg void OnBnClickedUnlockCheck(UINT nID);

	//own methods
	void calc_players();
	void save_players();
	afx_msg void OnMenuAbout();
	afx_msg void OnMenuEditGeneral();
	afx_msg void OnMenuEditCharactersStats();
	afx_msg void OnMenuEditMaterialsBronze();
	afx_msg void OnMenuEditMaterialsSilver();
	afx_msg void OnMenuEditMaterialsGold();
	afx_msg void OnMenuMainExit();
	afx_msg void OnMenuEditFairyfoods();
	afx_msg void OnMenuEditAmAvmap();
	afx_msg void OnMenuEditAmGsmap();
	afx_msg void OnMenuEditAmMqmap();
	afx_msg void OnBnClickedCharaMaxExpAll();
	afx_msg void OnBnClickedCharaMaxAtkAll();
	afx_msg void OnBnClickedCharaUnlockAll();
	afx_msg void OnMenuEditAmTlmap();
	afx_msg void OnMenuEditAmTmmap();
	afx_msg void OnMenuEditFairies();
	afx_msg void OnMenuEditCharactersWeapons();
};

