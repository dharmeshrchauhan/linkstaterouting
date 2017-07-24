// Queue.cpp: implementation of the CQueue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RouterNode.h"
#include "Queue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CQueue Qin;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CQueue::CQueue()
{

}

CQueue::~CQueue()
{
	int nSize = p.GetSize();
	for(int i=0; i<nSize; i++)
		delete p[i];
	p.RemoveAll();
}

int CQueue::Insert(CPacket &pkt)
{
	CPacket* ptemp = new CPacket;
	*ptemp = pkt;
	
	try
	{
	cs.Lock();
	p.Add(ptemp);
	cs.Unlock();
	return 1;
	}
	catch(CMemoryException meDummy)
	{
		return 0;
	}

}


int CQueue::Retrieve(CPacket &pkt)
{
	cs.Lock();
	if(!p.GetSize())
	{
		cs.Unlock();
		return 0;
	}
	
	pkt = *(p.GetAt(0));
	p.RemoveAt(0,1);
	return 1;
}
