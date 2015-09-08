// MANET.h : main header file for the GTNS application
//

#if !defined(AFX_MANET_H__E7D4329F_3C10_4BCE_911A_34FB5D5F7542__INCLUDED_)
#define AFX_MANET_H__E7D4329F_3C10_4BCE_911A_34FB5D5F7542__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMANETApp:
// See MANET.cpp for the implementation of this class
//

class CMANETApp : public CWinApp
{
public:
//	CRouter* router;
	CMANETApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMANETApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMANETApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANET_H__E7D4329F_3C10_4BCE_911A_34FB5D5F7542__INCLUDED_)
