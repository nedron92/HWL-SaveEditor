#pragma once


// CZeldaEditAdventureModeItem-Dialogfeld

class CZeldaEditAdventureModeItem : public CDialogEx
{
	DECLARE_DYNAMIC(CZeldaEditAdventureModeItem)

public:
	CZeldaEditAdventureModeItem(CWnd* pParent = NULL, int i_type = -1);   // Standardkonstruktor
	virtual ~CZeldaEditAdventureModeItem();

// Dialogfelddaten
	enum { IDD = IDD_EDIT_AMITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	HICON m_hIcon;
	HWLSaveEdit::HWLSaveEditor *save;
	int i_type;
	int i_map;
	int i_map_max;
	const int maxAMItemsShown = 12;

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
};
