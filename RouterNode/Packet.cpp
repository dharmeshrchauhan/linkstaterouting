// Packet.cpp: implementation of the CPacket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RouterNode.h"
#include "Packet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPacket::CPacket()
{}

CPacket::CPacket(packet_type Type, int Source)
{
	m_Type = Type;
	m_Source = Source;
}


CPacket::~CPacket()
{

}
