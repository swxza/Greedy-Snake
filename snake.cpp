#include "snake.h"
#include "infoFile.h"
#include <Windows.h>

void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;//横坐标
	pos.Y = y;//纵坐标
	SetConsoleCursorPosition(hOut, pos);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//定义显示器句柄变量

//初始化列表
Snake::Snake(Wall & tmpWall, Food & tmpfood):wall(tmpWall), food(tmpfood)
{
	//pHead = NULL;
}


Snake:: ~Snake()
{

}

//初始化蛇
void Snake::initSnake()
{
	//销毁所有节点
	destroyPoint();

	//添加节点
	addPoint(5, 3);
	addPoint(5, 4);
	addPoint(5, 5);
	addPoint(5, 6);

}

//销毁蛇
void Snake::destroyPoint()
{
	Point * pCur;
	while (pHead != NULL)
	{
		pCur = pHead->next;
		delete pHead;
		pHead = pCur;
	}

	//while (!lSnake.empty())
	//{
	//	pair<int, int> p = lSnake.front();
	//	lSnake.pop_front();
	//}

}

//添加节点
void Snake::addPoint(int x, int y)
{

	//pair<int, int> p;
	//p.first = x;
	//p.second = y;
	//if (!lSnake.empty())
	//{
	//	p = lSnake.front();
	//	wall.setWall(p.first, p.second, '=');
	//}

	//lSnake.push_front(make_pair(x, y));
	//p = lSnake.front();
	//wall.setWall(p.first, p.second, '@');



	//创建新节点
	Point * newPoint = new Point;
	if (newPoint == NULL)
	{
		return;
	}
	//新节点赋值  给数据域赋值
	newPoint->x = x;
	newPoint->y = y;

	newPoint->next = NULL;
	if (pHead != NULL)
	{
		//将原有的蛇头变为蛇身
		wall.setWall(pHead->x, pHead->y, '=');
		gotoxy(hOut, pHead->y * 2, pHead->x);
		cout << '=';
	}
	//新节点变为头
	newPoint->next = pHead;
	//将新建的节点变为头节点
	pHead = newPoint;
	wall.setWall(pHead->x, pHead->y, '@');
	gotoxy(hOut, pHead->y * 2, pHead->x);
	cout << '@';
}

//删除尾节点
void Snake::delPoint()
{
	Point * pre = pHead;
	Point * cur = pre->next;
	if (pHead == NULL || pHead->next == NULL)
	{
		return;
	}
	while (cur->next != NULL)
	{
		pre = pre->next;
		cur = pre->next;
	}

	wall.setWall(cur->x, cur->y, ' ');
	gotoxy(hOut, cur->y * 2, cur->x);
	cout << ' ';
	delete cur;

	cur = NULL;
	pre->next = NULL;
	
	//pair<int, int> p = lSnake.back();
	//wall.setWall(p.first, p.second, ' ');
	//lSnake.pop_back();
	
}

//蛇移动，参数是方向
bool Snake::move(char key)
{
	int x = pHead->x;
	int y = pHead->y;

	//pair<int, int> p = lSnake.front();
	//int x = p.first;
	//int y = p.second;

	switch (key)
	{
	case UP:
		x--;
		break;
	case DOWN:
		x++;
		break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	default:
		break;
	}


	Point * pre = pHead;
	Point * cur = pre->next;
	while (cur->next != NULL)
	{
		pre = pre->next;
		cur = pre->next;
	}
	//cur蛇尾

	//pair<int, int> cur = lSnake.back();

	if (cur->x == x && cur->y == y)
	//if (cur.first == x && cur.second == y)
	{
		isRool = true;
	}
	else
	{
		//判断游戏结束
		if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=')
		{
			addPoint(x, y);
			delPoint();
			system("cls");
			wall.draw();

			cout << "GameOver!" << endl;
			cout << "您的最终得分为：" << getScore() << "分" << endl;
			return false;
		}
	}

	

	

	//正常移动
	//吃到食物
	if (wall.getWall(x, y) == '#')
	{
		addPoint(x, y);
		//重新设置食物
		food.setFood();
	}
	//未吃到食物
	else
	{

		if (isRool == true)
		{
			//正常移动
			addPoint(x, y);
			delPoint();
			wall.setWall(x, y, '@');
			gotoxy(hOut, y * 2, x);
			cout << '@';
		}
		else
		{
			addPoint(x, y);
			delPoint();
		}
		
	}

	return true;
}


int Snake::getSleepTime()
{
	int stime = 0;
	int size = countList();
	if (size < 30)
	{
		stime = 200;
	}
	else if(size >= 30 && size <= 50)
	{
		stime = 100;
	}
	else
	{
		stime = 50;
	}


	return stime;
}


int Snake::countList()
{
	int size = 0;

	Point * curP = pHead;
	while (curP != NULL)
	{
		size++;
		curP = curP->next;
	}

	return size;
}

int Snake::getScore()
{
	int size = countList();
	int score = (size-4) * 100;

	return score;
}

//4 保存游戏
void Snake::saveGame(char key)
{
	InfoFile file;
	file.key = key;

	file.foodX = food.getFoodX();
	file.foodY = food.getFoodY();

	file.num = countList();

	Point * curP = pHead;

	
	for (int i = 0; i < countList(); i++)
	{
    	file.snakeX[i] = curP->x;
		file.snakeY[i] = curP->y;
		curP = curP->next;
	}
	

	
	file.saveInfo();
}

//5读取游戏
void Snake::readGame(char *key)
{
	//销毁原来的蛇
	destroyPoint();

	//初始化墙
	wall.initWall();

	//读取存档
	InfoFile file;
	file.readInfo();

	//设置方向
	*key = file.key;

	//设置食物
	wall.setWall(file.foodX, file.foodY, '#');

	//蛇长度
	int num = file.num;

	//设置节点
	for (int i = 0; i < num; i++)
	{
		addPoint(file.snakeX[num - i - 1], file.snakeY[num - i - 1]);
	}
}
