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
	m_UserState = US_IDEL;
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
		Msg->RecogID = (DWORD)this;
		CMainThread::getInstance()->PushNode((char *)Msg, buflen - sizeof(MessageHead));

// 		if (Msg->MessageID == 1002)
// 		{
// 			OutputDebugString("这是我收到的找座位的信息");
// 			//SendBuffer("who are you", 11);
// 		}

	}
}

void CUserClient::initialization()
{

}
void CUserClient::SendMessageToClient(DWORD MessageID, DWORD WPARAM, char* buffer, int buflen)
{
	MessageDefault msg;
	msg.MessageID = MessageID;
	msg.WParam = WPARAM;
	msg.LParam = buflen;
	msg.RecogID = (DWORD)this;

	MessageHead msgHead;
	msgHead.Signed = 0xFF545454;
	msgHead.CompressID = 0;
	msgHead.BufferPosition = sizeof(MessageHead);
	msgHead.BufferLen = sizeof(MessageDefault);
	int len = sizeof(MessageHead)+sizeof(MessageDefault)+buflen;
	char * buf = new char[len];
	memmove_s(buf, sizeof(MessageHead), &msgHead, sizeof(MessageHead));
	char * tmpbuf = (char*)(buf + sizeof(MessageHead));
	memmove_s(tmpbuf, sizeof(MessageDefault), &msg, sizeof(MessageDefault));
	tmpbuf = tmpbuf + sizeof(MessageDefault);
	memmove_s(tmpbuf, buflen, buffer, buflen);
	SendBuffer(buf, len);
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

void CUserClient::setUserState(CUserState us)
{
	m_UserState = us;
}

CUserState CUserClient::getUserState()
{
	return m_UserState;
}
