#pragma  once
#include "stdafx.h"

typedef  struct tagMessageHead{
	DWORD Signed;  //Э��ͷǩ��     ����Ϊ0xFF5454;
	DWORD CompressID; //Ŀǰû����δ�������������Ƿ�ѹ��
	DWORD BufferPosition;
	DWORD BufferLen;

}MessageHead,*pMessageHead;

typedef struct  tagMessageDefault
{
	DWORD RecogID;
	DWORD MessageID;
	DWORD WParam;
	DWORD LParam;
}MessageDefault,*pMessageDefault;