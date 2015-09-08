#if !defined(AFX_LINKDIALOG_H__DD20420C_1CAF_4111_9FC0_F596225012E0__INCLUDED_)
#define AFX_LINKDIALOG_H__DD20420C_1CAF_4111_9FC0_F596225012E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LinkDialog.h : header file
//

/////////////////////////////
#include "Link.h"
/////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLinkDialog dialog

class CLinkDialog : public CDialog
{
// Construction
public:
	BOOL enabled;
	void PushLinkData(CLink* link);
	void GetLinkData(CLink* link);
	CLinkDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLinkDialog)
	enum { IDD = IDD_DIALOG_LINK };
	CEdit	m_out;
	CEdit	m_in;
	CString	m_router1;
	CString	m_router2;
	int		m_frequency;
	int		m_duplex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinkDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLinkDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINKDIALOG_H__DD20420C_1CAF_4111_9FC0_F596225012E0__INCLUDED_)
