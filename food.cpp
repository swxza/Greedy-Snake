#include "food.h"
#include <Windows.h>

void gotoxy2(HANDLE hOut2, int x, int y)
{
	COORD pos;
	pos.X = x;//横坐标
	pos.Y = y;//纵坐标
	SetConsoleCursorPosition(hOut2, pos);
}
HANDLE hOut2 = GetStdHandle(STD_OUTPUT_HANDLE);//定义显示器句柄变量

Food::Food(Wall & tmpWall): wall(tmpWall)
{

}


Food::~Food()
{

}

void Food::setFood()
{
	while (1)
	{
		foodX = rand() % (wall.ROW - 2) + 1;
		foodY = rand() % (wall.COL - 2) + 1;

		if (wall.getWall(foodX, foodY) == ' ')
		{
			wall.setWall(foodX, foodY, '#');
			gotoxy2(hOut2, foodY * 2, foodX);
			cout << '#';
			break;
		}
	}
	
}

int Food::getFoodX()
{
	return this->foodX;

}


int Food::getFoodY()
{

	return this->foodY;
}