#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "wall.h"
#include "snake.h"
#include "food.h"
#include <conio.h>
#include <ctime>
#include <Windows.h>
using namespace std;
#include <Windows.h>

void gotoxy3(HANDLE hOut3, int x, int y)
{
	COORD pos;
	pos.X = x;//横坐标
	pos.Y = y;//纵坐标
	SetConsoleCursorPosition(hOut3, pos);
}
HANDLE hOut3 = GetStdHandle(STD_OUTPUT_HANDLE);//定义显示器句柄变量

int pauseScene()
{
	int ret = -1;

	while (true)
	{
		system("cls");
		cout << "请输入选择：" << endl;
		cout << "1.继续游戏" << endl;
		cout << "2.保存游戏" << endl;
		cout << "3.读取游戏" << endl;
		cout << "0.退出游戏" << endl;

		cin >> ret;

		if (ret == 0 || ret == 1 || ret == 2 || ret == 3)
		{
			return ret;
		}

		//重置标志位
		cin.clear();

		//清空缓冲区
		cin.sync();

		//标志位为0代表正常  为1代表不正常
		//cout << "标志位" << cin.fail() << endl;
	}

	

	
}


//程序入口
int main()
{
	//随机数种子
	srand((unsigned int)time(NULL));

	Wall wall;
	wall.initWall();
	wall.draw();

	Food food(wall);
	food.setFood();

	Snake snake(wall, food);
	snake.initSnake();

	gotoxy3(hOut3, 0, wall.ROW);
	cout << "得分：" << snake.getScore() << "分" << endl;

	//死亡标识
	bool isDead = false;

	//上一次方向的标识
	char preKey = NULL;

	//测试移动代码
	//snake.move('w');
	//snake.move('w');
	//snake.move('a');
	////测试
	//cout << wall.getWall(0, 0) << endl;
	//wall.setWall(5, 5, '=');
	//cout << wall.getWall(5, 5) << endl;
	//cout << wall.getWall(5, 6) << endl;

	
	
	while (!isDead)
	{
		char key = _getch();   //接收用户的输入的字符  头文件<conio.h>

		if (preKey == NULL && key == snake.LEFT)   //解决  激活游戏不能用左按键
		{
			continue;
		}

		do
		{
			if (key == snake.UP || key == snake.DOWN || key == snake.LEFT || key == snake.RIGHT)
			{
				//记录上一次按键
				if (key == snake.UP && preKey == snake.DOWN || key == snake.DOWN && preKey == snake.UP ||
					key == snake.LEFT && preKey == snake.RIGHT || key == snake.RIGHT && preKey == snake.LEFT)
				{
					key = preKey;
				}
				else
				{
					preKey = key;//更新方向
				}

				if (snake.move(key) == true)
				{
					//system("cls");
					//wall.draw();
					gotoxy3(hOut3, 0, wall.ROW);
					cout << "得分：" << snake.getScore() << "分" << endl;
					Sleep(snake.getSleepTime());
				}
				else
				{
					isDead = true;
					break;
				}
			}
			else if (key == ' ')
			{
				//空格进入暂停  暂停有暂停的界面
				int select = pauseScene();

				switch (select)
				{
				case 0://退出
					exit(0);
					break;
				case 1://继续
				{
					system("cls");
					wall.draw();
					cout << "得分：" << snake.getScore() << "分" << endl;
					key = preKey;
					break;
				}	
				case 2://保存
				{
					snake.saveGame(preKey);
					system("cls");
					cout << "存档成功！" << endl;
					system("pause");
					break;
				}
				case 3://读取
				{
					snake.readGame(&key);
					preKey = key;
					system("cls");
					wall.draw();
					cout << "得分：" << snake.getScore() << "分" << endl;
					break;
				}					
				default:
					break;
				}
			}
			else
			{
				key = preKey;    //当前的输入按键强制变为上一次方向
			}
			
		} while (!_kbhit());  //如果用户没有任何输入，返回0   _kbhit


		

	}
	
	


	system("pause");
	return EXIT_SUCCESS;
}