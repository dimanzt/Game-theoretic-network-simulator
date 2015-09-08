// MANETView.cpp : implementation of the CMANETView class
//

#include "stdafx.h"
#include "MANET.h"

#include "MANETDoc.h"
#include "MANETView.h"


/////////////////////////////
#include "ProtocolDialog.h"
#include "SimDlg.h"
#include "Stat.h"
#include "RandomTraffic.h"
//#include "ForceSelfishness.h"
/////////////////////////////


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMANETView

IMPLEMENT_DYNCREATE(CMANETView, CView)

BEGIN_MESSAGE_MAP(CMANETView, CView)
	//{{AFX_MSG_MAP(CMANETView)
	ON_COMMAND(ID_NETWORK_ROUTER_ADD, OnNetworkRouterAdd)
	ON_COMMAND(ID_NETWORK_ROUTER_EDIT, OnNetworkRouterEdit)
	ON_COMMAND(ID_NETWORK_ROUTER_DELETE, OnNetworkRouterDelete)
	ON_COMMAND(ID_NETWORK_ROUTER_SELFGENERATE_1, OnNetworkRouterSelfgenerate1)
	ON_COMMAND(ID_NETWORK_ROUTER_SELFGENERATE_2, OnNetworkRouterSelfgenerate2)
	ON_COMMAND(ID_NETWORK_ROUTER_SELFGENERATE_5, OnNetworkRouterSelfgenerate5)
	ON_COMMAND(ID_NETWORK_ROUTER_SELFGENERATE_10, OnNetworkRouterSelfgenerate10)
	ON_COMMAND(ID_NETWORK_ROUTER_SELFGENERATE_20, OnNetworkRouterSelfgenerate20)
	ON_COMMAND(ID_NETWORK_ROUTER_SELFGENERATE_50, OnNetworkRouterSelfgenerate50)
	ON_COMMAND(ID_NETWORK_ROUTER_SELFGENERATE_100, OnNetworkRouterSelfgenerate100)
	ON_COMMAND(ID_NETWORK_ROUTER_PREFERENCES, OnNetworkRouterPreferences)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ROUTER_ADD, OnRouterAdd)
	ON_COMMAND(ID_ROUTER_EDIT, OnRouterEdit)
	ON_COMMAND(ID_ROUTER_DELETE, OnRouterDelete)
	ON_COMMAND(ID_NETWORK_LINK_ROUTERSCLICK, OnNetworkLinkRoutersclick)
	ON_WM_CREATE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_LINK_LINKFROMHERE, OnLinkLinkfromhere)
	ON_COMMAND(ID_LINK_LINKTOHERE, OnLinkLinktohere)
	ON_COMMAND(ID_NETWORK_LINK_SELFGENERATE, OnNetworkLinkSelfgenerate)
	ON_COMMAND(ID_NETWORK_TRAFFIC_ADD, OnNetworkTrafficAdd)
	ON_COMMAND(ID_SIMULATE_RUN, OnSimulateRun)
	ON_COMMAND(ID_NETWORK_LINK_DEFAULTPREFERENCES, OnNetworkLinkDefaultpreferences)
	ON_COMMAND(ID_NETWORK_LINK_ADD, OnNetworkLinkAdd)
	ON_COMMAND(ID_NETWORK_LINK_DELETE, OnNetworkLinkDelete)
	ON_COMMAND(ID_NETWORK_LINK_EDIT, OnNetworkLinkEdit)
	//ON_COMMAND(ID_NETWORK_TRAFFIC_SELFGENERATE, OnNetworkTrafficSelfgenerate)
	ON_COMMAND(ID_SIMULATION_STATISTICS, OnSimulationStatistics)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_ROUTER_FORCESELFISHNESS, &CMANETView::OnRouterForceselfishness)
	ON_COMMAND(ID_SELF_ANYTYPE, &CMANETView::OnSelfAnytype)
	ON_COMMAND(ID_SELF_AD, &CMANETView::OnSelfAdhoc)
	ON_COMMAND(ID_SELF_SELFISHI, &CMANETView::OnSelfSelfish1)
	ON_COMMAND(ID_SELF_SELFISHII, &CMANETView::OnSelfSelfish2)
	ON_COMMAND(ID_GAME_DEFAULTPREFERENCES, &CMANETView::OnGameDefaultpreferences)
	ON_COMMAND(ID_SELF_ALLCONNECTIONS, &CMANETView::OnSelfAllconnections)
	ON_COMMAND(ID_GRID_64, &CMANETView::OnGrid64)
	ON_COMMAND(ID_GRID_100, &CMANETView::OnGrid100)
	ON_COMMAND(ID_GRID_144, &CMANETView::OnGrid144)
	ON_COMMAND(ID_PROTOCOL_DEFAULTPREFERENCES, &CMANETView::OnProtocolDefaultpreferences)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMANETView construction/destruction

CMANETView::CMANETView()
{
	// TODO: add construction code here
	FS=new CForceSelfishness;
	this->DefaultLink.Frequency=10;
}

CMANETView::~CMANETView()
{
	if(FS!=NULL)
		delete FS;
}

BOOL CMANETView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMANETView drawing

