// Router.cpp : implementation file
//
#include "stdafx.h"
#include "MANET.h"

#include "Router.h"

/////////////////////////////
#include "RouterDialog.h"
#include "Link.h"
#include "Traffic.h"
#include "Packet.h"
/////////////////////////////

/////////////////////////////
#include <math.h>
/////////////////////////////


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CRouter

//Selfishness Bound
#define MAX_POWER 200000 //2000000000
#define MIN1_POWER MAX_POWER/4 //1000
#define MIN2_POWER MAX_POWER/2//2000
#define TimeOutFactor 3


CRouter::CRouter(CString Name,int X_axis,int Y_axis,int Rect_Length,int Rect_Width,int COVERAGE,int DELAY,int Buffer_Size,CString Image_Path,int type)
{
	this->Caption			=Name;
	this->X					=X_axis;
	this->Y					=Y_axis;
	this->RectLength		=Rect_Length;
	this->RectWidth			=Rect_Width;
	this->Rectangle.top		=Y;
	this->Rectangle.bottom	=Y+RectLength;
	this->Rectangle.left	=X;
	this->Rectangle.right	=X+RectWidth;
	this->Coverage			=COVERAGE;
	this->Delay				=DELAY;
	this->BufferSize		=Buffer_Size;
	this->ImagePath			=Image_Path;
	this->Type				=0;//0=Adhoc
	///////////////////////////////////
	this->Created			=0;//not created
	this->RReqSeqNum		=0;
	this->TCR				=0;
	this->RRepSeqNum		=0;
	this->DataSeqNum		=0;
	this->RReqExp			=-1;
	this->RRepExp			=-1;
	this->DataExp			=-1;
	this->ProcessDelay		=-1;//it means infinite!
	this->SendData			=FALSE;
	this->Clock				=0;
	this->HelloPeriod		=100;
	this->TCRcredit			=500;
	this->GenDataCounter	=0;
	this->GenAckCounter		=0;
	this->GenSelDataCounter =0;
	this->GenSelfishAckCounter=0;
	this->GenRReqCounter	=0;
	this->GenRRepCounter	=0;
	this->EstablishedConnectionsCounter=0;
	DataTransCounter		=0;
	AckTransCounter			=0;
	RReqTransCounter		=0;
	RRepTransCounter		=0;
	//PacketUploaders.Add("");
	Power					=MAX_POWER;
	Game_Strategy			=1;
	//pre_Type				=0; //Shows what was previous type of router? if selfish3
	///////////////////////////////////
}

CRouter::~CRouter()
{
	int rreqp;
	for(rreqp=0;rreqp<GenRReqPackets.GetSize();rreqp++)
		if( ((CPacket*)(GenRReqPackets[rreqp]))!=NULL )
			delete ((CPacket*)(GenRReqPackets[rreqp]));
	GenRReqPackets.RemoveAll();

	int rrepp;
	for(rrepp=0;rrepp<GenRRepPackets.GetSize();rrepp++)
		if( ((CPacket*)(GenRRepPackets[rrepp]))!=NULL )
			delete ((CPacket*)(GenRRepPackets[rrepp]));
	GenRRepPackets.RemoveAll();

	int datap;
	for(datap=0;datap<GenDataPackets.GetSize();datap++)
		if( ((CPacket*)(GenDataPackets[datap]))!=NULL )
			delete ((CPacket*)(GenDataPackets[datap]));
	GenDataPackets.RemoveAll();

	int ackp;
	for(ackp=0;ackp<GenAckPackets.GetSize();ackp++)
		if( ((CPacket*)(GenAckPackets[ackp]))!=NULL )
			delete ((CPacket*)(GenAckPackets[ackp]));
	GenAckPackets.RemoveAll();

	int il;
	for(il=0;il<Links.GetSize();il++)
		if( ((CLink*)(Links[il]))!=NULL )
			delete ((CLink*)(Links[il]));
	Links.RemoveAll();

	int it;
	for(it=0;it<Traffics.GetSize();it++)
		if( ((CTraffic*)(Traffics[it]))!=NULL )
			delete ((CTraffic*)(Traffics[it]));
	Traffics.RemoveAll();

	int ig;
	for(ig=0;ig<Games.GetSize();ig++)
		if( ((CGame*)(Games[ig]))!=NULL )
			delete ((CGame*)(Games[ig]));
	Games.RemoveAll();
}


BEGIN_MESSAGE_MAP(CRouter, CButton)
	//{{AFX_MSG_MAP(CRouter)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRouter message handlers

void CRouter::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	Moved=0;
	LeftPreviousPosition=point;
	CButton::OnLButtonDown(nFlags, point);
}

void CRouter::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(GetCapture()==this)
	{
		ReleaseCapture();
		if(Moved)
		{
			int dx=point.x-LeftPreviousPosition.x;
			int dy=point.y-LeftPreviousPosition.y;
			Rectangle.bottom+=dy;
 			Rectangle.top+=dy;
 			Rectangle.left+=dx;
			Rectangle.right+=dx;
			this->RECT2XY(Rectangle);
 			MoveWindow(&Rectangle);	
			GetParent()->Invalidate();
		}
		else
		{
			this->OnClicked();
			//CRouterDialog rd;
			//rd.GetRouterData(this);
			//if(rd.DoModal()==IDOK)
			//rd.PushRouterData(this);
		}
	}
	CButton::OnLButtonUp(nFlags, point);
}

void CRouter::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if((GetCapture()==this)&&(nFlags==MK_LBUTTON))
	{
		Moved=1;
		int dx=point.x-LeftPreviousPosition.x;
		int dy=point.y-LeftPreviousPosition.y;
		Rectangle.bottom+=dy;
		Rectangle.top+=dy;
		Rectangle.left+=dx;
		Rectangle.right+=dx; 			
		this->RECT2XY(Rectangle);
		MoveWindow(&Rectangle);
		//GetParent()->Invalidate();
	}
	CButton::OnMouseMove(nFlags, point);
}


void CRouter::OnClicked() 
{
	// TODO: Add your control notification handler code here
	CRouterDialog rd;
	rd.GetRouterData(this);
	if(rd.DoModal()==IDOK)
	{
		rd.PushRouterData(this);
		//HINSTANCE hinst;
		//if(this->Type==1)
		//	this->SetBitmap(::LoadBitmap(NULL/*hinst*/, MAKEINTRESOURCE(IDB_Selfish1)));//OBM_CLOSE)));
	}
}

void CRouter::Update(CString Name,int X_axis,int Y_axis,int Rect_Length,int Rect_Width,int COVERAGE,int DELAY,int Buffer_Size,CString Image_Path,int type)
{
	this->Caption			=Name;
	this->X					=X_axis;
	this->Y					=Y_axis;
	this->RectLength		=Rect_Length;
	this->RectWidth			=Rect_Width;
	this->Rectangle.top		=Y;
	this->Rectangle.bottom	=Y+RectLength;
	this->Rectangle.left	=X;
	this->Rectangle.right	=X+RectWidth;
	this->Coverage			=COVERAGE;
	this->Delay				=DELAY;
	this->BufferSize		=Buffer_Size;
	this->ImagePath			=Image_Path;
	this->Type				=type;
}

void CRouter::RECT2XY(RECT rectangle)
{
	this->X			=rectangle.left;
	this->Y			=rectangle.top;
	this->RectLength=rectangle.bottom-Y;
	this->RectWidth	=rectangle.right-X;
}

void CRouter::XY2RECT(long x,long y)
{
	this->Y					=y;
	this->X					=x;
	this->Rectangle.top		=y;
	this->Rectangle.left	=x;
	this->Rectangle.bottom	=Y+RectLength;
	this->Rectangle.right	=X+RectWidth;
}

void CRouter::UpdateRect()
{
	this->Rectangle.top		=Y;
	this->Rectangle.left	=X;
	this->Rectangle.bottom	=Y+RectLength;
	this->Rectangle.right	=X+RectWidth;	
}

void CRouter::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{	// storing code
		ar<<Caption<<Type<<Rectangle<<Coverage<<Delay<<BufferSize<<ImagePath;
		//for(int i=0;i<links.GetSize();i++)
		//	((CLink*)(links[i]))->Serialize(ar);
	}
	else
	{	// loading code
		ar>>Caption>>Type>>Rectangle>>Coverage>>Delay>>BufferSize>>ImagePath;
		this->RECT2XY(Rectangle);
	}
}

void CRouter::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//CMANETView* pParent=
	//	this->GetParent()->OnRButtonDown(nFlags,point);
	//pParent->PreviousRouter=this;
	CButton::OnRButtonDown(nFlags, point);
}

void CRouter::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CButton::OnRButtonUp(nFlags, point);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

CPacket* CRouter::GenRReq(int protocol, CRouter *destination)//CTraffic* tr)
{
	Packet=new CPacket(rand(),0/*type=RReq*/,protocol,Caption,destination->Caption,++RReqSeqNum,RReqExp,TCR);
	return Packet;
}

