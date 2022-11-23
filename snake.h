#pragma once
#include<iostream>
using namespace std;
#include "wall.h"
#include "food.h" 
#include<list>

//蛇节点
struct Point
{
	//数据域
	int x;
	int y;

	//指针域
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

	//1.初始化蛇
	void initSnake();

	//1.1 销毁蛇
	void destroyPoint();

	//1.2添加节点
	void addPoint(int x, int y);

	//2.1删除尾节点
	void delPoint();

	//2.2蛇移动   返回值代表蛇是否移动，如果是false代表gameover
	bool move(char key);

	//3.1 难度设定 根据蛇的长度 改变游戏的运行速度
	int getSleepTime();

	//3.2 获取蛇的长度
	int countList();

	//3.3分数获取
	int getScore();

	//4 保存游戏
	void saveGame(char key);

	//5读取游戏
	void readGame(char *key);

private:

	//记录头节点
	Point * pHead;

	//保存住墙对象
	Wall & wall;

	//食物对象
	Food & food;

	//循环标识
	bool isRool = false;

	//list<pair<int, int>> lSnake;
};