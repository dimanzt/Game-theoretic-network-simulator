// Path.h: interface for the CPath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATH_H__5C71AA7D_08DD_43E8_9DA0_2F4CBA5AD36B__INCLUDED_)
#define AFX_PATH_H__5C71AA7D_08DD_43E8_9DA0_2F4CBA5AD36B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////
#include "Packet.h"
/////////////////////////////

class CPath  :  public CObject
{
public:
	unsigned		SeqNum;					//Set by Packet
	BOOL			Update(CPacket* packet);//Update the path with current received packet
	unsigned		SizeCount;				//Count the number of paths to dest
	//unsigned 		Size;					//
	unsigned		TickNum;				//Number of Ticks to Destination
	unsigned		HopNum;					//Number of Hops to Destination
	CString			FirstHop;				//First Hop to Destination
	CStringArray	Intermediates;
//	CString			Destination;
//	CString			Source;
	CPath(CString firsthop="",unsigned ticknum=0,unsigned hopnum=0,unsigned size=0, unsigned seqnum=0);
	virtual ~CPath();

};

#endif // !defined(AFX_PATH_H__5C71AA7D_08DD_43E8_9DA0_2F4CBA5AD36B__INCLUDED_)
