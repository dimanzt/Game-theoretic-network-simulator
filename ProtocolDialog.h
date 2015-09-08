#pragma once


// CProtocolDialog dialog

class CProtocolDialog : public CDialog
{
	DECLARE_DYNAMIC(CProtocolDialog)

public:
	CProtocolDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProtocolDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_Protocol };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int Protocol;
};