CPacket* CRouter::GenRRep(CPacket* packet)//int protocol, CRouter *source, CRouter *destination)
{
	Packet=new CPacket(packet->ID,1/*type=RRep*/,packet->Protocol,Caption,packet->Source,++RRepSeqNum,RRepExp);
	return Packet;
}

CPacket* CRouter::GenDataPacket(CPacket *packet)
{
	Packet=new CPacket(packet->ID,2/*type=Data*/,packet->Protocol,Caption,packet->Source,++DataSeqNum,DataExp);
	return Packet;
}

CPacket* CRouter::GenAckPacket(CPacket* packet)
{
	Packet=new CPacket(packet->ID,3/*type=Ack*/,packet->Protocol,packet->Destination,packet->Source,packet->SeqNum,packet->Expiration);
	return Packet;
}

void CRouter::Broadcast(CPacket* packet)
{
	if(LinkSize=Links.GetSize())
	{
		int uis=UploadersIndexes.GetSize();
		if((Caption==packet->Source)||(Caption==packet->Destination))
		{
			for(int i=0;i<LinkSize;i++)
			{
				((CLink*)(Links[i]))->Upload(packet,this);
				packet->HopCount++;
				//DIMAN
				if(Power>0)Power-=4;
				if(packet->Type)
					RRepTransCounter++;
				else
					RReqTransCounter++;
			}
		}
		else if(uis>0)
		{
			for(int i=0;i<LinkSize;i++)
			{
				if(i!=UploadersIndexes[0])
				{
					((CLink*)(Links[i]))->Upload(packet,this);
					packet->HopCount++;
					if(Power>0)Power-=4;
					if(packet->Type)
						RRepTransCounter++;
					else
						RReqTransCounter++;
				}
			}
		}
	}				
}

void CRouter::ProcessCredit()
{
	if(LinkSize=Links.GetSize())
		for(int i=0;i<LinkSize;i++)
			///if(!(Clock%HelloPeriod))
				///credits[i]+=70;
			///	credits[i]+=HelloPeriod/2;
			//else 
			if (Credits[i]!=0)
				Credits[i]--;

}

void CRouter::ProcessTimers()
{
	int OutQueueSize=OutQueue.GetSize();
	int i=0;
	//for(int i=0;i<queueoutsize;i++)
	while(i<OutQueueSize)
	{
		if(Timers[i]!=0)
		{
			Timers[i]--;
			if (Timers[i]==0)
			{ //find the next hop to which packet was given
				//////////////////////////
				Credits[NextHops[i]]=0; //and remove its credit
				((CGame*)(Games[NextHops[i]]))->AddneighborAction(0); //NextHops[i] = Neighbor who discarded our packet
				//////////////////////////
				OutQueue.RemoveAt(i);
				Timers.RemoveAt(i);
				NextHops.RemoveAt(i);
				OutQueueSize--;
				//////////////////////////
			}
		}
		i++;
	}
}

void CRouter::Receive()
{
	if(LinkSize=Links.GetSize())
		for(int l=0;l<LinkSize;l++)
			if(((CLink*)(Links[l]))->Transmit(this))
				if(((Packet=((CLink*)(Links[l]))->Download(this))!=NULL)
					&&((Packet->Destination==this->Caption)||(this->Type!=1)))
				{
					//DIMAN

						//Power Management to be selfish!
						if(Power<MIN1_POWER)
						{
							this->Type=1;//Selfish1
						}
						else if(Power<MIN2_POWER)
						{
							this->Type=2;//Selfish2
						}
						//else if(Power<0)
						//	Power=MAX_POWER;

						///if (credits[l]!= 0) //ignore the packet if sender has no credit
						///{
						///GiveCredit() if neighbor forward packet
					
					int q=0;
					int OutQueueSize=0;
					if (Packet->Type==2) //for data packets
					{
						if(Power>0)Power-=10;//DIMAN// ghablan 4 bood man data ro 10 barabare RREQ gereftam
						OutQueueSize=OutQueue.GetSize();
						while((q<OutQueueSize)&&(Packet!=(CPacket*)(OutQueue[q])))
							q++;
						if(q<OutQueueSize)
						{
							if (Timers[q]!=0)
							{
								((CGame*)(Games[l]))->AddneighborAction(1); //Forwarding Data = Receiving Confirmation
								Credits[l]+=Packet->Credit; //"l" is index of the uploader
								Timers.RemoveAt(q);			//give credit and empty the queueout of that packet
								OutQueue.RemoveAt(q);
								NextHops.RemoveAt(q);
							}
						}
					}
					else //for control packets
					{
						if(Power>0)Power--;
						if ( Packet->Source != (((CRouter*)(Neighbors[l]))->Caption) )  //if sender is not the packet source
							Credits[l]+=Packet->Credit;			//give credit
						if ( (Credits[l]==0) && (Packet->Type==0) && (TCRcounters[l]!=0) && (Packet->Uploader==Packet->Source) )
						///if ( (credits[l]==0) && (TCRcounters[l]!=0)) ///&& (Packet->Uploader==Packet->Source) )
							{
								TCRcounters[l]--;
								Credits[1]+=TCRcredit;
							}
					}
					/////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////
					///////////We can add here GAME theoretic decisions//////////////////
					/////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////
					//int action;
					if( (((CGame*)(Games[l]))->main_strategy()) == 1) //Forward
					//if ((Credits[l]!= 0))///||(Packet->Type==3)) //ignore the packet if sender has no credit
					{											//forward ack packets anyway!
						((CGame*)(Games[l]))->AddmyAction(1);
						if(q==OutQueueSize)//not for credit
						{
							if(PacketRepetition=IsProcessed((CRouter*)(Neighbors[l]),Packet))
								//Already Processed? if yes,do nothing
							{
								if(ProcessedPackets.GetSize()>20000)
								{// Also ProcessedNeighbors.GetSize()>20000
									int pps;
									for(pps=0;pps<10000;pps++)
									{
										ProcessedPackets.RemoveAt(0);
										ProcessedNeighbors.RemoveAt(0);
									}
								}
								ProcessedPackets.Add(Packet);	//processedpackets ~ processedneighbors
								ProcessedNeighbors.Add((CRouter*)(Neighbors[l]));
								/////////////////////////
								PacketUploaders.Add(((CRouter*)(Neighbors[l]))->Caption);
								UploadersIndexes.Add(l);
								PacketRepetitions.Add(PacketRepetition);
								if(!ReceivedPackets.Add((CPacket*)Packet))//if Packet is not the first
									ProcessDelay=GetProcessDelay(Packet);
								//ReceivePackets ~ packetrepetitions ~ PacketUploaders ~ uploaderindexes
								/////////////////////////
								GetParent()->Invalidate();
								/////////////////////////
							}
							else
							{
								//if(Packet->Type==2)
								//{//Source must delete the path		
								//}
							}
						}
					}
					else
						((CGame*)(Games[l]))->AddmyAction(0);
				}
}

BYTE CRouter::IsProcessed(CRouter* neighbor, CPacket* packet)
{//0=own packet or same packet same neighbor, 1=same packet, 2=new packet
	if(packet->Source!=Caption) //if we didnt originate the packet
	{
		if(ProcessedPacketSize=ProcessedPackets.GetSize()) //if there is any processedpacket
		{												   //look up the processed packets to see if 
														   //the received one was processed before
			int ppc=0;
			ReturnValue=2;//Default=new packet
			//int SamePacketCounter=0;
			while(	(ppc<ProcessedPacketSize) &&
					((packet!=(CPacket*)(ProcessedPackets[ppc])) ||
					(neighbor!=(CRouter*)(ProcessedNeighbors[ppc]))) )//same packet and same neighbor?
			{
				if(packet==(CPacket*)(ProcessedPackets[ppc]))
					ReturnValue=1; //same packet
					//SamePacketCounter++;
				ppc++;
			}
			if(ppc<ProcessedPacketSize) //if received packet was found in previously processed ones
			{//same packet from the same neighbor
				if(packet->Type<2)	//rreq or rrep -> not a data or ack packet
					return 0;//same packet same neighbor
				else
				{// data or ack packet
					int sti=GetTableIndexToSource(packet);
					if((sti!=-1)&&(PathSize=((CTable*)(Tables[sti]))->Paths.GetSize()))
					{//Get the Destine-Table Matched With Packet!
						int psc=0;
						while((psc<PathSize)&&(((CPath*)(((CTable*)(Tables[sti]))->Paths[psc]))->FirstHop!=neighbor->Caption))
							psc++;
						if(psc<PathSize)//Get the FirstHop Matched
						{
							if(packet->SeqNum>((CPath*)(((CTable*)(Tables[sti]))->Paths[psc]))->SeqNum)
								return 1;//same packet same neighbor BUT new SeqNum
							else
								return 0;//same packet same neighbor OLD SeqNum
						}
						else
							return 2;//no path to neighbor to reach the source
					}
					else
						return 2;//no table to the source of data or ack packet
				}
			}
			else
				return ReturnValue;	//new packet || same packet but not from the same neighbor

//			if(ReceivedPacketSize=ReceivedPackets.GetSize())	//search previously received packets
//			{
//				int rpc=0;
//				while((rpc<ReceivedPacketSize)&&(packet!=(CPacket*)(ReceivedPackets[rpc])))
//					rpc++;
//				if(rpc<ReceivedPacketSize)		//packet received before
//				{
//					if(neighbor->Caption==PacketUploaders[rpc])
//						return 0;			//same neighbor,same packet,received before
//					else
//						return 1;			//received before but from another neighbor
//				}
//			}

		}
		else
			return 2;//new packet, not originated by us
	}
	else
		return 3;//own packet
}

