// Traffic.h: interface for the CTraffic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAFFIC_H__4C398788_6752_48A0_84DC_A43CA7262EFE__INCLUDED_)
#define AFX_TRAFFIC_H__4C398788_6752_48A0_84DC_A43CA7262EFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


///////////////////////////////////////
#include "Router.h"
///////////////////////////////////////


class CTraffic  : public CObject
{
	DECLARE_SERIAL(CTraffic);
public:
	int				DataRate;
	int				Start;
	int				Protocol;//0=LMAR 1=AOMDV 2=ITAOMDV
	CRouter*		Destination;
	CRouter*		Source;
	void			Serialize(CArchive& ar);
	CTraffic(CRouter* source=NULL,CRouter* destination=NULL,int protocol=0,int start=0);
	virtual ~CTraffic();
};

#endif // !defined(AFX_TRAFFIC_H__4C398788_6752_48A0_84DC_A43CA7262EFE__INCLUDED_)
