#if !defined(AFX_CTRAFFICDIALOG_H__A7367487_E869_430D_9975_8BACDE864C2F__INCLUDED_)
#define AFX_CTRAFFICDIALOG_H__A7367487_E869_430D_9975_8BACDE864C2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrafficDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTrafficDialog dialog

class CTrafficDialog : public CDialog
{
// Construction
public:
	CTrafficDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTrafficDialog)
	enum { IDD = IDD_DIALOG_TRAFFIC };
	CString	m_destination;
	CString	m_source;
	int		m_protocol;
	int		m_start;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrafficDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTrafficDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioElmar();
	afx_msg void OnBnClickedRadioAomdv();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTRAFFICDIALOG_H__A7367487_E869_430D_9975_8BACDE864C2F__INCLUDED_)
