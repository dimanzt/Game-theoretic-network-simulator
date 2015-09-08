// SimDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MANET.h"
#include "SimDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimDlg dialog


CSimDlg::CSimDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimDlg::IDD, pParent)
	, clock(0)
{
	//{{AFX_DATA_INIT(CSimDlg)
	m_master = 0;
	m_slave1 = 0;
	m_slave2 = 0;
	//}}AFX_DATA_INIT
}


void CSimDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ResumeStop, m_resumestop);
	DDX_Control(pDX, IDC_LIST_EVENTS, m_events);
	DDX_Slider(pDX, IDC_SLIDER_MasterSpeed, m_master);
	DDX_Slider(pDX, IDC_SLIDER_SlaveSpeed1, m_slave1);
	DDX_Slider(pDX, IDC_SLIDER_SlaveSpeed2, m_slave2);
	DDX_Text(pDX, IDC_EDIT_Clock, clock);
}


BEGIN_MESSAGE_MAP(CSimDlg, CDialog)
	//{{AFX_MSG_MAP(CSimDlg)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_MasterSpeed, OnReleasedcaptureSLIDERMasterSpeed)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SlaveSpeed1, OnReleasedcaptureSLIDERSlaveSpeed1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SlaveSpeed2, OnReleasedcaptureSLIDERSlaveSpeed2)
	ON_BN_CLICKED(IDC_BUTTON_ResumeStop, OnBUTTONResumeStop)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimDlg message handlers

BOOL CSimDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(TRUE);

	//timer=FALSE;
	ASSERT_VALID(Document); //check that the document variable is set!
	
	this->m_master=100;								//set master timer to 100
	SetTimer(1,m_master,0);							//Set Timer Interruption for every 1ms
	this->m_slave1=0;								//SlaveSpeed0=0;
	this->m_slave2=0;								//SlaveSpeed1=0;
	TicksPerInterrupt=(m_slave1+1)*(m_slave2+1);
	this->m_events.EnableWindow(FALSE);
	this->RouterSize=Document->Routers.GetSize();
	this->Timer=FALSE;								//First to Clock!
	this->CLOCK=0;									//First Clock = 0!
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSimDlg::OnReleasedcaptureSLIDERMasterSpeed(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SetTimer(1,m_master,0);	//Set Timer Interruption for every 1 ms
	UpdateData(FALSE);
	*pResult = 0;
}

void CSimDlg::OnReleasedcaptureSLIDERSlaveSpeed1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	TicksPerInterrupt=(m_slave1+1)*(m_slave2+1);
	UpdateData(FALSE);
	*pResult = 0;
}

void CSimDlg::OnReleasedcaptureSLIDERSlaveSpeed2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	TicksPerInterrupt=(m_slave1+1)*(m_slave2+1);
	UpdateData(FALSE);
	*pResult = 0;
}

void CSimDlg::OnBUTTONResumeStop() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString str;
	this->GetDlgItemText(IDC_BUTTON_ResumeStop,str);
	if(str=="Resume")
	{
		this->SetDlgItemText(IDC_BUTTON_ResumeStop,"Pause");
		SetTimer(1,m_master,0);
		Timer=TRUE;
	}
	else
	{
		this->SetDlgItemText(IDC_BUTTON_ResumeStop,"Resume");
		KillTimer(1);
		Timer=FALSE;
	}
	UpdateData(FALSE);
}

void CSimDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(TRUE);
	if(Timer)
	{
		for(TicPerIntCounter=0;TicPerIntCounter<TicksPerInterrupt;TicPerIntCounter++)
		{
			CLOCK++;
			RouterSize=Document->Routers.GetSize();
			for(RouterSizeCounter=0;RouterSizeCounter<RouterSize;RouterSizeCounter++)
				((CRouter*)(Document->Routers[RouterSizeCounter]))->tick();
		}
		this->clock=CLOCK;
	}
	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}