void CMANETView::OnDraw(CDC* pDC)
{
	CMANETDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	int RouterSize=pDoc->Routers.GetSize();
	for(int i=0;i<RouterSize;i++)
	{
		Router=(CRouter*)(pDoc->Routers[i]);
		int LinkSize=Router->Links.GetSize();
		for(int i=0;i<LinkSize;i++)
			((CLink*)(Router->Links[i]))->Draw(pDC);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMANETView printing

BOOL CMANETView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMANETView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMANETView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMANETView diagnostics

#ifdef _DEBUG
void CMANETView::AssertValid() const
{
	CView::AssertValid();
}

void CMANETView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMANETDoc* CMANETView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMANETDoc)));
	return (CMANETDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMANETView message handlers

void CMANETView::OnNetworkRouterAdd()
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int RouterSize=pDoc->Routers.GetSize();

	CRouterDialog RouterDialog;
	RouterDialog.GetRouterData(&DefaultRouter);

	if(RouterDialog.DoModal()==IDOK)
	{
		int i=0;
		while((i<RouterSize)&&(((CRouter*)(pDoc->Routers[i]))->Caption!=RouterDialog.m_caption))
			i++;
		if(i==RouterSize)
		{
			Router=new CRouter;
			RouterDialog.PushRouterData(Router);
			pDoc->Routers.Add((CRouter*)Router);
			Router->Create(Router->Caption,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,Router->Rectangle,this,1);
			Router->Created=1;
		}
		else
			MessageBox("Your Router, Called "+RouterDialog.m_caption+", Already Added To Network!");
	}
}

void CMANETView::OnNetworkRouterEdit() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	CCaptionDialog CaptionDialog;
	CaptionDialog.m_caption="";
	if(CaptionDialog.DoModal())
	{
		int RouterSize=pDoc->Routers.GetSize();
		for(int i=0;i<RouterSize;i++)
			if(CaptionDialog.m_caption==((CRouter*)(pDoc->Routers[i]))->Caption)
			{
				CRouterDialog RouterDialog;
				RouterDialog.GetRouterData((CRouter*)(pDoc->Routers[i]));
				if(RouterDialog.DoModal()==IDOK)
					RouterDialog.PushRouterData((CRouter*)(pDoc->Routers[i]));
			}
	}
}

void CMANETView::OnNetworkRouterDelete() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	CCaptionDialog CaptionDialog;
	CaptionDialog.m_caption="";
	if(CaptionDialog.DoModal())
	{
		int RouterSize=pDoc->Routers.GetSize();
		int i=0;
		while(i<RouterSize)
			if(CaptionDialog.m_caption==((CRouter*)(pDoc->Routers[i]))->Caption)
			{
				delete ((CRouter*)(pDoc->Routers[i]));
				pDoc->Routers.RemoveAt(i);
				RouterSize--;
			}
			else
				i++;
	}
}

CString CMANETView::int2str(unsigned int i)
{
	CString s=(i>0)?"":"0";
	unsigned int j=i;
	while(j>0)
	{
		s=((char)((j%10)+'0'))+s;
		j=j/10;
	}
	return s;
}

void CMANETView::OnNetworkRouterSelfgenerate1() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	srand((unsigned)time(NULL));
	Router=new CRouter(DefaultRouter.Caption+int2str(pDoc->Routers.GetSize()),rand()%1000,rand()%500,DefaultRouter.RectLength,DefaultRouter.RectWidth,DefaultRouter.Coverage,DefaultRouter.Delay,DefaultRouter.BufferSize,DefaultRouter.ImagePath,DefaultRouter.Type);
	pDoc->Routers.Add((CRouter*)Router);
	Router->Create(Router->Caption,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,Router->Rectangle,this,1);
	Router->Created=1;
}

void CMANETView::OnNetworkRouterSelfgenerate2() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	srand((unsigned)time(NULL));
	for(int i=0;i<2;i++)
	{
		Router=new CRouter(DefaultRouter.Caption+int2str(pDoc->Routers.GetSize()),rand()%1000,rand()%500,DefaultRouter.RectLength,DefaultRouter.RectWidth,DefaultRouter.Coverage,DefaultRouter.Delay,DefaultRouter.BufferSize,DefaultRouter.ImagePath,DefaultRouter.Type);
		pDoc->Routers.Add((CRouter*)Router);
		Router->Create(Router->Caption,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,Router->Rectangle,this,1);
		Router->Created=1;
	}
}

void CMANETView::OnNetworkRouterSelfgenerate5() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	srand((unsigned)time(NULL));
	for(int i=0;i<5;i++)
	{
		Router=new CRouter(DefaultRouter.Caption+int2str(pDoc->Routers.GetSize()),rand()%1000,rand()%500,DefaultRouter.RectLength,DefaultRouter.RectWidth,DefaultRouter.Coverage,DefaultRouter.Delay,DefaultRouter.BufferSize,DefaultRouter.ImagePath,DefaultRouter.Type);
		pDoc->Routers.Add((CRouter*)Router);
		Router->Create(Router->Caption,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,Router->Rectangle,this,1);
		Router->Created=1;
	}
}

void CMANETView::OnNetworkRouterSelfgenerate10() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	srand((unsigned)time(NULL));
	for(int i=0;i<10;i++)
	{
		rand();
		Router=new CRouter(DefaultRouter.Caption+int2str(pDoc->Routers.GetSize()),rand()%1000,rand()%500,DefaultRouter.RectLength,DefaultRouter.RectWidth,DefaultRouter.Coverage,DefaultRouter.Delay,DefaultRouter.BufferSize,DefaultRouter.ImagePath,DefaultRouter.Type);
		pDoc->Routers.Add((CRouter*)Router);
		Router->Create(Router->Caption,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,Router->Rectangle,this,1);
		Router->Created=1;
	}
}

