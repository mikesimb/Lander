#include "stdafx.h"
#include "LandGameTable.h"
#include "uProtocol.h"


CLandGameTable::CLandGameTable()
{
	Game_State = -2;
	for (int i = 0; i < 3; i++)
	{
		m_UserList[i] = NULL;
	}
}


CLandGameTable::~CLandGameTable()
{
}


void CLandGameTable::GameStart()
{
	int k;
	for (k = 0; k < 20; k++)
		PlayCards[1][k].Click = false;
	for (k = 0; k < 3; k++)
		Sendleft[k].Click = true;

	Power = 10;
	OutCards[0].Num = 16;
	PlayerMaininfo = 0;
	SendCard();
	PlayerMain = rand() % 3;
	Game_State = -1;
}

bool CLandGameTable::CheckCard(int pl)
{
	CCard *Ca = PlayCards[pl];//用Ca 指针来代替Player[pl]，使程序简单容易理解
	int i, j;
	int num1, min1, type1;
	int num2, min2, type2;
	j = 0;
	for (i = 0; i < 20 && Ca[i].Num <= 15; i++)
	if (Ca[i].Click)
	{
		PreOut[j] = Ca[i];
		j++;
	}
	if (j == 0)
		return false;
	else if (j != 20)
	{
		PreOut[j].Num = 16;//表示此后的都没有牌了
	}
	Ca = PreOut;//现在把CA指到这里
	CardsInfo(Ca, num2, min2, type2);
	if (OutCards[0].Num == 16)//上次没有人走牌
	{
		if ((type2 == 4 && num2 == 4) || type2 == 5)
			Power *= 2;
		if (type2 != 0)
			return true;
	}
	if (OutPlayer == PlayerAc)//上次走牌的人 OutPlayer就是自己，那么自己可以随便走什么
	{//改变
		if ((type2 == 4 && num2 == 4) || type2 == 5)
			Power *= 2;
		if (type2 != 0)
			return true;
	}
	if (type2 == 0)
		return false;
	CardsInfo(OutCards, num1, min1, type1);
	if (type1 == 5)//双鬼
		return false;
	if (type2 == 5)
	{
		Power *= 2;
		return true;
	}
	if (type1 == 4 && type2 == 4)
	{
		if (num2 == num1)
		{
			if (min1 < min2)
			{
				if (num1 == 4)
					Power *= 2;
				return true;
			}
			else
				return false;
		}
	}
	if (num2 == 4 && type2 == 4)
	{
		Power *= 2;
		return true;
	}
	if (type2 == type1)
	{
		if (num1 == num2)
		{
			if (min1 < min2)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	return false;
}


void CLandGameTable::SendCard()
{
	int i, j, k;
	bool Cards[55] = { false };	//对应54张扑克,其中Cards[54]做初始化用 必须为true;
	//其中0-51为4个1-13 52是小王 53是大王
	Cards[54] = true;
	for (j = 0; j < 17; j++)
	for (i = 0; i < 3; i++)
	{
		CCard &Ca = PlayCards[i][j];
		k = 54;//保证必进入While循环进行随机
		while (Cards[k])
			k = rand() % 54;
		Cards[k] = true;
		Ca.Click = false;
		if (k == 53 || k == 52)
		{
			Ca.Num = k - 38;
			Ca.Pow = k - 38;
			Ca.Type = 4;
			Ca.Click = false;
		}
		else
		{
			Ca.Click = false;
			Ca.Num = k % 13 + 1;
			Ca.Type = k / 13;
			if (Ca.Num == 1 || Ca.Num == 2)
				Ca.Pow = Ca.Num + 11;
			else
				Ca.Pow = Ca.Num - 2;
		}
	}
	i = 0;
	for (k = 0; k < 54; k++)
	if (!Cards[k])
	{
		CCard &Ca = Sendleft[i];
		i++;
		if (k == 53 || k == 52)
		{
			Ca.Num = k - 38;
			Ca.Pow = k - 38;
			Ca.Type = 4;
			Ca.Click = true;
		}
		else
		{
			Ca.Num = k % 13 + 1;
			Ca.Type = k / 13;
			Ca.Click = true;
			if (Ca.Num == 1 || Ca.Num == 2)
				Ca.Pow = Ca.Num + 11;
			else
				Ca.Pow = Ca.Num - 2;
		}
	}
	Sendleft[i].Num = 16;
	PlayCards[0][17].Num = 16;
	PlayCards[1][17].Num = 16;
	PlayCards[2][17].Num = 16;

}
////////////////////////////////////////////////////////////////////////
/*
* 函数名称：DoMSG(	int num		//第几的一张牌
int action)	//行为
* 函数介绍：消息响应
* 输入参数：action含义
1点牌  3放弃出牌 4出牌（或接受当地主）
* 输出参数：bool
* 返回值  ：true 表示响应成功 false为失败
*/
bool CLandGameTable::DoMsg(int num, int action)
{

	if (action == 1)//唯一用得到前面1个参数的地方
	{
		CCard &Ca = PlayCards[PlayerAc][num];
		if (Ca.Click)
			Ca.Click = false;
		else
			Ca.Click = true;
		return true;
	}
	if (Game_State == -1 && PlayerMain == PlayerAc)
	{
		if (action == 4)
		{
			PlayCards[PlayerAc][17] = Sendleft[0];
			PlayCards[PlayerAc][18] = Sendleft[1];
			PlayCards[PlayerAc][19] = Sendleft[2];
			SortCard(PlayCards[PlayerAc]);
			Game_State = PlayerAc;
			OutPlayer = PlayerAc;//改变
			return true;
		}
		if (action == 3)
		{
			PlayerMain = (PlayerMain + 1) % 3;
			PlayerMaininfo++;
			if (PlayerMaininfo == 3)
				Game_State = -2;
			return true;
		}
	}
	if (Game_State != PlayerAc)
		return false;
	else if (action == 4)
	{
		if (CheckCard(Game_State))
		{
			//能出牌当然出牌咯
			int i, j;
			for (i = 0; i < 20 && PreOut[i].Num <= 15; i++)
				OutCards[i] = PreOut[i];
			if (i != 20)
				OutCards[i].Num = 16;
			j = 0;
			CCard *Ca = PlayCards[Game_State];
			for (i = 0; i < 20 && Ca[i].Num <= 15; i++)
			if (!Ca[i].Click)
			{
				Ca[j] = Ca[i];
				j++;
			}
			OutPlayer = Game_State;
			Ca[j].Num = 16;
			Updata();
			return true;
		}
		else
			return false;
	}
	else if (action == 3 && OutPlayer != PlayerAc)
	{
		Game_State = (Game_State + 1) % 3;//直接更改游戏玩家
		return true;
	}

	return false;
}

void CLandGameTable::Updata()
{
	int j;
	CCard *ca = PlayCards[Game_State];
	for (j = 0; j < 20 && ca[j].Num <= 15; j++);
	if (j != 0)
		Game_State = (Game_State + 1) % 3;
	else
	{
		//改变
		if (Game_State == PlayerMain)
			MessageBox(GetActiveWindow(), "地主胜利!", "胜利", 0);
		else
			MessageBox(GetActiveWindow(), "农民胜利!", "胜利", 0);
		Game_State += 3;
	}
}
////////////////////////////////////////////////////////////////////////
/*
* 函数名称：CardsInfo(Card ca[],int &num,int &min,int &type)
* 函数介绍：把ca中的牌信息反应出来
* 输入参数：ca[]需要反应的牌信息
* 输出参数：int &num,int &max,int &type
* 返回值  ：num表示有多少张牌,min表示起作用的牌中值最小的一个的大小
例如3个5带一个8，那么起作用的就是5 min=5，num=3，type表示类型
1：3带1、2      2：4带2(4带2、两对)             3：连子
4：全相同       5：双鬼炸弹                     6：飞机
7：三顺         0：错牌！不能走出去的
*/

void CLandGameTable::CardsInfo(CCard ca[], int &num, int &min, int &type)
{
	int i, k, n;
	int same[10] = { 0 };
	int nsame[10] = { 0 };

	for (n = 0; n < 20 && ca[n].Num <= 15; n++);
	type = 0;
	num = n;
	if (n >= 5)
	{
		for (k = 0; k < n - 1; k++)//连牌
		if (ca[k].Pow != ca[k + 1].Pow - 1)
			break;
		if (k == n - 1 && ca[k].Pow <= 12)//牌不能连到2 2的pow就是12
		{
			min = ca[0].Pow;
			type = 3;
			return;
		}

		i = -1;
		for (k = 0; k < n; k++)
		{
			if (i<0 || ca[k].Pow != same[i])
				i++;
			if (i>2)
				break;
			same[i] = ca[k].Pow;
			nsame[i]++;
		}
		if (i >= 2)
		{
			int tem;
			for (tem = 0; tem<i; tem++)
			if (nsame[tem] != 2 && same[tem] != same[tem + 1] - 1)
				break;
			if (nsame[tem] == 2)
				tem++;
			if (tem>i)//三顺
			{
				type = 7;
				min = same[0];
			}
			int ty1 = 0, ty2 = 0, num3 = 0;
			int kmin = 0;

			for (tem = 0; tem <= i; tem++)//飞机
			if (nsame[tem] == 1)
			{
				ty1++;
			}
			else if (nsame[tem] == 2)
			{
				ty2++;
			}
			else if (nsame[tem] == 3 && kmin == 0)
			{
				kmin = same[tem];
				for (; tem<i; tem++)
				if (nsame[tem] == 3 && same[tem] == same[tem + 1] - 1)
					num3++;
				else
					break;
				if (tem == i && nsame[tem] == 3)
					num3++;
			}
			else
				break;
			if ((ty1 == 0 || ty2 == 0) && tem>i)
			{
				if ((num3 == ty1 || num3 == ty2 || ty1 == ty2) && num3 != 0)
				{
					type = 6;
					min = kmin;
				}
			}
		}
		if (i<2)//3带n 或 4带n
		{
			int maxnum = -1;
			for (k = 0; k <= 2; k++)
			if (nsame[k]>maxnum)
			{
				maxnum = nsame[k];
				i = k;
			}
			if (maxnum == 3 && n == 5)
			{
				type = 1;
				min = same[i];
				return;
			}
			else if (maxnum == 4)
			{
				type = 2;
				min = same[i];
				return;
			}
		}
	}
	else if (n > 2)
	{
		i = -1;
		for (k = 0; k < n; k++)
		{
			if (i<0 || ca[k].Pow != same[i])
				i++;
			if (i>2)
				break;
			same[i] = ca[k].Pow;
			nsame[i]++;
		}
		if (i <= 2)
		{
			int maxnum = -1;
			for (k = 0; k <= 2; k++)
			if (nsame[k] > maxnum)
			{
				maxnum = nsame[k];
				i = k;
			}
			if (maxnum == 3 && n == 4)
			{
				type = 1;
				min = same[i];
				return;
			}
			else if (maxnum == 3 && n == 3)
			{
				type = 4;
				min = same[i];
				return;
			}
			else if (maxnum == 4 && n == 4)
			{
				type = 4;
				min = same[i];
				return;
			}
		}
	}
	else if (n == 2)
	{
		if (ca[0].Pow == ca[1].Pow)
		{
			type = 4;
			min = ca[0].Pow;
		}
		else if (ca[0].Pow == 14 && ca[1].Pow == 15)
		{
			type = 5;
			min = ca[1].Pow;
		}
	}
	else if (n == 1)
	{
		min = ca[0].Pow;
		type = 4;
	}
}

void CLandGameTable::SortCard(CCard ca[])
{
	int i, j;
	CCard temp;
	for (i = 0; i < 20 && ca[i].Num <= 15; i++)
	for (j = i + 1; j<20 && ca[j].Num <= 15; j++)
	if (ca[i].Pow>ca[j].Pow)
	{
		temp = ca[i];
		ca[i] = ca[j];
		ca[j] = temp;
	}
}

int CLandGameTable::getPlayerCount()
{
	int result = 0;
	for (int i = 0; i < 3; i++)
	{
		if (m_UserList[i] != NULL)
		{
			result++;
		}
	}
	return result;
}

int CLandGameTable::AddPlayer(CUserClient * client)
{
	for (int i = 0; i < 3; i++)
	{
		if (m_UserList[i] == NULL)
		{
			m_UserList[i] = client;
			//发送信息给其他桌的人
			int tIndex = m_TableIndex;
			//发送信息到客户端
		   client->SendMessageToClient(SM_FIND_PLACE, tIndex, i);
			//需要给你的同桌你的信息
		   BoradcastTableAddUserMessage(i);
			break;
		}
	}
	return -1;
}

void CLandGameTable::BroadcastMessage(int Seat, char * buf, int buflen)
{
	for (int i = 0; i < 3; i++)
	{
		if ((i != Seat) && (m_UserList[i] != NULL))
		{
			m_UserList[i]->SendMessageToClient(SM_ADD_USER, Seat, (char*)&UI, sizeof(UserInfo) );
		}
	}
}

void CLandGameTable::BoradcastTableAddUserMessage(int Seat)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (m_UserList[j] != NULL)
			{
				UserInfo UI;
				sprintf_s(UI.name, 15, "User%d", i);
				UI.icon = 0;

			}
			m_UserList[i]->SendMessageToClient(SM_ADD_USER, Seat, &UI, sizeof(UserInfo));
		}
	}
}
