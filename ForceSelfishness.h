#pragma once


// CForceSelfishness dialog

class CForceSelfishness : public CDialog
{
	DECLARE_DYNAMIC(CForceSelfishness)

public:
	CForceSelfishness(CWnd* pParent = NULL);   // standard constructor
	virtual ~CForceSelfishness();

// Dialog Data
	enum { IDD = IDD_DIALOG_ForceSelfishness };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int SelfishType;
	int RoutersNum;
};
