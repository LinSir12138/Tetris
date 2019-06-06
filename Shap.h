#pragma once
#include "Background.h"
#include <iostream>
#include <graphics.h>
#include <stdio.h>		//_stprintf_s����Ҫ�õ��������������
#include <string>
#include <cstdlib>
#include <ctime>			//���������
#include <conio.h>		//��ȡ�����¼�
#include <Windows.h>		//Sleep�����õ�
#include <fstream>
using namespace std;


//����˹�������Ϸ����
class Shap
{
public:
	Shap();		//ֻ�ǽ���һ����ͼ���ڣ������ʼ��������Initialization ������ʵ��
	~Shap();
	void Initialization();		//��ʼ��
	void random1();		//���������ǰ����
	void random2();		//���������һ������
	void draw(int deviationX, int deviationY, int type, string newColor);		//����ǰ����һ������
	void drawNextBlock(int type, string newColor);
	// move ����Ĳ���x, y �� 4 * 4 ��������Ͻǵ�����
	void move(int flag, int type, int x, int y);		//�ƶ�һ������,flag== 1��ʾ�����ƣ�flag == 2��ʾ������,type ��ʾ��������
	// turn ����Ĳ���x, y �� 4 * 4 ��������Ͻǵ�����
	void turn(int type, int x, int y);		//��ת����
	bool down();		//������Ȼ����
	void clear(int deviationX, int devaitionY, int type);		//�������飬�ڷ�����ת���߷����ƶ�ʱ����
	void setColor(string newColor);
	void inspect();		//�����鲻�ܼ�������ʱ����鱳�������Ƿ�������ȥһ�л����
	void gameOverUI();		//��Ϸ����ʱ��UI����
	bool ifGameOver(int type, string newColor);		//��Ϸ�Ƿ����,����Ϊ�������ͺͷ�����ɫ

	int eliminateLine;		//�Ѿ�����������
	int sumScore;			//�ܵ÷֣�����һ��100�֣�ͬʱ��������300�֣�ͬʱ����3��500�֣�ͬʱ����4��800�֣�
	int getNumber() const { return blockNumber1; }
	int nowX, nowY;		//�������ڵ� 4 * 4 ��������Ͻǵ�����
	string color1;		//��ǰ������ɫ
	string color2;		//��һ���������ɫ
	int blockColor1;		//��ǰ������ɫ����ı��
	int blockNumber1;		//��ǰ����ı��
	int blockColor2;		//��һ���������ɫ����ı��
	int blockNumber2;		//��һ������ı��
	int accountIndex;		//�û���¼ʱ���û����ļ��ж�Ӧ���±�
	string maxScore;
	int gameoverChooseFlag;		//����Ϸ����������е�ѡ�����ѡ�񡰼�����Ϸ�����⸳ֵΪ1��ѡ�񡰷��ء����⸳ֵΪ2


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~����ĺ�����ѡ����棬����ĺ�������Ϸ����~~~~~~~~~~~~~~~~~~~~~~~~~~~

	void loadingLeft();		//������ߵ�ͼ�ν���
	void loadingRight();	//�����ұߵ�ͼ�ν���
	void mianMouse();			//���
	void mainUI();			//������
	//justStartGame��������������һ��������ʾ���ͣ�T ��ʾ�ο͵�¼�� F ��ʾ�˺������¼,�ڶ�������Ϊ��Ӧ�˺����ļ��е��±꣬���Ϊ�ο͵�¼��ò���Ϊ0
	void justStartGame(char type, int index);	//���ٿ�ʼ��Ϸ
	void myRegister();		//ע��
	int myLogIn();			//��¼
	void myAbout();			//���ڽ���
	void myExit();			//�˳�
	string getFlag() const;
	bool getIfBack() const;
	bool getIfStartGame() const;
	void Wchar_tToString(std::string& szDst, wchar_t *wchar)
	{
		wchar_t * wText = wchar;
		DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);// WideCharToMultiByte������
		char *psText; // psTextΪchar*����ʱ���飬��Ϊ��ֵ��std::string���м����
		psText = new char[dwNum];
		WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte���ٴ�����
		szDst = psText;// std::string��ֵ
		delete[]psText;// psText�����
	}

private:
	//���ϵ��£�������
	//ÿ�еĵ�һ��Ԫ���Ƿ���ı�ţ�֮��8��Ԫ�ط�Ϊ4�ԣ�ÿһ�Էֱ�Ϊ�����ͷ��������һ��С������������Ͻǵ������ƫ����
	int site[19][9] = {
		//  1  2  3  4  5  6  7  8
	//   N  X  Y  X  Y  X  Y  X  Y
		{0, 2, 0, 0, 1, 1, 1, 2, 1},
		{1, 1, 0, 1, 1, 1, 2, 2, 2},		// L��
		{2, 0, 1, 1, 1, 2, 1, 0, 2},
		{3, 1, 0, 2, 0, 2, 1, 2, 2},

		{4, 0, 0, 0, 1, 1, 1, 2, 1},
		{5, 1, 0, 2, 0, 1, 1, 1, 2},
		{6, 0, 0, 1, 0, 2, 0, 2, 1},		// ��L��
		{7, 2, 0, 2, 1, 2, 2, 1, 2},

		{8, 1, 0, 0, 1, 1, 1, 2, 1},
		{9, 1, 0, 1, 1, 2, 1, 1, 2},		// T��
		{10, 0, 1, 1, 1, 2, 1, 1, 2},
		{11, 1, 0, 0, 1, 1, 1, 1, 2},

		{12, 0, 0, 1, 0, 1, 1, 2, 1},		//��������
		{13, 2, 0, 1, 1, 2, 1, 1, 2},

		{14, 1, 0, 2, 0, 0, 1, 1, 1},		//��������
		{15, 1, 0, 1, 1, 2, 1, 2, 2},

		{16, 0, 0, 1, 0, 2, 0, 3, 0},		// ֱ����
		{17, 1, 0, 1, 1, 1, 2, 1, 3},

		{18, 0, 0, 1, 0, 0, 1, 1, 1}		//������
	};

	//�����ƶ�����Щλ��Ӧ��Ϊ��
	int moveLeft[19][9] = {
	{0, 1, 0, -1, 1},
	{1, 0, 0, 0, 1, 0, 2},
	{2, -1, 1, -1, 2},				// L��
	{3, 0, 0, 1, 1, 1, 2},

	{4, -1, 0, -1, 1},
	{5, 0, 0, 0, 1, 0, 2},			// ��L��
	{6, -1, 0, 1, 1},
	{7, 1, 0, 1, 1, 0, 2},

	{8, 0, 0, -1, 1},
	{9, 0, 0, 0, 1, 0, 2},			// T��
	{10, -1, 1, 0, 2},
	{11, 0, 0, -1, 1, 0, 2},

	{12, -1, 0, 0, 1},				//��������
	{13, 1, 0, 0, 1, 0, 2},
	{14, 0, 0, -1, 1},				//��������
	{15, 0, 0, 0, 1, 1, 2},

	{16, -1, 0},					// ֱ����
	{17, 0, 0, 0, 1, 0, 2, 0, 3},

	{18, -1, 0, -1, 1}				//������
	};

	//�����ƶ�����Щλ��Ӧ��Ϊ��
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

	//�����ƶ�ʱ��Щλ��Ӧ��Ϊ��
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

	//��ת����Щλ��Ӧ��Ϊ�գ���Ϊ�����3��λ��Ϊ�գ����Եڶ���Ԫ�ص��±�����Ϊ 3 * 2 + 1 = 7
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

