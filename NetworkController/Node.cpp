// Node.cpp: implementation of the CNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NetworkController.h"
#include "Node.h"
#include "Packet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const char RouAppName[] = ".\\r.exe";  
const char CommLineAppName[] = ".\\c.exe";

enum COMMAND{ UP, DOWN, REPORT, SHUTDOWN} ;
enum ACK    { ACKUP, ACKDOWN, ACKREP, ACKSHUTDOWN} ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNode::CNode(CPoint pt, UINT nSelf):m_ahRead(),m_ahWrite()
{
	m_Location = pt;
	m_SELF = nSelf;
	m_Status = UP;
}


CNode::~CNode()
{
	m_ahRead.RemoveAll();
	m_ahWrite.RemoveAll();
}


//////////////////////////////////////////////////////////////////////
// CCommLine Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommLine::CCommLine(CNode * pNode1, CNode * pNode2)
{
	m_pNode1 = pNode1;
	m_pNode2 = pNode2;
}

CCommLine::~CCommLine()
{

}


//This process returns handle to new process
int CNode::Run()
{
	if(m_Status == DOWN)
		return 0;
	
	UINT nSize = 2*m_ahRead.GetSize() + 3;
	char** args = new char*[nSize];
	UINT NodeThread(void * argparam);
	unsigned i;
	for(i=0; i<nSize; i++)
		args[i] = new char[30];
	strcpy(args[0],RouAppName);
	CString str;
	
	str.Format("%u",m_SELF);
	strcpy(args[1],str);

	strcpy(args[2],"999");
	
	for(i=3; i<nSize; i+=2)
	{
		str.Format("%u",(unsigned)m_ahRead[(i-3)/2]);
		strcpy(args[i],str);
		str.Format("%u",(unsigned)m_ahWrite[(i-3)/2]);
		strcpy(args[i+1],str);
	}
    
	args[i] = 0;

	char CmdLine[100] = "";
	for(i=0; args[i+1]!= 0; i++)
	{
		strcat(CmdLine, args[i]);
		strcat(CmdLine, " ");
	}
	strcat(CmdLine, args[i]);

    STARTUPINFO suInfo;
	memset( &suInfo, 0, sizeof(suInfo));
	suInfo.cb = sizeof(suInfo);
//	PROCESS_INFORMATION procInfo ;

/*	
	if (!CreateProcess(args[0],
		          CmdLine,
				  NULL,
				  NULL,
				  TRUE,
				  NORMAL_PRIORITY_CLASS,
				  NULL,
				  "c:",
				  &suInfo,
				  &procInfo))
		 AfxMessageBox("Proccess creation failed",0,0);

*/

	int handle = _spawnv(_P_NOWAIT, args[0], args);
	Sleep(2000);
//		if (!::PostThreadMessage(procInfo.dwThreadId, 0x1010, 0, 0))
//			AfxMessageBox("Message posted successfully",0,0);
//		else
//			AfxMessageBox("Error in posting message",0,0);
	
	
	for(i=0; i<nSize ; i++)
	{
		delete[] args[i];
	}

//	return int(procInfo.hProcess) ;
	return handle;
		
}



