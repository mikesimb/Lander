#pragma once
#include "Card.h"
#include "LandGameServer.h"
class CLandGameTable
{
public:
	CLandGameTable();
	~CLandGameTable();
	CUserClient m_UserList[3];
	bool DoMsg(int num, int action);
	void GameStart();//��Ϸ��ʼ�������ơ�
	//bool MainComputer;//����������������true ������Ϊfalse;
	CCard PlayCards[3][20];//���20����
	int PlayerAc;//��̨�����ϵ����
	int PlayerMain;//����
	CCard OutCards[20];//�ߵ��ƣ�һ��Ҳ����20����
	int OutPlayer;//���Ƶ����
	CCard Sendleft[3];//��¼ʣ�µ�3����
	int Game_State;
	void Updata();
	// -2��Ϸû��ʼ
	// -1��Ϸ׼���У�ѡ����
	// 0-2 ��Ϸ��ҳ���
	// 3-5 ��Ӧ0-2���ʤ��
	int Power;//���㵱ǰ��Ϸ���ũ��ʤ����ÿ�˵õķ�
	int PlayerMaininfo;//��¼�м������ѡ��������� �������������Ϸ����
	void SendCard();	//����
	void SortCard(CCard ca[]);
private:
	//	void SortCard(Card ca[]);
	void CardsInfo(CCard ca[], int &num, int &min, int &type);
	//	void SendCard();	//����
	bool CheckCard(int pl);
	CCard PreOut[20];
};

