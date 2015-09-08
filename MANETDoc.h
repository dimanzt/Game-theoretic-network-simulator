// MANETDoc.h : interface of the CMANETDoc class
//
/////////////////////////////////////////////////////////////////////////////



#if !defined(AFX_MANETDOC_H__161A7121_92A2_49F2_9D83_D92DFCAC553F__INCLUDED_)
#define AFX_MANETDOC_H__161A7121_92A2_49F2_9D83_D92DFCAC553F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////
#include "Router.h"
#include "Traffic.h"
#include "Link.h"
#include "RouterDialog.h"
/////////////////////////////



class CMANETDoc : public CDocument
{
protected: // create from serialization only
	CMANETDoc();
	DECLARE_DYNCREATE(CMANETDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMANETDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CObArray Routers;
	CRouter* Router;
//	CObArray links;
	CLink*	 Link;
//	CObArray traffics;
	CTraffic* Traffic;
	virtual ~CMANETDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMANETDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANETDOC_H__161A7121_92A2_49F2_9D83_D92DFCAC553F__INCLUDED_)
