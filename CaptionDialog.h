#if !defined(AFX_CAPTIONDIALOG_H__8743800B_D557_4E62_A154_90BD4EB139E7__INCLUDED_)
#define AFX_CAPTIONDIALOG_H__8743800B_D557_4E62_A154_90BD4EB139E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CaptionDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCaptionDialog dialog

class CCaptionDialog : public CDialog
{
// Construction
public:
	CCaptionDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCaptionDialog)
	enum { IDD = IDD_DIALOG_CAPTION };
	CString	m_caption;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaptionDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCaptionDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPTIONDIALOG_H__8743800B_D557_4E62_A154_90BD4EB139E7__INCLUDED_)