void CMANETView::OnNetworkRouterSelfgenerate20() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	srand((unsigned)time(NULL));
	for(int i=0;i<20;i++)
	{
		Router=new CRouter(DefaultRouter.Caption+int2str(pDoc->Routers.GetSize()),rand()%1000,rand()%500,DefaultRouter.RectLength,DefaultRouter.RectWidth,DefaultRouter.Coverage,DefaultRouter.Delay,DefaultRouter.BufferSize,DefaultRouter.ImagePath,DefaultRouter.Type);
		pDoc->Routers.Add((CRouter*)Router);
		Router->Create(Router->Caption,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,Router->Rectangle,this,1);
		Router->Created=1;
	}
}

void CMANETView::OnNetworkRouterSelfgenerate50() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	srand((unsigned)time(NULL));
	for(int i=0;i<50;i++)
	{
		Router=new CRouter(DefaultRouter.Caption+int2str(pDoc->Routers.GetSize()),rand()%1000,rand()%500,DefaultRouter.RectLength,DefaultRouter.RectWidth,DefaultRouter.Coverage,DefaultRouter.Delay,DefaultRouter.BufferSize,DefaultRouter.ImagePath,DefaultRouter.Type);
		pDoc->Routers.Add((CRouter*)Router);
		Router->Create(Router->Caption,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,Router->Rectangle,this,1);
		Router->Created=1;
	}
}

void CMANETView::OnNetworkRouterSelfgenerate100() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	srand((unsigned)time(NULL));
	for(int i=0;i<100;i++)
	{
		Router=new CRouter(DefaultRouter.Caption+int2str(pDoc->Routers.GetSize()),rand()%1000,rand()%500,DefaultRouter.RectLength,DefaultRouter.RectWidth,DefaultRouter.Coverage,DefaultRouter.Delay,DefaultRouter.BufferSize,DefaultRouter.ImagePath,DefaultRouter.Type);
		pDoc->Routers.Add((CRouter*)Router);
		Router->Create(Router->Caption,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,Router->Rectangle,this,1);
		Router->Created=1;
	}
}

void CMANETView::OnNetworkRouterPreferences() 
{
	// TODO: Add your command handler code here
	CRouterDialog routerdialog;
	routerdialog.GetRouterData(&DefaultRouter);
	if(routerdialog.DoModal()==IDOK)
		routerdialog.PushRouterData(&DefaultRouter);
}

void CMANETView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	if(RouterClick)
	{
		GetParentFrame()->ActivateFrame();
		this->CursorPosition=point;
		ScreenToClient(&CursorPosition);
		UpdateWindow();
		//CMenu menu;
		//if (menu.LoadMenu(IDR_MENU_LINK))
		//{
		//	CMenu* pPopup = menu.GetSubMenu(0);
			Popuplinkmenu=linkmenu.GetSubMenu(0);
			ASSERT(Popuplinkmenu!=NULL);
			//Popuplinkmenu->EnableMenuItem(ID_LINK_LINKFROMHERE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);//MF_BYPOSITION | MF_DISABLED | MF_GRAYED);
			Popuplinkmenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,AfxGetMainWnd());
		//}
//		if(PreviousRouter!=CurrentRouter)
//		{
//		}
	}
	else //RouterClick==0
	{
		GetParentFrame()->ActivateFrame();
		this->CursorPosition=point;
		ScreenToClient(&CursorPosition);
		UpdateWindow();
		CMenu menu;
		if (menu.LoadMenu(IDR_MENU_ROUTER))
		{
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,AfxGetMainWnd());
		}
	}
}

void CMANETView::OnRouterAdd() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRouterDialog RouterDialog;
	RouterDialog.GetRouterData(&DefaultRouter);
	if(RouterDialog.DoModal()==IDOK)
	{
		Router=new CRouter;//(routerdialog.m_caption,routerdialog.m_Xaxis,routerdialog.m_Yaxis,routerdialog.m_length,routerdialog.m_width,routerdialog.m_coverage,routerdialog.m_delay,routerdialog.m_buffersize,routerdialog.m_imagepath,routerdialog.m_type);
		RouterDialog.PushRouterData(Router);//GetRouterData(router);
		pDoc->Routers.Add((CRouter*)Router);
		Router->Create(Router->Caption,WS_CHILD|WS_VISIBLE|BS_BITMAP,Router->Rectangle,this,1);
		Router->Created=1;
	}	
}

void CMANETView::OnRouterEdit() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	int RouterSize=pDoc->Routers.GetSize();
	for(int i=0;i<RouterSize;i++)
	{
		Router=(CRouter*)(pDoc->Routers[i]);
		if( (Router->Rectangle.left<CursorPosition.x)&&(Router->Rectangle.right >CursorPosition.x)&&
			(Router->Rectangle.top <CursorPosition.y)&&(Router->Rectangle.bottom>CursorPosition.y) )
		{
			CRouterDialog RouterDialog;
			RouterDialog.GetRouterData((CRouter*)(pDoc->Routers[i]));
			if(RouterDialog.DoModal()==IDOK)
				RouterDialog.PushRouterData((CRouter*)(pDoc->Routers[i]));
		}
	}
}

