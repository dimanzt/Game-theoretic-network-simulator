#if !defined(AFX_STAT_H__7972EB5A_41EE_4FD1_8B47_87D984948DAA__INCLUDED_)
#define AFX_STAT_H__7972EB5A_41EE_4FD1_8B47_87D984948DAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Stat.h : header file
//

/////////////////////////////
#include "MANETDoc.h"
#include "afxwin.h"
/////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CStat dialog

class CStat : public CDialog
{
// Construction
public:
	CMANETDoc*		Document;
	CStat(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStat)
	enum { IDD = IDD_DIALOG_Stat };

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStat)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	//int RReqTransNumber;
	int RReqTransNum;
	int RRepTransNum;
	int GenDataNum;
	int GenAckNum;
	//int EstablishedConnectionsNum;
	int DataTransNum;
	//int TotalPower;
	//int GenSelfishAckNum;
	CFile myFile;
	int GenSelDataNum;
	int GenSelfishAckNum;
	int TotalPower;
	int AdhocNum;
	int Selfish1Num;
	int Selfish2Num;
	//DIMAN CHANGED
	double avg_RDD_perHop;
	double avg_DFD_perHop;
	double avg_RDD;
	//DIMAN CHANGED
	//CString StrNum;
	char StrArray[100];
	char TABch;
	char ch;
	void int2str(int integer);
	void write2file(int interger);
	CString StrNum;
	CEdit AdHocNodes;
	int EstabConn;
	int ClockNum;
	CRouter* router;
	CPacket* packet;
	double MinDataDelay;
	double MaxDataDelay;
	double MinDiscoDelay;
	double MaxDiscoDelay;
	double AvgDiscoDelay;
	double AvgDataDelay;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAT_H__7972EB5A_41EE_4FD1_8B47_87D984948DAA__INCLUDED_)