void CCommLine::Run()
{
	enum PIPES{READ,WRITE};


//comment out this line to simulate connection line by CommLine application 
#define ____ONLY_PIPES

#if !defined(____ONLY_PIPES)   //CommLine Application is used for links
	

	int  hpipe1C[2], hpipeC1[2],  //Node1 to CL and CL to Node1
		 hpipe2C[2], hpipeC2[2],
		 hpipeNC[2], hpipeCN[2];  //NC to CL and CL to NC
		                          //i.e N = NC, C = CL
	int  pid1, pid2;

	pid1 = _pipe ( hpipe1C, 10*sizeof(CPacket), _O_BINARY);
	ASSERT(pid1 != -1);
	pid2 = _pipe ( hpipeC1, 10*sizeof(CPacket), _O_BINARY);
	ASSERT(pid2 != -1);

	pid1 = _pipe ( hpipe2C, 10*sizeof(CPacket), _O_BINARY);
	ASSERT(pid1 != -1);
	pid2 = _pipe ( hpipeC2, 10*sizeof(CPacket), _O_BINARY);
	ASSERT(pid2 != -1);

	pid1 = _pipe ( hpipeNC, 10*sizeof(CPacket), _O_BINARY);
	ASSERT(pid1 != -1);
	pid2 = _pipe ( hpipeCN, 10*sizeof(CPacket), _O_BINARY);
	ASSERT(pid2 != -1);

	char** args = new char*[11];
	char temp[30];

	unsigned i;
	for(i=0; i<10; i++)
		args[i] = new char[30];

	strcpy(args[0],CommLineAppName);

	strcpy(args[1],"0");

	strcpy(args[2],"0");

	strcpy(args[3], itoa(UP, temp, 10));

	strcpy(args[4], itoa(hpipeNC[READ], temp, 10));

	strcpy(args[5], itoa(hpipeCN[WRITE],temp, 10));

	strcpy(args[6], itoa(hpipe1C[READ], temp, 10));

	strcpy(args[7], itoa(hpipeC1[WRITE],temp, 10));

	strcpy(args[8], itoa(hpipe2C[READ], temp, 10));

	strcpy(args[9], itoa(hpipeC2[WRITE],temp, 10));
	
    
	args[10] = NULL;

	int handle = _spawnv(_P_NOWAIT, args[0], args);

	ASSERT(handle != -1);

	for(i=0; i<11 ; i++)
	{
		delete[] args[i];
	}

	
	m_pNode1->AddNeighbour((HANDLE)hpipeC1[READ], (HANDLE)hpipe1C[WRITE]);
	m_pNode2->AddNeighbour((HANDLE)hpipeC2[READ], (HANDLE)hpipe2C[WRITE]);


#else    
	          //CommLine Application is not used for links

	int  hpipe12[2], hpipe21[2];  //Node1 to Node2 and vice versa
		                          
	int  pid1, pid2;

	pid1 = _pipe ( hpipe12, 10*sizeof(CPacket), _O_BINARY);
	ASSERT(pid1 != -1);
	pid2 = _pipe ( hpipe21, 10*sizeof(CPacket), _O_BINARY);
	ASSERT(pid2 != -1);

	
	m_pNode1->AddNeighbour((HANDLE)hpipe21[READ], (HANDLE)hpipe12[WRITE]);
	m_pNode2->AddNeighbour((HANDLE)hpipe12[READ], (HANDLE)hpipe21[WRITE]);


#endif
}

//////////////////////////////////////////////////////////////////////
// CNetwork Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNetwork::CNetwork():m_apCommLine(),m_apNode()
{

}

CNetwork::~CNetwork()
{
	UINT nNodes, nCommLines,i,nSize;
	nNodes     = m_apNode.GetSize();
	nCommLines = m_apCommLine.GetSize();
	nSize	   = m_aHandle.GetSize();

	for(i=0;i<nNodes;i++)
		delete m_apNode[i];
	
	for(i=0;i<nCommLines;i++)
		delete m_apCommLine[i];

	for(i=0; i<nSize; i++)
		TerminateProcess((void*)m_aHandle[i], 0);

	m_apNode.RemoveAll();
	m_apCommLine.RemoveAll();
	m_aHandle.RemoveAll();
}

void CNetwork::Run()
{
	UINT nCommLines, nNodes, nSize;
	nCommLines = m_apCommLine.GetSize();
	nNodes	   = m_apNode.GetSize();
	
	UINT i,j;

	for(i=0; i<nNodes; i++)
	{
		if( (nSize = m_apNode[i]->m_ahRead.GetSize())
			  == 0)
			  continue;
		
		for(j=0;j<nSize;j++)
		{
			_close((unsigned)m_apNode[i]->m_ahRead[j]);
			_close((unsigned)m_apNode[i]->m_ahWrite[j]);
		}
		m_apNode[i]->m_ahRead.RemoveAll();
		m_apNode[i]->m_ahWrite.RemoveAll();
		TerminateProcess((void*)m_aHandle[i],0);
	}

	for(i=0; i<nCommLines; i++)
		m_apCommLine[i]->Run();

	for(i=0; i<nNodes; i++)
		m_aHandle.Add(m_apNode[i]->Run());

}

UINT nAddr = 1;

void CNetwork::AddNewNode(CPoint pt)
{
	CNode* pNode = new CNode(pt,nAddr++);
	m_apNode.Add(pNode);
}



void CNetwork::AddNewCommLine(UINT nNodeIndex1, UINT nNodeIndex2)
{
	RemoveLine(nNodeIndex1, nNodeIndex2);
	CCommLine* pCommLine = new CCommLine(m_apNode[nNodeIndex1],
										 m_apNode[nNodeIndex2]);
	m_apCommLine.Add(pCommLine);

}