void CMANETView::OnRouterDelete() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	int RouterSize=pDoc->Routers.GetSize();
	int i=0;
	while(i<RouterSize)
	{
		Router=(CRouter*)(pDoc->Routers[i]);
		if( (Router->Rectangle.left<CursorPosition.x)&&(Router->Rectangle.right >CursorPosition.x)&&
			(Router->Rectangle.top <CursorPosition.y)&&(Router->Rectangle.bottom>CursorPosition.y) )
		{
			delete Router;
			pDoc->Routers.RemoveAt(i);
			RouterSize--;
		}
		else
			i++;
	}
}


void CMANETView::OnNetworkLinkRoutersclick() 
{
	// TODO: Add your command handler code here
	CMenu* menu_bar=AfxGetMainWnd()->GetMenu();
	CMenu* network_menu=menu_bar->GetSubMenu(3);
	ASSERT(network_menu!=NULL);
	UINT state=network_menu->GetMenuState(ID_NETWORK_LINK_ROUTERSCLICK, MF_BYCOMMAND);//MF_DISABLED | MF_GRAYED);
	ASSERT(state!=0xFFFFFFFF);
	if (state & MF_CHECKED)
	{
		RouterClick=0;
		network_menu->CheckMenuItem(ID_NETWORK_LINK_ROUTERSCLICK, MF_UNCHECKED | MF_BYCOMMAND);
	}
	else
	{
		RouterClick=1;
		network_menu->CheckMenuItem(ID_NETWORK_LINK_ROUTERSCLICK, MF_CHECKED | MF_BYCOMMAND);
	}
}

int CMANETView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	this->RouterCounter=0;
	this->RouterClick=0;
	this->linkmenu.LoadMenu(IDR_MENU_LINK);
	//this->Popuplinkmenu=linkmenu.GetSubMenu(0);
	this->Popuplinkmenu=NULL;
	//this->Popuplinkmenu->EnableMenuItem(ID_LINK_LINKTOHERE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	//ASSERT(Popuplinkmenu!=NULL);
	this->fromRouter=NULL;
	this->toRouter=NULL;
	this->PreviousRouter=NULL;
	this->CurrentRouter=NULL;
	this->Link=NULL;
	this->Router=NULL;
	this->Traffic=NULL;
	this->Document=NULL;
	return 0;
}

void CMANETView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CurrentPosition=point;
	CView::OnRButtonDown(nFlags, point);
}

void CMANETView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CView::OnRButtonUp(nFlags, point);
}

void CMANETView::OnLinkLinkfromhere() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	int RouterSize=pDoc->Routers.GetSize();
	int i=0;
	while(i<RouterSize) //first router is chosen
	{
		Router=(CRouter*)(pDoc->Routers[i]);
		if( (Router->Rectangle.left<CursorPosition.x)&&(Router->Rectangle.right >CursorPosition.x)&&
			(Router->Rectangle.top <CursorPosition.y)&&(Router->Rectangle.bottom>CursorPosition.y) )
		{
			i=RouterSize;
			fromRouter=Router;
			Popuplinkmenu->CheckMenuItem(ID_LINK_LINKFROMHERE,   MF_CHECKED | MF_BYCOMMAND);
			UINT fromstate=Popuplinkmenu->GetMenuState(ID_LINK_LINKFROMHERE , MF_BYCOMMAND);
			UINT tostate  =Popuplinkmenu->GetMenuState(ID_LINK_LINKTOHERE   , MF_BYCOMMAND);
			if(tostate & MF_CHECKED)
			{
				if(fromstate & MF_CHECKED)
				{
					Popuplinkmenu->CheckMenuItem(ID_LINK_LINKFROMHERE, MF_UNCHECKED | MF_BYCOMMAND);
					Popuplinkmenu->CheckMenuItem(ID_LINK_LINKTOHERE  , MF_UNCHECKED | MF_BYCOMMAND);
				}
				if((fromRouter!=NULL)&&(toRouter!=NULL))
				{
					Link=new CLink(fromRouter,toRouter);
					//pDoc->links.Add((CLink*)link);
					this->Invalidate();
				}
			}
		}
		else
			i++;
	}
	//CMenu menu;
	//if (menu.LoadMenu(IDR_MENU_LINK))
	//if(i+1==routersize)
	//{
		//GetParentFrame()->ActivateFrame();
		//Popuplinkmenu=linkmenu.GetSubMenu(0);
		//CMenu* pPopup=menu.GetSubMenu(0);
		//ASSERT(pPopup!=NULL);
		//UINT state;
		//state=Popuplinkmenu->GetMenuState(ID_LINK_LINKFROMHERE, MF_BYCOMMAND);//MF_BYPOSITION);//MF_BYCOMMAND);
		//state=MF_BYCOMMAND;
		//state=MF_DISABLED;
		//state=MF_BYCOMMAND | MF_DISABLED | MF_GRAYED;
		//ASSERT(state!=0xFFFFFFFF);
		//state=Popuplinkmenu->EnableMenuItem(ID_LINK_LINKFROMHERE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);//MF_BYPOSITION | MF_DISABLED | MF_GRAYED);
		//state=Popuplinkmenu->CheckMenuItem(ID_LINK_LINKFROMHERE, MF_CHECKED | MF_BYCOMMAND);
		//state=pPopup->CheckMenuItem(ID_LINK_LINKFROMHERE, MF_CHECKED | MF_BYCOMMAND);
		//state=Popuplinkmenu->GetMenuState(ID_LINK_LINKFROMHERE,MF_BYCOMMAND);
		//state=pPopup->GetMenuState(ID_LINK_LINKFROMHERE,MF_BYCOMMAND);
	//}
}

