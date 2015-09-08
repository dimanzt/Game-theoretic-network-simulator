// Table.h: interface for the CTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLE_H__796C0E7B_E997_4B87_8639_1DAD8BEAC740__INCLUDED_)
#define AFX_TABLE_H__796C0E7B_E997_4B87_8639_1DAD8BEAC740__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////
#include "Path.h"
#include "Packet.h"
/////////////////////////////


class CTable  :  public CObject
{
public:
	//unsigned		SeqNum;
	unsigned		PathSize;
	int				ChangePath();
	unsigned		Round;
	int				Index;
	void			SetPath(CString uploader, unsigned tickcount,unsigned hopcount,unsigned sizecount);
	void			SetPathByPacket(CPacket* p);
	CObArray		Paths;
	CPath*			path;
	CString			Destination;
	CString			Source; //it's vuluntary
	CTable(CString destination="");
	virtual ~CTable();

};

#endif // !defined(AFX_TABLE_H__796C0E7B_E997_4B87_8639_1DAD8BEAC740__INCLUDED_)
