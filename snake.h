#pragma once
#include<iostream>
using namespace std;
#include "wall.h"
#include "food.h" 
#include<list>

//�߽ڵ�
struct Point
{
	//������
	int x;
	int y;

	//ָ����
	Point * next;
};

class Snake
{
public:
	Snake(Wall & tmpWall, Food & tmpfood);
	~Snake();


	enum
	{
		UP = 'w', DOWN = 's', LEFT = 'a', RIGHT = 'd'
	};

	//1.��ʼ����
	void initSnake();

	//1.1 ������
	void destroyPoint();

	//1.2��ӽڵ�
	void addPoint(int x, int y);

	//2.1ɾ��β�ڵ�
	void delPoint();

	//2.2���ƶ�   ����ֵ�������Ƿ��ƶ��������false����gameover
	bool move(char key);

	//3.1 �Ѷ��趨 �����ߵĳ��� �ı���Ϸ�������ٶ�
	int getSleepTime();

	//3.2 ��ȡ�ߵĳ���
	int countList();

	//3.3������ȡ
	int getScore();

	//4 ������Ϸ
	void saveGame(char key);

	//5��ȡ��Ϸ
	void readGame(char *key);

private:

	//��¼ͷ�ڵ�
	Point * pHead;

	//����סǽ����
	Wall & wall;

	//ʳ�����
	Food & food;

	//ѭ����ʶ
	bool isRool = false;

	//list<pair<int, int>> lSnake;
};