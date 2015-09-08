// ForceSelfishness.cpp : implementation file
//

#include "stdafx.h"
#include "MANET.h"
#include "ForceSelfishness.h"


// CForceSelfishness dialog

IMPLEMENT_DYNAMIC(CForceSelfishness, CDialog)

CForceSelfishness::CForceSelfishness(CWnd* pParent /*=NULL*/)
	: CDialog(CForceSelfishness::IDD, pParent)
	, SelfishType(0)
	, RoutersNum(0)
{

}

CForceSelfishness::~CForceSelfishness()
{
}

void CForceSelfishness::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_S1, SelfishType);
	DDX_Text(pDX, IDC_EDIT_RoutersNum, RoutersNum);
}


BEGIN_MESSAGE_MAP(CForceSelfishness, CDialog)
END_MESSAGE_MAP()


// CForceSelfishness message handlers
