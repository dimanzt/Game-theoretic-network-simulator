// End2End.cpp : implementation file
//

#include "stdafx.h"
#include "MANET.h"
#include "End2End.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnd2End dialog


CEnd2End::CEnd2End(CWnd* pParent /*=NULL*/)
	: CDialog(CEnd2End::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEnd2End)
	m_router1 = _T("");
	m_router2 = _T("");
	//}}AFX_DATA_INIT
}


void CEnd2End::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnd2End)
	DDX_Text(pDX, IDC_EDIT_ROUTER1, m_router1);
	DDX_Text(pDX, IDC_EDIT_ROUTER2, m_router2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEnd2End, CDialog)
	//{{AFX_MSG_MAP(CEnd2End)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnd2End message handlers
