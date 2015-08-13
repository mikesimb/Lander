#pragma once
#include <WinSock2.h>
#include <list>
#include <functional>
#include "ZQCommon.h"






#pragma comment(lib,"ws2_32.lib")

#define MAX_BUFFER_LEN     4096
#define DISCONNECT_FLAG   0xFFFFFFFE
#define SHUTDOWN_FLAG    0xFFFFFFFF

typedef enum {ioNone,ioRead,ioWrite}  IoOperator;

typedef struct  __Blocktag
{
	WSAOVERLAPPED  overloapped;
	WSABUF     buf;
	char     MsgBuf[MAX_BUFFER_LEN];
	IoOperator OperatorType;
}Block,*pBlock;

class CZQCustomIOCPServer
{

	friend class CZQAcceptThread;
	friend class CZQWorkThread;
	friend class CZQCustomClient;
public:
	CZQCustomIOCPServer();
	virtual ~CZQCustomIOCPServer();
    
	virtual void Initialize();
	virtual void Finalize();
	int getClientCount();
protected:
	void SocketAccept(SOCKET  s, sockaddr_in addr);
	void FreeClient(CZQCustomClient * client);
	void FreeAllClient();
	void ReleaseFreeClientList();
	void CheckClientActived();	

//	virtual  CZQCustomClient * OnCreateClient();
	OnCreateSocketClientNotifyEvent  m_CreateSocketClient;
	OnSocketConnectNotifyEvent     m_OnClientSocketConnect;
	OnSocketConnectNotifyEvent     m_onClientSocketDisconnect;
	
private:
	 //·þÎñÆ÷µÄ¼àÌýSOCKET;
	SOCKET  m_socket;
	char      m_address[16];
	int         m_port;
	HANDLE   m_hCompletionPort;
	int   m_iWorkThreadCount;
	pBlock   m_pBlock;
	bool m_isRunning;

	CRITICAL_SECTION  m_ClientCS;

	CZQAcceptThread * m_AcceptThread;
	CZQWorkThread ** m_WorkThread;

	std::list<CZQCustomClient * > m_ClientList;
	std::list<CZQCustomClient *> m_FreeClientList;

	
};

