#pragma once


// CGameDialog dialog

class CGameDialog : public CDialog
{
	DECLARE_DYNAMIC(CGameDialog)

public:
	CGameDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGameDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_GAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_Strategy;
};
