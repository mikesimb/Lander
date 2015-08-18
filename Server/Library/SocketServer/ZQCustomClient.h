#pragma once
#include <WinSock2.h>
#include "ZQCustomIOCPServer.h"

typedef struct __ClientSendDataNodetag
{
	char * Buf;
	int       buflen;
	int       iStartPosition;
	__ClientSendDataNodetag * Next;

}ClientSendDataNode,*pClientSendData;


class CZQCustomClient
{
	friend class CZQCustomIOCPServer;

public:
	CZQCustomClient();
	virtual ~CZQCustomClient();


	void SetAcitveTick(DWORD dwTick);
	void DoRevice(pBlock data, int buflen);
	void DoSend(pBlock data, int buflen);
	void ReadyReviceNextData(pBlock data);
	void ReadySendNextData(pBlock data, int buflen);
	//这个是为了能够让以后更加自由的处理SOCKETRead消息
	virtual void SocketRead(pBlock data, int buflen);

	void SendBuffer(pBlock block);
	void SendBuffer(char * buffer, int buflen);
	void ForceClose();
	//关闭连接
	void Close();
	//发送队列加入数据
	void AddNode(pBlock data);
	void DeleteBeginNode();
	void ClearNodes();
	SOCKET  getsocket(){ return m_socket; };

	SOCKET getSocket();
	void setSocket(SOCKET socket);

	void setAddress(char * ip);
	char * getAddress();

	HANDLE getIOCPHandle();
	void setIOCPHandle(HANDLE handle);

	void setPort(int port);
	int getPort();


	void ClearReviceData();
	pBlock getReviceData();


private:
	SOCKET    m_socket;
	char         m_address[16];
	int            m_Port;
	HANDLE  m_IOCP;
	Block        m_ReviceData;
	Block        m_SendData;
	//标志，因为是多线程发送，所以，需要有个状态来控制。
	bool         m_IsSending;
	//下边是发送队列的数据
	pClientSendData   m_beginpSendData;
	pClientSendData   m_endSendData;
	int          m_SendNodeCount;

	DWORD m_dwActiveTick;

	CRITICAL_SECTION  m_SendCS;
};

