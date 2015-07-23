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
		pMessageHead  MsgHead = (pMessageHead)&data->MsgBuf[0];
		pMessageDefault Msg = (pMessageDefault)(&data->MsgBuf[MsgHead->BufferPosition]);
		if (Msg->MessageID == 1002)
		{
			Msg->RecogID = (DWORD)this;
			CMainThread::getInstance()->PushNode((char *)Msg, buflen-sizeof(MessageHead));
			OutputDebugString("这是我收到的找座位的信息");
		}

	}
}

void CUserClient::initialization()
{

}

void CUserClient::SendMessageToClient(DWORD MessageID, DWORD WPARAM, DWORD LPARAM)
{
	MessageDefault msg; 
	msg.MessageID = MessageID;
	msg.WParam = WPARAM;
	msg.LParam = LPARAM;
	msg.RecogID = (DWORD)this;

	MessageHead msgHead;
	msgHead.Signed = 0xFF545454;
	msgHead.CompressID = 0;
	msgHead.BufferPosition = sizeof(MessageHead);
	msgHead.BufferLen = sizeof(MessageDefault);
	int buflen = sizeof(MessageHead)+sizeof(MessageDefault);
	char * buf = new char[buflen];
	memmove_s(buf, sizeof(MessageHead), &msgHead, sizeof(MessageHead));
	char * tmpbuf = (char*)(buf + sizeof(MessageHead));
	memmove_s(tmpbuf, sizeof(MessageDefault), &msg, sizeof(MessageDefault));
	SendBuffer(buf, buflen);
	delete buf;

}
