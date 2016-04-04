#pragma once


// CZeldaEditFairyFoods-Dialogfeld

class CZeldaEditFairyFoods : public CDialogEx
{
	DECLARE_DYNAMIC(CZeldaEditFairyFoods)

public:
	CZeldaEditFairyFoods(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CZeldaEditFairyFoods();

// Dialogfelddaten
	enum { IDD = IDD_EDIT_FAIRYFOODS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	HICON m_hIcon;
	HWLSaveEdit::HWLSaveEditor *save;
	int i_page;
	int i_page_max;
	const int maxFairyFoodsShown = 30;

	DECLARE_MESSAGE_MAP()

	//own methods
	void calc_fairyFood();
	void save_fairyFood();

public:

	afx_msg void OnEnChangeValueEdit(UINT nID);

	afx_msg void OnMenuAbout();
	afx_msg void OnMenuEditGeneral();
	afx_msg void OnMenuEditCharactersStats();
	afx_msg void OnMenuEditMaterialsBronze();
	afx_msg void OnMenuEditMaterialsSilver();
	afx_msg void OnMenuEditMaterialsGold();
	afx_msg void OnMenuMainExit();
	afx_msg void OnMenuEditFairyfoods();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedFairyfoodPagePrevious();
	afx_msg void OnBnClickedFairyfoodPageNext();
	afx_msg void OnMenuEditAmAvmap();
	afx_msg void OnMenuEditAmGsmap();
	afx_msg void OnMenuEditAmMqmap();
	afx_msg void OnBnClickedFairyfoodMaxValuePage();
	afx_msg void OnBnClickedFairyfoodMaxValueAll();
	afx_msg void OnBnClickedFairyfoodMaxValueGratitude();
};
