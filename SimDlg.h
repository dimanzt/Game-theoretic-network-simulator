#if !defined(AFX_SIMDLG_H__5E0BB64B_45D1_4522_827B_91937CC40C1E__INCLUDED_)
#define AFX_SIMDLG_H__5E0BB64B_45D1_4522_827B_91937CC40C1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SimDlg.h : header file
//

/////////////////////////////
#include "MANETDoc.h"
/////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CSimDlg dialog

class CSimDlg : public CDialog
{
// Construction
public:
	unsigned		CLOCK;
	BOOL			Timer;
	int				RouterSizeCounter;
	unsigned		TicPerIntCounter;
	int				RouterSize;
	CMANETDoc*		Document;
	unsigned		TicksPerInterrupt;
	CSimDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSimDlg)
	enum { IDD = IDD_DIALOG_SIMULATION };
	CButton	m_resumestop;
	CListBox	m_events;
	int		m_master;
	int		m_slave1;
	int		m_slave2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSimDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnReleasedcaptureSLIDERMasterSpeed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSLIDERSlaveSpeed1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSLIDERSlaveSpeed2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBUTTONResumeStop();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int clock;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMDLG_H__5E0BB64B_45D1_4522_827B_91937CC40C1E__INCLUDED_)
