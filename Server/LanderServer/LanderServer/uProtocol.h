#pragma  once
#include "stdafx.h"
#pragma  pack(4)
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
#pragma  pack()


#define  CM_FIND_PLACE 1002
#define  SM_FIND_PLACE 1003
#define  CM_USER_READY 1004
#define  SM_USER_READY 1005