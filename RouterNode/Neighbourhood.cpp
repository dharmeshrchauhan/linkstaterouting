// Neighbourhood.cpp: implementation of the CNeighbourhood class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RouterNode.h"
#include "Neighbourhood.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#include "DropNeighbourTimer.h"
CTypedPtrArray<CPtrArray, DropNeighbourTimer*>
		       aNbrTimer;

//////////////////////////////////////////////////////////////////////
// Construction
//////////////////////////////////////////////////////////////////////


void CNeighbourhood::InitInstance(int argc, char** argv)
{
	ASSERT(argc>4 && argc%2);
	nSize = (argc-3)/2;

	m_Self = atoi(argv[1]);
	CCriticalSection *pcs;
	for(int i=0; i<nSize; i++)
	{
		m_anNbr.Add(-1);
		pcs = new CCriticalSection;
		m_acsNbr.Add(pcs);
		aNbrTimer.Add( new DropNeighbourTimer(i, 120000, this) );
	}

}

CNeighbourhood::~CNeighbourhood()
{
	for(int i=0; i<nSize; i++)
	{
		delete m_acsNbr[i];
		delete aNbrTimer[i];
	}
	m_acsNbr.RemoveAll();
	m_anNbr.RemoveAll();
	aNbrTimer.RemoveAll();
}

///////////////////////////////////////////////////////////////
CNeighbourhood Nbr;
///////////////////////////////////////////////////////////////

void CNeighbourhood::Update(int nIndex, int nAddr)
{
	ASSERT(nIndex < nSize);

	if(nAddr != -1)     // We don't need to set timer if 
						// neighbour is being dropped
	{
		aNbrTimer[nIndex]->Start();
	}
	
	m_acsNbr[nIndex]->Lock();

	if(m_anNbr[nIndex] == nAddr)
	{
		m_acsNbr[nIndex]->Unlock();
		return;
	}
	m_anNbr[nIndex] = nAddr;
	m_acsNbr[nIndex]->Unlock();
	m_evUpdate.SetEvent();

}

int CNeighbourhood::Retrieve(int nIndex)
{
	ASSERT(nIndex < nSize);
	int temp;
	m_acsNbr[nIndex]->Lock();
	temp = m_anNbr[nIndex];
	m_acsNbr[nIndex]->Unlock();
	return temp;
}