// TrafficDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MANET.h"
#include "TrafficDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrafficDialog dialog


CTrafficDialog::CTrafficDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTrafficDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrafficDialog)
	m_destination = _T("");
	m_source = _T("");
	m_protocol = -1;
	m_start = 0;
	//}}AFX_DATA_INIT
}


void CTrafficDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrafficDialog)
	DDX_Text(pDX, IDC_EDIT_DESTINATION, m_destination);
	DDX_Text(pDX, IDC_EDIT_SOURCE, m_source);
	DDX_Radio(pDX, IDC_RADIO_GTAMR, m_protocol);
	DDX_Text(pDX, IDC_EDIT_START, m_start);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTrafficDialog, CDialog)
	//{{AFX_MSG_MAP(CTrafficDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrafficDialog message handlers

BOOL CTrafficDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(TRUE);

	this->m_destination="";
	this->m_source="";
	this->m_protocol=0;
	this->m_start=0;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


