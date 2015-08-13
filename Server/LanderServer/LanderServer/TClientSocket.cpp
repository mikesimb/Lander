#include "stdafx.h"
#include "TClientSocket.h"


TClientSocket::TClientSocket()
{
}


TClientSocket::~TClientSocket()
{
}

void TClientSocket::setActived(bool active)
{
	if (active)
	{
		if ((m_Socket != INVALID_SOCKET) || (m_port == 0)
			|| (inet_addr(m_address) == INADDR_NONE))
		{
			return;
		}
		if (m_WorkThread != NULL)
		{
			m_WorkThread->Terminate();
			PostQueuedCompletionStatus(m_IOCP, 0, 0, LPOVERLAPPED(SHUTDOWN_FLAG));
			delete(m_WorkThread);
		}
		ActiveStart();
		m_WorkThread = new CZQWorkThread();
		m_WorkThread->Resume();
	}
	else
	{
		if (m_WorkThread != NULL)
		{
			m_WorkThread->Terminate();
			PostQueuedCompletionStatus(m_IOCP, 0, 0, LPOVERLAPPED(SHUTDOWN_FLAG));
			delete(m_WorkThread);
			ActiveStop();
		}
	}

}

bool TClientSocket::ActiveStart()
{
	bool Result = false;
	sockaddr_in toAddr;
	if ((m_Socket != INVALID_SOCKET) || (m_port = 0) || inet_addr(m_address) == INADDR_NONE)
		return Result;

	m_IOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	if (m_IOCP != 0)
	{
		m_Socket = WSASocket(PF_INET, SOCK_STREAM, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (m_Socket != INVALID_SOCKET)
		{
			
			memset(&toAddr, 0, sizeof(SOCKADDR));
			toAddr.sin_family  = PF_INET;
			WSAHtons(m_Socket, m_port, &toAddr.sin_port);
			toAddr.sin_addr.S_un.S_addr = inet_addr(m_address);
		}
		if (CreateIoCompletionPort((HANDLE)m_Socket, m_IOCP, DWORD(this), 0) == 0)
		{
			m_Socket = INVALID_SOCKET;
			return false;
		}

		int ErrorCode = 0;
		Result = WSAConnect(m_Socket, (sockaddr*)&toAddr, sizeof(toAddr), NULL, NULL, NULL, NULL);

		if (!Result)
		{
			ErrorCode = WSAGetLastError();
			Result = ErrorCode = WSAEWOULDBLOCK;
			if (m_onClientErrorNotify)
				m_onClientErrorNotify(this, ErrorCode);
		}
		else
		{
			if (m_OnClientSocketConnect)
			{
				m_OnClientSocketConnect(this);
			}
			if (m_Socket != INVALID_SOCKET)
			{
				memset()
			}
		}
		
	}


	return Result;
}
