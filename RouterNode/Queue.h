// Queue.h: interface for the CQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUEUE_H__2C12AFCF_5300_4FCA_8402_3AA26BBE50F0__INCLUDED_)
#define AFX_QUEUE_H__2C12AFCF_5300_4FCA_8402_3AA26BBE50F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include"packet.h"

class CQueue  
{
public:
	CQueue();
	virtual ~CQueue();

private:
	CCriticalSection cs;
	CTypedPtrArray<CPtrArray, CPacket*> p;

public:
	int Insert(CPacket &pack);
    int Retrieve(CPacket &pack);
};

#endif // !defined(AFX_QUEUE_H__2C12AFCF_5300_4FCA_8402_3AA26BBE50F0__INCLUDED_)
