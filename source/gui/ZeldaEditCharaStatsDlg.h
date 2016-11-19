#pragma once


// CZeldaEditCharaStatsDlg-Dialogfeld

class CZeldaEditCharaStatsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZeldaEditCharaStatsDlg)

public:
	CZeldaEditCharaStatsDlg(CWnd* pParent = NULL, int i_chara_id = 0, int i_skipped_charas = 0);   // Standardkonstruktor
	virtual ~CZeldaEditCharaStatsDlg();

// Dialogfelddaten
	enum { IDD = IDD_EDIT_CHARA_STATS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	HICON m_hIcon;

	HWLSaveEdit::HWLSaveEditor *save;
	int i_chara_id, i_skipped_charas;

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedSave();

	//own methods
	void calc_stats();
	void save_stats();
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
	afx_msg void OnMenuEditAmTlmap();
	afx_msg void OnMenuEditAmTmmap();
	afx_msg void OnMenuEditFairies();
	afx_msg void OnMenuEditCharactersWeapons();
	afx_msg void OnMenuEditAmMwwmap();
	afx_msg void OnMenuEditAmKimap();
	afx_msg void OnMenuEditAmGtmap();
	afx_msg void OnMenuEditCharactersOverview();
	afx_msg void OnBnClickedButtonCstatsEditWeapons();
	afx_msg void OnBnClickedButtonCstatsMaxStatsUsedWeapons();
	afx_msg void OnBnClickedCstatsCharaMaxStats();
	afx_msg void OnBnClickedCstatsPagePrevious();
	afx_msg void OnBnClickedCstatsPageNext();
	afx_msg void OnEnChangeEditCstatsCharaLvl();
	afx_msg void OnEnChangeEditCstatsCharaExp();
	afx_msg void OnEnChangeEditCstatsCharaAtk();
	afx_msg void OnEnChangeEditCstatsCharaHearts();
	afx_msg void OnBnClickedCheckCstatsCharaUnlock();
};

