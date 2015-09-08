// Packet.h: interface for the CPacket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKET_H__E223F61F_A3A0_463C_A876_9215EB309CFA__INCLUDED_)
#define AFX_PACKET_H__E223F61F_A3A0_463C_A876_9215EB309CFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////
//#include "Router.h"
/////////////////////////////



class CPacket  :  public CObject
{
	DECLARE_SERIAL(CPacket);
public:
	unsigned		RouteDiscoveryDelay;
	unsigned		DataForwardingDelay;
	unsigned		TimeoutCounter;			//Countdown Timeout
	unsigned		Credit;					//Packet Credit
	unsigned		Timeout;				//Stop - Start = Timeout
	unsigned		Start,Stop;				//Start & Stop Clock = Length of Traveled Path
	BOOL			SendData;				//Can Data Be Sent?
	BOOL			TCR;					//Temporary Credit Request, will be 1 if request exists
	CStringArray	hops;					//Array of passed hops
	int				ChangePath;				//Set to change the current path
	CString			Uploader;				//Name of the Uploader
	unsigned		SizeCount;				//Counter of Path-Size
	unsigned		TickCount;				//Counter of Ticks
	unsigned		HopCount;				//Counter of Hops
	int				ID;						//Randomly Generated
	int				Type;					//0=RouteRequestPacket(Default) 1=RouteReplyPacket 2=DataPacket 3=AckPacket
	int				Protocol;				//0=ELMAR(Default) 1=AODV 2=DSR
	CString			Source;					//Generator of the Packet
	CString			Destination;			//Packet Receiver
	unsigned		SeqNum;					//Set by Router
	int				Expiration;				//-1=Never Expire(Default)
	int				TransmissionDelay;		//Delay of Transmission in Links
	int				ProcessDelay;			//Delay of Processing in Routers
	CPacket(int id=rand(),int type=0,int protocol=0,CString source="", CString destination="",unsigned seqnum=0,int expiration=-1, BOOL TCR=0);
	virtual ~CPacket();
};

#endif // !defined(AFX_PACKET_H__E223F61F_A3A0_463C_A876_9215EB309CFA__INCLUDED_)
