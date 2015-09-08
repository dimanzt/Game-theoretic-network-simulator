#if !defined(AFX_RANDOMTRAFFIC_H__E4C9FF7E_A60A_4C98_A746_22617E1757A4__INCLUDED_)
#define AFX_RANDOMTRAFFIC_H__E4C9FF7E_A60A_4C98_A746_22617E1757A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RandomTraffic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RandomTraffic dialog

class RandomTraffic : public CDialog
{
// Construction
public:
	RandomTraffic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RandomTraffic)
	enum { IDD = IDD_DIALOG_RandomTraffic };
	int		m_connection_num;
	int		m_datarate;
	//int		m_start_range;
	int		m_protocol;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RandomTraffic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RandomTraffic)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int StartTick;
	int StopTick;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RANDOMTRAFFIC_H__E4C9FF7E_A60A_4C98_A746_22617E1757A4__INCLUDED_)
