#include "stdafx.h"
#include "ZQCustomClient.h"


CZQCustomClient::CZQCustomClient()
{
	m_beginpSendData = NULL;
	m_endSendData = NULL;
	InitializeCriticalSection(&m_SendCS);
	m_IsSending = false;
}


CZQCustomClient::~CZQCustomClient()
{
	closesocket(m_socket);
	ClearNodes();
	DeleteCriticalSection(&m_SendCS);

}

void CZQCustomClient::DoRevice(pBlock data, int buflen)
{
	
	if (buflen > 0)
	{
		data->MsgBuf[buflen + 1] = '#0';
		char str[255];
		sprintf_s(str, 255, "BufferLen is :%d", buflen);
		OutputDebugString(str);
		SocketRead(data, buflen);
		if (m_socket != INVALID_SOCKET)
			ReadyReviceNextData(data);
		
	}
}

void CZQCustomClient::DoSend(pBlock data, int buflen)
{
	int  SendLen = 0;
	// 发送部分一定有个发送的队列
	pClientSendData Node;
	memset(&m_SendData, 0, sizeof(m_SendData));
	while (m_SendNodeCount > 0)
	{
		Node = m_beginpSendData;
		if (Node)
		{
			if ((SendLen + Node->buflen) < 4096)
			{
				memmove_s(Node->Buf, Node->buflen, &m_SendData.MsgBuf, Node->buflen);
				SendLen += Node->buflen;
				DeleteBeginNode();
			}
		}
		if (SendLen >0)
			ReadySendNextData(&m_SendData, SendLen);
	}
}

void CZQCustomClient::ReadyReviceNextData(pBlock data)
{
	DWORD Transfer;
	DWORD flags = 0;
	DWORD ErrorCode;
	data->OperatorType = ioRead;
	data->buf.len = 8*1024;
	data->buf.buf = data->MsgBuf;
	//memset(&pContext->ol, 0, sizeof(pContext->ol));
	memset(&data->overloapped, 0, sizeof(WSAOVERLAPPED));
	if ((m_socket == INVALID_SOCKET) || (WSARecv(m_socket, &data->buf, 1, (LPDWORD)(&Transfer), (LPDWORD)(&flags), (LPWSAOVERLAPPED)&data->overloapped, NULL) == SOCKET_ERROR))
	{
		ErrorCode = GetLastError();
		if (ErrorCode != ERROR_IO_PENDING)
		{
			OutputDebugString("function is Error :CZQCustomClient::ReadReviceData(pBlock data, int buflen) ");
		}
	}
}

void CZQCustomClient::ReadySendNextData(pBlock data, int buflen)
{
	int iSendlen = 0;
	int iRemainLen = 0;
	EnterCriticalSection(&m_SendCS);
	m_IsSending = false;
	pClientSendData node = NULL;
	while (m_beginpSendData)
	{
		node = m_beginpSendData;
		iRemainLen = MAX_BUFFER_LEN - iSendlen;
		int iDatalen = node->buflen - node->iStartPosition;
		if (iDatalen > iRemainLen)
		{
			memmove_s(&data->MsgBuf[iSendlen], iRemainLen, &node->Buf[node->iStartPosition], node->buflen);
			iSendlen = MAX_BUFFER_LEN;
			node->iStartPosition += iRemainLen;
			break;
		}
		else
		{
			memmove_s(&data->MsgBuf[iSendlen], iDatalen, &node->Buf[iSendlen], node->buflen);
			iSendlen += iDatalen;
			m_beginpSendData = node->Next;
			if (m_beginpSendData == NULL)
				m_endSendData = NULL;
			free(node->Buf);
			delete (node);

		}

	}


	if (iSendlen > 0)
	{
		m_IsSending = true;
		//这里需要记录一下总的发送数量。
		int ErrorCode = 0;
		DWORD  Transfer = 0;
		DWORD   flags = 0;
		data->OperatorType = ioWrite;
		data->buf.len = iSendlen;
		data->buf.buf = data->MsgBuf;
		memset(&data->overloapped, 0, sizeof(data->overloapped));
		if ((m_socket == INVALID_SOCKET) || (WSASend(m_socket, &data->buf, 1, &Transfer, flags, &data->overloapped, NULL) == SOCKET_ERROR))
		{
			ErrorCode = WSAGetLastError();
			if (ErrorCode != ERROR_IO_PENDING)
			{
				//发送出错了
				m_IsSending = false;
				Close();
			}
		}
		m_IsSending = false;

	}
	LeaveCriticalSection(&m_SendCS);
	
}

