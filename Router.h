#if !defined(AFX_ROUTER_H__7A353D96_8609_4E9A_85CB_BAD85DD12104__INCLUDED_)
#define AFX_ROUTER_H__7A353D96_8609_4E9A_85CB_BAD85DD12104__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Router.h : header file
//

///////////////////////////////////////
//#include "RouterDialog.h"
//#include "Link.h"
//#include "Traffic.h"
//#include "RouterDialog.h"
//#include "Link.h"
//#include "Traffic.h"
#include "Packet.h"
#include "Table.h"
#include "Game.h"
///////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CRouter window

class CRouter : public CButton
{
// Construction
public:
	CRouter(CString Name="",int X_axis=0,int Y_axis=0,int Rect_Length=10, int Rect_Width=10, int COVERAGE=100,int DELAY=1,int Buffer_Size=10,CString Image_Path="",int type=0);
	virtual	~CRouter();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRouter)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	//int				pre_Type; //DIMAN
	int				Game_Strategy;
	int				ReturnValue;
	int				EstablishedConnectionsCounter;
	int				DataTransCounter;
	int				AckTransCounter;
	int				RReqTransCounter;
	int				RRepTransCounter;
	int				GenDataCounter;
	int				GenAckCounter;
	int				GenSelfishAckCounter;
	int				GenSelDataCounter;
	int				GenRReqCounter;
	int				GenRRepCounter;
	int				Type;//0=Ad-hoc, 1=Selfish1, 2=Selfish2, 3=Selfish3;
	CPoint			Start;
	CPoint			End;
	COLORREF		RGB;
//	unsigned		Start,Stop;
	unsigned		Clock;
//	CPacket*		AckPacket;
//	CPacket*		DataPacket;
//	clock_t			start,finish;
//	int				TimeOut;
	inline int		GetNextHop(CPacket* packet,CTable* table);
	inline int		GetNextBenignHop(CPacket* packet,CTable *table);
	inline void		GetTableIndexToSourceAndDest(CPacket* packet,int* s,int* d);
	inline int		GetTableIndexToSource(CPacket* packet);
	inline int		GetTableIndexToDest(CPacket* packet);
	void			ProcessAckPacket2 (CPacket* packet);
	void			ProcessAckPacket1 (CPacket* packet);
	void			ProcessAckPacket0 (CPacket* packet);
	void			ProcessAckPacket  (CPacket* packet);
	void			ProcessRRepPacket2(CPacket* packet);
	void			ProcessRRepPacket1(CPacket* packet);
	void			ProcessRRepPacket0(CPacket* packet);
	void			ProcessRRepPacket (CPacket* packet);
	void			ProcessRReqPacket2(CPacket* packet);
	void			ProcessRReqPacket1(CPacket* RReqPacket);
	void			ProcessRReqPacket0(CPacket* packet);
	void			ProcessRReqPacket (CPacket* packet);
	void			ProcessDataPacket2(CPacket* packet);
	void			ProcessDataPacket1(CPacket* packet);
	void			ProcessDataPacket0(CPacket* packet);
	virtual void	ProcessDataPacket (CPacket* packet);
	BOOL			SendData;
	BYTE			IsProcessed(CRouter* neighbor, CPacket* packet);
//	BYTE			IsBroadcast(CPacket* packet);
	int				ProcessDelay;
	void			Process();
	void			SparkTraffic();
	int				GetProcessDelay(CPacket* packet);
	int				HelloPeriod;
	int				LinkSize;
	int				NeighborSize;
	int				DataPacketSize;
	int				ProcessedPacketSize;
	int				GenRReqPacketSize;
	int				ReceivedPacketSize;
	int				PathSize;
	int				TrafficSize;
	int				TableSize;
	void			tick();
	void			Receive();
	void			ProcessCredit();
	void			ProcessTimers();
	void			Broadcast(CPacket* packet);
	unsigned		DataSeqNum;	//Data  Packet  Sequence Number
	unsigned		RReqSeqNum;	//Route Request Sequence Number
	unsigned		RRepSeqNum;	//Route Reply   Sequence Number
	int				DataExp;	//Data  Packet  Expiration
	int				RReqExp;	//Route Request Expiration
	int				RRepExp;	//Route Reply   Expiration
	CPacket*		GenAckPacket	(CPacket* packet);
	CPacket*		GenDataPacket	(CPacket* packet);
	CPacket*		GenRRep			(CPacket* packet);
	CPacket*		GenRReq			(int protocol, CRouter* destination);
	CRouter*		Neighbor;				//CRouter Pointer
	CPacket*		Packet;					//CPacket Pointer, Auxiliary Variable
	CPacket*		DataPacket;
	CTable*			Table;					//CTable Pointer
