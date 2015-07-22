#pragma once
#include "ZQThread.h"

typedef struct ProcessMessageNode
{

};

class CMainThread :public CZQThread
{
public:
	CMainThread();
	~CMainThread();
public:
	void Execute();

};

