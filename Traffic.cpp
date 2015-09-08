// Traffic.cpp: implementation of the CTraffic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MANET.h"
#include "Traffic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CTraffic,CObject,1);


CTraffic::CTraffic(CRouter* source,CRouter* destination,int protocol,int start)
{
	this->Source=source;
	this->Destination=destination;
	this->Protocol=protocol;
	this->Start=start;
	source->Traffics.Add(this);
}

CTraffic::~CTraffic()
{

}

void CTraffic::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
		ar<<Destination->Caption<<Protocol<<Start;
	}
	else
	{	// loading code
		ar>>Protocol>>Start;//cuz Protocol and Caption has got in CDocument b4
	}
}
