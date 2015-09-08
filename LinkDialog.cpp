// LinkDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MANET.h"
#include "LinkDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinkDialog dialog


CLinkDialog::CLinkDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CLinkDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLinkDialog)
	m_router1 = _T("");
	m_router2 = _T("");
	m_frequency = 0;
	m_duplex = -1;
	//}}AFX_DATA_INIT
}


void CLinkDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLinkDialog)
	DDX_Control(pDX, IDC_EDIT_OUT, m_out);
	DDX_Control(pDX, IDC_EDIT_IN, m_in);
	DDX_Text(pDX, IDC_EDIT_IN, m_router1);
	DDX_Text(pDX, IDC_EDIT_OUT, m_router2);
	DDX_Text(pDX, IDC_EDIT_FREQUENCY, m_frequency);
	DDX_Radio(pDX, IDC_RADIO_FULL, m_duplex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLinkDialog, CDialog)
	//{{AFX_MSG_MAP(CLinkDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinkDialog message handlers

BOOL CLinkDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(TRUE);

	//this->m_duplex=0;
	//this->m_router1="";
	//this->m_router2="";
	//this->m_frequency=10;

	if(!enabled)
	{
		m_in.EnableWindow(FALSE);
		m_out.EnableWindow(FALSE);
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLinkDialog::GetLinkData(CLink *link)
{
	if(link->Router1!=NULL)
		m_router1	=link->Router1->Caption;
	if(link->Router2!=NULL)
		m_router2	=link->Router2->Caption;
	m_duplex		=link->Duplex;
	m_frequency		=link->Frequency;
}

void CLinkDialog::PushLinkData(CLink *link)
{
	//link->Router1	=m_router1;
	//link->Router2	=m_router2;
	link->Duplex	=m_duplex;
	link->Frequency	=m_frequency;
}
