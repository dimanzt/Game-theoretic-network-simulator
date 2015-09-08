#if !defined(AFX_CAPTION_H__63E47633_2A8E_4502_896B_735808D39D09__INCLUDED_)
#define AFX_CAPTION_H__63E47633_2A8E_4502_896B_735808D39D09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Caption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCaption dialog

class CCaption : public CDialog
{
// Construction
public:
	CCaption(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCaption)
	enum { IDD = IDD_DIALOG_CAPTION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaption)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCaption)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPTION_H__63E47633_2A8E_4502_896B_735808D39D09__INCLUDED_)
