// CaptionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MANET.h"
#include "CaptionDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaptionDialog dialog


CCaptionDialog::CCaptionDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCaptionDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCaptionDialog)
	m_caption = _T("");
	//}}AFX_DATA_INIT
}


void CCaptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCaptionDialog)
	DDX_Text(pDX, IDC_EDIT_CAPTION, m_caption);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCaptionDialog, CDialog)
	//{{AFX_MSG_MAP(CCaptionDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaptionDialog message handlers
