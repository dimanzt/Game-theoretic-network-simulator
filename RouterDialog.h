#if !defined(AFX_ROUTERDIALOG_H__EBE0D0A0_6559_45DA_AC85_C37D3B5BA936__INCLUDED_)
#define AFX_ROUTERDIALOG_H__EBE0D0A0_6559_45DA_AC85_C37D3B5BA936__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RouterDialog.h : header file
//

/////////////////////////////
#include "Router.h"
/////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CRouterDialog dialog

class CRouterDialog : public CDialog
{
// Construction
public:
	void PushRouterData(CRouter* r);
	void GetRouterData(CRouter* r);
	CRouterDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRouterDialog)
	enum { IDD = IDD_DIALOG_ROUTER };
	int		m_Xaxis;
	int		m_Yaxis;
	CString	m_caption;
	int		m_length;
	int		m_buffersize;
	int		m_coverage;
	int		m_delay;
	CString	m_imagepath;
	int		m_width;
	int		m_type;
	int		m_power;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRouterDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRouterDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int m_ForwardedData;
	int m_GameStrategy;
	afx_msg void OnBnClickedRadioSelfish();
	afx_msg void OnBnClickedRadioSelfish3();
	afx_msg void OnBnClickedRadioAdhoc();
	afx_msg void OnBnClickedRadioAdhoc2();
	afx_msg void OnBnClickedRadioFr();
	afx_msg void OnBnClickedRadioSelfish2();
	afx_msg void OnBnClickedRadioFr2();
	afx_msg void OnBnClickedRadioMalicious();
	afx_msg void OnBnClickedRadioTft();
	afx_msg void OnBnClickedRadioErtft();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROUTERDIALOG_H__EBE0D0A0_6559_45DA_AC85_C37D3B5BA936__INCLUDED_)