void CZQCustomClient::SocketRead(pBlock data, int buflen)
{
	m_dwActiveTick = GetTickCount();
}

void CZQCustomClient::SendBuffer(pBlock block)
{
	AddNode(block);
	if (!m_IsSending)
		ReadySendNextData(&m_SendData, 0);

}

void CZQCustomClient::SendBuffer(char * buffer, int buflen)
{
	pBlock block = new Block();
	memcpy_s(block->MsgBuf, 4096, buffer, buflen);
	block->OperatorType = ioWrite;
	block->buf.len = buflen;
	SendBuffer(block);
	delete block;
}

void CZQCustomClient::ForceClose()
{
	if (m_socket != INVALID_SOCKET)
	{
		memset(&m_ReviceData, 0, sizeof(m_ReviceData));
		//PostQueuedCompletionStatus(m_IOCP, 0, DWORD(this), (LPOVERLAPPED)DISCONNECT_FLAG);
	}
}

void CZQCustomClient::Close()
{

}

void CZQCustomClient::AddNode(pBlock data)
{
	pClientSendData Node;
	char * Buf;
	int buflen = data->buf.len;
	EnterCriticalSection(&m_SendCS);
	Node = new ClientSendDataNode;
	Buf = (char*)malloc(data->buf.len);
	memset(Buf, 0, data->buf.len);
	memcpy_s(Buf, buflen, data->MsgBuf, buflen);
	Node->Buf = Buf;
	Node->buflen = data->buf.len;
	Node->Next = NULL;
	Node->iStartPosition = 0;
	if (m_beginpSendData == NULL)
	{
		m_beginpSendData = Node;
		m_endSendData = Node;

	}
	else
	if (m_beginpSendData != NULL)
	{
		pClientSendData Node1;
		Node1 = m_endSendData;
		Node1->Next = Node->Next;
		m_endSendData->Next = Node;
	}
	m_SendNodeCount++;
	LeaveCriticalSection(&m_SendCS);

}

void CZQCustomClient::DeleteBeginNode()
{
	pClientSendData node;
	EnterCriticalSection(&m_SendCS);
	node = m_beginpSendData;
	m_beginpSendData = node->Next;
	free(node->Buf);
	delete(node);
	m_SendNodeCount--;
	LeaveCriticalSection(&m_SendCS);
}

void CZQCustomClient::ClearNodes()
{
	pClientSendData Node;
	EnterCriticalSection(&m_SendCS);
	while (m_beginpSendData != NULL)
	{
		Node = m_beginpSendData;
		if (Node !=NULL)
		m_beginpSendData = Node->Next;
		if (m_beginpSendData == NULL)
		{
			m_endSendData = NULL;
		}
		free(Node->Buf);
		delete(Node);
	}
	LeaveCriticalSection(&m_SendCS);
	m_SendNodeCount = 0;
//	m_Sending = false;
}

void CZQCustomClient::SetAcitveTick(DWORD dwTick)
{
	m_dwActiveTick = dwTick;
}

SOCKET CZQCustomClient::getSocket()
{
	return m_socket;
}

void CZQCustomClient::setSocket(SOCKET socket)
{
	m_socket = socket;
}

void CZQCustomClient::setAddress(char * ip)
{
	memcpy_s(&m_address[0], 16, ip, 16);

}

char * CZQCustomClient::getAddress()
{
	return  m_address;
}

HANDLE CZQCustomClient::getIOCPHandle()
{
	return m_IOCP;
}

void CZQCustomClient::setIOCPHandle(HANDLE handle)
{
	m_IOCP = handle;
}

void CZQCustomClient::setPort(int port)
{
	m_Port = port;
}

int CZQCustomClient::getPort()
{
	return m_Port;
}

void CZQCustomClient::ClearReviceData()
{
	memset(&m_ReviceData, 0, sizeof(m_ReviceData));

}

pBlock CZQCustomClient::getReviceData()
{
	return &m_ReviceData;
}


