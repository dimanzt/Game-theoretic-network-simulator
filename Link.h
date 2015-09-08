// Link.h: interface for the CLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINK_H__6C2873E4_C033_4DD3_940E_94F4BF170F49__INCLUDED_)
#define AFX_LINK_H__6C2873E4_C033_4DD3_940E_94F4BF170F49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////
#include "Router.h"
#include "Game.h"
/////////////////////////////

class CLink  : public CObject
{
	DECLARE_SERIAL(CLink);
public:
	int			AckCounter;		//Count the uploaded ack packets
	int			DataCounter;	//Count the uploaded data packets
	int			RRepCounter;	//Count the uploaded RReps
	int			RReqCounter;	//Count the uploaded RReqs
	int			packetsize;
	BOOL		Transmit(CRouter* router);
	CPacket*	Download(CRouter* router);
	BOOL		Upload(CPacket* p, CRouter* r);
	int			Distance2();
	int			Delay;
	int			Duplex;
	int			Frequency;	//No. of Pixels per Tick
	CObArray	p1s,p2s;	//Packets Uploaded from Router1,2
	CWordArray	pd1s,pd2s;	//Propagation Delays 1,2
	void		SerializeRouter(CArchive &ar, CRouter* mainrouter);
	BOOL		drawn;
	CPoint		start;
	CPoint		end;
	COLORREF	rgb;
	void		Draw(CDC *pDC);
	CPacket*	packet;
	CRouter*	Router2;
	CRouter*	Router1;
	CGame*		game;
	void		Serialize(CArchive& ar);
	CLink(CRouter* router1=NULL,CRouter* router2=NULL,int frequency=10,int duplex=0);
	virtual ~CLink();
};

#endif // !defined(AFX_LINK_H__6C2873E4_C033_4DD3_940E_94F4BF170F49__INCLUDED_)
