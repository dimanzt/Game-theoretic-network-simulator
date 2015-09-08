// ProtocolDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MANET.h"
#include "ProtocolDialog.h"


// CProtocolDialog dialog

IMPLEMENT_DYNAMIC(CProtocolDialog, CDialog)

CProtocolDialog::CProtocolDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CProtocolDialog::IDD, pParent)
	, Protocol(0)
{

}

CProtocolDialog::~CProtocolDialog()
{
}

void CProtocolDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_GTAMR, Protocol);
}


BEGIN_MESSAGE_MAP(CProtocolDialog, CDialog)
END_MESSAGE_MAP()


// CProtocolDialog message handlers