void CNetwork::Draw(CDC *pDC)
{
	UINT nNodes = m_apNode.GetSize();
	UINT nCommLines = m_apCommLine.GetSize();
	UINT i;

	for(i=0;i<nNodes;i++)
	m_apNode[i]->Draw(pDC);

	CPen pen(PS_DOT, 1, RGB(255,0,0));
	CPen* ppen;
	ppen = pDC->SelectObject(&pen);
	
	for(i=0;i<nCommLines;i++)
		m_apCommLine[i]->Draw(pDC);

	pDC->SelectObject(ppen);

}

void CNode::Draw(CDC* pDC)
{
	pDC->Rectangle(m_Location.x - 10 , m_Location.y - 10,
				   m_Location.x + 10 , m_Location.y + 10 );
	char lpsz[10] = " ";
	if(m_SELF < 10)
		itoa(m_SELF, lpsz+1, 10);
	else
		itoa(m_SELF, lpsz, 10);
	pDC->TextOut(m_Location.x-9, m_Location.y-9, lpsz,2);
	
	if(m_Status == DOWN)
	{
		pDC->MoveTo(m_Location.x - 10, m_Location.y - 10);
		pDC->LineTo(m_Location.x + 10, m_Location.y + 10);
		pDC->MoveTo(m_Location.x - 10, m_Location.y + 10);
		pDC->LineTo(m_Location.x + 10, m_Location.y - 10);
	}

}

int CNetwork::NodeClicked(CPoint pt)
{
	int nUBound = m_apNode.GetUpperBound();
	
	for(int i = nUBound; i>=0; i--)
		if(m_apNode[i]->IsClicked(pt))
			return i;
	return -1;
}

bool CNode::IsClicked(CPoint pt)
{
	if( pt.x <= m_Location.x+10 &&
		pt.x >= m_Location.x-10 &&
		pt.y <= m_Location.y+10 &&
		pt.y >= m_Location.y-10)

		return true;
	else
		return false;

}

void CCommLine::Draw(CDC *pDC)
{
	pDC->MoveTo(m_pNode1->m_Location);
	pDC->LineTo(m_pNode2->m_Location);
}

void CNetwork::CloseCommLines()
{
	UINT i,j,nSize,nNodes;
	nNodes = m_apNode.GetSize();
	
	for(i=0;i<nNodes;i++)
	{
		nSize = m_apNode[i]->m_ahRead.GetSize();
		for(j=0;j<nSize;j++)
		{
			_close((unsigned)m_apNode[i]->m_ahRead[j]);
			_close((unsigned)m_apNode[i]->m_ahWrite[j]);
		}
	}
}

void CNetwork::RemoveLine(UINT nIndex1, UINT nIndex2)
{
	ASSERT( nIndex1<m_apNode.GetSize() &&
		    nIndex2<m_apNode.GetSize() );
	UINT nSize = m_apCommLine.GetSize();
	UINT i;
	for(i=0;i<nSize;i++)
		if(m_apCommLine[i]->m_pNode1 == m_apNode[nIndex1] &&
		   m_apCommLine[i]->m_pNode2 == m_apNode[nIndex2] ||
		   m_apCommLine[i]->m_pNode1 == m_apNode[nIndex2] &&
		   m_apCommLine[i]->m_pNode2 == m_apNode[nIndex1] )

		{
			delete m_apCommLine[i];
			m_apCommLine.RemoveAt(i);
			break;
		}
}

void CNetwork::RemoveNode(UINT nIndex)
{
	ASSERT(nIndex<m_apNode.GetSize());

	UINT nSize = m_apCommLine.GetSize();
	UINT i;

	for(i=0;i<nSize;i++)
		if(m_apCommLine[i]->m_pNode1 == m_apNode[nIndex] ||
		   m_apCommLine[i]->m_pNode2 == m_apNode[nIndex] )
		{
			delete m_apCommLine[i];
			m_apCommLine.RemoveAt(i);
			i--; nSize--;
		}
	delete m_apNode[nIndex];
	m_apNode.RemoveAt(nIndex);
}

void CNetwork::NodeDown(UINT nIndex)
{
	ASSERT(nIndex < m_apNode.GetSize());
	
	m_apNode[nIndex]->m_Status = CNode::DOWN;
	TerminateProcess((void*)m_aHandle[nIndex], 0);
}



void CNetwork::NodeUp(UINT nIndex)
{
	if(m_apNode[nIndex]->m_Status == CNode::UP)
		return;
	m_apNode[nIndex]->m_Status = CNode::UP;
	m_aHandle[nIndex] = m_apNode[nIndex]->Run();
}
