// Stat.cpp : implementation file
//

#include "stdafx.h"
#include "MANET.h"
#include "Stat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStat dialog


CStat::CStat(CWnd* pParent /*=NULL*/)
	: CDialog(CStat::IDD, pParent)
	, RReqTransNum(0)
	, RRepTransNum(0)
	, GenDataNum(0)
	, GenAckNum(0)
	, DataTransNum(0)
	, TotalPower(0)
	, AdhocNum(0)
	, Selfish1Num(0)
	, Selfish2Num(0)
	, TABch(9)
	, StrNum(_T(""))
	, EstabConn(0)
	, ClockNum(0)
	, MinDataDelay(0)
	, MaxDataDelay(0)
	, MinDiscoDelay(0)
	, MaxDiscoDelay(0)
	, AvgDiscoDelay(0)
	, AvgDataDelay(0)
{
	//{{AFX_DATA_INIT(CStat)
//	m_processedpackets = 0;
	//}}AFX_DATA_INIT
}


void CStat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStat)
	///DDX_Text(pDX, IDC_EDIT_ProcessedPackets, m_processedpackets);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_RReqTransNumber, RReqTransNum);
	DDX_Text(pDX, IDC_EDIT_RRepTransNumber, RRepTransNum);
	DDX_Text(pDX, IDC_EDIT_GenDataTransNumber, GenDataNum);
	DDX_Text(pDX, IDC_EDIT_GenAckTransNumber, GenAckNum);
	DDX_Text(pDX, IDC_EDIT_DataTransNumber, DataTransNum);
	DDX_Text(pDX, IDC_EDIT_TotalPower, TotalPower);
	DDX_Text(pDX, IDC_EDIT_AdhocNum, AdhocNum);
	DDX_Text(pDX, IDC_EDIT_Selfish1Num, Selfish1Num);
	DDX_Text(pDX, IDC_EDIT_Selfish2Num, Selfish2Num);
	DDX_Text(pDX, IDC_EDIT_EstabConn, EstabConn);
	DDX_Text(pDX, IDC_EDIT_Clock, ClockNum);
	DDX_Text(pDX, IDC_EDIT_MinDataDelay, MinDataDelay);
	DDX_Text(pDX, IDC_EDIT_MaxDataDelay, MaxDataDelay);
	DDX_Text(pDX, IDC_EDIT_MinDiscoDelay, MinDiscoDelay);
	DDX_Text(pDX, IDC_EDIT_MaxDiscoDelay, MaxDiscoDelay);
	DDX_Text(pDX, IDC_EDIT_AvgDiscoDelay, AvgDiscoDelay);
	DDX_Text(pDX, IDC_EDIT_AvgDataDelay2, AvgDataDelay);
}


BEGIN_MESSAGE_MAP(CStat, CDialog)
	//{{AFX_MSG_MAP(CStat)
	//}}AFX_MSG_MAP
//	ON_EN_CHANGE(IDC_EDIT7, &CStat::OnEnChangeEdit7)
//	ON_EN_CHANGE(IDC_EDIT6, &CStat::OnEnChangeEdit6)
//	ON_EN_CHANGE(IDC_EDIT8, &CStat::OnEnChangeEdit8)
//	ON_EN_CHANGE(IDC_EDIT_CAPTION, &CStat::OnEnChangeEditCaption)
//	ON_EN_CHANGE(IDC_EDIT10, &CStat::OnEnChangeEdit10)
//	ON_EN_CHANGE(IDC_EDIT_RReqTransNumber, &CStat::OnEnChangeEditRreqtransnumber)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStat message handlers

