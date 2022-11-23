#include "snake.h"
#include "infoFile.h"
#include <Windows.h>

void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;//������
	pos.Y = y;//������
	SetConsoleCursorPosition(hOut, pos);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//������ʾ���������

//��ʼ���б�
Snake::Snake(Wall & tmpWall, Food & tmpfood):wall(tmpWall), food(tmpfood)
{
	//pHead = NULL;
}


Snake:: ~Snake()
{

}

//��ʼ����
void Snake::initSnake()
{
	//�������нڵ�
	destroyPoint();

	//��ӽڵ�
	addPoint(5, 3);
	addPoint(5, 4);
	addPoint(5, 5);
	addPoint(5, 6);

}

//������
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

//��ӽڵ�
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



	//�����½ڵ�
	Point * newPoint = new Point;
	if (newPoint == NULL)
	{
		return;
	}
	//�½ڵ㸳ֵ  ��������ֵ
	newPoint->x = x;
	newPoint->y = y;

	newPoint->next = NULL;
	if (pHead != NULL)
	{
		//��ԭ�е���ͷ��Ϊ����
		wall.setWall(pHead->x, pHead->y, '=');
		gotoxy(hOut, pHead->y * 2, pHead->x);
		cout << '=';
	}
	//�½ڵ��Ϊͷ
	newPoint->next = pHead;
	//���½��Ľڵ��Ϊͷ�ڵ�
	pHead = newPoint;
	wall.setWall(pHead->x, pHead->y, '@');
	gotoxy(hOut, pHead->y * 2, pHead->x);
	cout << '@';
}

//ɾ��β�ڵ�
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

//���ƶ��������Ƿ���
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
	//cur��β

	//pair<int, int> cur = lSnake.back();

	if (cur->x == x && cur->y == y)
	//if (cur.first == x && cur.second == y)
	{
		isRool = true;
	}
	else
	{
		//�ж���Ϸ����
		if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=')
		{
			addPoint(x, y);
			delPoint();
			system("cls");
			wall.draw();

			cout << "GameOver!" << endl;
			cout << "�������յ÷�Ϊ��" << getScore() << "��" << endl;
			return false;
		}
	}

	

	

	//�����ƶ�
	//�Ե�ʳ��
	if (wall.getWall(x, y) == '#')
	{
		addPoint(x, y);
		//��������ʳ��
		food.setFood();
	}
	//δ�Ե�ʳ��
	else
	{

		if (isRool == true)
		{
			//�����ƶ�
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

//4 ������Ϸ
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

//5��ȡ��Ϸ
void Snake::readGame(char *key)
{
	//����ԭ������
	destroyPoint();

	//��ʼ��ǽ
	wall.initWall();

	//��ȡ�浵
	InfoFile file;
	file.readInfo();

	//���÷���
	*key = file.key;

	//����ʳ��
	wall.setWall(file.foodX, file.foodY, '#');

	//�߳���
	int num = file.num;

	//���ýڵ�
	for (int i = 0; i < num; i++)
	{
		addPoint(file.snakeX[num - i - 1], file.snakeY[num - i - 1]);
	}
}
