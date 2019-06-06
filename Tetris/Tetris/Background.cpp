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
			XY[i][j] = 0;	//0表示该区域是空的，没有小方块
			colors[i][j] = "0xEDECEC";	//将每一格的颜色初始化为 灰白白（比灰白更白一点）
		}
	}

	for (int i = 0; i < 24; i++)
	{
		//左右边框设置为1
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
	XY[deviationX][deviationY] = 1;		//有小方块的地方用1表示（在该位置显示小方块）
}

void Background::setBackgroundFalse(int deviationX, int deviationY)
{
	XY[deviationX][deviationY] = 0;		//将该位置的小方块擦除
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

//这里传入的参数是每一个小方格相对于坐标原点偏移量
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

