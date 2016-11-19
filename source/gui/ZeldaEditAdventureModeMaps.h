#pragma once


// CZeldaEditAdventureModeMaps-Dialogfeld

class CZeldaEditAdventureModeMaps : public CDialogEx
{
	DECLARE_DYNAMIC(CZeldaEditAdventureModeMaps)

public:
	CZeldaEditAdventureModeMaps(CWnd* pParent = NULL, int i_map = -1);   // Standardkonstruktor
	virtual ~CZeldaEditAdventureModeMaps();

// Dialogfelddaten
	enum { IDD = IDD_EDIT_AMMAPS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	HICON m_hIcon;
	HWLSaveEdit::HWLSaveEditor *save;
	int i_map, i_skipped_maps;

	DECLARE_MESSAGE_MAP()

	//own methods
	void calc_amItems();
	void save_amItems();

public:

	afx_msg void OnEnChangeValueEdit(UINT nID);

	afx_msg void OnMenuMainExit();
	afx_msg void OnMenuEditGeneral();
	afx_msg void OnMenuEditCharactersStats();
	afx_msg void OnMenuEditMaterialsBronze();
	afx_msg void OnMenuEditMaterialsSilver();
	afx_msg void OnMenuEditMaterialsGold();
	afx_msg void OnMenuEditFairyfoods();

	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedAMItemPagePrevious();
	afx_msg void OnBnClickedAMItemPageNext();
	afx_msg void OnMenuEditAmAvmap();
	afx_msg void OnMenuEditAmGsmap();
	afx_msg void OnMenuEditAmMqmap();
	afx_msg void OnBnClickedAmitemMaxValueMap();
	afx_msg void OnMenuEditAmTlmap();
	afx_msg void OnMenuEditAmTmmap();
	afx_msg void OnMenuEditFairies();
	afx_msg void OnMenuEditCharactersWeapons();
	afx_msg void OnMenuEditAmMwwmap();
	afx_msg void OnMenuEditAmKimap();
	afx_msg void OnMenuEditAmGtmap();
	afx_msg void OnBnClickedAmmapMaxValueAll();
	afx_msg void OnMenuEditCharactersOverview();
};