BOOL CStat::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(TRUE);
	ASSERT_VALID(Document); //check that the document variable is set!
	this->RReqTransNum=0;
	this->RRepTransNum=0;
	this->GenDataNum=0;
	this->GenAckNum=0;
	this->AdhocNum=0;
	this->Selfish1Num=0;
	this->Selfish2Num=0;
	int RouterSize=Document->Routers.GetSize();
	int i;
	//DIMAN CHANGED
	int j;
	int Packet_rdd = 0;
	int Packet_dfd = 0;
	int NumDataPackets = 0;
	double max_Routdiscovery_delay = 0;
	double min_Routdiscovery_delay = 10000000;
	double min_DataForwarding_delay = 10000000;
	double max_DataForwarding_delay = 0;
	//DIMAN CHANGED
	int pow=0;
	avg_RDD_perHop = 0;
	avg_DFD_perHop = 0;
	avg_RDD = 0;

	for(i=0;i<RouterSize;i++)
	{
		router = ((CRouter*)(Document->Routers[i]));
		RReqTransNum				+=	router->RReqTransCounter;
		RRepTransNum				+=	router->RRepTransCounter;
		GenDataNum					+=	router->GenDataCounter;
		GenSelDataNum				+=  router->GenSelDataCounter;
		GenAckNum					+=	router->GenAckCounter;
		GenSelfishAckNum			+=	router->GenSelfishAckCounter;
		DataTransNum				+=	router->DataTransCounter;
		EstabConn					+=  router->EstablishedConnectionsCounter;
		TotalPower					+=	router->Power;
		ClockNum					+=	router->Clock;
		if (router->Type==0)
			AdhocNum++;
		if (router->Type==1)
			Selfish1Num++;
		if (router->Type==2)
			Selfish2Num++;
		//DIMAN CHANGED
		int DataPacketSize=router->DataPackets.GetSize();
		NumDataPackets += DataPacketSize;
		for(j=0;j<DataPacketSize;j++)
		{
			packet = (CPacket*)(router->DataPackets[j]);
			//avg_RDD			+= packet->RouteDiscoveryDelay;
			if ( ((double)(packet->RouteDiscoveryDelay)) / ((double)(packet->HopCount)) 
				> ((double)(max_Routdiscovery_delay))) 
				max_Routdiscovery_delay = ((double)(packet->RouteDiscoveryDelay)) / ((double)(packet->HopCount));
			
			if ( ( ((double)(packet->RouteDiscoveryDelay)) / ((double)(packet->HopCount)) 
				< ((double)(min_Routdiscovery_delay))) && (((double)(packet->RouteDiscoveryDelay))>1) ) 
				min_Routdiscovery_delay = ((double)(packet->RouteDiscoveryDelay)) / ((double)(packet->HopCount));
		
			if (( ((double)(packet->DataForwardingDelay)) / ((double)(packet->HopCount)) 
				> ((double)(max_DataForwarding_delay))) && (((double)(packet->DataForwardingDelay)) / ((double)(packet->HopCount)) < 1000000000))
				max_DataForwarding_delay = ((double)(packet->DataForwardingDelay)) / ((double)(packet->HopCount));
			
			if ( ( ((double)(packet->DataForwardingDelay)) / ((double)(packet->HopCount)) < ((double)(min_DataForwarding_delay)) ) 
				&& (((double)(packet->DataForwardingDelay))>1) ) 
			//{
				min_DataForwarding_delay = ((double)(packet->DataForwardingDelay)) / ((double)(packet->HopCount));
			//	if(min_DataForwarding_delay<1)
			//		min_DataForwarding_delay++;
			//}
		    //DIMAN CHANGED ye && ezafe kardam ke route hayee ke tashki nemishan delay eshoon hesab nashe!
			if ((((double)(packet->RouteDiscoveryDelay))>1)&&(((double)(packet->RouteDiscoveryDelay))<10000000))
			{
				Packet_rdd++;
				avg_RDD_perHop	+= ((double)(packet->RouteDiscoveryDelay)) / ((double)(packet->HopCount));
			}
			//DIMAN CHANGED ye && ezafe kardam ke route hayee ke tashki nemishan delay eshoon hesab nashe!
			if ((((double)(packet->DataForwardingDelay))>1)&&(((double)(packet->DataForwardingDelay))<10000000))
			{
				Packet_dfd++;
				avg_DFD_perHop  += ((double)(packet->DataForwardingDelay)) / ((double)(packet->HopCount));
			}
			//packet = (CPacket*)(router->DataPackets[j]);
			//packet->DataForwardingDelay;
			//packet->RouteDiscoveryDelay;
			//packet->HopCount;
			//DIMAN CHANGED
		}
	}
	//DIMAN CHANGED
	avg_RDD_perHop = avg_RDD_perHop / (Packet_rdd);
	avg_DFD_perHop = avg_DFD_perHop / (Packet_dfd);
	//DIMAN CHANGED
	ClockNum=ClockNum/RouterSize;


	///////////////Initialize the File
	if(!myFile.Open(_T("myFile.txt"), CFile::modeReadWrite))
		myFile.Open(_T("myFile.txt"),CFile::modeCreate);
	myFile.SeekToEnd();

	this->MaxDataDelay = max_DataForwarding_delay;
	this->MinDataDelay = min_DataForwarding_delay;
	this->AvgDataDelay = avg_DFD_perHop;

	this->MaxDiscoDelay = max_Routdiscovery_delay;
	this->MinDiscoDelay = min_Routdiscovery_delay;
	this->AvgDiscoDelay = avg_RDD_perHop;

	///DIMAN
	//	ch=(char)13; //CarriageReturn
	//myFile.Write(&ch,1);
	//ch=(char)10; //NewLine
	//myFile.Write(&ch,1);
	//myFile.Flush();
	///DIMAN
	//////////////////////////////////

	///////////////Writing Data 2 File
	write2file(DataTransNum);
	write2file(RReqTransNum);
	write2file(RRepTransNum);
	write2file(GenDataNum);
	write2file(GenAckNum);
	write2file(EstabConn);
	//DIMAN CHANGED
	//write2file(GenSelDataNum);
	//write2file(GenSelfishAckNum);
	//DIMAN CHANGED
	write2file(TotalPower);
	write2file(AdhocNum);
	write2file(Selfish1Num);
	write2file(Selfish2Num);
	write2file(ClockNum);
	//DIMAN CHANGED
	//write2file(GenSelDataNum);
	//write2file(GenSelfishAckNum);
	//DIMAN CHANGED
	write2file((int)(100*avg_RDD_perHop));
	write2file((int)(100*avg_DFD_perHop));
	//DIMAN CHANGED

	//DIMAN CHANGED
	
	write2file((int)(100*max_Routdiscovery_delay));
	write2file((int)(100*min_Routdiscovery_delay));
	write2file((int)(100*max_DataForwarding_delay));
	write2file((int)(100*min_DataForwarding_delay));
	
	//y_axis=rand();
	//write2file(y_axis);
	//write2file(RAND_MAX + 1);
	///////////////////////////////////
	//############DIMAN
	//for(i=0;i<RouterSize;i++)
	//{
	//	pow=((CRouter*)(Document->Routers[i]))->Power;
		//next line
	//	myFile.SeekToEnd();
	//	ch=(char)13; //CarriageReturn
	//	myFile.Write(&ch,1);
	//	ch=(char)10; //NewLine
	//	myFile.Write(&ch,1);
	//	myFile.Flush();
		// next line
	//	if (pow<0)
	//		write2file(0);
	//	else
	//		write2file(pow);
	//}
	//for(i=0;i<RouterSize;i++)
	//{
	//	x_axis=((CRouter*)(Document->Routers[i]))->X;
	//	y_axis=((CRouter*)(Document->Routers[i]))->Y;
		//next line
	//	myFile.SeekToEnd();
	//	ch=(char)13; //CarriageReturn
	//	myFile.Write(&ch,1);
	//	ch=(char)10; //NewLine
	//	myFile.Write(&ch,1);
	//	myFile.Flush();
		//next line
	//	write2file(x_axis);
	//	write2file(y_axis);
	//}
	//#############DIMAN


	///////////////Finalize Writings
	myFile.SeekToEnd();
	ch=(char)13; //CarriageReturn
	myFile.Write(&ch,1);
	ch=(char)10; //NewLine
	myFile.Write(&ch,1);
	myFile.Flush();
	/////////////////////////////////

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStat::int2str(int integer)
{
	this->StrNum="";
	if(integer==0)
		StrNum="0";
	else
	{
		while(integer>0)
		{
			StrNum.Insert(0,(char)((integer%10)+(int)'0'));
			integer=integer/10;
		}
	}
}

void CStat::write2file(int integer)
{
	///int2str(DataTransNum)
	this->StrNum="";
	if(integer==0)
		StrNum="0";
	else
	{
		while(integer>0)
		{
			StrNum.Insert(0,(char)((integer%10)+(int)'0'));
			integer=integer/10;
		}
	}
	////////////////////////
	for(int i=0;i<StrNum.GetLength();i++)
		StrArray[i]=StrNum[i];
	myFile.Write(&StrArray, StrNum.GetLength());
	//ch=(char)9; //TAB
	myFile.Write(&TABch,1);
	myFile.Write(&TABch,1);
}

