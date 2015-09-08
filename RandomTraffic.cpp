// RandomTraffic.cpp : implementation file
//

#include "stdafx.h"
#include "MANET.h"
#include "RandomTraffic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RandomTraffic dialog


RandomTraffic::RandomTraffic(CWnd* pParent /*=NULL*/)
	: CDialog(RandomTraffic::IDD, pParent)
	, StartTick(0)
	, StopTick(0)
{
	//{{AFX_DATA_INIT(RandomTraffic)
	m_connection_num = 0;
	m_datarate = 0;
	//m_start_range = 0;
	StartTick = 0;
	StopTick = 0;
	m_protocol = -1;
	//}}AFX_DATA_INIT
}


void RandomTraffic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RandomTraffic)
	DDX_Text(pDX, IDC_EDIT_Connection, m_connection_num);
	DDX_Text(pDX, IDC_EDIT_DataRate, m_datarate);
	//DDX_Text(pDX, IDC_EDIT_Range, m_start_range);
	DDX_Radio(pDX, IDC_RADIO_GTAMR, m_protocol);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_START, StartTick);
	DDX_Text(pDX, IDC_EDIT_Stop, StopTick);
}


BEGIN_MESSAGE_MAP(RandomTraffic, CDialog)
	//{{AFX_MSG_MAP(RandomTraffic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RandomTraffic message handlers

BOOL RandomTraffic::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(TRUE);
	this->m_connection_num=10;///sabz
	this->m_datarate=10;	// packet per 1000ticks
	this->m_protocol=0;
	//this->m_start_range=1000;	// tick
	this->StartTick=0; 
	this->StopTick=1000;	
	UpdateData(FALSE);
	///////////////////////////////////

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
