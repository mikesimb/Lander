#pragma once
#include "ZQCustomClient.h"
#include "ZQCommon.h"
#include "ZQWorkThread.h"
class CZQClientSocket
{
private:
	CZQCustomClient * m_CustomClient;
	CZQWorkThread * m_WorkThread;

public:
	CZQClientSocket();
	~CZQClientSocket();

	//����IP��ַ
	//���ö˿ں�
	//����
};

