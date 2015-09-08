// GameDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MANET.h"
#include "GameDialog.h"


// CGameDialog dialog

IMPLEMENT_DYNAMIC(CGameDialog, CDialog)

CGameDialog::CGameDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGameDialog::IDD, pParent)
	, m_Strategy(1)
{

}

CGameDialog::~CGameDialog()
{
}

void CGameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_TFT, m_Strategy);
}


BEGIN_MESSAGE_MAP(CGameDialog, CDialog)
END_MESSAGE_MAP()


// CGameDialog message handlers
