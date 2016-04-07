#pragma once


// CZeldaEditMaterials-Dialogfeld

class CZeldaEditMaterials : public CDialogEx
{
	DECLARE_DYNAMIC(CZeldaEditMaterials)

public:
	CZeldaEditMaterials(CWnd* pParent = NULL, int i_type=-1);   // Standardkonstruktor

	virtual ~CZeldaEditMaterials();

// Dialogfelddaten
	enum { IDD = IDD_EDIT_MATERIALS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	HICON m_hIcon;
	HWLSaveEdit::HWLSaveEditor *save;
	int i_type;
	int i_page;
	int i_page_max;
	const int maxMaterialsShown = 30;

	DECLARE_MESSAGE_MAP()

	//own methods
	void calc_materials();
	void save_materials();

public:

	afx_msg void OnEnChangeValueEdit(UINT nID);

	afx_msg void OnMenuEditGeneral();
	afx_msg void OnMenuEditCharactersStats();
	afx_msg void OnMenuEditMaterialsBronze();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSave();
	afx_msg void OnMenuEditMaterialsSilver();
	afx_msg void OnBnClickedMaterialPagePrevious();
	afx_msg void OnBnClickedMaterialPageNext();
	afx_msg void OnMenuEditMaterialsGold();
	afx_msg void OnMenuMainExit();
	afx_msg void OnMenuEditFairyfoods();
	afx_msg void OnMenuEditAmAvmap();
	afx_msg void OnMenuEditAmGsmap();
	afx_msg void OnMenuEditAmMqmap();
	afx_msg void OnBnClickedMaterialMaxValueAll();
	afx_msg void OnMenuEditAmTlmap();
	afx_msg void OnMenuEditAmTmmap();
	afx_msg void OnMenuEditFairies();
};
