// MANETView.h : interface of the CMANETView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MANETVIEW_H__430279D7_7EC8_4D5E_BD8E_19F222A8DE13__INCLUDED_)
#define AFX_MANETVIEW_H__430279D7_7EC8_4D5E_BD8E_19F222A8DE13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////
#include "Link.h"
#include "LinkDialog.h"
#include "Traffic.h"
#include "TrafficDialog.h"
#include "Router.h"
#include "RouterDialog.h"
#include "Game.h"
#include "GameDialog.h"
#include "CaptionDialog.h"
#include "End2End.h"
#include "ForceSelfishness.h"
/////////////////////////////



class CMANETView : public CView
{
protected: // create from serialization only
	CMANETView();
	DECLARE_DYNCREATE(CMANETView)

// Attributes
public:
	CMANETDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMANETView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	//CFile			myFile;
	CForceSelfishness* FS;
	BOOL			CheckTrafficRepetition(CRouter* SourceAddress, CRouter* DestAddress);
	CLink			DefaultLink;
	BOOL			CheckNetwork();
	int				Distance2(CRouter* ri,CRouter* rj);
	CMenu			linkmenu;
	CMenu*			Popuplinkmenu;
	BYTE			RouterCounter;
	CString			int2str(unsigned int i);
	BOOL			RouterClick;
	CRouter*		fromRouter;
	CRouter*		toRouter;
	CRouter*		PreviousRouter;
	CRouter*		CurrentRouter;
	POINT			CursorPosition;
	POINT			CurrentPosition;
	POINT			PreviousPosition;
	CTraffic*		Traffic;
	CLink*			Link;
	CMANETDoc*		Document;
	CRouter*		Router;
	CRouter			DefaultRouter;
	virtual			~CMANETView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMANETView)
	afx_msg void OnNetworkRouterAdd();
	afx_msg void OnNetworkRouterEdit();
	afx_msg void OnNetworkRouterDelete();
	afx_msg void OnNetworkRouterSelfgenerate1();
	afx_msg void OnNetworkRouterSelfgenerate2();
	afx_msg void OnNetworkRouterSelfgenerate5();
	afx_msg void OnNetworkRouterSelfgenerate10();
	afx_msg void OnNetworkRouterSelfgenerate20();
	afx_msg void OnNetworkRouterSelfgenerate50();
	afx_msg void OnNetworkRouterSelfgenerate100();
	afx_msg void OnNetworkRouterPreferences();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRouterAdd();
	afx_msg void OnRouterEdit();
	afx_msg void OnRouterDelete();
	afx_msg void OnNetworkLinkRoutersclick();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLinkLinkfromhere();
	afx_msg void OnLinkLinktohere();
	afx_msg void OnNetworkLinkSelfgenerate();
	afx_msg void OnNetworkTrafficAdd();
	afx_msg void OnSimulateRun();
	afx_msg void OnNetworkLinkDefaultpreferences();
	afx_msg void OnNetworkLinkAdd();
	afx_msg void OnNetworkLinkDelete();
	afx_msg void OnNetworkLinkEdit();
	//afx_msg void OnNetworkTrafficSelfgenerate();
	afx_msg void OnSimulationStatistics();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRouterForceselfishness();
	int DestTrafficCheck(CRouter* Node);
	afx_msg void OnSelfAnytype();
	afx_msg void OnSelfAdhoc();
	afx_msg void OnSelfSelfish1();
	afx_msg void OnSelfSelfish2();
	afx_msg void OnGameDefaultpreferences();
	afx_msg void OnSelfAllconnections();
	afx_msg void OnGrid64();
	afx_msg void OnGrid100();
	afx_msg void OnGrid225();
	afx_msg void OnGrid144();
	afx_msg void OnProtocolDefaultpreferences();
};

#ifndef _DEBUG  // debug version in MANETView.cpp
inline CMANETDoc* CMANETView::GetDocument()
   { return (CMANETDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANETVIEW_H__430279D7_7EC8_4D5E_BD8E_19F222A8DE13__INCLUDED_)
