#pragma once
#include "ZQCommon.h"
#include "ZQWorkThread.h"
#include "ZQCustomClient.h"
class TClientSocket
{
private:
	CZQCustomClient ActiveSocket;

	HANDLE m_IOCP;
	SOCKET m_Socket;
	char      m_address[16];
	int       m_port;
	bool      m_Active;


	CZQWorkThread * m_WorkThread;
	onClientSocketDisConnectNotifyEvent      m_OnClientSocketConnect;
	onClientSocketConnectNotifyEvent         m_onClientSocketDisconnect;
	onClientErrorNotifyEvent                 m_onClientErrorNotify;
protected:
	bool ActiveStart();
	void ActiveStop();

public:
	TClientSocket();
	virtual ~TClientSocket();
	void setServerPort(int port);
	int  getServerPort();

	void setServerIP(char * IP);
	char * getServerIP();

	bool getActived();
	void setActived(bool active);


};

