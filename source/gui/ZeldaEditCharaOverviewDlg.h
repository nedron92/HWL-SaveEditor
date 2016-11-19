#pragma once


// CZeldaEditCharaOverviewDlg-Dialogfeld

class CZeldaEditCharaOverviewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZeldaEditCharaOverviewDlg)

public:
	CZeldaEditCharaOverviewDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CZeldaEditCharaOverviewDlg();

// Dialogfelddaten
	enum { IDD = IDD_EDIT_CHARA_OVERVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	HICON m_hIcon;

	HWLSaveEdit::HWLSaveEditor *save;

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedEditButton(UINT nID);
	afx_msg void OnBnClickedUnlockCheck(UINT nID);

	//own methods
	void calc_players();
	void save_players();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedCharaMaxStatsAll();
	afx_msg void OnBnClickedCharaUnlockAll();
	afx_msg void OnMenuMainExit();
	afx_msg void OnMenuEditGeneral();
	afx_msg void OnMenuEditCharactersOverview();
	afx_msg void OnMenuEditCharactersStats();
	afx_msg void OnMenuEditCharactersWeapons();
	afx_msg void OnMenuEditMaterialsBronze();
	afx_msg void OnMenuEditMaterialsSilver();
	afx_msg void OnMenuEditMaterialsGold();
	afx_msg void OnMenuEditFairyfoods();
	afx_msg void OnMenuEditAmAvmap();
	afx_msg void OnMenuEditAmGsmap();
	afx_msg void OnMenuEditAmMqmap();
	afx_msg void OnMenuEditAmTlmap();
	afx_msg void OnMenuEditAmTmmap();
	afx_msg void OnMenuEditAmMwwmap();
	afx_msg void OnMenuEditAmKimap();
	afx_msg void OnMenuEditAmGtmap();
	afx_msg void OnMenuEditFairies();
};
