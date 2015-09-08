// Table.cpp: implementation of the CTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MANET.h"
#include "Table.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTable::CTable(CString destination)
{
	this->Destination=destination;
	//////////////////////////////
	this->Index=0; //this index specifies which path is the current path
	this->Round=0; //number of rounds that all path checked
	//this->SeqNum=0;	//Sequence Number of the destination
}

CTable::~CTable()
{

}

void CTable::SetPathByPacket(CPacket *p)
{
	path=new CPath(p->Uploader,p->TickCount,p->HopCount,p->SizeCount,p->SeqNum);
	Paths.Add(path);
}

void CTable::SetPath(CString uploader, unsigned tickcount,unsigned hopcount,unsigned sizecount)
{
	path=new CPath(uploader,tickcount,hopcount,sizecount);
	Paths.Add(path);
}

int CTable::ChangePath()//CPacket *p)
{
	if(PathSize=Paths.GetSize())
	{
		Index++;
		if(Index==(unsigned)Paths.GetSize())
		{
			Round++;
			Index=0;
		}
		return 1;
	}
	else
		return 0;
}
