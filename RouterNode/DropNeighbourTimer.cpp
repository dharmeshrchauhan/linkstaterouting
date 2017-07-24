// DropNeighbourTimer.cpp: implementation of the DropNeighbourTimer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RouterNode.h"
#include "DropNeighbourTimer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DropNeighbourTimer::DropNeighbourTimer()
{

}

DropNeighbourTimer::~DropNeighbourTimer()
{

}

DropNeighbourTimer::DropNeighbourTimer(unsigned nIndex, DWORD MaxTime, CNeighbourhood *pNbr)
:m_MaxTime(MaxTime), m_pNbr(pNbr), m_nIndex(nIndex)
{
	m_Status = idle;	
}


UINT DropMonitor(void * p)
{
	DropNeighbourTimer * pdnt = (DropNeighbourTimer *) p;

	while(pdnt->m_Status == DropNeighbourTimer::running)
	{
		char temp[50];
//	AfxMessageBox(itoa(GetTickCount() - pdnt->m_StartTime,temp,10));

		if(GetTickCount() - pdnt->m_StartTime  > pdnt->m_MaxTime)
		{
//			AfxMessageBox(itoa(GetTickCount() - pdnt->m_StartTime,temp,10));
			pdnt->m_pNbr->Update(pdnt->m_nIndex, -1);
			pdnt->m_Status = DropNeighbourTimer::idle;

//			AfxMessageBox(itoa(GetTickCount() - pdnt->m_StartTime,temp,10));
		}
	}
	
	ExitThread(0);
	return 0;
}

void DropNeighbourTimer::Start()
{
	if(m_Status == running)
		Stop();
	
	m_StartTime = GetTickCount();
	m_Status    = running;

	m_pthMonitor= AfxBeginThread(DropMonitor, (void *) this);
	m_pthMonitor->m_bAutoDelete = true;
}

void DropNeighbourTimer::Stop()
{
	if(m_Status == idle) return;
	m_Status = idle;

	DWORD exitcode=259;

	while(exitcode == 259)
	{
		GetExitCodeThread(m_pthMonitor->m_hThread , &exitcode);
	//	char temp[50];
	//	AfxMessageBox(itoa(exitcode,temp,10));
	}

//	char temp[50];
//	AfxMessageBox(itoa(exitcode,temp,10));
}