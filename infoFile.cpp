#include "infoFile.h"
#include <fstream>


InfoFile::InfoFile()
{


}
InfoFile:: ~InfoFile()
{


}

//������Ϸ
void InfoFile::saveInfo()
{
	ofstream ofs(_FILE_PATH);
	if (!ofs.is_open())
	{
		return;
	}

	ofs << key << endl;//���淽��
	ofs << foodX << "|";
	ofs << foodY << endl;//����ʳ��
	ofs << num << endl;//���泤��
	for (int i = 0; i < num; i++)
	{
		ofs << snakeX[i] << "|";
		ofs << snakeY[i] << endl;
	}

	ofs.close();

}

//��ȡ��Ϸ
void InfoFile::readInfo()
{
	ifstream ifs(_FILE_PATH);
	if (!ifs.is_open())
	{
		return;
	}

	char buf[1024];
	ifs.getline(buf, sizeof(buf));
	
	//���з���
	key = buf[0];

	memset(buf, 0, sizeof(buf));
	ifs.getline(buf, sizeof(buf)); 

	//ʳ��
	char * str = strtok(buf, "|");
	foodX = atoi(str);
	strtok(NULL, "|");
	foodY = atoi(str);

	//����
	memset(buf, 0, sizeof(buf));
	ifs.getline(buf, sizeof(buf));
	num = atoi(buf);

	//������
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