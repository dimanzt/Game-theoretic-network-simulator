#include "stdafx.h"
//#include 
#include "Game.h"

CGame::CGame(void)
{
//	pre_maction=1; //010001010
//	pre_naction=1;
//	maction=1;
//	naction=1;
	int i;
//	double error;
	for(i=0;i<MEMORY_SIZE;i++)
		m_Actions[i]=1;
	for(i=0;i<MEMORY_SIZE;i++)
		n_Actions[i]=1;
	m_Forward_counter=1;// 0/0=?
	n_Forward_counter=1;// 0/0=?
	m_Send_counter=1;// 0/0=?
	n_Send_counter=1;// 0/0=?
	StrategyNum=1;
}

CGame::~CGame(void)
{
}

int CGame::AddmyAction(int action)
{// 0=Discard 1=Forward
	this->n_Send_counter++;//n_Send = m_Receive
	if(action==1)
		this->m_Forward_counter++;
	if(MEMORY_SIZE)
	{
		int i;
		for(i=0;i<MEMORY_SIZE-1;i++)
			m_Actions[i]=m_Actions[i+1];
		m_Actions[MEMORY_SIZE-1]=action;
		return 1;
	}
	else
		return 0;
}

int CGame::AddneighborAction(int action)
{
	this->m_Send_counter++;//m_Send = n_Receive
	if(action==1)
		this->n_Forward_counter++;
	if(MEMORY_SIZE)
	{
		int i;
		for(i=0;i<MEMORY_SIZE-1;i++)
			n_Actions[i]=n_Actions[i+1];
		n_Actions[MEMORY_SIZE-1]=action;
		return 1;
	}
	else
		return 0;
}

int CGame::ERTFT_strategy(void)////main_strategy(void)
{
	//add error
	//////////////DIMAN
	//if (rand()<((RAND_MAX+1)/1000))
	//{ 
	//	if (n_Actions[MEMORY_SIZE-1]==1)
	//	n_Actions[MEMORY_SIZE-1]=0;
	//} 
	/////add error
	/////////////DIMAN

	if((m_Actions[MEMORY_SIZE-1]==1)&&(n_Actions[MEMORY_SIZE-1]==0))
	{
		//this->AddmyAction(0);
		return 0;
	}
	else
		if((m_Actions[MEMORY_SIZE-1]==0)&&(n_Actions[MEMORY_SIZE-1]==0)&&(m_Actions[MEMORY_SIZE-2]==1)&&(n_Actions[MEMORY_SIZE-2]==0))
			return 0;
		else
		{
		//this->AddmyAction(1);
		return 1;
		}
}
////DIMAN
int CGame::main_strategy(void)//ERTFT_strategy(void)
{
	//add error
	//////////////DIMAN
	//if (rand()<((RAND_MAX+1)/1000))
	//{ 
	//	if (n_Actions[MEMORY_SIZE-1]==1)
	//	n_Actions[MEMORY_SIZE-1]=0;
	//} 
	/////add error
	/////////////DIMAN
	if(StrategyNum==0)
		return CGame::TFT_strategy();
	else if(StrategyNum==1)
		return CGame::ERTFT_strategy();
	else if(StrategyNum==2)
		return CGame::Forwarding_Ratio_strategy();
	else 
		return 1;
}
//DIMAN

int CGame::TFT_strategy(void)
{
	//add error
	//////////////DIMAN
	//if (rand()<((RAND_MAX+1)/1000))
	//{ 
	//	if (n_Actions[MEMORY_SIZE-1]==1)
	//	n_Actions[MEMORY_SIZE-1]=0;
	//} 
	/////add error
	/////////////DIMAN

	if((n_Actions[MEMORY_SIZE-1]==0))
	{
		//this->AddmyAction(0);
		return 0;
	}
	else
	{
		//this->AddmyAction(1);
		return 1;
	}
}
int CGame::Forwarding_Ratio_strategy(void)
{
	//add error
	//////////////DIMAN
	//if (rand()<((RAND_MAX+1)*0.2))
	//{ 
	//	if (n_Actions[MEMORY_SIZE-1]==1)
	//	n_Actions[MEMORY_SIZE-1]=0;
	//} 
	/////add error
	/////////////DIMAN

	int my_Forwarding_Ratio;
	int Neighbor_Forwarding_Ratio;
	my_Forwarding_Ratio=m_Forward_counter/n_Send_counter;
	Neighbor_Forwarding_Ratio=n_Forward_counter/m_Send_counter;

	if (my_Forwarding_Ratio>Neighbor_Forwarding_Ratio)
		return 0;//Discard
	else
		return 1;//Forward
}