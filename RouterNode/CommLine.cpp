// CommLine.cpp: implementation of the CCommLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RouterNode.h"
#include "CommLine.h"
#include "Queue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommLine::CCommLine(int hRead, int hWrite):
m_hRead(hRead),
m_hWrite(hWrite)
{
	void RunOutputLine(void *pCommLine);
	void RunInputLine (void *pCommLine);

	m_hReadThread  = _beginthread(RunInputLine,0,(void*)this);
	m_hWriteThread = _beginthread(RunOutputLine, 0, (void*)this );
	m_ReadyToWrite.SetEvent();  
	m_InBufferReady.SetEvent(); 
		
}

CCommLine::~CCommLine()
{
	TerminateThread((void*)m_hReadThread,0);
	TerminateThread((void*)m_hWriteThread,0);
}

void  RunOutputLine(void *pCommLine)
{
	CCommLine* pCL = (CCommLine*)pCommLine;
	while(1)
	{
		pCL->m_OutBufferReady.Lock();      //buffer empty
		ASSERT((pCL->m_OutBuffer).m_Source == atoi(__argv[1]));

		if(write(pCL->m_hWrite, &(pCL->m_OutBuffer), 
				  sizeof(CPacket)))
		{
			pCL->m_ReadyToWrite.SetEvent();

#ifdef _DEBUG
//			static int mbRetCode;
//			CString str;
//			str.Format("%d",(pCL->m_InBuffer).m_Source);
//			ASSERT(pCL->m_OutBuffer.m_Source < 10);
//			if(mbRetCode != IDOK)
//				mbRetCode =	AfxMessageBox(str,
//				             0,
//						     -1);
#endif
		}
	}
}

void  RunInputLine(void *pCommLine)
{
	extern CQueue Qin;
	CCommLine *pCL = (CCommLine*)pCommLine;
	while(1)
	{
		pCL->m_InBufferReady.Lock();
		Sleep(500);
		if(read(pCL->m_hRead, &(pCL->m_InBuffer), sizeof(CPacket)))
		{
			if((pCL->m_InBuffer).m_Source <0 || 
				(pCL->m_InBuffer).m_Source > 100)
			{
		//		AfxMessageBox("loop skipped");
		//		continue;
			}
#ifdef _DEBUG
//			static int mbRetCode;
//			CString str;
//			str.Format("%u",(pCL->m_InBuffer).m_Source);
//			ASSERT((pCL->m_InBuffer).m_Source < 10);
			//if(mbRetCode != IDOK)
			//	mbRetCode =	AfxMessageBox(str,
			//	             MB_OK | MB_ICONINFORMATION,
			//			     -1);
#endif
			CPacket pkt = pCL->m_InBuffer;
//			Qin.Insert(pkt);
			pCL->m_ReadyToRead.SetEvent();
		}
	}
}



bool CCommLine::ReceiveInput(CPacket &pkt)
{
	if(m_ReadyToRead.Lock(10000L))
	{
		pkt = m_InBuffer;
		m_InBufferReady.SetEvent();
		return true;
	}
	else
		return false;
}

void CCommLine::SendOutput(CPacket &pkt)
{
	m_ReadyToWrite.Lock();
	m_OutBuffer = pkt;
	m_OutBufferReady.SetEvent();
}


