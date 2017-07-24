// Neighbourhood.h: interface for the CNeighbourhood class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEIGHBOURHOOD_H__6ACBDD06_00FC_4032_A630_EF0116C4ACDC__INCLUDED_)
#define AFX_NEIGHBOURHOOD_H__6ACBDD06_00FC_4032_A630_EF0116C4ACDC__INCLUDED_

#include "RouterNodeDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNeighbourhood  
{
private:
	CUIntArray m_anNbr;
	CTypedPtrArray<CObArray, CCriticalSection*>
		       m_acsNbr;
public:
	int m_Self;
	CEvent m_evUpdate;
	int nSize;
	~CNeighbourhood();
	int Retrieve(int nIndex);
	void Update(int nIndex, int nAddr);
	void InitInstance(int argc, char** argv);
	
};



#endif // !defined(AFX_NEIGHBOURHOOD_H__6ACBDD06_00FC_4032_A630_EF0116C4ACDC__INCLUDED_)
