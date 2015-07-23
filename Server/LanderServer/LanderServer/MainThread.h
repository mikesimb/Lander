#pragma once
#include "stdafx.h"
#include "ZQThread.h"
#include "uProtocol.h"
#include "LandGameServer.h"

typedef struct tagProcessMessageNode
{
	char * Buffer;
	int    BufferLen;
	tagProcessMessageNode * next;
}ProcessMessageNode, *pProcessMessageNode;

class CMainThread :public CZQThread
{
public:
	CMainThread();
	~CMainThread();

	CList<CLandGameServer*> m_TableList;

public:
	void Execute();
	void PushNode(char * Buffer,int BufLen);
	void PopNode();
	void ClearNode();
	void DispachClientMessage();
	static CMainThread * getInstance();
private:
	pProcessMessageNode  m_TopProcessMessageNode;
	pProcessMessageNode m_LastProcessMessageNoed;
	CRITICAL_SECTION   PM_CS;
};

