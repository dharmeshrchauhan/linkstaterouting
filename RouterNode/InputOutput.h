// InputOutput.h: interface for the CInputOutput class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INPUTOUTPUT_H__AF286DBB_B93F_4653_B284_2C62767C884A__INCLUDED_)
#define AFX_INPUTOUTPUT_H__AF286DBB_B93F_4653_B284_2C62767C884A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include"CommLine.h"
#include"Packet.h"

class CInputOutput  
{
private:
	CTypedPtrArray<CPtrArray,CCommLine*> m_apCommLine;
public:
	int m_Self;
	CInputOutput();
	int m_hThread;
	friend UINT HandleInputPackets(void* pInputOutput);
	void SendHello();
	void InitInstance(int argc, char** argv);
	virtual ~CInputOutput();
};

#endif // !defined(AFX_INPUTOUTPUT_H__AF286DBB_B93F_4653_B284_2C62767C884A__INCLUDED_)