int CRouter::GetProcessDelay(CPacket* packet)
{
	if(packet->Type==0)			//Route Request Packet *3
	{
		return 3*Delay;
	}
	else if(packet->Type==1)	//Route Reply Packet *3
	{
		return 3*Delay;
	}
	else if(packet->Type==2)	//Data Packet *1
	{
		return Delay;
	}
	else if(packet->Type==3)	//Ack Packet *1
	{
		return Delay;
	}
	else
		return 0;
}

void CRouter::SparkTraffic()
{
	if(TrafficSize=Traffics.GetSize())
	{
		int t=0;
		while(t<TrafficSize)
		{
			if( ((CTraffic*)(Traffics[t]))->Start )
			{
				((CTraffic*)(Traffics[t]))->Start--;
				t++;
			}
			else
			{
				Packet=GenRReq(((CTraffic*)(Traffics[t]))->Protocol,((CTraffic*)(Traffics[t]))->Destination);
				GenRReqPackets.Add((CPacket*)Packet);
				Packet->Start=Clock;					//Save current clock of router
				Broadcast(Packet);
				delete ((CTraffic*)(Traffics[t]));		//traffic ->cntrl packets.that's why we delete them
				Traffics.RemoveAt(t);
				TrafficSize--;
			}
		}
	}
	if(DataPacketSize=DataPackets.GetSize())
	{
		int dpsc=0;
		while((dpsc<DataPacketSize)&&(((CPacket*)(DataPackets[dpsc]))->SendData))
		{
			DataPacket=(CPacket*)(DataPackets[dpsc]);
			if(!(DataPacket->TimeoutCounter--))
			{//When datapacket times out
				DataPacket->TimeoutCounter = DataPacket->Timeout;
				int sti=GetTableIndexToDest(DataPacket);
				if(sti!=-1)
				{
					//DataPacket->ChangePath=TRUE;
					//int n=GetNextHop(datapacket,(CTable*)(Tables[sti]));
					int n=GetNextBenignHop(DataPacket,(CTable*)(Tables[sti]));
					if(n!=-1)
					{
						DataPacket->SeqNum++;
						((CLink*)(Links[n]))->Upload(DataPacket,this);
						DataPacket->HopCount++;
						if(Power>0)Power-=40;//DIMAN// ghablan 16 bood man data ro 10 barabare RREQ gereftam
						if (this->Type==0)
							GenDataCounter++;
						else
							GenSelDataCounter++;
						if(DataPacket->Destination!=((CRouter*)(Neighbors[n]))->Caption)
						{
							OutQueue.Add((CPacket*)DataPacket);
							Timers.Add(4*((CLink*)(Links[n]))->Delay); //modified/
							NextHops.Add(n);
						}
					}
					else
					{
						DataPacket->Stop=Clock;
						DataPacket->SendData=FALSE;
						//EstablishedConnectionsCounter++;
						//DeadLock Zone
						//no benign neighbor to destination
					}
				}
			}
			dpsc++;
		}
	}
}

void CRouter::tick()
{
	if(Power>0)
	{
		Receive();//Receive Packets
		Process();//Process Packets
	///	ProcessCredit(); //Update Credits as time goes by
		ProcessTimers(); //Update Timers as time goes by
		SparkTraffic();//Spark Traffics
	}
	Clock++;
}


void CRouter::Process()
{
	if(ReceivedPackets.GetSize())
	{
		if(ProcessDelay)
			ProcessDelay--;//decrease ProcessDelay until it reaches ZERO
		else //ProcessDelay==0
		{
			Packet=(CPacket*)(ReceivedPackets[0]);		//Get Current Packet To Be To Process

			if(Packet->Type==0)							//Route Request Packet Processing
			{
				ProcessRReqPacket(Packet);
				//processedpackets.Add(Packet);			//Add Current Packet to processedpackets Array
			}
			else if(Packet->Type==1)					//Route Reply Packet Processing
			{
				ProcessRRepPacket(Packet);
				//processedpackets.Add(Packet);			//Add Current Packet to processedpackets Array
			}
			else if(Packet->Type==2)					//Data Packet Processing
			{
				ProcessDataPacket(Packet);
				//processedpackets.Add(Packet);			//Add Current Packet to processedpackets Array
			}
			else if(Packet->Type==3)					//Ack Packet Processing
			{
				ProcessAckPacket(Packet);
				//processedpackets.Add(Packet);
			}
			else
			{
				//ProcessAnyPacket(Packet);
				//processedpackets.Add(Packet);
			}
			/////////////////Last Modifications////////////////////////////////
			ReceivedPackets.RemoveAt(0);				//Remove Current Packet from packets Array
			PacketUploaders.RemoveAt(0);				//Remove Current Packet-Uploader from PacketUploaders Array
			UploadersIndexes.RemoveAt(0);
			PacketRepetitions.RemoveAt(0);				//Remove Current Packet Repetition Type
			if(ReceivedPackets.GetSize())				//Set Next Process Delay
				ProcessDelay=((CPacket*)(ReceivedPackets[0]))->ProcessDelay;
			else
				ProcessDelay=-1;						//infinite
			///////////////////////////////////////////////////////////////////
		}
	}
}

void CRouter::ProcessRReqPacket(CPacket* packet)
{
	if(packet->Protocol==0)
		ProcessRReqPacket0(packet);
	else if(packet->Protocol==1)
		ProcessRReqPacket1(packet);
	else if(packet->Protocol==2)
		ProcessRReqPacket2(packet);
}

void CRouter::ProcessRRepPacket(CPacket* packet)
{
	if(packet->Protocol==0)
		ProcessRRepPacket0(packet);
	else if(packet->Protocol==1)
		ProcessRRepPacket1(packet);
	else if(packet->Protocol==2)
		ProcessRRepPacket2(packet);
}

void CRouter::ProcessDataPacket(CPacket* packet)
{
	if((!this->Type)||(packet->Destination==Caption))
	{//Router Type == Ad-hoc
		if(packet->Protocol==0)
			ProcessDataPacket0(packet);
		else if(packet->Protocol==1)
			ProcessDataPacket1(packet);
		else if(packet->Protocol==2)
			ProcessDataPacket2(packet);
	}
}

void CRouter::ProcessAckPacket(CPacket* packet)
{
	if((this->Type!=1)||(packet->Destination==Caption))
	{
		if(packet->Protocol==0)
			ProcessAckPacket0(packet);
		else if(packet->Protocol==1)
			ProcessAckPacket1(packet);
		else if(packet->Protocol==2)
			ProcessAckPacket2(packet);
	}
}

/*BYTE CRouter::IsBroadcast(CPacket* packet)
{
	if(packet->Source!=Caption)
	{
		if(processedpacketsize=processedpackets.GetSize())
		{
			int ppc=0;
			while((ppc<processedpacketsize)&&(packet!=(CPacket*)(processedpackets[ppc])))
				ppc++;
			if(ppc<processedpacketsize)
			{
				if(neighbor==(CRouter*)(processedneighbors[ppc]))
					return 0;//Repeated Packet from Repeated Neighbor
				else
					return 1;//Repeated Packet Only
			}
			else
				return 2;//new packet
		}
		else
			return 2;//new packet
	}
	else
		return 0;//own packet
}*/

inline int CRouter::GetNextHop(CPacket* packet,CTable *table)
{
	if(PathSize=table->Paths.GetSize())
	{//Get the Destine-Table Matched With Packet!
		if(packet->ChangePath)//Policy to Change Previous Path
		{
			if(!table->Round)
				packet->ChangePath=FALSE;
			table->ChangePath();
		}
		//while((psc<PathSize)&&(!((CPath*)(table->Paths[psc]))->SizeCount))
		//	psc++;
		if(NeighborSize=Neighbors.GetSize())
		{//Get the Firsthop-Neighbor Matched With Packet!
			int nsc=0;
			while((nsc<NeighborSize)&&(((CPath*)(table->Paths[table->Index]))->FirstHop!=((CRouter*)(Neighbors[nsc]))->Caption))
				nsc++;
			if(nsc<NeighborSize)
			{//Send Packet to Firsthop Neighbor = Upload to proper link
				//((CPath*)(table->Paths[psc]))->SizeCount--;
				return nsc;
			}
			else
			{	
				if ((table->Index) >= 0)
				{
				delete (CPath*)(table->Paths[table->Index]);
				table->Paths.RemoveAt(table->Index);
				table->Index=table->Index%table->Paths.GetSize();
				return GetNextHop(packet,table);
				}
				else
					return -1;
			}
		}
		else
			return -1;
	}
	else
		return -1;
}

