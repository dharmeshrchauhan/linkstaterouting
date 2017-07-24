// CommLine.h: interface for the CCommLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMLINE_H__BA9B3FB4_BFAA_4132_8550_C613F9997D57__INCLUDED_)
#define AFX_COMMLINE_H__BA9B3FB4_BFAA_4132_8550_C613F9997D57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include"packet.h"

class CCommLine  
{
private:
	int m_hRead;
	int m_hWrite;
	CPacket m_InBuffer;
	CPacket m_OutBuffer;
	CEvent m_InBufferReady;
	CEvent m_OutBufferReady;
	unsigned long   m_hWriteThread;
	unsigned long   m_hReadThread;

	friend void  RunInputLine(void *dummy);
	friend void  RunOutputLine(void *dummy);

public:

	CCommLine(int hRead, int hWrite);
	virtual ~CCommLine();
	
	CEvent m_ReadyToRead;
	CEvent m_ReadyToWrite;

	void SendOutput(CPacket& pkt);
	bool ReceiveInput(CPacket& pkt);


};

#endif // !defined(AFX_COMMLINE_H__BA9B3FB4_BFAA_4132_8550_C613F9997D57__INCLUDED_)
