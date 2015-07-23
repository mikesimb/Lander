#pragma once
#include "ZQThread.h"

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

public:
	void Execute();

private:
	pProcessMessageNode  m_TopProcessMessageNode;
	pProcessMessageNode m_LastProcessMessageNoed;
	CRITICAL_SECTION   PM_CS;

};

