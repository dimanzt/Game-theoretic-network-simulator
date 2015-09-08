#if !defined(AFX_END2END_H__DE6FB60D_870B_4805_A15D_3B36557CA4EE__INCLUDED_)
#define AFX_END2END_H__DE6FB60D_870B_4805_A15D_3B36557CA4EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// End2End.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEnd2End dialog

class CEnd2End : public CDialog
{
// Construction
public:
	CEnd2End(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEnd2End)
	enum { IDD = IDD_DIALOG_End2End };
	CString	m_router1;
	CString	m_router2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnd2End)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEnd2End)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_END2END_H__DE6FB60D_870B_4805_A15D_3B36557CA4EE__INCLUDED_)
