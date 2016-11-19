#pragma once

// CZeldaEditGeneralDlg-Dialogfeld

class CZeldaEditGeneralDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZeldaEditGeneralDlg)

public:
	CZeldaEditGeneralDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CZeldaEditGeneralDlg();

// Dialogfelddaten
	enum { IDD = IDD_EDIT_GENERAL };

protected:
	HICON m_hIcon;

	HWLSaveEdit::HWLSaveEditor *save;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	//own methods
	void calc_general();
	void save_general();

public:
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedExit();
	afx_msg void OnMenuEditCharactersStats();
	afx_msg void OnMenuAbout();
	afx_msg void OnEnChangeRubyEdit();
	afx_msg void OnMenuMainFileOpen();

	void calc_disabledState_AmMaps();
	int get_active_window_id();
	afx_msg void OnMenuMainFileClose();
	afx_msg void OnMenuMainExit();
	afx_msg void OnMenuEditMaterialsBronze();
	afx_msg void OnMenuEditMaterialsSilver();
	afx_msg void OnMenuEditMaterialsGold();
	afx_msg void OnMenuEditFairyfoods();
	afx_msg void OnMenuEditAmAvmap();
	afx_msg void OnMenuEditAmGsmap();
	afx_msg void OnMenuEditAmMqmap();
	afx_msg void OnMenuEditGeneral();
	afx_msg void OnBnClickedRubyMax();
	afx_msg void OnMenuEditAmTlmap();
	afx_msg void OnMenuEditAmTmmap();
	afx_msg void OnMenuEditFairies();
	afx_msg void OnMenuEditCharactersWeapons();
	afx_msg void OnBnClickedButtonHelpUnlockWeaponStates();
	afx_msg void OnBnClickedButtonHelpUnlockAllMaterials();
	afx_msg void OnBnClickedStaticGeneral();
	afx_msg void OnMenuCheckforupdates();
	afx_msg void OnMenuEditAmMwwmap();
	afx_msg void OnMenuEditAmKimap();
	afx_msg void OnMenuEditAmGtmap();
	afx_msg void OnMenuEditCharactersOverview();
};
