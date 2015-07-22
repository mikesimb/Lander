#pragma once
#include "ZQCustomIOCPServer.h"
#include "ZQCustomClient.h"


class CLandGameServer :public CZQCustomIOCPServer
{
public:
	CLandGameServer();
	virtual ~CLandGameServer();

	static CLandGameServer* getInstance();
private:

public:
	//斗地主的主要SERVER
	void onClientSocketConnect(CZQCustomClient* Socket);
	void onClientSocketDisconnect(CZQCustomClient * Socket);
	void onClientSocketError(CZQCustomClient * socket, int ErrorCode);
	bool ClientCheckIpAddress(char * IP);
	CZQCustomClient* onCreateClientSocket();

};

class CUserClient :public CZQCustomClient
{
public:
	CUserClient();
	virtual ~CUserClient();
private:
	char * m_ReviceBuffer;
	int   m_ReviceBufferLen;

	void ProcClientMsg(char* Buf, int buflen);
protected:
	virtual void SocketRead(pBlock data, int buflen);
	void initialization();

};