inline int CRouter::GetNextBenignHop(CPacket* packet,CTable *table)
{//Get next benign hop 
	if(PathSize=table->Paths.GetSize())
	{//Get the Destine-Table Matched With Packet!
		if(NeighborSize=Neighbors.GetSize())
		{//Get the Firsthop-Neighbor Matched With Packet!
			int IsNotSource=(packet->Source!=Caption)?1:0;
			int nsc;
			while(!table->Round)
			{
				nsc=0;
				while((nsc<NeighborSize)&&(((CPath*)(table->Paths[table->Index]))->FirstHop!=((CRouter*)(Neighbors[nsc]))->Caption))
					nsc++;
				if(nsc<NeighborSize)
				{//Send Packet to Firsthop Neighbor = Upload to proper link
					if( ((CGame*)(Games[nsc]))->main_strategy() == 1 )
					//if(Credits[nsc]>0)
					{// Neighbor must have credit 
						if(IsNotSource)
						{//Intermediate-node
							if(nsc!=UploadersIndexes[0])
							//Non-Uploader
								return nsc; //if first hop is a benign node give it the data
							else
							{//Uploader
								table->ChangePath();
								packet->ChangePath=FALSE;
							}
						}
						else
						{//Source-node
							return nsc;
						}
					}
					else			//otherwise,change your path to the destination
					{
						table->ChangePath();
						packet->ChangePath=FALSE;
						//return GetNextBenignHop(packet,table);
					}
				}
				else
				{
					delete (CPath*)(table->Paths[table->Index]);
					table->Paths.RemoveAt(table->Index);
					if(table->Paths.GetSize())
						table->Index=table->Index%table->Paths.GetSize();
					//else
					//	delete table;
					//return GetNextBenignHop(packet,table);
				}
			}
			//Only 4 Demi
			table->Round=0;		//zero table->round since each time packet expires we search the whole table only once to find a new path
								//by making it zero we finish this round and reset it for next time trials.
			if(IsNotSource)
			{
				packet->ChangePath=TRUE;
				return UploadersIndexes[0];
			}
			else
				return -1;
		}
		else
			//return UploadersIndexes[0];
			return -1;
	}
	else
		//return UploadersIndexes[0];
		return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void CRouter::ProcessDataPacket0(CPacket* packet)//ELMAR
{
	//if(LoopFree(p)){
	if(packet->Destination!=Caption)
	{
		if(TableSize=Tables.GetSize())
		{//For Each Destination We have Some Paths
			int tdc=0;
			while((tdc<TableSize)&&(((CTable*)(Tables[tdc]))->Destination!=packet->Destination))
				tdc++;
			if(packet->ChangePath)
			{
				if(tdc<TableSize)
				{
					Table=(CTable*)(Tables[tdc]);
					PathSize=Table->Paths.GetSize();
					int pdc=0;
					while((pdc<PathSize)&&(((CPath*)(Table->Paths[pdc]))->FirstHop!=PacketUploaders[0]))
						pdc++;
					if(pdc<PathSize)
					{
						delete (CPath*)(Table->Paths[pdc]);
						Table->Paths.RemoveAt(pdc);
						packet->ChangePath=FALSE;
						if(Table->Paths.GetSize())
						{
							if(pdc<Table->Index)
								Table->Index--;
							Table->Index=Table->Index%Table->Paths.GetSize();
						}
						else
						{
							delete Table;
							Tables.RemoveAt(tdc);
						}
					}
				}
			}
			else
			{//To set Ack path
				int tsc=0;
				while((tsc<TableSize)&&(((CTable*)(Tables[tsc]))->Destination!=packet->Source))
					tsc++;
				if(tsc<TableSize)
				{
					Table=(CTable*)(Tables[tsc]);
					if(PathSize=Table->Paths.GetSize())
					{//Get the Destine-Table Matched With Packet!
						int psc=0;
						while((psc<PathSize)&&(((CPath*)(Table->Paths[psc]))->FirstHop!=PacketUploaders[0]))
							psc++;
						if(psc<PathSize)
						{
							Table->Index=psc;
							packet->Uploader=PacketUploaders[0];
							((CPath*)(Table->Paths[psc]))->Update(packet);
						}
					}
				}
			}
			TableSize=Tables.GetSize();
			if((tdc<TableSize))//&&(PathSize=((CTable*)(Tables[tsc]))->Paths.GetSize()))
			{//Get the Destine-Table Matched With Packet!
				//int psc=0;
				//while((psc<PathSize)&&(!((CPath*)(((CTable*)(Tables[tsc]))->Paths[psc]))->SizeCount))
				//	psc++;
				//if((psc<PathSize)&&(neighborsize=neighbors.GetSize()))
				//{//Get the Firsthop-Neighbor Matched With Packet!
					//int nsc=0;
				int ndc=0;
				///if(packet->ChangePath)
				ndc=GetNextBenignHop(packet,(CTable*)(Tables[tdc]));
				//CString s=((CRouter*)(Neighbors[ndc]))->Caption;
				///else
				///	nsc=GetNextHop(packet,(CTable*)(Tables[tsc]));
					//while((nsc<neighborsize)&&(((CPath*)(((CTable*)(Tables[tsc]))->Paths[psc]))->FirstHop!=((CRouter*)(neighbors[nsc]))->Caption))
					//	nsc++;
					//if(nsc<neighborsize)
					//{//Send Packet to Firsthop Neighbor = Upload to proper link
					//	if(packet->ChangePath)//Policy to Change Previous Path
					//		((CPath*)(((CTable*)(Tables[tsc]))->Paths[psc]))->SizeCount--;
						//Set timers[nsc]
					if(ndc>-1)
					{
						((CLink*)(Links[ndc]))->Upload(packet,this);
						packet->HopCount++;
						if(Power>0)Power-=40;//DIMAN//ghablan 16 bood man data packet ro 10 barabare RREQ gerftam
						DataTransCounter++;
						if(UploadersIndexes.GetSize()>0)
						{
							((CLink*)(Links[UploadersIndexes[0]]))->Upload(packet,this); //to inform uploader about forwarding of the packet ;)
							if(Power>0)Power-=10;//DIMAN//ghablan 4 bood, man data ra 10 barabare RREQ gereftam
							if((packet->Destination!=((CRouter*)(Neighbors[ndc]))->Caption)
								&&(ndc!=UploadersIndexes[0]))//We're sure that UploadersIndexes[0].GetSize>0
							{
								OutQueue.Add((CPacket*)packet);//timer value we wait for next hop to fwd data packet
								Timers.Add(3*((CLink*)(Links[ndc]))->Delay); //modified
								NextHops.Add(ndc);
							}
						}
					}
					else
					{
						
					}
			}
			else
			{//No Path to Dest!
			}
		}
	}
	else
	{
		if(NeighborSize=Neighbors.GetSize())
		{
			int nsc=0;
			while((nsc<NeighborSize)&&(((CRouter*)(Neighbors[nsc]))->Caption!=PacketUploaders[0]))
				nsc++;
			if(nsc<NeighborSize)
			{
				//packet->ChangePath=FALSE;
				Packet=GenAckPacket(packet);
				GenAckPackets.Add((CPacket*)Packet);
				((CLink*)(Links[nsc]))->Upload(Packet,this);
				Packet->HopCount++;
				if(Power>0)Power-=10;//DIMAN ghablan 4 bood man data ro 10 barabare RREQ gereftam
				if (this->Type==0)
					GenAckCounter++;
				else
					GenSelfishAckCounter++;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void CRouter::ProcessAckPacket0(CPacket* packet)//GTAMR
{
	if(packet->Destination!=Caption)
	{
		if(TableSize=Tables.GetSize())
		{//For Each Destination We have Some Paths
			int tsc=0;
			while((tsc<TableSize)&&(((CTable*)(Tables[tsc]))->Destination!=packet->Destination))
				tsc++;
			if(tsc<TableSize)
			{//Get the Destine-Table Matched With Packet!
				Table=(CTable*)(Tables[tsc]);
				PathSize=Table->Paths.GetSize();
				//int psc=0;
				//while((psc<PathSize)&&(!((CPath*)(((CTable*)(Tables[tsc]))->Paths[psc]))->SizeCount))
				//	psc++;
				if(Table->Index<PathSize)
				{//Get the Firsthop-Neighbor Matched With Packet!
					NeighborSize=Neighbors.GetSize();
					int nsc=0;
					//while((nsc<neighborsize)&&(((CPath*)(((CTable*)(Tables[tsc]))->Paths[psc]))->FirstHop!=((CRouter*)(neighbors[nsc]))->Caption))
					while((nsc<NeighborSize)&&(((CPath*)(Table->Paths[Table->Index]))->FirstHop!=((CRouter*)(Neighbors[nsc]))->Caption))
						nsc++;
					if(nsc<NeighborSize)
					{//Send Packet to Firsthop Neighbor = Upload to proper link
						//if(packet->ChangePath)//Policy to Change Previous Path
						//	((CPath*)(((CTable*)(Tables[tsc]))->Paths[psc]))->SizeCount--;
						((CLink*)(Links[nsc]))->Upload(packet,this);
						packet->HopCount++;
						if(Power>0)Power-=4;
						AckTransCounter++;
					}
				}
			}
		}
	}
	else
	{
		if(DataPacketSize=DataPackets.GetSize())
		{
			int dpsc=0;
			while((dpsc<DataPacketSize)&&(packet->ID!=((CPacket*)(DataPackets[dpsc]))->ID))
				dpsc++;
			if(dpsc<DataPacketSize)
			{
				CPacket* DataPacket=(CPacket*)(DataPackets[dpsc]);
				DataPacket->Stop=Clock;
				DataPacket->DataForwardingDelay=DataPacket->Stop-DataPacket->Start;
				DataPacket->SendData=FALSE;
				this->EstablishedConnectionsCounter++;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline int CRouter::GetTableIndexToDest(CPacket* packet)
{
	if(TableSize=Tables.GetSize())
	{
		int tsc=0;
		while((tsc<TableSize)&&(((CTable*)(Tables[tsc]))->Destination!=packet->Destination))
			tsc++;
		if(tsc<TableSize)
			return tsc;
		else
			return -1;
	}
	else
		return -1;
}

inline int CRouter::GetTableIndexToSource(CPacket* packet)
{
	if(TableSize=Tables.GetSize())
	{
		int tsc=0;
		while((tsc<TableSize)&&(((CTable*)(Tables[tsc]))->Destination!=packet->Source))
			tsc++;
		if(tsc<TableSize)
			return tsc;
		else
			return -1;
	}
	else
		return -1;
}

inline void CRouter::GetTableIndexToSourceAndDest(CPacket* packet, int *stc, int *dtc)
{
	int tsc=0;
	*dtc=-1;
	*stc=-1;
	if(TableSize=Tables.GetSize())
	{
		while((tsc<TableSize)&&((*dtc<0)||(*stc<0)))
		{
			if(((CTable*)(Tables[tsc]))->Destination==packet->Destination)
				*dtc=tsc;
			if(((CTable*)(Tables[tsc]))->Destination==packet->Source     )
				*stc=tsc;
			tsc++;
		}
	}
}

void CRouter::ProcessRReqPacket0(CPacket* RReqPacket)//ELMAR
{
	if(RReqPacket->Destination!=Caption)
	{
		if(TableSize=Tables.GetSize())//For Each Source and Destination May it be We have Some Paths
		{
			int t=0;
			int td=-1,ts=-1;
			while((t<TableSize)&&((td<0)||(ts<0)))
			{
				if(((CTable*)(Tables[t]))->Destination==RReqPacket->Destination)
					td=t;
				if(((CTable*)(Tables[t]))->Destination==RReqPacket->Source     )
					ts=t;
				t++;
			}
			if(ts!=-1)
			{
				if(PathSize=((CTable*)(Tables[ts]))->Paths.GetSize())
				{//Get the Destine-Table Matched With Packet!
					int psc=0;
					while((psc<PathSize)&&(((CPath*)(((CTable*)(Tables[ts]))->Paths[psc]))->FirstHop!=PacketUploaders[0]))
						psc++;
					if(psc<PathSize)//Get the FirstHop Matched
					{
						RReqPacket->Uploader=PacketUploaders[0];
						((CPath*)(((CTable*)(Tables[ts]))->Paths[psc]))->Update(RReqPacket);
					}
					else
					{
						RReqPacket->Uploader=PacketUploaders[0];
						//((CTable*)(Tables[ts]))->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
						((CTable*)(Tables[ts]))->SetPathByPacket(RReqPacket);
					}
				}
				else
				{
					RReqPacket->Uploader=PacketUploaders[0];
					//((CTable*)(Tables[ts]))->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
					((CTable*)(Tables[ts]))->SetPathByPacket(RReqPacket);
				}
			}
			else
			{//No table for source
				if(RReqPacket->Source!=Caption)
				{
					Table=new CTable(RReqPacket->Source);
					Tables.Add(Table);
					RReqPacket->Uploader=PacketUploaders[0];
					Table->SetPathByPacket(RReqPacket);
					//Table->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
					//Broadcast(RReqPacket);
				}
			}
			if(td!=-1)//Is there any path to destination node?
			{	//DIMAN CHANGED
				//int ts=GetTableIndexToSource(RReqPacket);
				//if( ((CTable*)(Tables[td]))->Paths.GetSize()==Neighbors.GetSize() )
				//{
				//	if(PacketRepetitions[0]==2)
				//	{
				//		Packet=GenRRep(RReqPacket);
				//		GenRRepPackets.Add((CPacket*)Packet);
				//		if(ts!=-1)
				//		{
				//			int n=GetNextHop(RReqPacket,(CTable*)(Tables[ts]));
				//			if(n!=-1)
				//			{
				//				((CLink*)(Links[n]))->Upload(Packet,this);
				//				Packet->HopCount++;
				//				if(Power>0)Power-=4;
				//				RReqTransCounter++;
				//			}
				//			else
				//				Broadcast(RReqPacket);
				//		}
				//		else
				//			Broadcast(RReqPacket);
				//	}
				//}
				//else//destination Paths are not clear!
				//DIMAN CHANGED
					if(PacketRepetitions[0]==2)
						Broadcast(RReqPacket);
			}
			else//unknown destination
				if(PacketRepetitions[0]==2)
					Broadcast(RReqPacket);
		}
		else
		{//There is no Table
			if(RReqPacket->Source!=Caption)
			{
				Table=new CTable(RReqPacket->Source);
				Tables.Add(Table);
				RReqPacket->Uploader=PacketUploaders[0];
				Table->SetPathByPacket(RReqPacket);
				//Table->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
				Broadcast(RReqPacket);
			}
		}
	}
	else//RReqPacket->Destination==this->Caption
	{
		int sti=GetTableIndexToSource(RReqPacket);
		if((sti!=-1)&&(PathSize=((CTable*)(Tables[sti]))->Paths.GetSize()))
		{//Get the Destine-Table Matched With Packet!
			int psc=0;
			while((psc<PathSize)&&(((CPath*)(((CTable*)(Tables[sti]))->Paths[psc]))->FirstHop!=PacketUploaders[0]))
				psc++;
			if(psc<PathSize)//Get the FirstHop Matched
			{
				RReqPacket->Uploader=PacketUploaders[0];
				((CPath*)(((CTable*)(Tables[sti]))->Paths[psc]))->Update(RReqPacket);
			}
			else
			{
				//((CTable*)(Tables[sti]))->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
				RReqPacket->Uploader=PacketUploaders[0];
				((CTable*)(Tables[sti]))->SetPathByPacket(RReqPacket);
			}
		}
		else
		{//No table to source exists!
			Table=new CTable(RReqPacket->Source);
			Tables.Add(Table);
			RReqPacket->Uploader=PacketUploaders[0];
			Table->SetPathByPacket(RReqPacket);
			//Table->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
		}

		//if(generatedRReqPacketsize=generatedRReqPackets.GetSize())//new rreq RReqPacket
		//PacketRepetition=PacketRepetitions[0];
		if(PacketRepetitions[0]==2)//new rreq RReqPacket
		{
			//int gpc=0;
			//while((gpc<generatedRReqPacketsize)&&(((CPacket*)(generatedRReqPackets[gpc]))->ID!=RReqPacket->ID))
			//	gpc++;
			//if(gpc==generatedRReqPacketsize)
			{
				Packet=GenRRep(RReqPacket);
				GenRRepPackets.Add((CPacket*)Packet);
				if(sti!=-1)
				{
					int n=GetNextHop(RReqPacket,(CTable*)(Tables[sti]));
					((CLink*)(Links[n]))->Upload(Packet,this);
					Packet->HopCount++;
					if(Power>0)Power-=4;
					RRepTransCounter++;
				}
				else
					Broadcast(Packet);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CRouter::ProcessRRepPacket0(CPacket* RRepPacket)
{
	if(RRepPacket->Destination!=Caption)
	{
		if(TableSize=Tables.GetSize())//For Each Destination We have Some Paths
		{
			int t=0;
			int td=-1,ts=-1;
			while((t<TableSize)&&((td<0)||(ts<0)))
			{
				if(((CTable*)(Tables[t]))->Destination==RRepPacket->Destination)
					td=t;
				if(((CTable*)(Tables[t]))->Destination==RRepPacket->Source     )
					ts=t;
				t++;
			}
			//if(td!=-1)//Is there any path to destination node?
			//{
			//	int n=GetNextHop(RRepPacket,(CTable*)(Tables[td]));
			//	if(n!=-1)
			//	{
			//		((CLink*)(links[n]))->Upload(RRepPacket,this);
			//		RRepPacket->HopCount++;
			//	}
			//}
			//else//unknown destination	 //injast
			//Only 4 Demi
			if(PacketRepetitions[0]==2)	//injast
				Broadcast(RRepPacket);	//injast
			if(ts!=-1)
			{
				if(PathSize=((CTable*)(Tables[ts]))->Paths.GetSize())
				{//Get the Destine-Table Matched With Packet!
					int psc=0;
					while((psc<PathSize)&&(((CPath*)(((CTable*)(Tables[ts]))->Paths[psc]))->FirstHop!=PacketUploaders[0]))
						psc++;
					if(psc<PathSize)
					{//Get the FirstHop Matched
						RRepPacket->Uploader=PacketUploaders[0];
						((CPath*)(((CTable*)(Tables[ts]))->Paths[psc]))->Update(RRepPacket);
					}
					else
					{
						//((CTable*)(Tables[ts]))->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
						RRepPacket->Uploader=PacketUploaders[0];
						((CTable*)(Tables[ts]))->SetPathByPacket(RRepPacket);
					}
				}
				else
				{
					RRepPacket->Uploader=PacketUploaders[0];
					((CTable*)(Tables[ts]))->SetPathByPacket(RRepPacket);
					//((CTable*)(Tables[ts]))->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
				}
			}
			else
			{//No table for source
				Table=new CTable(RRepPacket->Source);
				Tables.Add(Table);
				RRepPacket->Uploader=PacketUploaders[0];
				Table->SetPathByPacket(RRepPacket);
				//Table->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
			}
		}
		else
		{//There is no Table
			Table=new CTable(RRepPacket->Source);
			Tables.Add(Table);
			RRepPacket->Uploader=PacketUploaders[0];
			Table->SetPathByPacket(RRepPacket);
			//Table->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
			if(PacketRepetitions[0]==2)//injast
				Broadcast(RRepPacket); //injast
		}
	}
	else//RReqPacket->Destination==this->Caption
	{
		int sti=GetTableIndexToSource(RRepPacket);
		if(sti!=-1)
		{//Get the Destine-Table Matched With Packet!
			if(PathSize=((CTable*)(Tables[sti]))->Paths.GetSize())
			{
				int psc=0;
				while((psc<PathSize)&&(((CPath*)(((CTable*)(Tables[sti]))->Paths[psc]))->FirstHop!=PacketUploaders[0]))
					psc++;
				if(psc<PathSize)//Get the FirstHop Matched and upload the RReqPacket
				{
					RRepPacket->Uploader=PacketUploaders[0];
					((CPath*)(((CTable*)(Tables[sti]))->Paths[psc]))->Update(RRepPacket);
				}
				else
				{
					RRepPacket->Uploader=PacketUploaders[0];
					((CTable*)(Tables[sti]))->SetPathByPacket(RRepPacket);
					//((CTable*)(Tables[sti]))->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
				}
			}
			else
			{
				RRepPacket->Uploader=PacketUploaders[0];
				((CTable*)(Tables[sti]))->SetPathByPacket(RRepPacket);
			}
			///and also add this path to the table for future need! (like when the next hop turns out to be a selfish one)
			//Table=new CTable(RRepPacket->Source);
			//Tables.Add(Table);
			//RRepPacket->Uploader=PacketUploaders[0];
			//Table->SetPathByPacket(RRepPacket);
			//sti=Tables.GetSize()-1;
		}
		else
		{//No table to source exists!
			Table=new CTable(RRepPacket->Source);
			Tables.Add(Table);
			RRepPacket->Uploader=PacketUploaders[0];
			Table->SetPathByPacket(RRepPacket);
			//Table->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
			sti=Tables.GetSize()-1;
		}
		if(GenRReqPacketSize=GenRReqPackets.GetSize())
		{
			int gpsc=0;
			while	(	(gpsc<GenRReqPacketSize)&&
							(
							(RRepPacket->ID!=((CPacket*)(GenRReqPackets[gpsc]))->ID)||
							(((CPacket*)(GenRReqPackets[gpsc]))->SendData)
							)
					)
				gpsc++;
			if(gpsc<GenRReqPacketSize)
			{
				CPacket* rreq=(CPacket*)(GenRReqPackets[gpsc]);
				rreq->SendData=TRUE;
				rreq->Stop=Clock;
				//rreq->Timeout=(rreq->Stop-rreq->Start)*2;
				DataPacket=GenDataPacket(RRepPacket);		//Generate Data Packet////////HERE IS THE PROBLEM
				DataTransCounter++;
				DataPacket->Start=Clock;
				//queueout.Add((CPacket*)packet);		//// placed some lines below
				//timers.Add(3*((CLink*)(links[nsc]))->Delay);////
				DataPacket->SeqNum++;
				DataPackets.Add((CPacket*)DataPacket);
				//DataPacket->Start=rreq->Start;
				//DataPacket->Stop=rreq->Stop;
				DataPacket->RouteDiscoveryDelay=rreq->Stop-rreq->Start;
				DataPacket->Timeout=(rreq->Stop-rreq->Start)*TimeOutFactor;
				DataPacket->TimeoutCounter=DataPacket->Timeout;
				///DataPacket->Timeout=30;		//to let the things happen faster,shall be modified later
				DataPacket->SendData=TRUE;
				int n=GetNextHop(DataPacket,(CTable*)(Tables[sti]));
				if(n!=-1)
				{
					((CLink*)(Links[n]))->Upload(DataPacket,this);
					DataPacket->HopCount++;
					if(Power>0)Power-=4;
					if (this->Type==0)
						GenDataCounter++;
					else
						GenSelDataCounter++;
					if(DataPacket->Destination!=((CRouter*)(Neighbors[n]))->Caption)
					{
						OutQueue.Add((CPacket*)DataPacket);
						Timers.Add(3*((CLink*)(Links[n]))->Delay); //modified
						NextHops.Add(n);
					}
				}
			}
		}
	}
}

void CRouter::SetGames(int strategy)
{
	int gc;
	Game_Strategy=strategy;
	for(gc=0;gc<Games.GetSize();gc++)
		((CGame*)(this->Games[gc]))->StrategyNum=strategy;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void CRouter::ProcessRReqPacket1(CPacket* RReqPacket)//AODV
{
	if(RReqPacket->Destination!=Caption)
	{
		if(TableSize=Tables.GetSize())//For Each Source and Destination May it be We have Some Paths
		{
			int t=0;
			int td=-1,ts=-1;
			while((t<TableSize)&&((td<0)||(ts<0)))
			{
				if(((CTable*)(Tables[t]))->Destination==RReqPacket->Destination)
					td=t;
				if(((CTable*)(Tables[t]))->Destination==RReqPacket->Source     )
					ts=t;
				t++;
			}
			if(ts!=-1)
			{
				if(PathSize=((CTable*)(Tables[ts]))->Paths.GetSize())
				{//Get the Destine-Table Matched With Packet!
					int psc=0;
					while((psc<PathSize)&&(((CPath*)(((CTable*)(Tables[ts]))->Paths[psc]))->FirstHop!=PacketUploaders[0]))
						psc++;
					if(psc<PathSize)//Get the FirstHop Matched
					{
						RReqPacket->Uploader=PacketUploaders[0];
						((CPath*)(((CTable*)(Tables[ts]))->Paths[psc]))->Update(RReqPacket);
					}
					else
					{
						RReqPacket->Uploader=PacketUploaders[0];
						//((CTable*)(Tables[ts]))->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
						((CTable*)(Tables[ts]))->SetPathByPacket(RReqPacket);
					}
				}
				else
				{
					RReqPacket->Uploader=PacketUploaders[0];
					//((CTable*)(Tables[ts]))->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
					((CTable*)(Tables[ts]))->SetPathByPacket(RReqPacket);
				}
			}
			else
			{//No table for source
				if(RReqPacket->Source!=Caption)
				{
					Table=new CTable(RReqPacket->Source);
					Tables.Add(Table);
					RReqPacket->Uploader=PacketUploaders[0];
					Table->SetPathByPacket(RReqPacket);
					//Table->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
					//Broadcast(RReqPacket);
				}
			}
			if(PacketRepetitions[0]==2)
				Broadcast(RReqPacket);
		}
		else
		{//There is no Table
			if(RReqPacket->Source!=Caption)
			{
				Table=new CTable(RReqPacket->Source);
				Tables.Add(Table);
				RReqPacket->Uploader=PacketUploaders[0];
				Table->SetPathByPacket(RReqPacket);
				//Table->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
				Broadcast(RReqPacket);
			}
		}
	}
	else//RReqPacket->Destination==this->Caption
	{
		int sti=GetTableIndexToSource(RReqPacket);
		if((sti!=-1)&&(PathSize=((CTable*)(Tables[sti]))->Paths.GetSize()))
		{//Get the Destine-Table Matched With Packet!
			int psc=0;
			while((psc<PathSize)&&(((CPath*)(((CTable*)(Tables[sti]))->Paths[psc]))->FirstHop!=PacketUploaders[0]))
				psc++;
			if(psc<PathSize)//Get the FirstHop Matched
			{
				RReqPacket->Uploader=PacketUploaders[0];
				((CPath*)(((CTable*)(Tables[sti]))->Paths[psc]))->Update(RReqPacket);
			}
			else
			{
				//((CTable*)(Tables[sti]))->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
				RReqPacket->Uploader=PacketUploaders[0];
				((CTable*)(Tables[sti]))->SetPathByPacket(RReqPacket);
			}
		}
		else
		{//No table to source exists!
			Table=new CTable(RReqPacket->Source);
			Tables.Add(Table);
			RReqPacket->Uploader=PacketUploaders[0];
			Table->SetPathByPacket(RReqPacket);
			//Table->SetPath(PacketUploaders[0],RReqPacket->TickCount,RReqPacket->HopCount,RReqPacket->SizeCount);
		}

		//if(generatedRReqPacketsize=generatedRReqPackets.GetSize())//new rreq RReqPacket
		//PacketRepetition=PacketRepetitions[0];
		if(PacketRepetitions[0]==2)//new rreq RReqPacket
		{
			//int gpc=0;
			//while((gpc<generatedRReqPacketsize)&&(((CPacket*)(generatedRReqPackets[gpc]))->ID!=RReqPacket->ID))
			//	gpc++;
			//if(gpc==generatedRReqPacketsize)
			{
				Packet=GenRRep(RReqPacket);
				GenRRepPackets.Add((CPacket*)Packet);
				if(sti!=-1)
				{
					int n=GetNextHop(RReqPacket,(CTable*)(Tables[sti]));
					((CLink*)(Links[n]))->Upload(Packet,this);
					Packet->HopCount++;
					if(Power>0)Power-=4;
					RRepTransCounter++;
				}
				else
				{
					int n=GetNextHop(RReqPacket,(CTable*)(Tables[Tables.GetSize()-1]));
					((CLink*)(Links[n]))->Upload(Packet,this);
					Packet->HopCount++;
					if(Power>0)Power-=4;
					RRepTransCounter++;
					//Broadcast(Packet);
				}
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CRouter::ProcessRRepPacket1(CPacket* RRepPacket)//AODV
{
	if(RRepPacket->Destination!=Caption)
	{
		if(TableSize=Tables.GetSize())//For Each Destination We have Some Paths
		{
			int t=0;
			int td=-1,ts=-1;
			//mabda boodan ya maghsad boodan
			while((t<TableSize)&&((td<0)||(ts<0)))
			{
				if(((CTable*)(Tables[t]))->Destination==RRepPacket->Destination)
					td=t;
				if(((CTable*)(Tables[t]))->Destination==RRepPacket->Source     )
					ts=t;
				t++;
			}
			//if(td!=-1)//Is there any path to destination node?
			//{
			//	int n=GetNextHop(RRepPacket,(CTable*)(Tables[td]));
			//	if(n!=-1)
			//	{
			//		((CLink*)(links[n]))->Upload(RRepPacket,this);
			//		RRepPacket->HopCount++;
			//	}
			//}
			//else//unknown destination	 //injast
			//Only 4 Demi
			//DIMAN CHANGED
			int n=GetNextHop(RRepPacket,(CTable*)(Tables[td]));
			((CLink*)(Links[n]))->Upload(RRepPacket,this);
			RRepPacket->HopCount++;
			if(Power>0)Power-=4;
			RRepTransCounter++;
			//if(PacketRepetitions[0]==2)	//injast
			//	Broadcast(RRepPacket);	//injast
			//DIMAN CHANGED
			if(ts!=-1)
			{
				if(PathSize=((CTable*)(Tables[ts]))->Paths.GetSize())
				{//Get the Destine-Table Matched With Packet!
					int psc=0;
					while((psc<PathSize)&&(((CPath*)(((CTable*)(Tables[ts]))->Paths[psc]))->FirstHop!=PacketUploaders[0]))
						psc++;
					if(psc<PathSize)
					{//Get the FirstHop Matched
						RRepPacket->Uploader=PacketUploaders[0];
						((CPath*)(((CTable*)(Tables[ts]))->Paths[psc]))->Update(RRepPacket);
					}
					else
					{
						//((CTable*)(Tables[ts]))->SetPath(PacketUploaders[0],packet->TickCount,packet->HopCount,packet->SizeCount);
						RRepPacket->Uploader=PacketUploaders[0];
						((CTable*)(Tables[ts]))->SetPathByPacket(RRepPacket);
					}
				}
				else
				{
					RRepPacket->Uploader=PacketUploaders[0];
					((CTable*)(Tables[ts]))->SetPathByPacket(RRepPacket);
					//((CTable*)(Tables[ts]))->SetPath(PacketUploaders[0],packet->TickCount,packet->HopCount,packet->SizeCount);
				}
			}
			else
			{//No table for source
				Table=new CTable(RRepPacket->Source);
				Tables.Add(Table);
				RRepPacket->Uploader=PacketUploaders[0];
				Table->SetPathByPacket(RRepPacket);
				//Table->SetPath(PacketUploaders[0],packet->TickCount,packet->HopCount,packet->SizeCount);
			}
		}
		else
		{//There is no Table
			Table=new CTable(RRepPacket->Source);
			Tables.Add(Table);
			RRepPacket->Uploader=PacketUploaders[0];
			Table->SetPathByPacket(RRepPacket);
			//Table->SetPath(PacketUploaders[0],packet->TickCount,packet->HopCount,packet->SizeCount);
			//if(PacketRepetitions[0]==2)//injast
			//	Broadcast(RRepPacket); //injast
		}
	}
	else//packet->Destination==this->Caption
	{
		int sti=GetTableIndexToSource(RRepPacket);
		if(sti!=-1)
		{//Get the Destine-Table Matched With Packet!
			if(PathSize=((CTable*)(Tables[sti]))->Paths.GetSize())
			{
				int psc=0;
				while((psc<PathSize)&&(((CPath*)(((CTable*)(Tables[sti]))->Paths[psc]))->FirstHop!=PacketUploaders[0]))
					psc++;
				if(psc<PathSize)//Get the FirstHop Matched and upload the packet
				{
					RRepPacket->Uploader=PacketUploaders[0];
					((CPath*)(((CTable*)(Tables[sti]))->Paths[psc]))->Update(RRepPacket);
				}
				else
				{
					RRepPacket->Uploader=PacketUploaders[0];
					((CTable*)(Tables[sti]))->SetPathByPacket(RRepPacket);
					//((CTable*)(Tables[sti]))->SetPath(PacketUploaders[0],packet->TickCount,packet->HopCount,packet->SizeCount);
				}
			}
			else
			{
				RRepPacket->Uploader=PacketUploaders[0];
				((CTable*)(Tables[sti]))->SetPathByPacket(RRepPacket);
			}
			///and also add this path to the table for future need! (like when the next hop turns out to be a selfish one)
			//Table=new CTable(RRepPacket->Source);
			//Tables.Add(Table);
			//RRepPacket->Uploader=PacketUploaders[0];
			//Table->SetPathByPacket(RRepPacket);
			//sti=Tables.GetSize()-1;
		}
		else
		{//No table to source exists!
			Table=new CTable(RRepPacket->Source);
			Tables.Add(Table);
			RRepPacket->Uploader=PacketUploaders[0];
			Table->SetPathByPacket(RRepPacket);
			//Table->SetPath(PacketUploaders[0],packet->TickCount,packet->HopCount,packet->SizeCount);
			sti=Tables.GetSize()-1;
		}
		if(GenRReqPacketSize=GenRReqPackets.GetSize())
		{
			int gpsc=0;
			while	(	(gpsc<GenRReqPacketSize)&&
							(
							(RRepPacket->ID!=((CPacket*)(GenRReqPackets[gpsc]))->ID)||
							(((CPacket*)(GenRReqPackets[gpsc]))->SendData)
							)
					)
				gpsc++;
			if(gpsc<GenRReqPacketSize)
			{
				CPacket* rreq=(CPacket*)(GenRReqPackets[gpsc]);
				rreq->SendData=TRUE;
				rreq->Stop=Clock;
				//rreq->Timeout=(rreq->Stop-rreq->Start)*2;
				DataPacket=GenDataPacket(RRepPacket);		//Generate Data Packet////////HERE IS THE PROBLEM
				DataTransCounter++;
				DataPacket->Start=Clock;
				//queueout.Add((CPacket*)packet);		//// placed some lines below
				//timers.Add(3*((CLink*)(links[nsc]))->Delay);////
				DataPacket->SeqNum++;
				DataPackets.Add((CPacket*)DataPacket);
				//DataPacket->Start=rreq->Start;
				//DataPacket->Stop=rreq->Stop;
				DataPacket->RouteDiscoveryDelay=rreq->Stop-rreq->Start;
				DataPacket->Timeout=(rreq->Stop-rreq->Start)*TimeOutFactor;
				DataPacket->TimeoutCounter=DataPacket->Timeout;
				///DataPacket->Timeout=30;		//to let the things happen faster,shall be modified later
				DataPacket->SendData=TRUE;
				int n=GetNextHop(DataPacket,(CTable*)(Tables[sti]));
				if(n!=-1)
				{
					((CLink*)(Links[n]))->Upload(DataPacket,this);
					DataPacket->HopCount++;
					if(Power>0)Power-=4;
					if (this->Type==0)
						GenDataCounter++;
					else
						GenSelDataCounter++;
					if(DataPacket->Destination!=((CRouter*)(Neighbors[n]))->Caption)
					{
						OutQueue.Add((CPacket*)DataPacket);
						Timers.Add(3*((CLink*)(Links[n]))->Delay); //modified
						NextHops.Add(n);
					}
				}
			}
		}
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CRouter::ProcessDataPacket1(CPacket* packet)//AODV
{
	//if(LoopFree(p)){
	if(packet->Destination!=Caption)
	{
		if(TableSize=Tables.GetSize())
		{//For Each Destination We have Some Paths
			int tdc=0;
			while((tdc<TableSize)&&(((CTable*)(Tables[tdc]))->Destination!=packet->Destination))
				tdc++;
			if(packet->ChangePath)
			{
				if(tdc<TableSize)
				{
					Table=(CTable*)(Tables[tdc]);
					PathSize=Table->Paths.GetSize();
					int pdc=0;
					while((pdc<PathSize)&&(((CPath*)(Table->Paths[pdc]))->FirstHop!=PacketUploaders[0]))
						pdc++;
					if(pdc<PathSize)
					{
						delete (CPath*)(Table->Paths[pdc]);
						Table->Paths.RemoveAt(pdc);
						packet->ChangePath=FALSE;
						if(Table->Paths.GetSize())
						{
							if(pdc<Table->Index)
								Table->Index--;
							Table->Index=Table->Index%Table->Paths.GetSize();
						}
						else
						{
							delete Table;
							Tables.RemoveAt(tdc);
						}
					}
				}
			}
			else
			{//To set Ack path
				int tsc=0;
				while((tsc<TableSize)&&(((CTable*)(Tables[tsc]))->Destination!=packet->Source))
					tsc++;
				if(tsc<TableSize)
				{
					Table=(CTable*)(Tables[tsc]);
					if(PathSize=Table->Paths.GetSize())
					{//Get the Destine-Table Matched With Packet!
						int psc=0;
						while((psc<PathSize)&&(((CPath*)(Table->Paths[psc]))->FirstHop!=PacketUploaders[0]))
							psc++;
						if(psc<PathSize)
						{
							Table->Index=psc;
							packet->Uploader=PacketUploaders[0];
							((CPath*)(Table->Paths[psc]))->Update(packet);
						}
					}
				}
			}
			TableSize=Tables.GetSize();
			if((tdc<TableSize))//&&(PathSize=((CTable*)(Tables[tsc]))->Paths.GetSize()))
			{//Get the Destine-Table Matched With Packet!
				//int psc=0;
				//while((psc<PathSize)&&(!((CPath*)(((CTable*)(Tables[tsc]))->Paths[psc]))->SizeCount))
				//	psc++;
				//if((psc<PathSize)&&(neighborsize=neighbors.GetSize()))
				//{//Get the Firsthop-Neighbor Matched With Packet!
					//int nsc=0;
				int ndc=0;
				///if(packet->ChangePath)
				ndc=GetNextBenignHop(packet,(CTable*)(Tables[tdc]));
				//CString s=((CRouter*)(Neighbors[ndc]))->Caption;
				///else
				///	nsc=GetNextHop(packet,(CTable*)(Tables[tsc]));
					//while((nsc<neighborsize)&&(((CPath*)(((CTable*)(Tables[tsc]))->Paths[psc]))->FirstHop!=((CRouter*)(neighbors[nsc]))->Caption))
					//	nsc++;
					//if(nsc<neighborsize)
					//{//Send Packet to Firsthop Neighbor = Upload to proper link
					//	if(packet->ChangePath)//Policy to Change Previous Path
					//		((CPath*)(((CTable*)(Tables[tsc]))->Paths[psc]))->SizeCount--;
						//Set timers[nsc]
					if(ndc>-1)
					{
						((CLink*)(Links[ndc]))->Upload(packet,this);
						packet->HopCount++;
						if(Power>0)Power-=40;//DIMAN//ghablan 16 bood man data packet ro 10 barabare RREQ gerftam
						DataTransCounter++;
						if(UploadersIndexes.GetSize()>0)
						{
							((CLink*)(Links[UploadersIndexes[0]]))->Upload(packet,this); //to inform uploader about forwarding of the packet ;)
							if(Power>0)Power-=10;//DIMAN//ghablan 4 bood, man data ra 10 barabare RREQ gereftam
							if((packet->Destination!=((CRouter*)(Neighbors[ndc]))->Caption)
								&&(ndc!=UploadersIndexes[0]))//We're sure that UploadersIndexes[0].GetSize>0
							{
								OutQueue.Add((CPacket*)packet);//timer value we wait for next hop to fwd data packet
								Timers.Add(3*((CLink*)(Links[ndc]))->Delay); //modified
								NextHops.Add(ndc);
							}
						}
					}
					else
					{
						
					}
			}
			else
			{//No Path to Dest!
			}
		}
	}
	else
	{
		if(NeighborSize=Neighbors.GetSize())
		{
			int nsc=0;
			while((nsc<NeighborSize)&&(((CRouter*)(Neighbors[nsc]))->Caption!=PacketUploaders[0]))
				nsc++;
			if(nsc<NeighborSize)
			{
				//packet->ChangePath=FALSE;
				Packet=GenAckPacket(packet);
				GenAckPackets.Add((CPacket*)Packet);
				((CLink*)(Links[nsc]))->Upload(Packet,this);
				Packet->HopCount++;
				if(Power>0)Power-=10;//DIMAN ghablan 4 bood man data ro 10 barabare RREQ gereftam
				if (this->Type==0)
					GenAckCounter++;
				else
					GenSelfishAckCounter++;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CRouter::ProcessAckPacket1(CPacket* packet)//AODV
{
	if(packet->Destination!=Caption)
	{
		if(TableSize=Tables.GetSize())
		{//For Each Destination We have Some Paths
			int tsc=0;
			while((tsc<TableSize)&&(((CTable*)(Tables[tsc]))->Destination!=packet->Destination))
				tsc++;
			if(tsc<TableSize)
			{//Get the Destine-Table Matched With Packet!
				Table=(CTable*)(Tables[tsc]);
				PathSize=Table->Paths.GetSize();
				//int psc=0;
				//while((psc<PathSize)&&(!((CPath*)(((CTable*)(Tables[tsc]))->Paths[psc]))->SizeCount))
				//	psc++;
				if(Table->Index<PathSize)
				{//Get the Firsthop-Neighbor Matched With Packet!
					NeighborSize=Neighbors.GetSize();
					int nsc=0;
					//while((nsc<neighborsize)&&(((CPath*)(((CTable*)(Tables[tsc]))->Paths[psc]))->FirstHop!=((CRouter*)(neighbors[nsc]))->Caption))
					while((nsc<NeighborSize)&&(((CPath*)(Table->Paths[Table->Index]))->FirstHop!=((CRouter*)(Neighbors[nsc]))->Caption))
						nsc++;
					if(nsc<NeighborSize)
					{//Send Packet to Firsthop Neighbor = Upload to proper link
						//if(packet->ChangePath)//Policy to Change Previous Path
						//	((CPath*)(((CTable*)(Tables[tsc]))->Paths[psc]))->SizeCount--;
						((CLink*)(Links[nsc]))->Upload(packet,this);
						packet->HopCount++;
						if(Power>0)Power-=4;
						AckTransCounter++;
					}
				}
			}
		}
	}
	else
	{
		if(DataPacketSize=DataPackets.GetSize())
		{
			int dpsc=0;
			while((dpsc<DataPacketSize)&&(packet->ID!=((CPacket*)(DataPackets[dpsc]))->ID))
				dpsc++;
			if(dpsc<DataPacketSize)
			{
				CPacket* DataPacket=(CPacket*)(DataPackets[dpsc]);
				DataPacket->Stop=Clock;
				DataPacket->DataForwardingDelay=DataPacket->Stop-DataPacket->Start;
				DataPacket->SendData=FALSE;
				this->EstablishedConnectionsCounter++;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void CRouter::ProcessRReqPacket2(CPacket* packet)//AOMDV
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CRouter::ProcessRRepPacket2(CPacket* packet)//AOMDV
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CRouter::ProcessDataPacket2(CPacket* packet)//AOMDV
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CRouter::ProcessAckPacket2(CPacket* packet)//AOMDV
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
