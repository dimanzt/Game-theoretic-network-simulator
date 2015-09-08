#pragma once
#include "afx.h"

#define MEMORY_SIZE 10

class CGame :
	public CObject
{
public:
	int StrategyNum;
//	int pre_maction;
//	int pre_naction;
//	int maction;
//	int naction;
	int m_Actions [MEMORY_SIZE];
	int n_Actions [MEMORY_SIZE];
	int m_Forward_counter;
	int m_Send_counter;
	int n_Send_counter;
	int n_Forward_counter;
	CGame(void);
	~CGame(void);
	int AddmyAction(int action);
	int AddneighborAction(int action);
	int main_strategy(void);
	int TFT_strategy(void);
	int Forwarding_Ratio_strategy(void);
	int ERTFT_strategy(void);
};
