#pragma once
#include <iostream>
#include "wall.h"
using namespace std;

class Food
{
public:

	Food(Wall & tmpWall);
	~Food();

	//����ʳ��
	void setFood();

	int getFoodX();
	int getFoodY();


private:

	//ʳ��λ�ã���¼���λ��Ϊ�����������
	int foodX;
	int foodY;

	Wall & wall;
};