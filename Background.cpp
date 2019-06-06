#include "Background.h"



Background::Background()
{

}


Background::~Background()
{
}

void Background::backgroundInitialization()
{
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 15; j++) {
			XY[i][j] = 0;	//0��ʾ�������ǿյģ�û��С����
			colors[i][j] = "0xEDECEC";	//��ÿһ�����ɫ��ʼ��Ϊ �Ұװף��ȻҰ׸���һ�㣩
		}
	}

	for (int i = 0; i < 24; i++)
	{
		//���ұ߿�����Ϊ1
		XY[i][0] = 1;
		XY[i][14] = 1;
		colors[i][0] = "0xd8dbdc";
		colors[i][14] = "0xd8dbdc";
	}
	for (int i = 0; i < 15; i++) {
		XY[23][i] = 1;
		colors[23][i] = "0xd8dbdc";
	}


	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			cout << XY[i][j] << " ";
		}
		cout << endl;
	}
}

void Background::setBackgroundTrue(int deviationX, int deviationY)
{
	XY[deviationX][deviationY] = 1;		//��С����ĵط���1��ʾ���ڸ�λ����ʾС���飩
}

void Background::setBackgroundFalse(int deviationX, int deviationY)
{
	XY[deviationX][deviationY] = 0;		//����λ�õ�С�������
}

void Background::setXY(int newX, int newY, int number)
{
	XY[newX][newY] = number;
}

void Background::setColors(int deviationX, int deviationY, string s)
{
	colors[deviationX][deviationY] = s;
}

string Background::getColors(int deviationX, int deviationY) const
{
	return string(colors[deviationX][deviationY]);
}

int Background::getXY(int newX, int newY) const
{
	return XY[newX][newY];
}

//���ﴫ��Ĳ�����ÿһ��С�������������ԭ��ƫ����
bool Background::ifEmpty(int deviationX, int deviationY)
{
	if (XY[deviationX][deviationY] == 0) {
		return true;

	}
	else {
		return false;

	}
}

bool Background::ifFull(int deviationX, int deviationY)
{
	if (XY[deviationX][deviationY] == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