void CMANETView::OnLinkLinktohere() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	int RouterSize=pDoc->Routers.GetSize();
	int i=0;
	while(i<RouterSize) //second router is chosen
	{
		Router=(CRouter*)(pDoc->Routers[i]);
		if( (Router->Rectangle.left<CursorPosition.x)&&(Router->Rectangle.right >CursorPosition.x)&&
			(Router->Rectangle.top <CursorPosition.y)&&(Router->Rectangle.bottom>CursorPosition.y) )
		{
			i=RouterSize;
			toRouter=Router;
			Popuplinkmenu->CheckMenuItem(ID_LINK_LINKTOHERE,    MF_CHECKED | MF_BYCOMMAND);
			UINT tostate  =Popuplinkmenu->GetMenuState(ID_LINK_LINKTOHERE  , MF_BYCOMMAND);
			UINT fromstate=Popuplinkmenu->GetMenuState(ID_LINK_LINKFROMHERE, MF_BYCOMMAND);
			if(fromstate & MF_CHECKED)
			{
				if(tostate & MF_CHECKED)
				{
					Popuplinkmenu->CheckMenuItem(ID_LINK_LINKFROMHERE, MF_UNCHECKED | MF_BYCOMMAND);
					Popuplinkmenu->CheckMenuItem(ID_LINK_LINKTOHERE  , MF_UNCHECKED | MF_BYCOMMAND);
				}
				if((fromRouter!=NULL)&&(toRouter!=NULL))
				{
					Link=new CLink(fromRouter,toRouter);
					this->Invalidate();
				}
			}
		}
		else
			i++;
	}
}

void CMANETView::OnNetworkLinkSelfgenerate() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	int RouterSize=pDoc->Routers.GetSize();
	int i,j;
	CRouter *ri,*rj;
	for(i=0;i<RouterSize;i++)
	{
		ri=(CRouter*)(pDoc->Routers[i]);
		for(j=i+1;j<RouterSize;j++)
		{
			rj=(CRouter*)(pDoc->Routers[j]);
			int dis2i=ri->Coverage*ri->Coverage;
			int dis2j=rj->Coverage*rj->Coverage;
			int dis2ij=Distance2(ri,rj);
			if((dis2ij!=-1)&&(dis2ij<=dis2i)&&(dis2ij<=dis2j))
			{
				BOOL repeated=0;
				int neighborsize_i=ri->Neighbors.GetSize();
				int neighborsize_j=rj->Neighbors.GetSize();
				if(neighborsize_i<neighborsize_j)
				{
					int k=0;
					while((k<neighborsize_i)&&(rj!=((CRouter*)(ri->Neighbors[k]))))
						k++;
					if(k<neighborsize_i)
						repeated=1;
				}
				else
				{
					int k=0;
					while((k<neighborsize_j)&&(ri!=((CRouter*)(rj->Neighbors[k]))))
						k++;
					if(k<neighborsize_j)
						repeated=1;
				}
				if(!repeated)
					Link=new CLink(ri,rj,DefaultLink.Frequency,DefaultLink.Duplex);
			}
		}
	}
	this->Invalidate();
}

int CMANETView::Distance2(CRouter *ri, CRouter *rj)
{
	if((ri!=NULL)&&(rj!=NULL))
	{
		int deltaX=ri->X-rj->X;
		int deltaY=ri->Y-rj->Y;
		return ((deltaX*deltaX)+(deltaY*deltaY));
	}
	else
		return -1;
}

void CMANETView::OnNetworkTrafficAdd() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int RouterSize=pDoc->Routers.GetSize();
	CTrafficDialog td;
	if(td.DoModal()==IDOK)
	{
		if(td.m_destination!=td.m_source)
		{
			int i=0;
			BOOL sourcexist=0,destexist=0;
			CRouter *source,*dest;
			while((i<RouterSize)&&(!(sourcexist&&destexist)))
			{
				Router=(CRouter*)(pDoc->Routers[i]);
				if(td.m_source==Router->Caption)
				{
					source=(CRouter*)(pDoc->Routers[i]);
					sourcexist=1;
				}
				if(td.m_destination==Router->Caption)
				{
					dest=(CRouter*)(pDoc->Routers[i]);
					destexist=1;
				}
				i++;
			}
			if(sourcexist&&destexist)
			{
				Traffic=new CTraffic(source,dest,td.m_protocol,td.m_start);
				//source->traffics.Add((CTraffic*)traffic);
			}
			else if(sourcexist)
				MessageBox("There is No Destination Called "+td.m_destination+"!");
			else if(destexist)
				MessageBox("There is No Source Called "+td.m_source+"!");
			else
				MessageBox("Your Source and Destination Don't Exist!");
		}
		else
			MessageBox("The Source And The Destination Are The Same!");
	}
}

