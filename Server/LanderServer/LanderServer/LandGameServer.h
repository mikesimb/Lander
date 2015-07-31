#pragma once
#include "ZQCustomIOCPServer.h"
#include "ZQCustomClient.h"


enum CUserState{ US_IDEL, US_READY, US_GAMEING, USGAMEEND };

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

	void SendMessageToClient(DWORD MessageID, DWORD WPARAM, DWORD LPARAM);
	void SendMessageToClient(DWORD MessageID, DWORD WPARAM, char* buffer, int buflen);
	void setUserState(CUserState us);
	CUserState getUserState();
	void SeatIntTable(int tableNumber, int charId);
	void StandUpInTable();
private:
	char * m_ReviceBuffer;
	int   m_ReviceBufferLen;

	CUserState m_UserState;
	int    m_TabaleNumber;//桌子号
	int    m_CharID;//座位号

	void ProcClientMsg(char* Buf, int buflen);
protected:
	virtual void SocketRead(pBlock data, int buflen);
	void initialization();




	

};

