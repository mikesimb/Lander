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
		//���˵����ǰ���б��ǿյ�
		m_TopProcessMessageNode = Node;
		m_LastProcessMessageNoed = Node;
		
	}
	else
	{
		//˵����ǰ���б�Ϊ�գ���ô������Ҫ����
		if (m_LastProcessMessageNoed != NULL)
		{
			pProcessMessageNode TmpNode = m_LastProcessMessageNoed;
			m_LastProcessMessageNoed = Node;
			TmpNode->next = Node;
		}
		else
		{
			//������ֵĹ��ƾ����쳣�����
			if ((m_LastProcessMessageNoed = NULL) || (m_TopProcessMessageNode = NULL))
				OutputDebugString(" Push Node LastNode or TopNode = Null");
			else
				OutputDebugString(" Push Node δ֪���쳣״����");
		}
		
	}
	LeaveCriticalSection(&PM_CS);
}

void CMainThread::PopNode()
{
	EnterCriticalSection(&PM_CS);
	//��������ǵ������ϲ����Ϣ��
	if (m_TopProcessMessageNode != NULL)
	{
		
		pProcessMessageNode Node = m_TopProcessMessageNode;
		
		if (m_LastProcessMessageNoed == m_TopProcessMessageNode)
		{
			//���ʱ����ʵ���ֻ��һ����Ϣ�ڵ�
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
		if (Msg->MessageID == 1002)
		{
			OutputDebugString("��������Դ�����λ�õ���Ϣ��");
			//������Ҫ����
			//Msg->
			for (list<CLandGameTable*>::iterator it = m_TableList.begin(); it != m_TableList.end(); it++)
			{
				CLandGameTable* ct = (CLandGameTable*)*it;
				if (ct->getPlayerCount() < 3)
				{
					int Seat = ct->AddPlayer((CUserClient*)Msg->RecogID);
					int tIndex = ct->m_TableIndex;
					//������Ϣ���ͻ���
					CUserClient * client = (CUserClient*)Msg->RecogID;
					client->SendMessageToClient(1002, tIndex, Seat);

				}
				
			}

		}
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
