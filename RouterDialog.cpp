// RouterDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MANET.h"
#include "RouterDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////
#include "RouterDialog.h"
/////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CRouterDialog dialog


CRouterDialog::CRouterDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRouterDialog::IDD, pParent)
	, m_power(0)
	, m_ForwardedData(0)
	, m_GameStrategy(1)
{
	//{{AFX_DATA_INIT(CRouterDialog)
	m_Xaxis = 0;
	m_Yaxis = 0;
	m_caption = _T("");
	m_length = 0;
	m_buffersize = 0;
	m_coverage = 0;
	m_delay = 0;
	m_imagepath = _T("");
	m_width = 0;
	m_type = -1;
	//}}AFX_DATA_INIT
}


void CRouterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, m_Xaxis);
	DDX_Text(pDX, IDC_EDIT_Y, m_Yaxis);
	DDX_Text(pDX, IDC_EDIT_CAPTION, m_caption);
	DDX_Text(pDX, IDC_EDIT_LENGTH, m_length);
	DDX_Text(pDX, IDC_EDIT_BUFFER, m_buffersize);
	DDX_Text(pDX, IDC_EDIT_COVERAGE, m_coverage);
	DDX_Text(pDX, IDC_EDIT_DELAY, m_delay);
	DDX_Text(pDX, IDC_EDIT_IMAGE, m_imagepath);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_width);
	DDX_Text(pDX, IDC_EDIT_Power, m_power);
	DDX_Text(pDX, IDC_EDIT_ForwData, m_ForwardedData);
	DDX_Radio(pDX, IDC_RADIO_Adhoc, m_type);
	DDX_Radio(pDX, IDC_RADIO_TFT, m_GameStrategy);
}


BEGIN_MESSAGE_MAP(CRouterDialog, CDialog)
	//{{AFX_MSG_MAP(CRouterDialog)
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDC_RADIO_Malicious, &CRouterDialog::OnBnClickedRadioMalicious)
	ON_BN_CLICKED(IDC_RADIO_Adhoc, &CRouterDialog::OnBnClickedRadioAdhoc)
	ON_BN_CLICKED(IDC_RADIO_Selfish, &CRouterDialog::OnBnClickedRadioSelfish)
	ON_BN_CLICKED(IDC_RADIO_Selfish2, &CRouterDialog::OnBnClickedRadioSelfish2)
	ON_BN_CLICKED(IDC_RADIO_Selfish3, &CRouterDialog::OnBnClickedRadioSelfish3)
	

	//ON_BN_CLICKED(IDC_RADIO_Malicious, &CRouterDialog::OnBnClickedRadioMalicious)
	ON_BN_CLICKED(IDC_RADIO_TFT, &CRouterDialog::OnBnClickedRadioTft)
	ON_BN_CLICKED(IDC_RADIO_ERTFT, &CRouterDialog::OnBnClickedRadioErtft)
	ON_BN_CLICKED(IDC_RADIO_FR, &CRouterDialog::OnBnClickedRadioFr)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRouterDialog message handlers

BOOL CRouterDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(TRUE);
/*	this->m_caption="";
	this->m_coverage=100;
	this->m_delay=1;
	this->m_buffersize=10;
	this->m_imagepath="";
	this->m_Xaxis=0;
	this->m_Yaxis=0;
	this->m_length=10;
	this->m_width=10;
*/	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRouterDialog::GetRouterData(CRouter *r)
{
	m_type			=r->Type;
	m_caption		=r->Caption;
	m_coverage		=r->Coverage;
	m_delay			=r->Delay;
	m_buffersize	=r->BufferSize;
	m_imagepath		=r->ImagePath;
	m_Xaxis			=r->X;
	m_Yaxis			=r->Y;
	m_length		=r->RectLength;
	m_width			=r->RectWidth;
	m_power			=r->Power;
	m_ForwardedData	=r->DataTransCounter;
	m_GameStrategy	=r->Game_Strategy;
}

void CRouterDialog::PushRouterData(CRouter *r)
{
	r->Type				=m_type;
	r->Caption			=m_caption;
	r->Coverage			=m_coverage;
	r->Delay			=m_delay;
	r->BufferSize		=m_buffersize;
	r->ImagePath		=m_imagepath;
	r->X				=m_Xaxis;
	r->Y				=m_Yaxis;
	r->RectLength		=m_length;
	r->RectWidth		=m_width;
	r->Power			=m_power;
	r->DataTransCounter	=m_ForwardedData;
	r->Game_Strategy	=m_GameStrategy;
	r->SetGames(m_GameStrategy);
	r->UpdateRect();
}
void CRouterDialog::OnBnClickedRadioAdhoc()
{
	// TODO: Add your control notification handler code here
}

void CRouterDialog::OnBnClickedRadioSelfish()
{
	// TODO: Add your control notification handler code here
}
void CRouterDialog::OnBnClickedRadioSelfish2()
{
	// TODO: Add your control notification handler code here
}

void CRouterDialog::OnBnClickedRadioSelfish3()
{
	// TODO: Add your control notification handler code here
}




void CRouterDialog::OnBnClickedRadioTft()
{
	// TODO: Add your control notification handler code here
}

void CRouterDialog::OnBnClickedRadioErtft()
{
	// TODO: Add your control notification handler code here
}
void CRouterDialog::OnBnClickedRadioFr()
{
	// TODO: Add your control notification handler code here
}
