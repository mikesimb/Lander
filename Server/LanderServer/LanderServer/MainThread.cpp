#include "stdafx.h"
#include "MainThread.h"

using namespace std;

static CMainThread* g_MainThread;
CMainThread::CMainThread()
{
	InitializeCriticalSection(&PM_CS);
	m_LastProcessMessageNoed = NULL;
	m_TopProcessMessageNode = NULL;
	for (int i = 0; i < 100; i++)
	{
		CLandGameTable * table = new CLandGameTable();
		table->m_TableIndex = i;
		m_TableList.push_back(table);
	}
}


CMainThread::~CMainThread()
{
	DeleteCriticalSection(&PM_CS);
}

void CMainThread::Execute()
{
	while (!Terminated())
	{
		DispachClientMessage();

	}
}

void CMainThread::PushNode(char * Buffer, int BufLen)
{
	EnterCriticalSection(&PM_CS);
	pProcessMessageNode Node = new ProcessMessageNode;
	char * buf = new char[BufLen];
	memmove_s(buf, BufLen, Buffer, BufLen);
	Node->Buffer = buf;
	Node->BufferLen = BufLen;
	Node->next = NULL;
	if ((m_LastProcessMessageNoed == NULL) && (m_TopProcessMessageNode == NULL))
	{
		//这个说明当前的列表是空的
		m_TopProcessMessageNode = Node;
		m_LastProcessMessageNoed = Node;
		
	}
	else
	{
		//说明当前的列表不为空，那么我们需要插入
		if (m_LastProcessMessageNoed != NULL)
		{
			pProcessMessageNode TmpNode = m_LastProcessMessageNoed;
			m_LastProcessMessageNoed = Node;
			TmpNode->next = Node;
		}
		else
		{
			//这里出现的估计就是异常情况了
			if ((m_LastProcessMessageNoed = NULL) || (m_TopProcessMessageNode = NULL))
				OutputDebugString(" Push Node LastNode or TopNode = Null");
			else
				OutputDebugString(" Push Node 未知的异常状况！");
		}
		
	}
	LeaveCriticalSection(&PM_CS);
}

void CMainThread::PopNode()
{
	EnterCriticalSection(&PM_CS);
	//这个队列是弹出最上层的信息；
	if (m_TopProcessMessageNode != NULL)
	{
		
		pProcessMessageNode Node = m_TopProcessMessageNode;
		
		if (m_LastProcessMessageNoed == m_TopProcessMessageNode)
		{
			//这个时候其实里边只有一个消息节点
			m_TopProcessMessageNode = m_LastProcessMessageNoed = NULL;

		}
		else
			Node->next = m_TopProcessMessageNode;
		
		delete(Node->Buffer);
		delete Node;
	}
	LeaveCriticalSection(&PM_CS);
}

void CMainThread::ClearNode()
{
	while (m_TopProcessMessageNode)
	{ 
		PopNode();
	}
}

void CMainThread::DispachClientMessage()
{
	while (m_TopProcessMessageNode)
	{
		pProcessMessageNode Node = m_TopProcessMessageNode;
		pMessageDefault Msg = (pMessageDefault)Node->Buffer;
		switch (Msg->MessageID)
		{
		case CM_FIND_PLACE:
			OnCM_FIND_PLACE(Msg);
			break;
		case CM_USER_READY:
			OnCM_User_Ready(Msg);
			break;
		default:
			break;
		}
// 		if (Msg->MessageID == 1002)
// 		{
// 			OutputDebugString("在这里可以处理找位置的信息了");
// 			//这里需要处理
// 			//Msg->
// 			OnCM_FIND_PLACE(Msg);
// 		
// 		}

		PopNode();
	}
}

CMainThread * CMainThread::getInstance()
{
	if (g_MainThread == NULL)
	{
		g_MainThread = new CMainThread();
		g_MainThread->Initialize();

	}
	return g_MainThread;
}

void CMainThread::OnCM_FIND_PLACE(pMessageDefault Msg)
{
	for (list<CLandGameTable*>::iterator it = m_TableList.begin(); it != m_TableList.end(); it++)
	{
		CLandGameTable* ct = (CLandGameTable*)*it;
		if (ct->getPlayerCount() < 3)
		{
			int Seat = ct->AddPlayer((CUserClient*)Msg->RecogID);		
			if (Seat != -1)
				break;
		}

		if (ct->getPlayerCount() == 3)
		{
			ct->GameStart();
		}

	}

}

void CMainThread::OnCM_User_Ready(pMessageDefault Msg)
{
	CUserClient* client = (CUserClient *)Msg->RecogID;
	if (client->getUserState() == US_IDEL)
		client->setUserState(US_READY);
	else
	if (client->getUserState() == US_READY)
		client->setUserState(US_IDEL);
	client->SendMessageToClient(SM_USER_READY, client->getUserState(), 0);
	//这里需要广播给同桌的人你的状态消息

}
