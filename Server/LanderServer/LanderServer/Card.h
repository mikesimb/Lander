#pragma once
class CCard
{
public:
	CCard();
	virtual ~CCard();
	int Num;//������Ŀ 2-10 J=11 Q=12 K=13 A=1 Jok(С)=14 Jok(��)=15 ����15��ʾ���Ʋ�����
	int Pow;//�Ƶ�ʵ�ʴ�С�����綷������2�ͱ�A��
	//3-10 J Q  K  A  2  JoС Jo��
	//1-8  9 10 11 12 13 14   15
	int Type;//�Ƶ����� ����=0 ����=1 ÷��=2 ����=3
	bool Click;//�����ѡ�ֵ��ƽ���true��û��ѡ����false
};

