// Packet.cpp: implementation of the CPacket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MANET.h"
#include "Packet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CPacket,CObject,1);

CPacket::CPacket(int id,int type,int protocol,CString source, CString destination,unsigned seqnum,int expiration, BOOL TCR)
{
	/////////////////////////////////////////////
	this->ID				=id;
	this->Type				=type;
	this->Credit			=(Type==2)?200:100;
	this->Protocol			=protocol;
	this->Source			=source;
	this->Destination		=destination;
	this->SeqNum			=seqnum;
	this->Expiration		=expiration;
	this->TCR				=0;
	/////////////////////////////////////////////
	this->ProcessDelay		=0;
	this->TransmissionDelay	=0;
	this->HopCount			=0;
	this->TickCount			=0;
	this->Uploader			="";
	this->ChangePath		=0;
	this->SizeCount			=1;//eigen of multiply
	this->SendData			=FALSE;
	this->RouteDiscoveryDelay=0;
	this->DataForwardingDelay=0;
	this->TimeoutCounter=0;			//Countdown Timeout
	this->Credit=0;					//Packet Credit
	this->Timeout=0;				//Stop - Start = Timeout
	this->Start=0;
	this->Stop=0;		
	/////////////////////////////////////////////
}

CPacket::~CPacket()
{

}
