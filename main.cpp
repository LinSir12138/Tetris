#include <iostream>
#include<windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include "Background.h"
#include "Shap.h"
using namespace std;


int main(void)
{
	//PlaySound(TEXT("D:\\music\\shiji.wav"), NULL, SND_FILENAME | SND_ASYNC);  flase
	PlaySound(TEXT("res\\shiji.wav"), NULL, SND_LOOP | SND_ASYNC);

	int index;

	//Tetris tetirs;
	Shap shap;

	//whileѭ��1
	while (true)
	{

		cout << "44444444`````" << endl;
		shap.mainUI();		//����ѡ�����
		cout << "5555555" << endl;
		//���ٿ�ʼ��Ϸ
		if (shap.getFlag() == "Just StartGame") {
			//tetirs.justStartGame('T', 0);
			int ch;
			bool ifgameover;

			//whileѭ��2
			while (true)
			{
				shap.Initialization();		//��ʼ����ͼ���ڣ�������
				shap.random1();		//������ɷ����� number �� ��ɫ color
				shap.color2 = shap.color1;
				shap.blockColor2 = shap.blockColor1;
				shap.blockNumber2 = shap.blockNumber1;
				//whileѭ��3
				while (true)
				{
					bool ifGameUIChooseBack = false;		//����Ϸ����ʱ���Ƿ�ѡ���˷��أ�����Ϸ��;���������棩
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
						//ѡ��"������Ϸ"
						if (shap.gameoverChooseFlag == 1)
						{
							graphdefaults();		//��ʼ����ͼ������Ϊ֮ǰ�ı���ԭ�����꣬�Ժ�����ͼ���ܻ����Ӱ��
							break;		//����ѭ��3
						}
						//ѡ�񡰷��ء�
						else if (shap.gameoverChooseFlag == 2)
						{
							cout << "22222~~~~~" << endl;
							break;		//����ѭ��3
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
						//�����һ���������ˣ���_kbhit��������һ����0ֵ�����򷵻�0
						if (_kbhit())
						{
							ch = _getch();
							cout << ch << endl;
							//����A������
							if (ch == 75 || ch == 97) {
								shap.move(1, shap.getNumber(), shap.nowX, shap.nowY);
							}
							//����D������
							else if (ch == 77 || ch == 100)
							{
								shap.move(2, shap.getNumber(), shap.nowX, shap.nowY);
							}
							//����W����ת
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
							//��ͣ���û����� p ��ʱ��ͣ
							else if (ch == 112)
							{
								while (true)
								{
									settextcolor(0xFF5555);		//����ɫ
									settextstyle(20, 15, _T("����"), 0, 0, FW_EXTRABOLD, false, false, false);		//����������ʽ���������������ƣ�//��3�����غ���
									outtextxy(550, 710, _T("��ͣ�С�����"));
									ch = _getch();
									if (ch == 112)
									{
										setfillcolor(0x5fe1f2);
										solidrectangle(540, 708, 799, 744);
										break;
									}
								}
							}
							//���� B ������ʾ����
							else if (ch == 98)
							{
								HWND hwnd1;
								int i;
								hwnd1 = GetHWnd(); // ��ȡ��ǰ���ھ��
								// ������ֵ��ʽ��д�뵽�м���� s �У� _T("")�� unicode ���÷�
								i = MessageBox(hwnd1, _T("ȷ��Ҫ������������"), _T("����"), MB_OKCANCEL | MB_ICONQUESTION);
								if (i == 1)
								{
									ifGameUIChooseBack = true;		//ѡ���˷���
									shap.gameoverChooseFlag = 2;		//ͬʱҲ��ʾ����Ϸ���������Ը�ֵΪ2����������ѭ��2
									graphdefaults();		//��Ϊ����Ϸ����ʱ������������ԭ�㣬����������ʱ��Ҫ�ָ�����ԭ��
									break;
								}
								else if (i == 2)
								{
								}
							}

							//ע���������Ҷ�Ӧ��ch �ֱ�Ϊ��72�� 80,75,77��AWDS ��Ӧ�� ASCII��ֱ�Ϊ��97,119,100��115
						}
						Sleep(80);
					}
					if (ifGameUIChooseBack == true)
					{
						break;
					}
				}

				//����gameoverChoosegflagΪ 2 ʱ����ʾѡ���˷��أ����������棩
				if (shap.gameoverChooseFlag == 2)
				{
					cout << "`11111111```````" << endl;
					break;		//����ѭ��2
				}
			}
			cout << "3333333~~~~~~" << endl;
		}
		//ע���˺�
		else if (shap.getFlag() == "Register")
		{
			shap.myRegister();
		}
		//��¼��Ϸ
		else if (shap.getFlag() == "Log in")
		{
			index = shap.myLogIn();
			if (shap.getIfStartGame() == true)
			{
				int ch;
				bool ifgameover;

				//whileѭ��2
				while (true)
				{
					shap.Initialization();		//��ʼ����ͼ���ڣ�����,�û��±�
					shap.accountIndex = index;
					shap.random1();		//������ɷ����� number �� ��ɫ color
					shap.color2 = shap.color1;
					shap.blockColor2 = shap.blockColor1;
					shap.blockNumber2 = shap.blockNumber1;
					//whileѭ��3
					while (true)
					{
						bool ifGameUIChooseBack = false;		//����Ϸ����ʱ���Ƿ�ѡ���˷��أ�����Ϸ��;���������棩
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
							//ѡ��"������Ϸ"
							if (shap.gameoverChooseFlag == 1)
							{
								graphdefaults();		//��ʼ����ͼ������Ϊ֮ǰ�ı���ԭ�����꣬�Ժ�����ͼ���ܻ����Ӱ��
								break;		//����ѭ��3
							}
							//ѡ�񡰷��ء�
							else if (shap.gameoverChooseFlag == 2)
							{
								cout << "22222~~~~~" << endl;
								break;		//����ѭ��3
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
							//�����һ���������ˣ���_kbhit��������һ����0ֵ�����򷵻�0
							if (_kbhit())
							{
								ch = _getch();
								cout << ch << endl;
								//����A������
								if (ch == 75 || ch == 97) {
									shap.move(1, shap.getNumber(), shap.nowX, shap.nowY);
								}
								//����D������
								else if (ch == 77 || ch == 100)
								{
									shap.move(2, shap.getNumber(), shap.nowX, shap.nowY);
								}
								//����W����ת
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
								//��ͣ���û����� p ��ʱ��ͣ
								else if (ch == 112)
								{
									while (true)
									{
										settextcolor(0xFF5555);		//����ɫ
										settextstyle(20, 15, _T("����"), 0, 0, FW_EXTRABOLD, false, false, false);		//����������ʽ���������������ƣ�//��3�����غ���
										outtextxy(550, 710, _T("��ͣ�С�����"));
										ch = _getch();
										if (ch == 112)
										{
											setfillcolor(0x5fe1f2);
											solidrectangle(540, 708, 799, 744);
											break;
										}
									}
								}
								//���� B ������ʾ����
								else if (ch == 98)
								{
									HWND hwnd1;
									int i;
									hwnd1 = GetHWnd(); // ��ȡ��ǰ���ھ��
									// ������ֵ��ʽ��д�뵽�м���� s �У� _T("")�� unicode ���÷�
									i = MessageBox(hwnd1, _T("ȷ��Ҫ������������"), _T("����"), MB_OKCANCEL | MB_ICONQUESTION);
									if (i == 1)
									{
										ifGameUIChooseBack = true;		//ѡ���˷���
										shap.gameoverChooseFlag = 2;		//ͬʱҲ��ʾ����Ϸ���������Ը�ֵΪ2����������ѭ��2
										graphdefaults();		//��Ϊ����Ϸ����ʱ������������ԭ�㣬����������ʱ��Ҫ�ָ�����ԭ��
										break;
									}
									else if (i == 2)
									{
									}
								}
								//ע���������Ҷ�Ӧ��ch �ֱ�Ϊ��72�� 80,75,77��AWDS ��Ӧ�� ASCII��ֱ�Ϊ��97,119,100��115
							}
							Sleep(80);
						}
						if (ifGameUIChooseBack == true)
						{
							break;
						}

					}

					//����gameoverChoosegflagΪ 2 ʱ����ʾѡ���˷��أ����������棩
					if (shap.gameoverChooseFlag == 2)
					{
						cout << "`11111111```````" << endl;
						break;		//����ѭ��2
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