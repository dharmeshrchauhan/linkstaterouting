// InputOutput.cpp: implementation of the CInputOutput class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RouterNode.h"
#include "InputOutput.h"
#include "Neighbourhood.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInputOutput::CInputOutput()
{

}

void CInputOutput::InitInstance(int argc, char** argv)
{
	if(argc<5 || argc%2 == 0)
		exit(0);

	m_Self = atoi(argv[1]);
	CCommLine * pCL;
	for(int i=3; i<argc; i+=2)
	{
		pCL = new CCommLine(atoi(argv[i]),atoi(argv[i+1]));
		m_apCommLine.Add(pCL);
	}
	
//	ASSERT(0);
	CWinThread* pThread = (AfxBeginThread(HandleInputPackets,
										 (void*)this));
	m_hThread = (int)pThread->m_hThread;
}

UINT HandleInputPackets(void * pInputOutput)
{
//	ASSERT(0);
	CInputOutput * pIO = (CInputOutput*)pInputOutput;
	int nSize = pIO->m_apCommLine.GetSize();
	CPacket pkt;
//	CString str;	
	int pktcnt = 0;
	extern CNeighbourhood Nbr;
	while(1)
	for(int i=0;i<nSize;i++)
	{
		if( ! pIO->m_apCommLine[i]->ReceiveInput(pkt))
			continue;
//		str.Format("Self: %d, Line: %d, Count: %d",pIO->m_Self,i,
//												   ++pktcnt);
//5		AfxMessageBox(str,1,0); 
		switch(pkt.m_Type)
		{
		case reply:
			Nbr.Update(i , pkt.m_Source);
			break;

		case hello:
			CPacket pkt(reply,pIO->m_Self);
			pIO->m_apCommLine[i]->SendOutput(pkt);
		}
	}

	return 0;	
}


CInputOutput::~CInputOutput()
{
	int nSize = m_apCommLine.GetSize();
	for(int i=0;i<nSize;i++)
		delete m_apCommLine[i];
	m_apCommLine.RemoveAll();
	TerminateThread((void*)m_hThread,0);
}


/////////////////////////////////////////////////////////
CInputOutput IO;
/////////////////////////////////////////////////////////

void CInputOutput::SendHello()
{
	CPacket pkt(hello, m_Self);
	ASSERT(pkt.m_Source == m_Self);
	int nSize = m_apCommLine.GetSize();
	for(int i=0; i<nSize; i++)
		m_apCommLine[i]->SendOutput(pkt);
}