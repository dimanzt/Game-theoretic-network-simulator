// MANETDoc.cpp : implementation of the CMANETDoc class
//

#include "stdafx.h"
#include "MANET.h"

#include "MANETDoc.h"


/////////////////////////////
#include "MANETView.h"
/////////////////////////////


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMANETDoc

IMPLEMENT_DYNCREATE(CMANETDoc, CDocument)

BEGIN_MESSAGE_MAP(CMANETDoc, CDocument)
	//{{AFX_MSG_MAP(CMANETDoc)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMANETDoc construction/destruction

CMANETDoc::CMANETDoc()
{
	// TODO: add one-time construction code here

}

CMANETDoc::~CMANETDoc()
{
	int test=0;
}

BOOL CMANETDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	int RouterSize=Routers.GetSize();
	for(int i=0;i<RouterSize;i++)
		delete ((CRouter*)(Routers[i]));
	Routers.RemoveAll();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMANETDoc serialization

void CMANETDoc::Serialize(CArchive& ar)
{
	CString NotMainRouter = "NMR";
	if (ar.IsStoring())
	{
		// TODO: add storing code here
/*		ar<<traffics.GetSize();
		for(i=0;i<traffics.GetSize();i++)
			((CTraffic*)(traffics[i]))->Serialize(ar);
		ar<<links.GetSize();
		for(i=0;i<links.GetSize();i++)
			((CLink*)(links[i]))->Serialize(ar);
*/		
		int RouterSize=Routers.GetSize();
		ar<<RouterSize;
		for(int ir=0;ir<RouterSize;ir++)
			((CRouter*)(Routers[ir]))->Serialize(ar);
//		links.Serialize(ar);
//		routers.Serialize(ar);
//		traffics.Serialize(ar);
		for(int ir=0;ir<RouterSize;ir++)
		{
			Router=(CRouter*)(Routers[ir]);
			int LinkSize=Router->Links.GetSize();
			ar<<LinkSize;
			for(int il=0;il<LinkSize;il++)
			{
				//if( (((CLink*)(Router->Links[il]))->Router1) == Router )
				((CLink*)(Router->Links[il]))->Serialize(ar);
				//else
				//	ar<<NotMainRouter;
			}
			int TrafficSize=Router->Traffics.GetSize();
			ar<<TrafficSize;
			for(int it=0;it<TrafficSize;it++)
				((CTraffic*)(Router->Traffics[it]))->Serialize(ar);
		}
	}
	else
	{
		// TODO: add loading code here
		POSITION pos=GetFirstViewPosition();
		CView* pView=GetNextView(pos);
		int RouterSize;
		ar>>RouterSize;
		for(int ir=0;ir<RouterSize;ir++)
		{
			Router=new CRouter;
			Router->Serialize(ar);
			Routers.Add((CRouter*)Router);
			Router->Create(Router->Caption,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,Router->Rectangle,(CMANETView*)pView,1);
			//pView->UpdateWindow();
		}
		for(int ir=0;ir<RouterSize;ir++)
		{
			Router=(CRouter*)(Routers[ir]);
			//CLink TempLink;
			int LinkSize;
			int	duplex;
			int	frequency;	//No. of Pixels per Tick
			ar>>LinkSize;
			CString caption;
			for(int il=0;il<LinkSize;il++)
			{
				//TempLink.Serialize(&ar);
				ar>>caption;
				//if(caption != NotMainRouter)
				if(Router->Caption == caption)
				{
					ar>>caption;
					int ir2=0;
					while((ir2<RouterSize)&&(((CRouter*)(Routers[ir2]))->Caption!=caption))
						ir2++;
					if(ir2<RouterSize)
					{
						//if(ir2>ir)
						//{
						ar>>frequency;
						ar>>duplex;
						Link = new CLink(Router,(CRouter*)(Routers[ir2]),frequency,duplex);
						Link->Serialize(ar);
						//router->links.Add(link);
						//}
					}
					else
						AfxMessageBox("Error in CLink Object! There is no destination router!");
				}
				else
				{
					ar>>caption>>frequency>>duplex;
				}
			}
			int TrafficSize;
			ar>>TrafficSize;
			for(int it=0;it<TrafficSize;it++)
			{
				ar>>caption;
				int it2=0;
				while((it2<RouterSize)&&(((CRouter*)(Routers[it2]))->Caption!=caption))
					it2++;
				if(it2<RouterSize)
				{
					Traffic=new CTraffic(Router,(CRouter*)(Routers[it2]));
					Traffic->Serialize(ar);
					//no need for "router->traffics.Add(traffic);"
				}
				else
					AfxMessageBox("Error in CTraffic Object! There is no destination router!");
			}
		}
		((CMANETView*)pView)->UpdateWindow();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMANETDoc diagnostics

#ifdef _DEBUG
void CMANETDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMANETDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMANETDoc commands