void CMANETView::OnNetworkLinkDefaultpreferences() 
{
	// TODO: Add your command handler code here
	//CLink DefaultLink;
	CLinkDialog linkdialog;
	linkdialog.GetLinkData(&DefaultLink);
	linkdialog.enabled=0;
	//linkdialog.m_in.EnableWindow(FALSE);
	//linkdialog.m_out.EnableWindow(FALSE);
	if(linkdialog.DoModal()==IDOK)
		linkdialog.PushLinkData(&DefaultLink);
}

void CMANETView::OnNetworkLinkAdd() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int RouterSize=pDoc->Routers.GetSize();
	CLinkDialog LinkDialog;
	LinkDialog.GetLinkData(&DefaultLink);
	if(LinkDialog.DoModal()==IDOK)
	{
		int i=0;
		CRouter *router1=NULL,*router2=NULL;
		while((i<RouterSize)&&((router1==NULL)||(router2==NULL)))
		{
			Router=(CRouter*)(pDoc->Routers[i]);
			if(Router->Caption==LinkDialog.m_router1)
				router1=Router;
			if(Router->Caption==LinkDialog.m_router2)
				router2=Router;
			i++;
		}
		if((router1!=NULL)&&(router2!=NULL))
		{
			Link=new CLink(router1,router2);
			LinkDialog.PushLinkData(Link);
		}
		else
			MessageBox("The router, called "+LinkDialog.m_router1+" or "+LinkDialog.m_router2+", does not exist!");
	}
}

void CMANETView::OnNetworkLinkDelete() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	CEnd2End end2end;
	end2end.m_router1="";
	end2end.m_router2="";
	if(end2end.DoModal())
	{
		int RouterSize=pDoc->Routers.GetSize();
		int i=0;
		while((i<RouterSize)&&(((CRouter*)(pDoc->Routers[i]))->Caption!=end2end.m_router1))
			i++;
		if(i<RouterSize)
		{
			Router=(CRouter*)(pDoc->Routers[i]);
			int j=0;
			int NeighborSize=Router->Neighbors.GetSize();
			while((j<NeighborSize)&&(((CRouter*)(Router->Neighbors[j]))->Caption!=end2end.m_router2))
				j++;
			if(j<NeighborSize)
				delete ((CLink*)(Router->Links[j]));
			else
				MessageBox("Router2 was not found! May it be there is no link between them!");
		}
		else
			MessageBox("Router1 was not found!");
	}
}

void CMANETView::OnNetworkLinkEdit() 
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	CEnd2End end2end;
	end2end.m_router1="";
	end2end.m_router2="";
	if(end2end.DoModal())
	{
		int RouterSize=pDoc->Routers.GetSize();
		int i=0;
		while((i<RouterSize)&&(((CRouter*)(pDoc->Routers[i]))->Caption!=end2end.m_router1))
			i++;
		if(i<RouterSize)
		{
			Router=(CRouter*)(pDoc->Routers[i]);
			int j=0;
			int NeighborSize=Router->Neighbors.GetSize();
			while((j<NeighborSize)&&(((CRouter*)(Router->Neighbors[j]))->Caption!=end2end.m_router2))
				j++;
			if(j<NeighborSize)
			{
				Link=(CLink*)(Router->Links[j]);
				CLinkDialog LinkDialog;
				LinkDialog.GetLinkData(Link);
				LinkDialog.enabled=0;
				if(LinkDialog.DoModal()==IDOK)
					LinkDialog.PushLinkData(Link);
			}
			else
				MessageBox("Router2 was not found! May it be there is no link between them!");
		}
		else
			MessageBox("Router1 was not found!");
	}
}

void CMANETView::OnSimulateRun() 
{
	// TODO: Add your command handler code here
	if(CheckNetwork())
	{
		CSimDlg simulation;
		simulation.Document=this->GetDocument();
		simulation.DoModal();
	}
}

