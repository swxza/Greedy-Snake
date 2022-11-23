#include "infoFile.h"
#include <fstream>


InfoFile::InfoFile()
{


}
InfoFile:: ~InfoFile()
{


}

//保存游戏
void InfoFile::saveInfo()
{
	ofstream ofs(_FILE_PATH);
	if (!ofs.is_open())
	{
		return;
	}

	ofs << key << endl;//保存方向
	ofs << foodX << "|";
	ofs << foodY << endl;//保存食物
	ofs << num << endl;//保存长度
	for (int i = 0; i < num; i++)
	{
		ofs << snakeX[i] << "|";
		ofs << snakeY[i] << endl;
	}

	ofs.close();

}

//读取游戏
void InfoFile::readInfo()
{
	ifstream ifs(_FILE_PATH);
	if (!ifs.is_open())
	{
		return;
	}

	char buf[1024];
	ifs.getline(buf, sizeof(buf));
	
	//运行方向
	key = buf[0];

	memset(buf, 0, sizeof(buf));
	ifs.getline(buf, sizeof(buf)); 

	//食物
	char * str = strtok(buf, "|");
	foodX = atoi(str);
	strtok(NULL, "|");
	foodY = atoi(str);

	//长度
	memset(buf, 0, sizeof(buf));
	ifs.getline(buf, sizeof(buf));
	num = atoi(buf);

	//蛇链表
	for (int i = 0; i < num; i++)
	{
		memset(buf, 0, sizeof(buf));
		ifs.getline(buf, sizeof(buf));
		char * str2 = strtok(buf, "|");
		snakeX[i] = atoi(str2);
		str2 = strtok(NULL, "|");
		snakeY[i] = atoi(str2);

	}
	ifs.close();

}