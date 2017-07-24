 // DropNeighbourTimer.h: interface for the DropNeighbourTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DROPNEIGHBOURTIMER_H__A15CE26A_499B_4A26_B3A5_590A7FA85BFB__INCLUDED_)
#define AFX_DROPNEIGHBOURTIMER_H__A15CE26A_499B_4A26_B3A5_590A7FA85BFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "neighbourhood.h"

class DropNeighbourTimer  
{
public:
	void Stop();
	void Start();
	DropNeighbourTimer( unsigned nIndex, DWORD MaxTime, CNeighbourhood * pNbr);
	DropNeighbourTimer();
	virtual ~DropNeighbourTimer();

private:
	friend UINT DropMonitor(void * pdnt);

	enum {idle, running, resetting} m_Status;
	CWinThread *   m_pthMonitor;
	DWORD		   m_StartTime;         //milliseconds
	CNeighbourhood * m_pNbr;
	DWORD          m_MaxTime;
	unsigned       m_nIndex;      //offset in the m_pNbr
};

#endif // !defined(AFX_DROPNEIGHBOURTIMER_H__A15CE26A_499B_4A26_B3A5_590A7FA85BFB__INCLUDED_)