BOOL CMANETView::CheckNetwork()
{
	Document=GetDocument();
	ASSERT_VALID(Document);
	int RouterSize=Document->Routers.GetSize();
	//int linksize=document->links.GetSize();
	//int trafficsize=document->traffics.GetSize();
	if(!RouterSize)//&&linksize&&trafficsize)
	{
		MessageBox("There is no router!");
		return 0;
	}
	else
	{
		int ir=0;
		while((ir<RouterSize)&&(((CRouter*)(Document->Routers[ir]))!=NULL))
			ir++;
		if(ir<RouterSize)
		{
			MessageBox("Error in CRouter* no."+int2str(ir));
			return 0;
		}
		else
		{
			int LinkSize;
			int TrafficSize;
			for(ir=0;ir<RouterSize;ir++)
			{
				Router=(CRouter*)(Document->Routers[ir]);
				LinkSize=Router->Links.GetSize();
				int il=0;
				while((il<LinkSize)&&(((CLink*)(Router->Links[il]))!=NULL))
					il++;
				if(il<LinkSize)
				{
					MessageBox("Error in CLink* no. "+int2str(il)+" of CRouter* no. "+int2str(ir));
					return 0;
				}
				else
				{
					TrafficSize=Router->Traffics.GetSize();
					int it=0;
					while((it<TrafficSize)&&(((CTraffic*)(Router->Traffics[it]))!=NULL))
						it++;
					if(it<TrafficSize)
					{
						MessageBox("Error in CTraffic* no. "+int2str(it)+" of CRouter* no. "+int2str(ir));
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

void CMANETView::OnSimulationStatistics() 
{
	// TODO: Add your command handler code here
	if(CheckNetwork())
	{
		CStat statistics;
		statistics.Document=this->GetDocument();
		statistics.DoModal();
	}	
}

void CMANETView::OnRouterForceselfishness()
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	srand((unsigned)time(NULL));
	int RouterSize=pDoc->Routers.GetSize();
	if(CheckNetwork())
	{
		if(FS->DoModal()==IDOK)
		{
			int i;
			int NodeNum;
			CRouter* node;
			for(i=0;i<FS->RoutersNum;i++)
			{
				do//Skip These types of nodes
				{
					NodeNum=rand()%RouterSize;
					node=(CRouter*)(pDoc->Routers[NodeNum]);
				}while((node->Type)||(node->Traffics.GetSize())||(DestTrafficCheck(node)));
				//Choose a node which -> not selfish & not connected & not be destine traffic
				node->Type=FS->SelfishType+1;
			}
		}
	}
}

int CMANETView::DestTrafficCheck(CRouter* Node)
{
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	int RouterSize=pDoc->Routers.GetSize();
	int i,j,TrafficSize;
	for(i=0;i<RouterSize;i++)
	{
		Router=(CRouter*)(pDoc->Routers[i]);
		TrafficSize=Router->Traffics.GetSize();
		for(j=0;j<TrafficSize;j++)
		{
			Traffic=(CTraffic*)(Router->Traffics[j]);
			if(Node==Traffic->Destination)
				return 1;
		}
	}
	return 0;
}

BOOL CMANETView::CheckTrafficRepetition(CRouter* SourceAddress, CRouter* DestAddress)
{	//Repeated connection returns TRUE
	int ts=SourceAddress->Traffics.GetSize();
	for(int tsc=0;tsc<ts;tsc++)
		if(((CTraffic*)(SourceAddress->Traffics[tsc]))->Destination==DestAddress)
			return TRUE;
	return FALSE;
}

void CMANETView::OnSelfAnytype()
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	srand((unsigned)time(NULL));
	int RouterSize=pDoc->Routers.GetSize();
	RandomTraffic rt;
	if(rt.DoModal()==IDOK)
	{
		int source_index, dest_index, duration_index;
		CRouter *source,*dest;
		for(int ncc=0;ncc<rt.m_connection_num;ncc++)
		{
			do
			{
				source_index=rand()%RouterSize;
				dest_index=rand()%RouterSize;
				//duration_index=rand()%(rt.StopTick-rt.StartTick);//.m_start_range);
				duration_index=ncc*500;
				source=(CRouter*)(pDoc->Routers[source_index]);
				dest=(CRouter*)(pDoc->Routers[dest_index]);
			}while ((source_index==dest_index)||(CheckTrafficRepetition(source,dest)));
			Traffic=new CTraffic(source,dest,rt.m_protocol,rt.StartTick+duration_index);
			//source->traffics.Add((CTraffic*)traffic);
		}
	}
}

void CMANETView::OnSelfAdhoc()
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	srand((unsigned)time(NULL));
	int RouterSize=pDoc->Routers.GetSize();
	RandomTraffic rt;
	if(rt.DoModal()==IDOK)
	{
		int source_index, dest_index, duration_index; //start_index;
		CRouter *source,*dest;
		for(int ncc=0;ncc<rt.m_connection_num;ncc++)
		{
			do
			{
				source_index=rand()%RouterSize;
				dest_index=rand()%RouterSize;
				//duration_index=rand()%(rt.StopTick-rt.StartTick);//.m_start_range);
				duration_index=500*ncc;
				source=(CRouter*)(pDoc->Routers[source_index]);
				dest=(CRouter*)(pDoc->Routers[dest_index]);
			}while ((source->Type)||(dest->Type)||(source_index==dest_index)||(CheckTrafficRepetition(source,dest)));
			Traffic=new CTraffic(source,dest,rt.m_protocol,rt.StartTick+duration_index);//start_index);
			//source->traffics.Add((CTraffic*)traffic);
		}
	}
}

void CMANETView::OnSelfSelfish1()
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	srand((unsigned)time(NULL));
	int RouterSize=pDoc->Routers.GetSize();
	RandomTraffic rt;
	if(rt.DoModal()==IDOK)
	{
		int source_index, dest_index, duration_index;//start_index;
		CRouter *source,*dest;
		for(int ncc=0;ncc<rt.m_connection_num;ncc++)
		{
			do
			{
				source_index=rand()%RouterSize;
				dest_index=rand()%RouterSize;
				//duration_index=rand()%(rt.StopTick-rt.StartTick);//.m_start_range);
				duration_index=500*ncc;
				source=(CRouter*)(pDoc->Routers[source_index]);
				dest=(CRouter*)(pDoc->Routers[dest_index]);
			}while ((source->Type!=1)||(dest->Type!=1)
				||(source_index==dest_index)||(CheckTrafficRepetition(source,dest)));
			Traffic=new CTraffic(source,dest,rt.m_protocol,rt.StartTick+duration_index);//start_index);
			//source->traffics.Add((CTraffic*)traffic);
		}
	}
}

void CMANETView::OnSelfSelfish2()
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	srand((unsigned)time(NULL));
	int RouterSize=pDoc->Routers.GetSize();
	RandomTraffic rt;
	if(rt.DoModal()==IDOK)
	{
		int source_index, dest_index, duration_index;//start_index;
		CRouter *source,*dest;
		for(int ncc=0;ncc<rt.m_connection_num;ncc++)
		{
			do
			{
				source_index=rand()%RouterSize;
				dest_index=rand()%RouterSize;
				//duration_index=rand()%(rt.StopTick-rt.StartTick);//.m_start_range);
				duration_index=500*ncc;
				source=(CRouter*)(pDoc->Routers[source_index]);
				dest=(CRouter*)(pDoc->Routers[dest_index]);
			}while ((source->Type!=2)||(dest->Type!=2)
				||(source_index==dest_index)||(CheckTrafficRepetition(source,dest)));
			Traffic=new CTraffic(source,dest,rt.m_protocol,rt.StartTick+duration_index);//start_index);
			//source->traffics.Add((CTraffic*)traffic);
		}
	}
}

void CMANETView::OnGameDefaultpreferences()
{
	// TODO: Add your command handler code here
	Document=GetDocument();
	ASSERT_VALID(Document);
	int RouterSize=Document->Routers.GetSize();
	CGameDialog gamedialog;
	int i;
	if(gamedialog.DoModal()==IDOK)
	{
		for(i=0;i<RouterSize;i++)
			((CRouter*)(Document->Routers[i]))->SetGames(gamedialog.m_Strategy);
	}
		//routerdialog.PushRouterData(&DefaultRouter);
}

void CMANETView::OnSelfAllconnections()
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	srand((unsigned)time(NULL));
	int RouterSize=pDoc->Routers.GetSize();
	RandomTraffic rt;
	if(rt.DoModal()==IDOK)
	{
		int source_index, dest_index, duration_index;
		CRouter *source,*dest;
		int i,j;
		for(i=0;i<RouterSize;i++)
			for(j=i+1;j<RouterSize;j++)
			{
				do
				{
					source_index=i;
					dest_index=j;
					duration_index=rand()%(rt.StopTick-rt.StartTick);
					source=(CRouter*)(pDoc->Routers[source_index]);
					dest=(CRouter*)(pDoc->Routers[dest_index]);
				}while ((source_index==dest_index)||(CheckTrafficRepetition(source,dest)));
				Traffic=new CTraffic(source,dest,rt.m_protocol,rt.StartTick+duration_index);
				do
				{
					source_index=j;
					dest_index=i;
					duration_index=rand()%(rt.StopTick-rt.StartTick);
					source=(CRouter*)(pDoc->Routers[source_index]);
					dest=(CRouter*)(pDoc->Routers[dest_index]);
				}while ((source_index==dest_index)||(CheckTrafficRepetition(source,dest)));
				Traffic=new CTraffic(source,dest,rt.m_protocol,rt.StartTick+duration_index);
			}
	}
}

