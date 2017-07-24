// Node.h: interface for the CNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NODE_H__4CD36ECD_F28D_4E7F_8619_C6B19F785028__INCLUDED_)
#define AFX_NODE_H__4CD36ECD_F28D_4E7F_8619_C6B19F785028__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNode 
{
public:
	bool IsClicked(CPoint pt);
	void Draw(CDC *pDC);
//	CNode();
	int Run();
	CNode(CPoint pt, UINT nSelf);
	virtual ~CNode();
	void AddNeighbour(HANDLE hRead, HANDLE hWrite);
	friend class CCommLine;
	friend class CNetwork;
//	CNode& operator=(const CNode * Node);
//	CNode* operator->()
//	{  return this; }

protected:
	CPoint	    m_Location;
	int		    m_SELF;
	CPtrArray  m_ahRead ;
	CPtrArray  m_ahWrite;
	enum STATUS{UP,DOWN} m_Status;
};


class CCommLine  
{
public:
	void Draw(CDC * pDC);
//	CCommLine();
	void Run();
	CCommLine(CNode *, CNode *);
	virtual ~CCommLine();
	friend class CNetwork;
//	CCommLine* operator->()
//	{ return this; }

protected:
	CNode* m_pNode1;
	CNode* m_pNode2;

};

#endif // !defined(AFX_NODE_H__4CD36ECD_F28D_4E7F_8619_C6B19F785028__INCLUDED_)



inline void CNode::AddNeighbour(HANDLE hRead, HANDLE hWrite)
{
	m_ahRead.Add(hRead);
	m_ahWrite.Add(hWrite);
}


class CNetwork  
{
public:
	void NodeUp(UINT nIndex);
	void NodeDown(UINT nIndex);
	void RemoveNode(UINT nIndex);
	void RemoveLine(UINT nIndex1, UINT nIndex2);
	void CloseCommLines();
	int  NodeClicked(CPoint pt);
	void Draw(CDC* pDC);
	void AddNewCommLine(UINT nNodeIndex1, UINT nNodeIndex2);
	void AddNewNode(CPoint pt);
	void Run();
	CNetwork();
	virtual ~CNetwork();
	
protected:
	CTypedPtrArray<CPtrArray, CNode*>	   m_apNode;
	CTypedPtrArray<CPtrArray, CCommLine*>  m_apCommLine;
	CUIntArray							   m_aHandle;
};

/*

inline 	CNode& CNode::operator=(const CNode* Node)
{
	m_Location = Node->m_Location;
	m_SELF     = Node->m_SELF;
	m_ahRead.RemoveAll();
	m_ahRead.Copy(Node->m_ahRead);
	m_ahWrite.RemoveAll();
	m_ahWrite.Copy(Node->m_ahWrite);
	return *this;
}

 */