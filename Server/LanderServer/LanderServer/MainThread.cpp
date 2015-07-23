#include "stdafx.h"
#include "MainThread.h"

static CMainThread* g_MainThread;
CMainThread::CMainThread()
{
	InitializeCriticalSection(&PM_CS);
	m_LastProcessMessageNoed = NULL;
	m_TopProcessMessageNode = NULL;
}


CMainThread::~CMainThread()
{
	DeleteCriticalSection(&PM_CS);
}

void CMainThread::Execute()
{
	
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
		//˵����ǰ���б���Ϊ�գ���ô������Ҫ����
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
		if (Msg->MessageID = 1003)
		{
			OutputDebugString("��������Դ�����λ�õ���Ϣ��");

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