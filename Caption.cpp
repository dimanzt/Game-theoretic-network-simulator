// Caption.cpp : implementation file
//

#include "stdafx.h"
#include "MANET.h"
#include "Caption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaption dialog


CCaption::CCaption(CWnd* pParent /*=NULL*/)
	: CDialog(CCaption::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCaption)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCaption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCaption)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCaption, CDialog)
	//{{AFX_MSG_MAP(CCaption)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaption message handlers
