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
	void GameStart();//游戏初始化，发牌。
	//bool MainComputer;//主机，是主机则是true 不是则为false;
	CCard PlayCards[3][20];//最多20张牌
	int PlayerAc;//这台机器上的玩家
	int PlayerMain;//地主
	CCard OutCards[20];//走的牌，一次也最多出20张牌
	int OutPlayer;//走牌的玩家
	CCard Sendleft[3];//记录剩下的3张牌
	int Game_State;
	void Updata();
	// -2游戏没开始
	// -1游戏准备中，选地主
	// 0-2 游戏玩家出牌
	// 3-5 对应0-2玩家胜利
	int Power;//计算当前游戏如果农民胜利则每人得的分
	int PlayerMaininfo;//记录有几个玩家选择放弃地主 如果都放弃则游戏结束
	void SendCard();	//发牌
	void SortCard(CCard ca[]);
private:
	//	void SortCard(Card ca[]);
	void CardsInfo(CCard ca[], int &num, int &min, int &type);
	//	void SendCard();	//发牌
	bool CheckCard(int pl);
	CCard PreOut[20];
};

