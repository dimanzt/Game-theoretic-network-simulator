// Link.cpp: implementation of the CLink class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MANET.h"
#include "Link.h"

/////////////////////////////
#include <math.h>
/////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CLink,CObject,1);

CLink::CLink(CRouter* router1,CRouter* router2,int frequency,int duplex)
{
	RReqCounter=0;
	RRepCounter=0;
	DataCounter=0;
	AckCounter=0;
	Frequency=frequency;
	Duplex=duplex;
	if((router1!=NULL)&&(router2!=NULL))
	{
		this->Router1=router1;
		this->Router2=router2;
		Router1->Links.Add(this);
		Router1->Neighbors.Add((CRouter*)Router2);
		game=new CGame;
		Router1->Games.Add(game);//game of 1 with 2
		Router1->Credits.Add(30000); // Initialize neighbor credit by 10 ///modified for check
		Router1->TCRcounters.Add(0);
		Router2->Links.Add(this);
		Router2->Neighbors.Add((CRouter*)Router1);
		game=new CGame;
		Router2->Games.Add(game);//game of 2 with 1
		Router2->Credits.Add(30000); // Initialize neighbor credit by 10///modified for check
		Router2->TCRcounters.Add(0);
		/////////////////////////
		this->Delay=int(sqrtl(((Router1->X-Router2->X)*(Router1->X-Router2->X)+(Router1->Y-Router2->Y)*(Router1->Y-Router2->Y))))/Frequency;
		/////////////////////////
	}
}

CLink::~CLink()
{
	//remove the link from the router1
	if(Router1!=NULL)
	{
		for(int i1=0;i1<Router1->Links.GetSize();i1++)
			if( ((CLink*)(Router1->Links[i1]))==this )
			{
				Router1->Links.RemoveAt(i1);
	//remove the router2 as the neighbor of router1
//	for(i1=0;i1<Router1->neighbors.GetSize();i1++)
//		if( ((CRouter*)(Router1->neighbors[i1]))== Router2 )
				Router1->Neighbors.RemoveAt(i1);
				Router1->Credits.RemoveAt(i1);
				Router1->Games.RemoveAt(i1);
				//if( ((CGame*)(Router1->Games[i1]))!= NULL )
				//	delete ((CGame*)(Router1->Games[i1]));
			}
	}

	//remove the link from the router2
	if(Router2!=NULL)
	{
		for(int i2=0;i2<Router2->Links.GetSize();i2++)
			if( ((CLink*)(Router2->Links[i2]))==this )
			{
				Router2->Links.RemoveAt(i2);
	//remove the router1 as the neighbor of router2
//	for(i2=0;i2<Router2->neighbors.GetSize();i2++)
//		if( ((CRouter*)(Router2->neighbors[i2]))== Router1 )
				Router2->Neighbors.RemoveAt(i2);
				Router2->Credits.RemoveAt(i2);
				Router2->Games.RemoveAt(i2);
				//if( ((CGame*)(Router2->Games[i2]))!= NULL )
				//	delete ((CGame*)(Router2->Games[i2]));
			}
	}
}

void CLink::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
		//drawn=drawn?0:1;
		//if(drawn)
			//ar<</*Router1->Caption<<*/Router2->Caption<<Frequency<<Duplex;
		ar<<Router1->Caption<<Router2->Caption<<Frequency<<Duplex;
	}
	else
	{	// loading code
		//ar>>Router1->Caption>>Router2->Caption>>Frequency>>Duplex;
		//ar>>Frequency>>Duplex;
	}
}

