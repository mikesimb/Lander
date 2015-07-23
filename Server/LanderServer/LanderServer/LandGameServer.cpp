#include "stdafx.h"
#include "LandGameServer.h"
#include <functional>  
#include "uProtocol.h"
#include "MainThread.h"


static CLandGameServer* global_server;

CLandGameServer::CLandGameServer()
{
	//m_CreateSocketClient = std::bind(&CLandGameServer::onCreateClientSocket,this);
	m_CreateSocketClient = std::bind(&CLandGameServer::onCreateClientSocket, this);
	m_OnClientSocketConnect = std::bind(&CLandGameServer::onClientSocketConnect, this, std::placeholders::_1);
}


CLandGameServer::~CLandGameServer()
{
}

void CLandGameServer::onClientSocketConnect(CZQCustomClient* Socket)
{
	Socket->SendBuffer("who are you", 11);
	
}

CLandGameServer* CLandGameServer::getInstance()
{
	if (global_server == NULL)
	{
		global_server = new CLandGameServer();

	}
	return global_server;
}

CZQCustomClient* CLandGameServer::onCreateClientSocket()
{
	return new CUserClient;
}

CUserClient::CUserClient()
{

}

CUserClient::~CUserClient()
{

}

void CUserClient::ProcClientMsg(char* Buf, int buflen)
{

}

void CUserClient::SocketRead(pBlock data, int buflen)
{
	if (buflen > 0)
	{
		pMessageHead  MsgHead = (pMessageHead)data->buf.buf;
		pMessageDefault Msg = (pMessageDefault)(MsgHead + MsgHead->BufferPosition);
		if (Msg->MessageID = 1003)
		{
			Msg->RecogID = (DWORD)this;
			CMainThread::getInstance()->PushNode((char *)Msg, sizeof(MsgHead->BufferLen-sizeof(MessageHead)));
			OutputDebugString("这是我收到的找座位的信息");
		}

	}
}

void CUserClient::initialization()
{

}
