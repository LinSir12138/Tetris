#pragma once
#include "Background.h"
#include <iostream>
#include <graphics.h>
#include <stdio.h>		//_stprintf_s函数要用到，输出变量文字
#include <string>
#include <cstdlib>
#include <ctime>			//产生随机数
#include <conio.h>		//获取键盘事件
#include <Windows.h>		//Sleep函数用到
#include <fstream>
using namespace std;


//俄罗斯方块的游戏界面
class Shap
{
public:
	Shap();		//只是建立一个绘图窗口，具体初始化参数在Initialization 函数中实现
	~Shap();
	void Initialization();		//初始化
	void random1();		//随机数，当前方块
	void random2();		//随机数，后一个方块
	void draw(int deviationX, int deviationY, int type, string newColor);		//画当前方块一个方块
	void drawNextBlock(int type, string newColor);
	// move 传入的参数x, y 是 4 * 4 方框的左上角的坐标
	void move(int flag, int type, int x, int y);		//移动一个方块,flag== 1表示想左移，flag == 2表示向右移,type 表示方块类型
	// turn 传入的参数x, y 是 4 * 4 方框的左上角的坐标
	void turn(int type, int x, int y);		//旋转方块
	bool down();		//方块自然下落
	void clear(int deviationX, int devaitionY, int type);		//擦除方块，在方块旋转或者方块移动时调用
	void setColor(string newColor);
	void inspect();		//当方块不能继续下落时，检查背景，看是否满足消去一行或多行
	void gameOverUI();		//游戏结束时的UI界面
	bool ifGameOver(int type, string newColor);		//游戏是否结束,参数为方块类型和方块颜色

	int eliminateLine;		//已经消除的行数
	int sumScore;			//总得分，消除一行100分，同时消除两行300分，同时消除3行500分，同时消除4行800分；
	int getNumber() const { return blockNumber1; }
	int nowX, nowY;		//方块所在的 4 * 4 方格的左上角的坐标
	string color1;		//当前方块颜色
	string color2;		//后一个方块的颜色
	int blockColor1;		//当前方块颜色代表的编号
	int blockNumber1;		//当前方块的编号
	int blockColor2;		//后一个方块的颜色代表的编号
	int blockNumber2;		//后一个方块的编号
	int accountIndex;		//用户登录时该用户在文件中对应的下标
	string maxScore;
	int gameoverChooseFlag;		//在游戏结束界面进行的选择，如果选择“继续游戏”，这赋值为1，选择“返回”，这赋值为2


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~下面的函数是选择界面，上面的函数是游戏界面~~~~~~~~~~~~~~~~~~~~~~~~~~~

	void loadingLeft();		//加载左边的图形界面
	void loadingRight();	//加载右边的图形界面
	void mianMouse();			//鼠标
	void mainUI();			//主界面
	//justStartGame有两个参数，第一个参数表示类型，T 表示游客登录， F 表示账号密码登录,第二个参数为对应账号在文件中的下标，如果为游客登录则该参数为0
	void justStartGame(char type, int index);	//快速开始游戏
	void myRegister();		//注册
	int myLogIn();			//登录
	void myAbout();			//关于界面
	void myExit();			//退出
	string getFlag() const;
	bool getIfBack() const;
	bool getIfStartGame() const;
	void Wchar_tToString(std::string& szDst, wchar_t *wchar)
	{
		wchar_t * wText = wchar;
		DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);// WideCharToMultiByte的运用
		char *psText; // psText为char*的临时数组，作为赋值给std::string的中间变量
		psText = new char[dwNum];
		WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte的再次运用
		szDst = psText;// std::string赋值
		delete[]psText;// psText的清除
	}

