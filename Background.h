#pragma once
#include <iostream>
#include <string>
using namespace std;

//俄罗斯方块游戏界面的背景界面
class Background
{
public:
	Background();
	~Background();
	void backgroundInitialization();		//初始化背景，当继续开始游戏时会用到
	void setBackgroundTrue(int deviationX, int deviationY);
	void setBackgroundFalse(int deviationX, int deviationY);
	void setXY(int newX, int newY, int number);			//设置XY坐标对应的数字
	void setColors(int deviationX, int deviationY, string s);
	string getColors(int deviationX, int deviationY) const;

	int getXY(int newX, int newY) const;		//得到xy坐标对应的数字
	bool ifEmpty(int deviationX, int deviationY);		//判断该区域是否为空（没有小方块）
	bool ifFull(int deviationX, int deviationY);
private:
	//游戏区域有23行，13列，但是考虑到边界，background 设置为24行，15列
	int XY[24][15];		//23行，13列		//用每一个小方格的左上角的坐标(这里的坐标指的是偏移量)来代替该小方块的坐标
	string colors[24][15];		//用来存储每一个格子里的颜色
};

