enum packet_type{hello, reply, lst};
typedef int address;

class CPacket  
{
public:

	packet_type m_Type;
	address     m_Source;
	address     m_Dest;
};