void CMANETView::OnGrid64()
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	srand((unsigned)time(NULL));
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			{
				Router=new CRouter(DefaultRouter.Caption+int2str(pDoc->Routers.GetSize()),50+50*j,50+50*(i),DefaultRouter.RectLength,DefaultRouter.RectWidth,98,DefaultRouter.Delay,DefaultRouter.BufferSize,DefaultRouter.ImagePath,DefaultRouter.Type);
				pDoc->Routers.Add((CRouter*)Router);
				Router->Create(Router->Caption,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,Router->Rectangle,this,1);
				Router->Created=1;
		}

}


void CMANETView::OnGrid100()
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	srand((unsigned)time(NULL));
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
			{
				Router=new CRouter(DefaultRouter.Caption+int2str(pDoc->Routers.GetSize()),50+50*j,50+50*(i),DefaultRouter.RectLength,DefaultRouter.RectWidth,98,DefaultRouter.Delay,DefaultRouter.BufferSize,DefaultRouter.ImagePath,DefaultRouter.Type);
				pDoc->Routers.Add((CRouter*)Router);
				Router->Create(Router->Caption,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,Router->Rectangle,this,1);
				Router->Created=1;
		}

}



void CMANETView::OnGrid144()
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	srand((unsigned)time(NULL));
	for(int i=0;i<12;i++)
		for(int j=0;j<12;j++)
			{
				Router=new CRouter(DefaultRouter.Caption+int2str(pDoc->Routers.GetSize()),50+50*j,50+50*(i),DefaultRouter.RectLength,DefaultRouter.RectWidth,98,DefaultRouter.Delay,DefaultRouter.BufferSize,DefaultRouter.ImagePath,DefaultRouter.Type);
				pDoc->Routers.Add((CRouter*)Router);
				Router->Create(Router->Caption,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,Router->Rectangle,this,1);
				Router->Created=1;
		}
}

void CMANETView::OnProtocolDefaultpreferences()
{
	// TODO: Add your command handler code here
	CMANETDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CProtocolDialog pd;
	if(pd.DoModal()==IDOK)
	{
		int RouterSize=pDoc->Routers.GetSize();
		for(int ir=0;ir<RouterSize;ir++)
		{
			Router=(CRouter*)(pDoc->Routers[ir]);
			int TrafficSize = Router->Traffics.GetSize();
			for(int it=0;it<TrafficSize;it++)
			{
				Traffic=(CTraffic*)(Router->Traffics[it]);
				Traffic->Protocol=pd.Protocol;
			}
		}
	}
}
