#pragma once


// CZeldaEditCharaWeaponsDlg-Dialogfeld

class CZeldaEditCharaWeaponsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZeldaEditCharaWeaponsDlg)

public:
	CZeldaEditCharaWeaponsDlg(CWnd* pParent = NULL, int i_chara_id = 0, int i_skipped_charas = 0);   // Standardkonstruktor
	virtual ~CZeldaEditCharaWeaponsDlg();

// Dialogfelddaten
	enum { IDD = IDD_EDIT_CHARA_WEAPONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	HICON m_hIcon;
	HWLSaveEdit::HWLSaveEditor *save;
	int i_chara_id, i_weapon_type, i_weapon_slot, i_skipped_charas, i_skipped_weaponTypes, i_disabledWeaponSkillsCounter;

	DECLARE_MESSAGE_MAP()

	//own methods
	void calc_weapon();
	void save_weapon();

public:
	afx_msg void OnEnChangeKillSlotEdit(UINT nID);

	afx_msg void OnMenuEditGeneral();
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
	afx_msg void OnMenuEditFairies();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedCweaponCharPagePrevious();
	afx_msg void OnBnClickedCweaponCharPageNext();
	afx_msg void OnBnClickedCweaponTypePagePrevious();
	afx_msg void OnBnClickedCweaponTypePageNext();
	afx_msg void OnBnClickedCweaponSlotPagePrevious();
	afx_msg void OnBnClickedCweaponSlotPageNext();
	afx_msg void OnBnClickedCweaponDefaultWeapon();
	afx_msg void OnBnClickedCweaponDeleteWeapon();
	afx_msg void OnCbnSelchangeComboCweaponLevel();
	afx_msg void OnEnChangeEditCweaponDamageBase();
	afx_msg void OnEnKillfocusEditCweaponDamageBase();
	afx_msg void OnBnClickedCheckCweaponLegendary();
	afx_msg void OnBnClickedCweaponResetKills();
	afx_msg void OnBnClickedCweaponResetSkills();
	afx_msg void OnCbnSelchangeComboCweaponStars();
	afx_msg void OnMenuEditAmMwwmap();
	afx_msg void OnMenuEditAmKimap();
	afx_msg void OnMenuEditAmGtmap();
	afx_msg void OnBnClickedCheckCweaponMultielement();
	afx_msg void OnMenuMainExit();
	afx_msg void OnMenuEditCharactersOverview();
	afx_msg void OnBnClickedCweaponCopyValues();
	afx_msg void OnBnClickedCweaponPasteValues();
	afx_msg void OnMenuEditAmLrmap();
};
