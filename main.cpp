#include <iostream>
#include<windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include "Background.h"
#include "Shap.h"
using namespace std;

// Change MainUI
int main(void)
{
	//PlaySound(TEXT("D:\\music\\shiji.wav"), NULL, SND_FILENAME | SND_ASYNC);  flase
	PlaySound(TEXT("res\\shiji.wav"), NULL, SND_LOOP | SND_ASYNC);

	int index;

	//Tetris tetirs;
	Shap shap;

	//while循环1
	while (true)
	{

		cout << "44444444`````" << endl;
		shap.mainUI();		//加载选择界面
		cout << "5555555" << endl;
		//快速开始游戏
		if (shap.getFlag() == "Just StartGame") {
			//tetirs.justStartGame('T', 0);
			int ch;
			bool ifgameover;

			//while循环2
			while (true)
			{
				shap.Initialization();		//初始化绘图窗口，分数等
				shap.random1();		//随机生成方块编号 number 和 颜色 color
				shap.color2 = shap.color1;
				shap.blockColor2 = shap.blockColor1;
				shap.blockNumber2 = shap.blockNumber1;
				//while循环3
				while (true)
				{
					bool ifGameUIChooseBack = false;		//在游戏界面时，是否选择了返回（在游戏中途返回主界面）
					shap.color1 = shap.color2;
					shap.blockColor1 = shap.blockColor2;
					shap.blockNumber1 = shap.blockNumber2;
					shap.random2();
					shap.drawNextBlock(shap.blockNumber2, shap.color2);
					ifgameover = shap.ifGameOver(shap.blockNumber1, shap.color1);
					shap.draw(5, 0, shap.blockNumber1, shap.color1);
					if (ifgameover == true)
					{
						shap.gameOverUI();
						//选择"继续游戏"
						if (shap.gameoverChooseFlag == 1)
						{
							graphdefaults();		//初始化绘图因子因为之前改变了原点坐标，对后续绘图可能会产生影响
							break;		//跳出循环3
						}
						//选择“返回”
						else if (shap.gameoverChooseFlag == 2)
						{
							cout << "22222~~~~~" << endl;
							break;		//跳出循环3
						}
					}

					DWORD m_oldtime = GetTickCount();
					while (true)
					{
						bool ifCanDown;
						DWORD newtime = GetTickCount();
						if (newtime - m_oldtime >= 500)
						{
							m_oldtime = newtime;
							ifCanDown = shap.down();
							if (ifCanDown == false)
							{
								shap.inspect();
								break;
							}

						}
						//如果有一个键按下了，则_kbhit函数返回一个非0值，否则返回0
						if (_kbhit())
						{
							ch = _getch();
							cout << ch << endl;
							//按下A，左移
							if (ch == 75 || ch == 97) {
								shap.move(1, shap.getNumber(), shap.nowX, shap.nowY);
							}
							//按下D，右移
							else if (ch == 77 || ch == 100)
							{
								shap.move(2, shap.getNumber(), shap.nowX, shap.nowY);
							}
							//按下W，翻转
							else if (ch == 72 || ch == 119)
							{
								shap.turn(shap.getNumber(), shap.nowX, shap.nowY);
							}
							else if (ch == 80 || ch == 115)
							{
								//shap.down();
								ifCanDown = shap.down();
								if (ifCanDown == false)
								{
									shap.inspect();
									break;
								}
							}
							//暂停，用户按下 p 键时暂停
							else if (ch == 112)
							{
								while (true)
								{
									settextcolor(0xFF5555);		//亮蓝色
									settextstyle(20, 15, _T("宋体"), 0, 0, FW_EXTRABOLD, false, false, false);		//设置字体样式：长，宽，字体名称，//有3个重载函数
									outtextxy(550, 710, _T("暂停中···"));
									ch = _getch();
									if (ch == 112)
									{
										setfillcolor(0x5fe1f2);
										solidrectangle(540, 708, 799, 744);
										break;
									}
								}
							}
							//按下 B 键，表示返回
							else if (ch == 98)
							{
								HWND hwnd1;
								int i;
								hwnd1 = GetHWnd(); // 获取当前窗口句柄
								// 将变量值格式化写入到中间变量 s 中， _T("")是 unicode 的用法
								i = MessageBox(hwnd1, _T("确定要返回主界面吗？"), _T("返回"), MB_OKCANCEL | MB_ICONQUESTION);
								if (i == 1)
								{
									ifGameUIChooseBack = true;		//选择了返回
									shap.gameoverChooseFlag = 2;		//同时也表示了游戏结束，所以赋值为2，才能跳出循环2
									graphdefaults();		//因为在游戏界面时，更改了坐标原点，返回主界面时，要恢复坐标原点
									break;
								}
								else if (i == 2)
								{
								}
							}

							//注；上下左右对应的ch 分别为：72， 80,75,77，AWDS 对应的 ASCII码分别为：97,119,100，115
						}
						Sleep(80);
					}
					if (ifGameUIChooseBack == true)
					{
						break;
					}
				}

				//当该gameoverChoosegflag为 2 时，表示选择了返回（返回主界面）
				if (shap.gameoverChooseFlag == 2)
				{
					cout << "`11111111```````" << endl;
					break;		//跳出循环2
				}
			}
			cout << "3333333~~~~~~" << endl;
		}
		//注册账号
		else if (shap.getFlag() == "Register")
		{
			shap.myRegister();
		}
		//登录游戏
		else if (shap.getFlag() == "Log in")
		{
			index = shap.myLogIn();
			if (shap.getIfStartGame() == true)
			{
				int ch;
				bool ifgameover;

				//while循环2
				while (true)
				{
					shap.Initialization();		//初始化绘图窗口，分数,用户下标
					shap.accountIndex = index;
					shap.random1();		//随机生成方块编号 number 和 颜色 color
					shap.color2 = shap.color1;
					shap.blockColor2 = shap.blockColor1;
					shap.blockNumber2 = shap.blockNumber1;
					//while循环3
					while (true)
					{
						bool ifGameUIChooseBack = false;		//在游戏界面时，是否选择了返回（在游戏中途返回主界面）
						shap.color1 = shap.color2;
						shap.blockColor1 = shap.blockColor2;
						shap.blockNumber1 = shap.blockNumber2;
						shap.random2();
						shap.drawNextBlock(shap.blockNumber2, shap.color2);
						ifgameover = shap.ifGameOver(shap.blockNumber1, shap.color1);
						shap.draw(5, 0, shap.blockNumber1, shap.color1);
						if (ifgameover == true)
						{
							shap.gameOverUI();
							//选择"继续游戏"
							if (shap.gameoverChooseFlag == 1)
							{
								graphdefaults();		//初始化绘图因子因为之前改变了原点坐标，对后续绘图可能会产生影响
								break;		//跳出循环3
							}
							//选择“返回”
							else if (shap.gameoverChooseFlag == 2)
							{
								cout << "22222~~~~~" << endl;
								break;		//跳出循环3
							}
						}

						DWORD m_oldtime = GetTickCount();
						while (true)
						{
							bool ifCanDown;
							DWORD newtime = GetTickCount();
							if (newtime - m_oldtime >= 500)
							{
								m_oldtime = newtime;
								ifCanDown = shap.down();
								if (ifCanDown == false)
								{
									shap.inspect();
									break;
								}

							}
							//如果有一个键按下了，则_kbhit函数返回一个非0值，否则返回0
							if (_kbhit())
							{
								ch = _getch();
								cout << ch << endl;
								//按下A，左移
								if (ch == 75 || ch == 97) {
									shap.move(1, shap.getNumber(), shap.nowX, shap.nowY);
								}
								//按下D，右移
								else if (ch == 77 || ch == 100)
								{
									shap.move(2, shap.getNumber(), shap.nowX, shap.nowY);
								}
								//按下W，翻转
								else if (ch == 72 || ch == 119)
								{
									shap.turn(shap.getNumber(), shap.nowX, shap.nowY);
								}
								else if (ch == 80 || ch == 115)
								{
									shap.down();
									ifCanDown = shap.down();
									if (ifCanDown == false)
									{
										shap.inspect();
										break;
									}
								}
								//暂停，用户按下 p 键时暂停
								else if (ch == 112)
								{
									while (true)
									{
										settextcolor(0xFF5555);		//亮蓝色
										settextstyle(20, 15, _T("宋体"), 0, 0, FW_EXTRABOLD, false, false, false);		//设置字体样式：长，宽，字体名称，//有3个重载函数
										outtextxy(550, 710, _T("暂停中···"));
										ch = _getch();
										if (ch == 112)
										{
											setfillcolor(0x5fe1f2);
											solidrectangle(540, 708, 799, 744);
											break;
										}
									}
								}
								//按下 B 键，表示返回
								else if (ch == 98)
								{
									HWND hwnd1;
									int i;
									hwnd1 = GetHWnd(); // 获取当前窗口句柄
									// 将变量值格式化写入到中间变量 s 中， _T("")是 unicode 的用法
									i = MessageBox(hwnd1, _T("确定要返回主界面吗？"), _T("返回"), MB_OKCANCEL | MB_ICONQUESTION);
									if (i == 1)
									{
										ifGameUIChooseBack = true;		//选择了返回
										shap.gameoverChooseFlag = 2;		//同时也表示了游戏结束，所以赋值为2，才能跳出循环2
										graphdefaults();		//因为在游戏界面时，更改了坐标原点，返回主界面时，要恢复坐标原点
										break;
									}
									else if (i == 2)
									{
									}
								}
								//注；上下左右对应的ch 分别为：72， 80,75,77，AWDS 对应的 ASCII码分别为：97,119,100，115
							}
							Sleep(80);
						}
						if (ifGameUIChooseBack == true)
						{
							break;
						}

					}

					//当该gameoverChoosegflag为 2 时，表示选择了返回（返回主界面）
					if (shap.gameoverChooseFlag == 2)
					{
						cout << "`11111111```````" << endl;
						break;		//跳出循环2
					}
				}
			}

		}
		else if (shap.getFlag() == "About")
		{
			shap.myAbout();
		}
	}

	exit(-1);
	return 0;
}