private:
	//从上到下，从左到右
	//每行的第一个元素是方块的编号，之后8个元素分为4对，每一对分别为该类型方块的其中一个小方块相对于左上角的坐标的偏移量
	int site[19][9] = {
		//  1  2  3  4  5  6  7  8
	//   N  X  Y  X  Y  X  Y  X  Y
		{0, 2, 0, 0, 1, 1, 1, 2, 1},
		{1, 1, 0, 1, 1, 1, 2, 2, 2},		// L型
		{2, 0, 1, 1, 1, 2, 1, 0, 2},
		{3, 1, 0, 2, 0, 2, 1, 2, 2},

		{4, 0, 0, 0, 1, 1, 1, 2, 1},
		{5, 1, 0, 2, 0, 1, 1, 1, 2},
		{6, 0, 0, 1, 0, 2, 0, 2, 1},		// 逆L型
		{7, 2, 0, 2, 1, 2, 2, 1, 2},

		{8, 1, 0, 0, 1, 1, 1, 2, 1},
		{9, 1, 0, 1, 1, 2, 1, 1, 2},		// T型
		{10, 0, 1, 1, 1, 2, 1, 1, 2},
		{11, 1, 0, 0, 1, 1, 1, 1, 2},

		{12, 0, 0, 1, 0, 1, 1, 2, 1},		//正折线型
		{13, 2, 0, 1, 1, 2, 1, 1, 2},

		{14, 1, 0, 2, 0, 0, 1, 1, 1},		//逆折线型
		{15, 1, 0, 1, 1, 2, 1, 2, 2},

		{16, 0, 0, 1, 0, 2, 0, 3, 0},		// 直线型
		{17, 1, 0, 1, 1, 1, 2, 1, 3},

		{18, 0, 0, 1, 0, 0, 1, 1, 1}		//田字形
	};

	//向左移动是哪些位置应该为空
	int moveLeft[19][9] = {
	{0, 1, 0, -1, 1},
	{1, 0, 0, 0, 1, 0, 2},
	{2, -1, 1, -1, 2},				// L型
	{3, 0, 0, 1, 1, 1, 2},

	{4, -1, 0, -1, 1},
	{5, 0, 0, 0, 1, 0, 2},			// 逆L型
	{6, -1, 0, 1, 1},
	{7, 1, 0, 1, 1, 0, 2},

	{8, 0, 0, -1, 1},
	{9, 0, 0, 0, 1, 0, 2},			// T型
	{10, -1, 1, 0, 2},
	{11, 0, 0, -1, 1, 0, 2},

	{12, -1, 0, 0, 1},				//正折线型
	{13, 1, 0, 0, 1, 0, 2},
	{14, 0, 0, -1, 1},				//逆折线型
	{15, 0, 0, 0, 1, 1, 2},

	{16, -1, 0},					// 直线型
	{17, 0, 0, 0, 1, 0, 2, 0, 3},

	{18, -1, 0, -1, 1}				//田字形
	};

	//向右移动是哪些位置应该为空
	int moveRight[19][9] = {
	{0, 3, 0, 3, 1},
	{1, 2, 0, 2, 1, 3, 2},
	{2, 3, 1, 3, 2},
	{3, 3, 0, 3, 1, 3, 2},

	{4, 1, 0, 3, 1},
	{5, 3, 0, 2, 1, 2, 2},
	{6, 3, 0, 3, 1},
	{7, 3, 0, 3, 1, 3, 2},

	{8, 2, 0, 3, 1},
	{9, 2, 0, 3, 1, 2, 2},
	{10, 3, 1, 2, 2},
	{11, 2, 0, 2, 1, 2, 2},

	{12, 2, 0, 3, 1},
	{13, 3, 0, 3, 1, 2, 2},
	{14, 3, 0, 2, 1},
	{15, 2, 0, 3, 1, 3, 2},

	{16, 4, 0},
	{17, 2, 0, 2, 1, 2, 2, 2, 3},
	{18, 2, 0, 2, 1}
	};

	//向下移动时哪些位置应该为空
	int moveDown[19][9] = {
	{0, 0, 2, 1, 2, 2, 2},
	{1, 1, 3, 2, 3},
	{2, 0, 3, 1, 2, 2, 2},
	{3, 1, 1, 2, 3},

	{4, 0, 2, 1, 2, 2, 2},
	{5, 1, 3, 2, 1},
	{6, 0, 1, 1, 1, 2, 2},
	{7, 1, 3, 2, 3},

	{8, 0, 2 ,1, 2, 2, 2},
	{9, 1, 3, 2, 2},
	{10, 0, 2, 1, 3, 2, 2},
	{11, 0, 2, 1, 3},

	{12, 0, 1, 1, 2, 2, 2},
	{13, 1, 3, 2, 2},
	{14, 0, 2, 1, 2, 2, 1},
	{15, 1, 2, 2, 3},

	{16, 0, 1, 1, 1, 2, 1, 3, 1},
	{17, 1, 4},
	{18, 0, 2, 1, 2}
	};

	//旋转是哪些位置应该为空，因为最多有3个位置为空，所以第二个元素的下标设置为 3 * 2 + 1 = 7
	int turnIsempty[19][7] = {
	{0, 1, 0, 1, 2, 2, 2},
	{1, 0, 1, 0, 2, 2, 1},
	{2, 1, 0, 2, 0, 2, 2},
	{3, 0, 1, 1, 1},

	{4, 1, 0, 1, 2, 2, 0},
	{5, 0, 0, 2, 1},
	{6, 1, 2, 2, 2},
	{7, 0, 0, 0 ,1, 1, 1},

	{8, 1, 2},
	{9, 0, 1},
	{10, 1, 0},
	{11, 2, 1},

	{12, 1, 2, 2, 0},
	{13, 0, 0, 1, 0},
	{14, 2, 1, 2, 2},
	{15, 2, 0, 0, 1},

	{16, 1, 1, 1, 2, 1, 3},
	{17, 0, 0, 2, 0, 3, 0},

	{18}
	};

	string flag;
	bool ifBack;
	bool ifStartGame;
	Background background;
};

