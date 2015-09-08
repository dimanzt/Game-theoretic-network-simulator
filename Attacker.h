// Attacker.h: interface for the CAttacker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATTACKER_H__64369166_BB97_43CF_9757_EBE84B9E1427__INCLUDED_)
#define AFX_ATTACKER_H__64369166_BB97_43CF_9757_EBE84B9E1427__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Router.h"

class CAttacker : public CRouter  
{
public:
	void ProcessDataPacket(CPacket* packet){}
	CAttacker();
	virtual ~CAttacker();

};

#endif // !defined(AFX_ATTACKER_H__64369166_BB97_43CF_9757_EBE84B9E1427__INCLUDED_)