//	CLink*			link;
//	CTraffic*		traffic;
	BOOL			Moved;
	BOOL			Created;
	BOOL			TCR;
	int				Power;
	int				BufferSize;
	int				Delay;
	int				Coverage;
	int				RectLength;
	int				RectWidth;
	int				Y;
	int				X;
	int				TCRcredit;
///	int				GenSelDataCounter;
	POINT			LeftCurrentPosition;	//Current  Mouse Left -Button Click Position
	POINT			LeftPreviousPosition;	//Previous Mouse Left -Button Click Position
	POINT			RightCurrentPosition;	//Current  Mouse Right-Button Click Position
	POINT			RightPreviousPosition;	//Previous Mouse Right-Button Click Position
	RECT			Rectangle;				//location relative to top-left corner of router
	CString			ImagePath;				//Image Path of Router
	CString			Caption;				//Name of the Router
	BYTE			PacketRepetition;
	CString			PacketUploader;
	//////////////////////////////////////////
	CWordArray		Timers;					//Timers of sent packets 0-RTT*3
	CByteArray		NextHops;				//storing next hop for each forwarded packet in queue to monitor neighbor forwarding attitude
	CObArray		OutQueue;				//storing forwarded packets to see if they are forwarded by next hop
	//////////////////////////////////////////
	CStringArray	Connections;			//Routers that could be connected!
	CObArray		Tables;					//Array of Tables
	//////////////////////////////////////////
	CObArray		Links;					//Array of Links
	CObArray		Neighbors;				//Array of Neighbors
	CWordArray		Credits;				//Credits of neighbors 0-100
	CWordArray		TCRcounters;			//TCR counters of neighbors 0-100
	CObArray		Games;					//Array of Neighbor's Games
	//////////////////////////////////////////
	CObArray		DataPackets;			//Array of Data Packets
	CObArray		ProcessedPackets;		//Array of Processed Packets
	//////////////////////////////////////////
	//Isotope Arrays
	CStringArray	PacketUploaders;		//Array of Packets' Uploders
	CWordArray		UploadersIndexes;		//Indexes of uploaders ~ packetuploaders
	CObArray		ProcessedNeighbors;		//Array of Neighbors that their Packets Processed!
	CByteArray		PacketRepetitions;		//Array of Packets Repetition Type
	CObArray		ReceivedPackets;		//Array of Received Packets
	//////////////////////////////////////////
//	CObArray		GeneratedPackets;		//Array of Self-Generated Packets
	CObArray		GenRReqPackets;
	CObArray		GenRRepPackets;
	CObArray		GenDataPackets;
	CObArray		GenAckPackets;
	//////////////////////////////////////////
	CObArray		Traffics;				//Array of Traffics
	void			UpdateRect();			//Update the Rectangle of Router
	void			XY2RECT(long x,long y);	//Convert (X,Y) to RECTANGLE of Router
	void			RECT2XY(RECT rectangle);//Convert RECTANGLE of Router to (X,Y)
	void			Update(CString Name,int X_axis,int Y_axis,int Rect_Length,int Rect_Width,int COVERAGE,int DELAY,int Buffer_Size,CString Image_Path,int type);

	// Generated message map functions
protected:
	//{{AFX_MSG(CRouter)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClicked();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	void SetGames(int strategy);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROUTER_H__7A353D96_8609_4E9A_85CB_BAD85DD12104__INCLUDED_)
