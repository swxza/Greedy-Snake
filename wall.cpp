#include "wall.h"

Wall::Wall()
{

}


Wall:: ~Wall()
{

}


//初始化墙
void Wall::initWall()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (i == 0 || j == 0 || i == ROW - 1 || j == COL - 1)
			{
				gameArray[i][j] = '*';
			}
			else
			{
				gameArray[i][j] = ' ';
			}
		}
	}
}

//绘制二维数组到屏幕窗口
void Wall::draw()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			cout << gameArray[i][j] << ' ';
		}

		if (i == 5)
		{
			cout << "Snake Version 1.0";
		}
		if (i == 6)
		{
			cout << "create by wxz";
		}
		if (i == 7)
		{
			cout << " up   :w";
		}
		if (i == 8)
		{
			cout << " down :s";
		}
		if (i == 9)
		{
			cout << " left :a";
		}
		if (i == 10)
		{
			cout << " right:d";
		}


		cout << endl;
	}
}

void Wall::setWall(int x, int y, char key)
{
	gameArray[x][y] = key;
}

char Wall::getWall(int x, int y)
{
	return gameArray[x][y];
}

