// Path.cpp: implementation of the CPath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MANET.h"
#include "Path.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPath::CPath(CString firsthop,unsigned ticknum,unsigned hopnum,unsigned size,unsigned seqnum)
{
	///////////////////////////////////
	FirstHop			=firsthop;
	TickNum				=ticknum;
	HopNum				=hopnum;
	//Size				=size;
	///////////////////////////////////
	SizeCount			=size;
	SeqNum				=seqnum;
	///////////////////////////////////
}

CPath::~CPath()
{

}

BOOL CPath::Update(CPacket *packet)
{
	if(	//(FirstHop!=packet->Uploader)|| (HopNum!=packet->HopCount)  ||
		//(Size!=packet->SizeCount)   || (TickNum=packet->TickCount) ||
		(SeqNum<packet->SeqNum))
	{
		FirstHop=packet->Uploader;
		HopNum=packet->HopCount;
		SizeCount=packet->SizeCount;
		TickNum=packet->TickCount;
		//SizeCount=Size;
		SeqNum=packet->SeqNum;
		return 1;
	}
	else
		return 0;
}
