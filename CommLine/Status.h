// Status.h: interface for the CStatus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUS_H__EEB9A92A_5F7F_433D_90B7_26D1EB72AC91__INCLUDED_)
#define AFX_STATUS_H__EEB9A92A_5F7F_433D_90B7_26D1EB72AC91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


enum COMMAND{ UP, DOWN, REPORT, SHUTDOWN} ;
enum ACK    { ACKUP, ACKDOWN, ACKREP, ACKSHUTDOWN} ;

class CStatus  
{
	COMMAND m_Status;
	CCriticalSection cs;

public:
	CStatus();
	COMMAND Get();
	void Set(COMMAND com);
	virtual ~CStatus();

};


inline CStatus::CStatus()
{
   m_Status = UP;
}

inline void CStatus::Set(COMMAND com)
{
	cs.Lock();
	m_Status = com;
	cs.Unlock();
}

inline COMMAND CStatus::Get()
{
	cs.Lock();
	COMMAND temp = m_Status;
	cs.Unlock();
	return temp;
}
#endif // !defined(AFX_STATUS_H__EEB9A92A_5F7F_433D_90B7_26D1EB72AC91__INCLUDED_)