void CLink::Draw(CDC *pDC)
{
	drawn=(drawn)?0:1;//change the drawn to 0 if it may be 1 and viceversa!
	int distance2=Distance2();
	if((distance2>(Router1->Coverage*Router1->Coverage))||(distance2>(Router2->Coverage*Router2->Coverage)))
		rgb=RGB(255,0,0);
//	else
//		rgb=RGB(0,0,0);
	CPen pen(PS_SOLID,1,rgb);
	pDC->SelectObject(&pen);
	start.x=(Router1->Rectangle.left+Router1->Rectangle.right)/2;
	start.y=(Router1->Rectangle.top+Router1->Rectangle.bottom)/2;
	end.x  =(Router2->Rectangle.left+Router2->Rectangle.right)/2;
	end.y  =(Router2->Rectangle.top+Router2->Rectangle.bottom)/2;
	pDC->MoveTo(start);
	pDC->LineTo(end  );
/////////////////////////////////////////////////
/*	CPen penGreen;
	penGreen.CreatePen(PS_SOLID | PS_COSMETIC, 1, RGB(0, 255, 0));
	pDC->SelectObject(&penGreen);
	packetsize=p1s.GetSize();
	for(int i=0;i<packetsize;i++)
	{
		CPoint center(pd1s[i]*(end.x-start.x)/Delay,pd1s[i]*(end.y-start.y)/Delay);
		pDC->Ellipse(center.x-5,center.y-5,center.x+5,center.y+5);
		//pDC->SetPixel(end.x-(Frequency*((CPacket*)(p1s[i]))->TransmissionDelay)*(end.x-start.x)/distance2,
		//				end.y-(Frequency*((CPacket*)(p1s[i]))->TransmissionDelay)*(end.y-start.y)/distance2,
		//				RGB(0,255,0));
	}
	packetsize=p2s.GetSize();
	for(    i=0;i<packetsize;i++)
	{
		CPoint center(pd2s[i]*(end.x-start.x)/Delay,pd2s[i]*(end.y-start.y)/Delay);
		pDC->Ellipse(center.x-5,center.y-5,center.x+5,center.y+5);
		//pDC->SetPixel(end.x-(Frequency*((CPacket*)(p2s[i]))->TransmissionDelay)*(end.x-start.x)/distance2,
		//				end.y-(Frequency*((CPacket*)(p2s[i]))->TransmissionDelay)*(end.y-start.y)/distance2,
		//				RGB(0,255,0));
	}*/
/////////////////////////////////////////////////
}

void CLink::SerializeRouter(CArchive &ar, CRouter *mainrouter)
{
	if(mainrouter==Router2)
	{
		mainrouter=Router1;
		Router1=Router2;
		Router2=mainrouter;
	}
	this->Serialize(ar);
}

int CLink::Distance2()
{
	return ((Router1->X-Router2->X)*(Router1->X-Router2->X)+(Router1->Y-Router2->Y)*(Router1->Y-Router2->Y));
}

BOOL CLink::Upload(CPacket *p, CRouter *r)
{
	if(p!=NULL)
	{
		if(p->Type==0)
		{
			RReqCounter++;
			rgb=RGB(0,0,255);
		}
		else if(p->Type==1)
		{
			RRepCounter++;
			rgb=RGB(255,255,0);
		}
		else if(p->Type==2)
		{
			DataCounter++;
			rgb=RGB(255,0,255);
		}
		else if(p->Type==3)
		{
			AckCounter++;
			rgb=RGB(0,255,0);
		}

		if(r==Router1)
		{
			//p->TransmissionDelay=INT(sqrt(Distance2()))/Frequency;
			//p->Uploader=r->Caption;
			//p->hops.Add(r->Caption);
			p1s.Add(p);
			pd1s.Add(-1);//Propagation Delay=0 cuz the Router2 (next end hop) increase it to 1!
			return 1;
		}
		else if(r==Router2)
		{
			//p->TransmissionDelay=INT(sqrt(Distance2()))/Frequency;
			//p->Uploader=r->Caption;
			//p->hops.Add(r->Caption);
			p2s.Add(p);
			pd2s.Add(0);//Propagation Delay=1 is the default!
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

CPacket* CLink::Download(CRouter *router)
{
	if(router==Router1)
	{
		if(p2s.GetSize())
		{
			if(Delay>pd2s[0])//((CPacket*)(p2s[0]))->TransmissionDelay)
				return NULL;
			else//Download the packet
			{
				packet=(CPacket*)(p2s[0]);
				p2s .RemoveAt(0);
				pd2s.RemoveAt(0);
				return packet;
			}
		}
		return NULL;
	}
	else if(router==Router2)
	{
		if(p1s.GetSize())
		{
			if(Delay>pd1s[0])//((CPacket*)(p1s[0]))->TransmissionDelay)
				return NULL;
			else//Download the packet
			{
				packet=(CPacket*)(p1s[0]);
				p1s .RemoveAt(0);
				pd1s.RemoveAt(0);
				return packet;
			}
		}
		else
			return NULL;
	}
	else
		return NULL;
}

BOOL CLink::Transmit(CRouter* router)
{
	if(router==Router1)
	{
		if(packetsize=p2s.GetSize())
		{
			for(int j=0;j<packetsize;j++)
			{
				(pd2s[j])++;
				//((CPacket*)(p2s[j]))->TransmissionDelay--;
			}
			return 1;
		}
		else
			return 0;
	}
	else if(router==Router2)
	{
		if(packetsize=p1s.GetSize())
		{
			for(int i=0;i<packetsize;i++)
			{
				(pd1s[i])++;
				//((CPacket*)(p1s[i]))->TransmissionDelay--;
			}
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}
