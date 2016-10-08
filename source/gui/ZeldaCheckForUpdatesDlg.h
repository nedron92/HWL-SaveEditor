#pragma once


// CZeldaCheckForUpdatesDlg-Dialogfeld

class CZeldaCheckForUpdatesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZeldaCheckForUpdatesDlg)

public:
	CZeldaCheckForUpdatesDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CZeldaCheckForUpdatesDlg();

// Dialogfelddaten
	enum { IDD = IDD_CHECKFORUPDATES };

protected:

	HICON m_hIcon;
	HWLSaveEdit::HWLSaveEditor *save;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedStaticUpdateInformation();
//	afx_msg void OnStnClickedStaticUpdateInformationDetail();
};
