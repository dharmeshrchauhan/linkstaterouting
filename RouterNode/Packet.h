// Packet.h: interface for the CPacket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKET_H__240D18B3_DDD6_4612_9C7A_6B1D4B4A365B__INCLUDED_)
#define AFX_PACKET_H__240D18B3_DDD6_4612_9C7A_6B1D4B4A365B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum packet_type{hello, reply, lst};
typedef int address;

class CPacket  
{
public:

	packet_type m_Type;
	address     m_Source;
	address     m_Dest;

	CPacket();
	CPacket(packet_type Type, int Source );
	virtual ~CPacket();

};

#endif // !defined(AFX_PACKET_H__240D18B3_DDD6_4612_9C7A_6B1D4B4A365B__INCLUDED_)
