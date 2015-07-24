#pragma once
#include "stdafx.h"
#include "ZQThread.h"
#include "uProtocol.h"
#include "LandGameTable.h"
#include <list>

using namespace std;

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

	list<CLandGameTable*> m_TableList;

public:
	void Execute();
	void PushNode(char * Buffer,int BufLen);
	void PopNode();
	void ClearNode();
	void DispachClientMessage();
	void OnCM_FIND_PLACE(pMessageDefault Msg);
	void OnCM_User_Ready(pMessageDefault Msg);
	static CMainThread * getInstance();
private:
	pProcessMessageNode  m_TopProcessMessageNode;
	pProcessMessageNode m_LastProcessMessageNoed;
	CRITICAL_SECTION   PM_CS;
};

