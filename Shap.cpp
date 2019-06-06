#include "Shap.h"

const string fileAccountNumber = "res\\AccountNumber.txt";
const string fileAccountName = "res\\AccountName.txt";
const string fileAccountPassword = "res\\AccountPassword.txt";
const string fileMaxScore = "res\\MaxScore.txt";


Shap::Shap()
{
	//��ʼ��640 * 480 �Ļ�ͼ��Ļ,�����ùرմ��ڰ�ť
	initgraph(800, 744, NOCLOSE);

	// ���ñ���ɫΪ��ɫ
	setbkcolor(0xFFFFFF);
	// �ñ���ɫ�����Ļ
	cleardevice();

	HWND hwnd;
	// 1.���ô��ھ���������洰����Ϣ
	hwnd = GetHWnd();
	// 2.��ȡ���ھ��
	SetWindowText(hwnd, _T("����˹����"));
}


Shap::~Shap()
{
	_getch();			//�����������
	closegraph();		//�رջ�ͼ����
}

//��ʼ��
void Shap::Initialization()
{
	//��ʼ��640 * 480 �Ļ�ͼ��Ļ,�����ùرմ��ڰ�ť
	//��ʼ����ͼ������ Tetris.cpp �ļ��г�ʼ��
	//initgraph(800, 744, SHOWCONSOLE | NOCLOSE);
	// ���ñ���ɫΪ��ɫ
	background.backgroundInitialization();		//������ʼ��
	setbkcolor(0xFFFFFF);
	// �ñ���ɫ�����Ļ
	cleardevice();
	//������߾��ο�
	setfillcolor(0xd8dbdc);		//��߿����õ�ǰ�����ɫ �� ��ɫ
	fillrectangle(0, 0, 550, 744);		//�����ο�,4�������ֱ�Ϊ�������µ�����
	setfillcolor(0x5fe1f2);		//�ұ߿����õ�ǰ�����ɫ ����ɫ
	fillrectangle(550, 0, 800, 744);
	//��Ϸ�߿�
	setfillcolor(0xEDECEC);		//�ȻҰ׸���һ��,��Ϸ�ڿ����ɫ
	solidrectangle(73, 0, 476, 744);		//��13��ÿ��24
	setfillcolor(0xd8dbdc);
	solidrectangle(0, 713, 550, 744);

	//��ɱ��������ɺ����¶�������ԭ��
	setorigin(73 - 31, 0);		//��������ԭ��,���ǵ�������ƶ�����ת������ԭ���x����Ҫ����ƫ��һ�񣬼�31

	settextstyle(25, 20, _T("����"), 0, 0, FW_EXTRABOLD, false, false, false);		//����������ʽ���������������ƣ�//��3�����غ���
	settextcolor(0);
	setbkcolor(0x5fe1f2);		//�ұ߿����õ�ǰ�����ɫ ����ɫ
	setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������
	//����y�����ټ� 30
	outtextxy(530, 20, _T("Hello:"));
	outtextxy(530, 120, _T("Next:"));
	setfillcolor(0xFFFFFF);
	solidrectangle(560, 180, 720, 340);		//���� hello ���������
	outtextxy(530, 370, _T("MaxScore:"));
	outtextxy(530, 470, _T("NowScore:"));
	outtextxy(530, 570, _T("Lines:"));
	settextcolor(0xFF5555);		//����ɫ
	settextstyle(20, 15, _T("����"), 0, 0, FW_EXTRABOLD, false, false, false);		//����������ʽ���������������ƣ�//��3�����غ���
	outtextxy(520, 670, _T("��ͣ(P)"));
	outtextxy(650, 670, _T("�˳�(B)"));
	settextcolor(0);

	//��ʼ���ұ߿�ķ���
	setfillcolor(0x5fe1f2);
	//�ñ���ɫ���ο򸲸�
	solidrectangle(520, 405, 799, 465);		//���� maxScore ���������
	solidrectangle(520, 505, 799, 565);		//���� nextScore ���������
	solidrectangle(520, 605, 799, 665);		//���� lines ���������
	eliminateLine = 0;		//��ʼ��������������
	sumScore = 0;		//��ʼ���ܷ���
	wchar_t tempSumScore[15];
	wchar_t tempEliminateLine[15];
	_stprintf_s(tempSumScore, _T("%d"), sumScore);	// ������ֵ��ʽ��д�뵽�м���� tempSumScore �У� _T("")�� unicode ���÷�
	_stprintf_s(tempEliminateLine, _T("%d"), eliminateLine);
	settextstyle(25, 20, _T("����"), 0, 0, FW_EXTRABOLD, false, false, false);		//����������ʽ���������������ƣ�//��3�����غ���
	outtextxy(580, 520, tempSumScore);
	outtextxy(580, 620, tempEliminateLine);

	setfillcolor(0xFF5555);
	solidcircle(3, 3, 2);
	accountIndex = 0;		//���±��1��ʼ������һ��ѧ�����±�Ϊ1
	gameoverChooseFlag = 0;		//��ʼ��Ϊ 0��������һ�ζ�gameoverChooseFlag�ĸ�ֵ�Ժ�������Ӱ��
}

//ÿ�ο�ʼ��Ϸʱֻ����һ�Σ����ɵ�һ��������飬��ʾ�û����ƺ͸��û���߷�
void Shap::random1()
{
	int accountNumber;
	//string tempMaxScore;		//��ʱ��������߷�,��Ϊgetline������ȡ��������һ���ַ���
	string tempAccountName;		//�˺�����
	wchar_t wcharMaxScore[15];
	wchar_t wcharAccountName[15];
	fstream fileAccount;
	//�����ж��Ƿ�Ҫ��ʾ�û�����,������û����˺������¼������ʾ�˺����ƺ���߷֣�������ο͵�¼������ʾ�˺ź���߷�

	if (accountIndex != 0)
	{
		//�õ��˺Ÿ���
		fileAccount.open(fileAccountNumber, ios_base::in);
		fileAccount >> accountNumber;
		fileAccount.close();
		fileAccount.open(fileAccountName, ios_base::in);
		//��ΪaccountIndex��1��ʼ������һ��ѧ�����±�Ϊ1��ע��������i=1��i <= accountNumber
		for (int i = 1; i <= accountNumber; i++) {
			getline(fileAccount, tempAccountName, '\n');
			if (i == accountIndex)
			{
				break;
			}
		}
		fileAccount.close();
		//��ʾ��߷�
		fileAccount.open(fileMaxScore, ios_base::in);
		for (int i = 1; i <= accountNumber; i++)
		{
			getline(fileAccount, maxScore, '\n');
			if (i == accountIndex)
			{
				break;
			}
		}
	}
	//��ʾ�˺�����
	swprintf(wcharAccountName, 100, L"%S", tempAccountName.c_str());	//ע���д,name1ָ����ڴ�����洢��wchar_t���͵� 
	swprintf(wcharMaxScore, 100, L"%S", maxScore.c_str());
	outtextxy(530, 70, wcharAccountName);
	outtextxy(580, 420, wcharMaxScore);




	srand(int(time(0)));
	blockColor1 = (rand() % 7) + 1;
	//��Ӧ����ɫ�ֱ�Ϊ �죬 ������ �ƣ� �̣��࣬������
	switch (blockColor1)
	{
	case 1:
		color1 = "0x5555FF";		//��ɫ
		break;
	case 2:
		color1 = "0xEBACD2";		//��ɫ
		break;
	case 3:
		color1 = "0x55FFFF";		//��ɫ
		break;
	case 4:
		color1 = "0x55FF55";		//��ɫ
		break;
	case 5:
		color1 = "0xFFFF55";		//����ɫ
		break;
	case 6:
		color1 = "0xFF5555";		//����ɫ
		break;
	case 7:
		color1 = "0xAA00AA";		//��ɫ
		break;
	default:
		break;
	}

	blockNumber1 = (rand() % 19);		//0 ~ 18,������
}

//���ɺ������������
void Shap::random2()
{
	srand(int(time(0)) + 1);		//��ֹ�͵�һ�����ɵ������һ��
	blockColor2 = (rand() % 7) + 1;
	//��Ӧ����ɫ�ֱ�Ϊ �죬 ������ �ƣ� �̣��࣬������
	switch (blockColor2)
	{
	case 1:
		color2 = "0x5555FF";		//��ɫ
		break;
	case 2:
		color2 = "0xEBACD2";		//��ɫ
		break;
	case 3:
		color2 = "0x55FFFF";		//��ɫ
		break;
	case 4:
		color2 = "0x55FF55";		//��ɫ
		break;
	case 5:
		color2 = "0xFFFF55";		//����ɫ
		break;
	case 6:
		color2 = "0xFF5555";		//����ɫ
		break;
	case 7:
		color2 = "0xAA00AA";		//��ɫ
		break;
	default:
		break;
	}

	blockNumber2 = (rand() % 19);		//0 ~ 18,������
}

//�滭��ǰ���飬�����deviationX�� deviationY ��4 * 4 ��������Ͻǵĵ������ԭ�������ƫ�Ƹ�����
void Shap::draw(int deviationX, int deviationY, int type, string newColor)
{
	/*
		ע�� deviationX�� deviationY  ��ʾ��������� 4 * 4 ��������Ͻǵĵ������ ԭ�������ƫ�Ƹ�����
			 �� x, y ����ÿС��ĳ��ȣ��õ�Ox�� Oy����ʾ  4 * 4 ��������Ͻǵ�����
			 Ȼ���ڸ��ݷ��������type ����Ox�� Oy Ϊ�ο���������Ӧ�ķ���
			 Ĭ��ÿһ��С������ 31 * 31�� ���ǵ����ۣ�ʵ������ɫ�� Ϊ 28 * 28
	*/

	//Ox�� Oy����ʾ  4 * 4 ��������Ͻǵ�����
	int Ox, Oy;
	Ox = deviationX * 31;
	Oy = deviationY * 31;
	nowX = Ox;
	nowY = Oy;

	setColor(newColor);
	solidrectangle(Ox + 31 * site[type][1] + 1.5, Oy + 31 * site[type][2] + 1.5, Ox + 31 * site[type][1] + 1.5 + 28, Oy + 31 * site[type][2] + 1.5 + 28);
	solidrectangle(Ox + 31 * site[type][3] + 1.5, Oy + 31 * site[type][4] + 1.5, Ox + 31 * site[type][3] + 1.5 + 28, Oy + 31 * site[type][4] + 1.5 + 28);
	solidrectangle(Ox + 31 * site[type][5] + 1.5, Oy + 31 * site[type][6] + 1.5, Ox + 31 * site[type][5] + 1.5 + 28, Oy + 31 * site[type][6] + 1.5 + 28);
	solidrectangle(Ox + 31 * site[type][7] + 1.5, Oy + 31 * site[type][8] + 1.5, Ox + 31 * site[type][7] + 1.5 + 28, Oy + 31 * site[type][8] + 1.5 + 28);

	/*cout << deviationX << ", " << deviationY << endl;
	cout << deviationY + site[type][2] << endl;
	cout << deviationX + site[type][2] << endl;*/

	//�ڵ�ͼ�ϱ�Ǹõ�,//��ÿһ��С��������Ͻǵ������������С���������,�����¼����ƫ�Ƶĸ���
	//��Ϊbackground�е������ǵ�һ��Ԫ�����У��ڶ���Ԫ�����У����Ե�һ��Ԫ�ض�Ӧ����y���ڶ���Ԫ�ض�Ӧ����x
	background.setBackgroundTrue(deviationY + site[type][2], deviationX + site[type][1]);
	background.setBackgroundTrue(deviationY + site[type][4], deviationX + site[type][3]);
	background.setBackgroundTrue(deviationY + site[type][6], deviationX + site[type][5]);
	background.setBackgroundTrue(deviationY + site[type][8], deviationX + site[type][7]);

	cout << "draw newColor == " << color1 << endl;
	//Ϊÿһ��С��������ɫ
	background.setColors(deviationY + site[type][2], deviationX + site[type][1], newColor);
	background.setColors(deviationY + site[type][4], deviationX + site[type][3], newColor);
	background.setColors(deviationY + site[type][6], deviationX + site[type][5], newColor);
	background.setColors(deviationY + site[type][8], deviationX + site[type][7], newColor);


}

//���Ҳ�������һ�μ������ֵķ��飬���õ���ʾ�û�
void Shap::drawNextBlock(int type, string newColor)
{
	//Ox�� Oy����ʾ  4 * 4 ��������Ͻǵ�����
	int Ox, Oy;
	Ox = 590;
	Oy = 210;

	//��յ�ǰ�滭����
	setfillcolor(0xFFFFFF);
	solidrectangle(560, 180, 720, 340);		//�ð�ɫ�����ȸ��Ǹ����������������һ�εĻ�ͼͼ�񣩣������»�ͼ

	setColor(newColor);
	solidrectangle(Ox + 31 * site[type][1] + 1.5, Oy + 31 * site[type][2] + 1.5, Ox + 31 * site[type][1] + 1.5 + 28, Oy + 31 * site[type][2] + 1.5 + 28);
	solidrectangle(Ox + 31 * site[type][3] + 1.5, Oy + 31 * site[type][4] + 1.5, Ox + 31 * site[type][3] + 1.5 + 28, Oy + 31 * site[type][4] + 1.5 + 28);
	solidrectangle(Ox + 31 * site[type][5] + 1.5, Oy + 31 * site[type][6] + 1.5, Ox + 31 * site[type][5] + 1.5 + 28, Oy + 31 * site[type][6] + 1.5 + 28);
	solidrectangle(Ox + 31 * site[type][7] + 1.5, Oy + 31 * site[type][8] + 1.5, Ox + 31 * site[type][7] + 1.5 + 28, Oy + 31 * site[type][8] + 1.5 + 28);
}

//����Ĳ���x, y �� 4 * 4 ��������Ͻǵ�����,flag = 1��ʾ���ƣ� flag = 2��ʾ����,type��ʾ����ı��
void Shap::move(int flag, int type, int x, int y)
{
	//4 * 4 ��������Ͻǵĵ������ԭ�������ƫ�Ƹ����� 
	//cout << "x, y ==" << x << "," << y << endl;
	int deviationX, deviationY;
	deviationX = x / 31;
	deviationY = y / 31;
	bool ifempty1, ifempty2, ifempty3, ifempty4 = false;
	bool ifLeftEmpty = false;
	bool ifRightEmpty = false;
	//����
	if (flag == 1) {
		switch (type)
		{
			ifLeftEmpty = false;		//ÿ�ν���switch��ʱ��Ҫ��ʼ��ifLeftEmpty��ֵ(��Ҫ)
		case 16:
			ifempty1 = false;
			ifempty1 = background.ifEmpty(deviationY + moveLeft[type][2], deviationX + moveLeft[type][1]);
			if (ifempty1 == true)
			{
				ifLeftEmpty = true;
			}
			break;
		case 0:
		case 2:
		case 4:
		case 6:
		case 8:
		case 10:
		case 12:
		case 14:
		case 18:
			ifempty1 = false;
			ifempty2 = false;
			ifempty1 = background.ifEmpty(deviationY + moveLeft[type][2], deviationX + moveLeft[type][1]);
			ifempty2 = background.ifEmpty(deviationY + moveLeft[type][4], deviationX + moveLeft[type][3]);
			if (ifempty1 == true && ifempty2 == true)
			{
				ifLeftEmpty = true;
			}
			break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 9:
		case 11:
		case 13:
		case 15:
			ifempty1 = false;
			ifempty2 = false;
			ifempty3 = false;
			ifempty1 = background.ifEmpty(deviationY + moveLeft[type][2], deviationX + moveLeft[type][1]);
			ifempty2 = background.ifEmpty(deviationY + moveLeft[type][4], deviationX + moveLeft[type][3]);
			ifempty3 = background.ifEmpty(deviationY + moveLeft[type][6], deviationX + moveLeft[type][5]);
			if (ifempty1 == true && ifempty2 == true && ifempty3 == true)
			{
				ifLeftEmpty = true;
			}
		case 17:
			ifempty1 = false;
			ifempty2 = false;
			ifempty3 = false;
			ifempty4 = false;
			ifempty1 = background.ifEmpty(deviationY + moveLeft[type][2], deviationX + moveLeft[type][1]);
			ifempty2 = background.ifEmpty(deviationY + moveLeft[type][4], deviationX + moveLeft[type][3]);
			ifempty3 = background.ifEmpty(deviationY + moveLeft[type][6], deviationX + moveLeft[type][5]);
			ifempty4 = background.ifEmpty(deviationY + moveLeft[type][8], deviationX + moveLeft[type][7]);
			if (ifempty1 == true && ifempty2 == true && ifempty3 == true)
			{
				ifLeftEmpty = true;
			}
		default:
			break;
		}

		if (ifLeftEmpty)
		{
			//nowX = nowX - 31;
			clear(deviationX, deviationY, type);
			draw(deviationX - 1, deviationY, type, color1);
		}
	}
	//����
	else if (flag == 2)
	{
		switch (type)
		{
			ifRightEmpty = false;		//ÿ�ν���switchѭ����Ҫ����ifRightEmpty��ֵΪfalse
			//������������ֱ��ʾ�赲�÷������Ƶ�λ���м�������1 ��4
		case 16:
			ifempty1 = false;
			ifempty1 = background.ifEmpty(deviationY + moveRight[type][2], deviationX + moveRight[type][1]);
			if (ifempty1 == true)
			{
				ifRightEmpty = true;
			}
			break;
		case 0:
		case 2:
		case 4:
		case 6:
		case 8:
		case 10:
		case 12:
		case 14:
		case 18:
			ifempty1 = false;
			ifempty2 = false;
			ifempty1 = background.ifEmpty(deviationY + moveRight[type][2], deviationX + moveRight[type][1]);
			ifempty2 = background.ifEmpty(deviationY + moveRight[type][4], deviationX + moveRight[type][3]);
			if (ifempty1 == true && ifempty2 == true)
			{
				ifRightEmpty = true;
			}
			/*cout << "ifRightEmpty is" << ifRightEmpty << endl;*/
			break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 9:
		case 11:
		case 13:
		case 15:
			ifempty1 = false;
			ifempty2 = false;
			ifempty3 = false;
			ifempty1 = background.ifEmpty(deviationY + moveRight[type][2], deviationX + moveRight[type][1]);
			ifempty2 = background.ifEmpty(deviationY + moveRight[type][4], deviationX + moveRight[type][3]);
			ifempty3 = background.ifEmpty(deviationY + moveRight[type][6], deviationX + moveRight[type][5]);
			if (ifempty1 == true && ifempty2 == true && ifempty3 == true)
			{
				ifRightEmpty = true;
			}
			//cout << "ifRightEmpty is" << ifRightEmpty << endl;
			break;
		case 17:
			ifempty1 = false;
			ifempty2 = false;
			ifempty3 = false;
			ifempty4 = false;
			ifempty1 = background.ifEmpty(deviationY + moveRight[type][2], deviationX + moveRight[type][1]);
			ifempty2 = background.ifEmpty(deviationY + moveRight[type][4], deviationX + moveRight[type][3]);
			ifempty3 = background.ifEmpty(deviationY + moveRight[type][6], deviationX + moveRight[type][5]);
			ifempty4 = background.ifEmpty(deviationY + moveRight[type][8], deviationX + moveRight[type][7]);
			if (ifempty1 == true && ifempty2 == true && ifempty3 == true && ifempty4 == true)
			{
				ifRightEmpty = true;
			}
			//cout << "ifRightEmpty is" << ifRightEmpty << endl;
			break;
		default:
			break;
		}

		if (ifRightEmpty)
		{
			//nowX = nowX + 1;
			clear(deviationX, deviationY, type);
			draw(deviationX + 1, deviationY, type, color1);
		}
	}
}
// turn ����Ĳ���x, y �� 4 * 4 ��������Ͻǵ�����
void Shap::turn(int type, int x, int y)
{
	//4 * 4 ��������Ͻǵĵ������ԭ�������ƫ�Ƹ����� 
	int deviationX, deviationY;
	deviationX = x / 31;
	deviationY = y / 31;
	bool ifempty1, ifempty2, ifempty3, ifempty4 = false;
	bool ifTurnIsEmpty = false;

	switch (type)
	{
		ifTurnIsEmpty = false;
	case 18:
		ifTurnIsEmpty = true;
		break;
	case 8:
	case 9:
	case 10:
	case 11:
		ifempty1 = false;
		ifempty1 = background.ifEmpty(deviationY + turnIsempty[type][2], deviationX + turnIsempty[type][1]);
		if (ifempty1 == true)
		{
			ifTurnIsEmpty = true;
		}
		break;
	case 3:
	case 5:
	case 6:
	case 12:
	case 13:
	case 14:
	case 15:
		ifempty1 = false;
		ifempty2 = false;
		ifempty1 = background.ifEmpty(deviationY + turnIsempty[type][2], deviationX + turnIsempty[type][1]);
		ifempty2 = background.ifEmpty(deviationY + turnIsempty[type][4], deviationX + turnIsempty[type][3]);
		if (ifempty1 == true && ifempty2 == true)
		{
			ifTurnIsEmpty = true;
		}
		break;
	case 0:
	case 1:
	case 2:
	case 4:
	case 7:
	case 16:
	case 17:
		ifempty1 = false;
		ifempty2 = false;
		ifempty3 = false;
		ifempty1 = background.ifEmpty(deviationY + turnIsempty[type][2], deviationX + turnIsempty[type][1]);
		ifempty2 = background.ifEmpty(deviationY + turnIsempty[type][4], deviationX + turnIsempty[type][3]);
		ifempty3 = background.ifEmpty(deviationY + turnIsempty[type][6], deviationX + turnIsempty[type][5]);
		if (ifempty1 == true && ifempty2 == true && ifempty3 == true)
		{
			ifTurnIsEmpty = true;
		}
		break;
	default:
		break;
	}

	//ifTurnIsEmpty Ϊ��ʱ����ʾ���������ת
	if (ifTurnIsEmpty)
	{
		clear(deviationX, deviationY, type);
		//���ݷ���ı�ţ�ȷ����ת֮��ķ����ţ�����������ת֮��ķ���
		//��ת֮��ͬʱҪ�ı� Shap ���е� number
		switch (type)
		{
			//������ǣ�type + 1
		case 0:
		case 1:
		case 2:
		case 4:
		case 5:
		case 6:
		case 8:
		case 9:
		case 10:
		case 12:
		case 14:
		case 16:
			blockNumber1 = type + 1;
			break;
			//������ǣ�type - 3
		case 3:
		case 7:
		case 11:
			blockNumber1 = type - 3;
			break;
			//������ǣ�type - 1
		case 13:
		case 15:
		case 17:
			blockNumber1 = type - 1;
			break;
			//������ǣ�type����
		case 18:
			break;
		default:
			break;
		}
		draw(deviationX, deviationY, blockNumber1, color1);
	}
}

//������������
bool Shap::down()
{
	bool ifempty1, ifempty2, ifempty3, ifempty4;		//ÿ��������4��С���鹹��


	//��ֱ�����ܹ���24����Ϊ�����һ���Ǳ߽磬������0����22���ܹ�23������Ϸ����

	bool flagIfDown = false;		//�÷����ܷ�����
	//Ȼ���жϸ÷����ܷ����䣬����ܣ��������»�һ������һ����ķ���
	switch (blockNumber1)
	{
	case 17:
		ifempty1 = false;
		ifempty1 = background.ifEmpty(nowY / 31 + moveDown[blockNumber1][2], nowX / 31 + moveDown[blockNumber1][1]);
		if (ifempty1 == true) {
			flagIfDown = true;
		}
		break;
	case 1:
	case 3:
	case 5:
	case 7:
	case 9:
	case 11:
	case 13:
	case 15:
	case 18:
		ifempty1 = false;
		ifempty2 = false;
		ifempty1 = background.ifEmpty(nowY / 31 + moveDown[blockNumber1][2], nowX / 31 + moveDown[blockNumber1][1]);
		ifempty2 = background.ifEmpty(nowY / 31 + moveDown[blockNumber1][4], nowX / 31 + moveDown[blockNumber1][3]);
		if (ifempty1 == true && ifempty2 == true)
		{
			flagIfDown = true;
		}
		break;
	case 0:
	case 2:
	case 4:
	case 6:
	case 8:
	case 10:
	case 12:
	case 14:
		ifempty1 = false;
		ifempty2 = false;
		ifempty3 = false;
		ifempty1 = background.ifEmpty(nowY / 31 + moveDown[blockNumber1][2], nowX / 31 + moveDown[blockNumber1][1]);
		ifempty2 = background.ifEmpty(nowY / 31 + moveDown[blockNumber1][4], nowX / 31 + moveDown[blockNumber1][3]);
		ifempty3 = background.ifEmpty(nowY / 31 + moveDown[blockNumber1][6], nowX / 31 + moveDown[blockNumber1][5]);
		if (ifempty1 == true && ifempty2 == true && ifempty3 == true)
		{
			flagIfDown = true;
		}
		break;
	case 16:
		ifempty1 = false;
		ifempty2 = false;
		ifempty3 = false;
		ifempty4 = false;
		ifempty1 = background.ifEmpty(nowY / 31 + moveDown[blockNumber1][2], nowX / 31 + moveDown[blockNumber1][1]);
		ifempty2 = background.ifEmpty(nowY / 31 + moveDown[blockNumber1][4], nowX / 31 + moveDown[blockNumber1][3]);
		ifempty3 = background.ifEmpty(nowY / 31 + moveDown[blockNumber1][6], nowX / 31 + moveDown[blockNumber1][5]);
		ifempty4 = background.ifEmpty(nowY / 31 + moveDown[blockNumber1][8], nowX / 31 + moveDown[blockNumber1][7]);
		if (ifempty1 == true && ifempty2 == true && ifempty3 == true && ifempty4 == true
			)
		{
			flagIfDown = true;
		}
		break;
	default:
		break;
	}

	if (flagIfDown == true) {
		clear(nowX / 31, nowY / 31, blockNumber1);
		draw(nowX / 31, nowY / 31 + 1, blockNumber1, color1);
	}
	return flagIfDown;
}

//����Ĳ����� 4 * 4 �������Ͻ������ԭ���ƫ����
void Shap::clear(int deviationX, int deviationY, int type)
{
	//�ڵ�ͼ�ϱ�Ǹõ�,//��ÿһ��С��������Ͻǵ������������С���������,�����¼����ƫ�Ƶĸ���
	//��Ϊbackground�е������ǵ�һ��Ԫ�����У��ڶ���Ԫ�����У����Ե�һ��Ԫ�ض�Ӧ����y���ڶ���Ԫ�ض�Ӧ����x
	background.setBackgroundFalse(deviationY + site[type][2], deviationX + site[type][1]);
	background.setBackgroundFalse(deviationY + site[type][4], deviationX + site[type][3]);
	background.setBackgroundFalse(deviationY + site[type][6], deviationX + site[type][5]);
	background.setBackgroundFalse(deviationY + site[type][8], deviationX + site[type][7]);

	background.setColors(deviationY + site[type][2], deviationX + site[type][1], "0xEDECEC");
	background.setColors(deviationY + site[type][4], deviationX + site[type][3], "0xEDECEC");
	background.setColors(deviationY + site[type][6], deviationX + site[type][5], "0xEDECEC");
	background.setColors(deviationY + site[type][8], deviationX + site[type][7], "0xEDECEC");



	setfillcolor(0xEDECEC);
	solidrectangle(nowX + 31 * site[type][1] + 1.5, nowY + 31 * site[type][2] + 1.5, nowX + 31 * site[type][1] + 1.5 + 28, nowY + 31 * site[type][2] + 1.5 + 28);
	solidrectangle(nowX + 31 * site[type][3] + 1.5, nowY + 31 * site[type][4] + 1.5, nowX + 31 * site[type][3] + 1.5 + 28, nowY + 31 * site[type][4] + 1.5 + 28);
	solidrectangle(nowX + 31 * site[type][5] + 1.5, nowY + 31 * site[type][6] + 1.5, nowX + 31 * site[type][5] + 1.5 + 28, nowY + 31 * site[type][6] + 1.5 + 28);
	solidrectangle(nowX + 31 * site[type][7] + 1.5, nowY + 31 * site[type][8] + 1.5, nowX + 31 * site[type][7] + 1.5 + 28, nowY + 31 * site[type][8] + 1.5 + 28);
}

//���÷������ɫ
void Shap::setColor(string newColor)
{
	//��Ӧ����ɫ�ֱ�Ϊ �죬 �ȣ� �ƣ� �̣��࣬������
	if (newColor == "0x5555FF") {
		setfillcolor(0x5555FF);

	}
	else if (newColor == "0xEBACD2")
	{
		setfillcolor(0xEBACD2);
	}
	else if (newColor == "0x55FFFF")
	{
		setfillcolor(0x55FFFF);
	}
	else if (newColor == "0x55FF55")
	{
		setfillcolor(0x55FF55);
	}
	else if (newColor == "0xFFFF55")
	{
		setfillcolor(0xFFFF55);
	}
	else if (newColor == "0xFF5555")
	{
		setfillcolor(0xFF5555);
	}
	else
	{
		setfillcolor(0xAA00AA);
	}

}

//����Ƿ�Ҫ���Ѿ����еķ����������
void Shap::inspect()
{
	//�����Щ���Ѿ�����
	bool ifHaveFull = false;
	int tempflag;
	int sumLine = 0;
	int lines[23];
	for (int i = 22; i >= 0; i--)
	{
		tempflag = 1;
		for (int j = 1; j < 14; j++)
		{
			tempflag *= background.ifFull(i, j);
		}
		if (tempflag == 1)
		{
			ifHaveFull = true;
			lines[sumLine] = i;
			cout << lines[sumLine] << endl;
			sumLine++;
		}
	}

	eliminateLine += sumLine;		//������������������
	if (sumLine == 1)
	{
		sumScore += 100;
	}
	else if (sumLine == 2)
	{
		sumScore += 300;
	}
	else if (sumLine == 3)
	{
		sumScore += 500;
	}
	else if (sumLine == 4)
	{
		sumScore += 800;
	}

	//������߷�MaxScore��ֵ
	int toIntMaxScore = atoi(maxScore.c_str());
	cout << "toIntMaxScore==" << toIntMaxScore << endl;
	cout << "sumScore ==" << sumScore << endl;
	if (sumScore >= toIntMaxScore)
	{
		toIntMaxScore = sumScore;
		cout << "toIntMaxScore2 ==" << toIntMaxScore << endl;
		maxScore = to_string(sumScore);		//������߷ֶ�Ӧ���ַ���
		cout << "StringMaxScore==" << maxScore << endl;
		//����߷ָı�ʱ����������߷ִ���ļ���ȥ
		fstream fileAccount;
		if (accountIndex != 0)
		{
			int accountNumber;
			//�õ��˺Ÿ���
			fileAccount.open(fileAccountNumber, ios_base::in);
			fileAccount >> accountNumber;
			fileAccount.close();

			//������߷�
			//���ļ��ж�ȡ��߷֣����һ���ַ�������
			string *p = new string[accountNumber];	//��̬�����ַ�������
			fileAccount.open(fileMaxScore, ios_base::in);
			for (int i = 0; i < accountNumber; i++) {
				getline(fileAccount, p[i], '\n');
			}
			fileAccount.close();
			//��ΪaccountIndex��1��ʼ������һ��ѧ�����±�Ϊ1����������Ӧ��Ϊ��accountIndex - 1
			p[accountIndex - 1] = maxScore;		//����߷ָ�ֵ���ַ��������ж�Ӧ��Ԫ��
			//�ڽ����ַ�������д���ļ���
			fileAccount.open(fileMaxScore, ios_base::out);
			for (int i = 0; i < accountNumber; i++)
			{
				fileAccount << p[i];
				fileAccount << endl;
			}
			fileAccount.close();		//�ر��ļ�
		}
	}

	//�����ܷ�SumScore����������eliminateLines��ֵ
	wchar_t tempSumScore[15];
	wchar_t tempEliminateLine[15];
	wchar_t tempMaxScore[15];
	_stprintf_s(tempSumScore, _T("%d"), sumScore);	// ������ֵ��ʽ��д�뵽�м���� tempSumScore �У� _T("")�� unicode ���÷�
	_stprintf_s(tempEliminateLine, _T("%d"), eliminateLine);
	cout << "aaaa" << toIntMaxScore << endl;
	_stprintf_s(tempMaxScore, _T("%d"), toIntMaxScore);
	settextstyle(25, 20, _T("����"), 0, 0, FW_EXTRABOLD, false, false, false);		//����������ʽ���������������ƣ�//��3�����غ���
	settextcolor(0);		//��ɫ
	setbkcolor(0x5fe1f2);		//�ұ߿����õ�ǰ�����ɫ ����ɫ
	setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������
	outtextxy(580, 420, tempMaxScore);
	outtextxy(580, 520, tempSumScore);
	outtextxy(580, 620, tempEliminateLine);

	if (ifHaveFull == true)
	{
		//ɾ���Ѿ����˵�һ��
		for (int i = 0; i < sumLine; i++)	//��Ҫɾ�������У��ú���ִ�ж��ٱ�
		{

			if (i != 0)
			{
				lines[i] = lines[i] + i;		//��Ϊ����������,û����һ��֮��ԭ���������˵�һ���±���һ
			}
			//ע��˳����ı���ɫ���ڸı䱳��
			//�ı䷽�����ɫ
			int n;
			for (int a = lines[i]; a > 0; a--)
			{
				for (int b = 1; b < 14; b++)
				{


					if (background.getColors(a - 1, b) == "0x5555FF")
					{
						n = 5592575;
					}
					else if (background.getColors(a - 1, b) == "0xEBACD2")
					{
						n = 15445202;

					}
					else if (background.getColors(a - 1, b) == "0x55FFFF")
					{
						n = 5636095;
					}
					else if (background.getColors(a - 1, b) == "0x55FF55")
					{
						n = 5635925;
					}
					else if (background.getColors(a - 1, b) == "0xFFFF55")
					{
						n = 16777045;
					}
					else if (background.getColors(a - 1, b) == "0xFF5555")
					{
						n = 16733525;
					}
					else if (background.getColors(a - 1, b) == "0xAA00AA")
					{
						n = 11141290;
					}
					else if (background.getColors(a - 1, b) == "0xEDECEC")
					{
						n = 15592684;
					}

					setfillcolor(n);
					solidrectangle(b * 31 + 1.5, a * 31 + 1.5, b * 31 + 1.5 + 28, a * 31 + 1.5 + 28);

					int temp1 = background.getXY(a - 1, b);
					string temp2 = background.getColors(a - 1, b);
					//Sleep(800);
					background.setXY(a, b, temp1);
					background.setColors(a, b, temp2);
				}
			}

		}
	}

}

//��Ϸ����ʱ�Ľ���
void Shap::gameOverUI()
{
	graphdefaults();		//��ʼ����ͼ������Ϊ֮ǰ�ı���ԭ�����꣬�Ժ�����ͼ���ܻ����Ӱ��

	setfillcolor(0xEDECEC);		//�ȻҰ׸���һ��
	solidrectangle(73, 0, 476, 713);		//��13��ÿ��24
	settextstyle(45, 35, _T("����"), 0, 0, FW_EXTRABOLD, false, false, false);		//����������ʽ���������������ƣ�//��3�����غ���
	setbkcolor(0xEDECEC);		//��������ı�����ɫ����ͼ��
	settextcolor(0);
	outtextxy(75, 200, _T("GAME OVER !"));
	settextcolor(0xFF5555);	//����
	outtextxy(130, 370, _T("������Ϸ"));
	outtextxy(180, 500, _T("����"));

	MOUSEMSG m;		// ���������Ϣ
	while (true)
	{
		m = GetMouseMsg();
		if (m.x > 130 && m.x < 455 && m.y > 370 && m.y < 410)
		{
			setfillcolor(0x55FF55);
			solidcircle(100, 387, 20);
			solidcircle(440, 387, 20);

			//������¼��� ���������Ϸ
			//���������������Ϣ������������ˣ�
			if (m.uMsg == WM_LBUTTONUP) {
				gameoverChooseFlag = 1;		//ѡ���˼�����Ϸ����ֵΪ1
				break;		//����ѭ����gameOver����ִ�����
			}
		}
		else if (m.x > 180 && m.x < 380 && m.y > 500 && m.y < 540)
		{
			setfillcolor(0x55FF55);
			solidcircle(150, 517, 20);
			solidcircle(345, 517, 20);

			//������¼��� ������أ����������棩
			//���������������Ϣ������������ˣ�
			if (m.uMsg == WM_LBUTTONUP) {
				gameoverChooseFlag = 2;		//ѡ���˷��أ���ֵΪ2
				break;		//����ѭ����gameOver����ִ�����
			}
		}
		else
		{
			setfillcolor(0xEDECEC);
			solidcircle(100, 387, 20);
			solidcircle(440, 387, 20);
			solidcircle(150, 517, 20);
			solidcircle(345, 517, 20);
		}
	}

}

//�ж���Ϸ�Ƿ�����������鵽�ﶥ��ʱ����Ϸ����
bool Shap::ifGameOver(int type, string newColor)
{
	//Ox�� Oy����ʾ  4 * 4 ��������Ͻǵ�����
	int Ox, Oy;
	Ox = 5 * 31;
	Oy = 0 * 31;
	int flag1, flag2, flag3, flag4;
	flag1 = background.getXY(0 + site[type][2], 5 + site[type][1]);
	flag2 = background.getXY(0 + site[type][4], 5 + site[type][3]);
	flag3 = background.getXY(0 + site[type][6], 5 + site[type][5]);
	flag4 = background.getXY(0 + site[type][8], 5 + site[type][7]);

	//�����4����������һ���Ѿ�����С�����ˣ�˵���ͼ������ֵķ�����ص���˵����Ϸ����
	if (flag1 == 1 || flag2 == 1 || flag3 == 1 || flag4 == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//Tetris::Tetris()
//{
//	//��ʼ��640 * 480 �Ļ�ͼ��Ļ,�����ùرմ��ڰ�ť
//	initgraph(800, 744, SHOWCONSOLE | NOCLOSE);
//
//	// ���ñ���ɫΪ��ɫ
//	setbkcolor(0xFFFFFF);
//	// �ñ���ɫ�����Ļ
//	cleardevice();
//
//	HWND hwnd;
//	// 1.���ô��ھ���������洰����Ϣ
//	hwnd = GetHWnd();
//	// 2.��ȡ���ھ��
//	SetWindowText(hwnd, _T("����˹����"));
//
//	////���������ο�
//	//setfillcolor(0xd8dbdc);		//��߿����õ�ǰ�����ɫ �� ��ɫ
//	//fillrectangle(0, 0, 550, 600);		//�����ο�,4�������ֱ�Ϊ�������µ�����
//	//setfillcolor(0x5fe1f2);		//�ұ߿����õ�ǰ�����ɫ ����ɫ
//	//fillrectangle(550, 0, 800, 600);
//	////��߾��ο�
//	////����ַ���
//	//settextcolor(0x0000AA);		//����������ɫ:��ɫ
//	//setbkcolor(0xd8dbdc);		//�������ñ���ɫ������
//	//setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������
//	//settextstyle(80, 55, _T("����"), 0, 0, FW_EXTRABOLD, false, false, false);		//����������ʽ���������������ƣ�//��3�����غ���
//	//TCHAR s1[] = _T("Tetris");
//	//outtextxy(110, 90, s1);		//��ָ��λ������ַ�����x�� y�� �ַ���
//	////���ѡ��
//	//settextstyle(30, 30, _T("����"));		
//	//TCHAR s2[] = _T("Just StartGame");		//���ٿ�ʼ��Ϸ
//	//outtextxy(65, 225, s2);		//��ָ��λ������ַ�����x�� y�� �ַ���
//	//TCHAR s3[] = _T("Regist");		//ע��
//	//outtextxy(180, 300, s3);		//��ָ��λ������ַ�����x�� y�� �ַ���
//	//TCHAR s4[] = _T("Log in");		//��¼
//	//outtextxy(180, 375, s4);		//��ָ��λ������ַ�����x�� y�� �ַ���
//	//TCHAR s5[] = _T("Exit");		//�˳�
//	//outtextxy(210, 450, s5);		//��ָ��λ������ַ�����x�� y�� �ַ���
//	////�ұ߾��ο�
//	//settextcolor(0xFF5555);		//����������ɫ:����
//	//setbkcolor(0x5fe1f2);		//�������ñ���ɫ����ɫ
//	//setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������	
//	//settextstyle(20, 20, _T("����"));
//	//TCHAR sRight1[] = _T("Next:");
//	//outtextxy(580, 50, sRight1);
//	//TCHAR sRight2[] = _T("Score:");
//	//outtextxy(580, 250, sRight2);
//	//TCHAR sRight3[] = _T("Max Score:");
//	//outtextxy(580, 425, sRight3);
//	//MOUSEMSG m;		// ���������Ϣ
//	//
//	//while (true)
//	//{
//	//	m = GetMouseMsg();
//	//	//Բ���y����ͬһ����Ե��ַ�����y�����15
//	//	//���Բ���x��30�� �ұ߼�30
//	//	//����ĸ߶�Ϊ30
//	//	if ((m.x > 75) && (m.x < 500) && (m.y > 225) && (m.y < 255)) {
//	//		//�����ʾ��Just Start game
//	//		settextcolor(0);		//����������ɫ:��ɫ
//	//		setbkcolor(0xd8dbdc);		//�������ñ���ɫ����ɫ
//	//		setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������	
//	//		TCHAR t1[] = _T("Tips:Do not need to register, quick start the game!");
//	//		settextstyle(16, 0, _T("����"));	//�߶�ΪĬ��
//	//		outtextxy(10, 50, t1);
//	//		//���СԲ��
//	//		setbkcolor(0x5fe1f2);	//��ɫ
//	//		setfillcolor(0x5fe1f2);
//	//		solidcircle(40, 240, 10);
//	//		//�ұ�СԲ��
//	//		solidcircle(515, 240, 10);
//	//		//������¼�
//	//		//���������������Ϣ������������ˣ�
//	//		if (m.uMsg == WM_LBUTTONUP) {
//	//			cleardevice();
//	//		}
//	//	}
//	//	else if ((m.x > 180) && (m.x < 360) && (m.y > 300) && (m.y < 330))
//	//	{
//	//		//�����ʾ�� Register
//	//		settextcolor(0);		//����������ɫ:��ɫ
//	//		setbkcolor(0xd8dbdc);		//�������ñ���ɫ����ɫ
//	//		setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������	
//	//		TCHAR t2[] = _T("Tips:To register an account!");
//	//		settextstyle(16, 0, _T("����"));	//�߶�ΪĬ��
//	//		outtextxy(10, 50, t2);
//	//		setbkcolor(0x5fe1f2);	//��ɫ
//	//		setfillcolor(0x5fe1f2);
//	//		solidcircle(150, 315, 10);
//	//		solidcircle(390, 315, 10);
//	//	}
//	//	else if ((m.x > 180) && (m.x < 360) && (m.y > 375) && (m.y < 405))
//	//	{
//	//		//�����ʾ�� Log in
//	//		settextcolor(0);		//����������ɫ:��ɫ
//	//		setbkcolor(0xd8dbdc);		//�������ñ���ɫ����ɫ
//	//		setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������	
//	//		TCHAR t3[] = _T("Tips:Log in the game!");
//	//		settextstyle(16, 0, _T("����"));	//�߶�ΪĬ��
//	//		outtextxy(10, 50, t3);
//	//		setbkcolor(0x5fe1f2);	//��ɫ
//	//		setfillcolor(0x5fe1f2);
//	//		solidcircle(150, 390, 10);
//	//		solidcircle(390, 390, 10);
//	//	}
//	//	else if ((m.x > 180) && (m.x < 360) && (m.y > 450) && (m.y < 480))
//	//	{
//	//		//�����ʾ�� Exit
//	//		settextcolor(0);		//����������ɫ:��ɫ
//	//		setbkcolor(0xd8dbdc);		//�������ñ���ɫ����ɫ
//	//		setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������	
//	//		TCHAR t4[] = _T("Tips:To quit the game!");
//	//		settextstyle(16, 0, _T("����"));	//�߶�ΪĬ��
//	//		outtextxy(10, 50, t4);
//	//		setbkcolor(0x5fe1f2);	//��ɫ
//	//		setfillcolor(0x5fe1f2);
//	//		solidcircle(180, 465, 10);
//	//		solidcircle(360, 465, 10);
//	//		//������¼�
//	//		//���������������Ϣ������������ˣ�
//	//		if (m.uMsg == WM_LBUTTONUP) {
//	//			myExit();
//	//		}
//	//	}
//	//	else
//	//	{
//	//		setbkcolor(0xd8dbdc);		//��ɫ
//	//		setfillcolor(0xd8dbdc);
//	//		//����tips�е�����
//	//		settextcolor(0xd8dbdc);		//����������ɫ:��ɫ
//	//		setbkcolor(0xd8dbdc);		//�������ñ���ɫ����ɫ
//	//		setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������	
//	//		TCHAR tClean[] = _T("                                                   ");
//	//		settextstyle(16, 0, _T("����"));	//�߶�ΪĬ��
//	//		outtextxy(10, 50, tClean);
//	//		//solidrectangle(10, 50, 550, 40);
//	//		//clearrectangle(10, 50, 550, 40);
//	//		//����СԲ��
//	//		solidcircle(40, 240, 10);
//	//		solidcircle(515, 240, 10);
//	//		solidcircle(150, 315, 10);
//	//		solidcircle(390, 315, 10);
//	//		solidcircle(150, 390, 10);
//	//		solidcircle(390, 390, 10);
//	//		solidcircle(180, 465, 10);
//	//		solidcircle(360, 465, 10);
//	//	}
//	//	
//	//}
//	//_getch();			//�����������
//	//closegraph();		//�رջ�ͼ����
//}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~����ĺ�����ѡ����棬����ĺ�������Ϸ����~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Shap::loadingLeft()
{
	cout << "loadingLeft" << endl;
	//������߾��ο�
	setfillcolor(0xd8dbdc);		//��߿����õ�ǰ�����ɫ �� ��ɫ
	fillrectangle(0, 0, 550, 744);		//�����ο�,4�������ֱ�Ϊ�������µ�����

	//����ַ���
	settextcolor(0x0000AA);		//����������ɫ:��ɫ
	setbkcolor(0xd8dbdc);		//�������ñ���ɫ������
	setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������
	settextstyle(80, 55, _T("����"), 0, 0, FW_EXTRABOLD, false, false, false);		//����������ʽ���������������ƣ�//��3�����غ���
	TCHAR s1[] = _T("Tetris");
	outtextxy(110, 90, s1);		//��ָ��λ������ַ�����x�� y�� �ַ���
	//���ѡ��
	settextstyle(30, 30, _T("����"));
	TCHAR s2[] = _T("Just StartGame");		//���ٿ�ʼ��Ϸ
	outtextxy(65, 225, s2);		//��ָ��λ������ַ�����x�� y�� �ַ���
	TCHAR s3[] = _T("Register");		//ע��
	outtextxy(165, 300, s3);		//��ָ��λ������ַ�����x�� y�� �ַ���
	TCHAR s4[] = _T("Log in");		//��¼
	outtextxy(180, 375, s4);		//��ָ��λ������ַ�����x�� y�� �ַ���
	outtextxy(190, 450, _T("About"));
	settextcolor(0xFF5555);		//����������ɫ:����
	TCHAR s5[] = _T("Exit");		//�˳�
	outtextxy(210, 525, s5);		//��ָ��λ������ַ�����x�� y�� �ַ���

	settextcolor(0);		//����������ɫ:��ɫ
	settextstyle(25, 20, _T("����"), 0, 0, FW_EXTRABOLD, false, false, false);
	TCHAR sCreater[] = _T("-- create by �ֿ�");
	outtextxy(100, 640, sCreater);
}

void Shap::loadingRight()
{
	cout << "loadingright" << endl;
	setfillcolor(0x5fe1f2);		//�ұ߿����õ�ǰ�����ɫ ����ɫ
	fillrectangle(550, 0, 800, 744);

	//�ұ߾��ο�
	settextcolor(0xFF5555);		//����������ɫ:����
	setbkcolor(0x5fe1f2);		//�������ñ���ɫ����ɫ
	setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������	


	settextstyle(25, 20, _T("����"), 0, 0, FW_EXTRABOLD, false, false, false);		//����������ʽ���������������ƣ�//��3�����غ���
	settextcolor(0);
	setbkcolor(0x5fe1f2);		//�ұ߿����õ�ǰ�����ɫ ����ɫ
	setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������
	//��Ϊ������Ϸ����֮������ԭ��ı��ˣ�����������ĺ�����xҪ��������ԭ���ƫ������ʹ��ǰ���ͼ���غ�
	outtextxy(530 + 42, 20, _T("Hello:"));
	outtextxy(530 + 42, 120, _T("Next:"));
	setfillcolor(0xFFFFFF);
	solidrectangle(560 + 42, 180, 720 + 42, 340);
	outtextxy(530 + 42, 370, _T("MaxScore:"));
	outtextxy(530 + 42, 470, _T("NowScore:"));
	outtextxy(530 + 42, 570, _T("Lines:"));


}

//������(ѡ������Ľ���)��  ����ƶ�Ч��  �͵���¼�
void Shap::mianMouse()
{
	Sleep(1000);
	MOUSEMSG m;		// ���������Ϣ

	while (true)
	{
		m = GetMouseMsg();
		//Բ���y����ͬһ����Ե��ַ�����y�����15
		//���Բ���x��30�� �ұ߼�30
		//����ĸ߶�Ϊ30
		// Just Start Game
		if ((m.x > 75) && (m.x < 500) && (m.y > 225) && (m.y < 255)) {
			//�����ʾ��Just Start Game
			settextcolor(0);		//����������ɫ:��ɫ
			setbkcolor(0xd8dbdc);		//�������ñ���ɫ����ɫ
			setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������	
			TCHAR t1[] = _T("Tips:Do not need to register, quick start the game!");
			settextstyle(16, 0, _T("����"));	//�߶�ΪĬ��
			outtextxy(10, 50, t1);

			//���СԲ��
			setfillcolor(0x55FF55);		//��ɫ
			solidcircle(40, 240, 20);
			//�ұ�СԲ��
			solidcircle(515, 240, 20);

			//������¼�
			//���������������Ϣ������������ˣ�
			if (m.uMsg == WM_LBUTTONUP) {
				setbkcolor(0xFFFFFF);	//���ñ���ɫ
				cleardevice();			//�����Ļ���ݣ��õ�ǰ����ɫ�����Ļ����
				flag = "Just StartGame";		//����flag���������� Just StartGame
				break;
			}
		}
		// ע��
		else if ((m.x > 180) && (m.x < 360) && (m.y > 300) && (m.y < 330))
		{
			//�����ʾ�� Register
			settextcolor(0);		//����������ɫ:��ɫ
			setbkcolor(0xd8dbdc);		//�������ñ���ɫ����ɫ
			setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������	
			TCHAR t2[] = _T("Tips:To register an account!");
			settextstyle(16, 0, _T("����"));	//�߶�ΪĬ��
			outtextxy(10, 50, t2);

			setfillcolor(0x55FF55);
			solidcircle(145, 315, 20);
			solidcircle(430, 315, 20);

			// ������¼�  Register
				//���������������Ϣ������������ˣ�
			if (m.uMsg == WM_LBUTTONUP) {
				setbkcolor(0xFFFFFF);	//���ñ���ɫ
				cleardevice();			//�����Ļ���ݣ��õ�ǰ����ɫ�����Ļ����
				flag = "Register";		//����flag���������� Just StartGame
				break;
			}
		}
		//��¼
		else if ((m.x > 180) && (m.x < 360) && (m.y > 375) && (m.y < 405))
		{
			//�����ʾ�� Log in
			settextcolor(0);		//����������ɫ:��ɫ
			setbkcolor(0xd8dbdc);		//�������ñ���ɫ����ɫ
			setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������	
			TCHAR t3[] = _T("Tips:Log in the game!");
			settextstyle(16, 0, _T("����"));	//�߶�ΪĬ��
			outtextxy(10, 50, t3);

			setfillcolor(0x55FF55);
			solidcircle(150, 390, 20);
			solidcircle(390, 390, 20);

			// ������¼�  Log in
			//���������������Ϣ������������ˣ�
			if (m.uMsg == WM_LBUTTONUP) {
				setbkcolor(0xFFFFFF);	//���ñ���ɫ
				cleardevice();			//�����Ļ���ݣ��õ�ǰ����ɫ�����Ļ����
				flag = "Log in";		//����flag���������� Just StartGame
				break;
			}
		}
		// ����
		else if (m.x > 180 && m.x < 360 && m.y > 450 && m.y < 480)
		{
			setfillcolor(0x55FF55);
			solidcircle(150, 465, 20);
			solidcircle(390, 465, 20);

			// ������¼�  Log in
			//���������������Ϣ������������ˣ�
			if (m.uMsg == WM_LBUTTONUP) {
				flag = "About";		//����flag���������� Just StartGame
				break;
			}
		}
		// �˳�
		else if ((m.x > 180) && (m.x < 360) && (m.y > 525) && (m.y < 555))
		{
			//�����ʾ�� Exit
			settextcolor(0);		//����������ɫ:��ɫ
			setbkcolor(0xd8dbdc);		//�������ñ���ɫ����ɫ
			setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������	
			TCHAR t4[] = _T("Tips:To quit the game!");
			settextstyle(16, 0, _T("����"));	//�߶�ΪĬ��
			outtextxy(10, 50, t4);

			//��ɫ
			setfillcolor(0x55FF55);
			solidcircle(180, 540, 20);
			solidcircle(360, 540, 20);

			//������¼�
			//���������������Ϣ������������ˣ�
			if (m.uMsg == WM_LBUTTONUP) {
				cout << "aaaaa" << endl;
				myExit();
			}
		}
		else
		{
			setbkcolor(0xd8dbdc);		//��ɫ
			setfillcolor(0xd8dbdc);
			//����tips�е�����
			settextcolor(0xd8dbdc);		//����������ɫ:��ɫ
			setbkcolor(0xd8dbdc);		//�������ñ���ɫ����ɫ
			setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������	
			TCHAR tClean[] = _T("                                                   ");
			settextstyle(16, 0, _T("����"));	//�߶�ΪĬ��
			outtextxy(10, 50, tClean);
			//solidrectangle(10, 50, 550, 40);
			//clearrectangle(10, 50, 550, 40);
			//����СԲ��
			solidcircle(40, 240, 20);
			solidcircle(515, 240, 20);
			solidcircle(145, 315, 20);
			solidcircle(430, 315, 20);
			solidcircle(150, 390, 20);
			solidcircle(390, 390, 20);
			solidcircle(150, 465, 20);
			solidcircle(390, 465, 20);
			solidcircle(180, 540, 20);
			solidcircle(360, 540, 20);

		}

	}
	cout << "cccccccccc" << endl;
}

//����������ı���
void Shap::mainUI()
{
	loadingLeft();
	loadingRight();
	mianMouse();
}

void Shap::justStartGame(char type, int index)
{
	//������߾��ο�
	setfillcolor(0xd8dbdc);		//��߿����õ�ǰ�����ɫ �� ��ɫ
	fillrectangle(0, 0, 550, 744);		//�����ο�,4�������ֱ�Ϊ�������µ�����
	setfillcolor(0x5fe1f2);		//�ұ߿����õ�ǰ�����ɫ ����ɫ
	fillrectangle(550, 0, 800, 744);
	//��Ϸ�߿�
	setfillcolor(0xEDECEC);		//�ȻҰ׸���һ��
	solidrectangle(0, 0, 31, 31);
	solidrectangle(0, 40, 30, 70);
	solidrectangle(73.5, 0, 476.5, 744);		//��13��ÿ��24
	setfillcolor(0xd8dbdc);
	solidrectangle(0, 713, 550, 744);
	MOUSEMSG m;		// ���������Ϣ
	while (true)
	{
		m = GetMouseMsg();
	}
}

void Shap::myRegister()
{
	//wchar_t *accountName = new wchar_t[15];
	wchar_t accountName[15];
	wchar_t passWord[15];
	string strAccountNameCompare;
	string strAccountNameInput;
	string strAccountPassword;
	bool accountIfOk = true;
	//�����������������ÿ��Ա����û���û�������˺ź������ʱ���� start ��ť
	bool ifFinishAccountInput = false;		//�Ƿ��������˺�
	bool ifFinishPasswordInput = false;		//�Ƿ�����������
	int accountNumber;

	loadingRight();
	//������߾��ο�
	setfillcolor(0xd8dbdc);		//��߿����õ�ǰ�����ɫ �� ��ɫ
	fillrectangle(0, 0, 550, 744);		//�����ο�,4�������ֱ�Ϊ�������µ�����
	//solidrectangle(0, 0, 550, 600);

	//����ַ���
	settextcolor(0x0000AA);		//����������ɫ:��ɫ
	setbkcolor(0xd8dbdc);		//�������ñ���ɫ����ɫ
	setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������
	//settextstyle(80, 55, _T("����"), 0, 0, FW_EXTRABOLD, false, false, false);		//����������ʽ���������������ƣ�//��3�����غ���

	settextstyle(20, 20, _T("����"));
	settextcolor(0);		//����������ɫ:��ɫ
	TCHAR sRegister0[] = _T("Register a account!");		//�����˺�����
	outtextxy(15, 20, sRegister0);		//��ָ��λ������ַ�����x�� y�� �ַ���

	settextstyle(25, 25, _T("����"));
	settextcolor(0x0000AA);		//����������ɫ:��ɫ
	TCHAR sRegister1[] = _T("Enter account name");		//�����˺�����
	outtextxy(35, 100, sRegister1);		//��ָ��λ������ַ�����x�� y�� �ַ���

	TCHAR sRegister2[] = _T("Enter the password");		//��������
	outtextxy(35, 300, sRegister2);		//��ָ��λ������ַ�����x�� y�� �ַ���

	settextcolor(0xFF55FF);		//����������ɫ:�ۺ�
	TCHAR sRegister3[] = _T("Start");		//��������
	outtextxy(200, 475, sRegister3);		//��ָ��λ������ַ�����x�� y�� �ַ���

	settextcolor(0);		//����������ɫ:��ɫ
	TCHAR sRegister4[] = _T("Back");		//  Back
	outtextxy(395, 545, sRegister4);		//��ָ��λ������ַ�����x�� y�� �ַ���

	//����»���
	settextcolor(0);		//����������ɫ:��ɫ
	TCHAR sRegister5[] = _T("_________");		//�����˺ŵ��»���
	outtextxy(150, 200, sRegister5);		//��ָ��λ������ַ�����x�� y�� �ַ���
	outtextxy(150, 400, sRegister5);


	MOUSEMSG m;		// ���������Ϣ
	while (true)
	{
		m = GetMouseMsg();

		//�����˺�����
		if ((m.x > 35) && (m.x < 500) && (m.y > 100) && (m.y < 125)) {
			char ch;
			//�����ʾСԲ��,���СԲ��
			setfillcolor(0x55FF55);		//��ɫ
			solidcircle(20, 110, 20);
			//�ұ�СԲ��
			solidcircle(530, 110, 20);

			//������¼��� �����˺�����
			//���������������Ϣ������������ˣ�
			if (m.uMsg == WM_LBUTTONUP) {
				//�����û�������룬��Ϊ�û��˺������ظ�֮��accountIfOk��ֵΪ false �����û��ٴε������ʱ������accountIfOK��ֵ��
				//�ٴ��ж��û��Ƿ�������ȷ
				accountIfOk = true;		//Ĭ��������˺�û���⣬��������������������ظ��ģ��� accountIfOK ��Ϊ false��
				bool ifAccount;	//�ж��û�����������Ƿ���ȷ��
				string tempAccountName;
				ifAccount = InputBox(accountName, 10, L"Please input the account:", L"Enter account name", NULL, 0, 0, false);
				//�������ֵΪ�棬��˵���û����ˡ�ȷ����
				if (ifAccount) {
					//��һ�����ο򸲸�֮ǰ������˺�
					setfillcolor(0xd8dbdc);		//���õ�ǰ�����ɫ �� ��ɫ
					solidrectangle(150, 170, 549, 220);

					//��ʾ�˺ŵ���Ļ��
					settextcolor(0xFF55FF);		//����������ɫ:�ۺ�
					setbkcolor(0xd8dbdc);		//�������ñ���ɫ����ɫ
					setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������
					settextstyle(20, 20, _T("����"));
					outtextxy(210, 195, accountName);


				}
				//����ֵΪ�٣�˵���û����ˡ�ȡ����
				else
				{
				}

				//�õ��˺Ÿ���
				fstream fileAccount;
				//���û�и��ļ��򴴽�һ��
				fileAccount.open(fileAccountNumber, ios_base::out | ios_base::app);
				fileAccount.close();
				fileAccount.open(fileAccountNumber, ios_base::in);
				ch = fileAccount.get();
				fileAccount.close();
				//���Ϊ�յĻ�����ô����EOF�����ұ�ʾ���ø���Ϊ0
				if (ch == EOF) {
					accountNumber = 0;
				}
				else
				{
					fileAccount.open(fileAccountNumber, ios_base::in);
					//ʹ����ȡ��������ļ�����ȡ����
					fileAccount >> accountNumber;
					fileAccount.close();
				}

				//�����жϸ��˺��Ƿ���Ч
				if (accountNumber == 0) {
					accountIfOk = true;
				}
				else
				{
					fileAccount.open(fileAccountName, ios_base::in);
					for (int i = 0; i < accountNumber; i++) {
						getline(fileAccount, tempAccountName, '\n');
						Wchar_tToString(strAccountNameCompare, accountName);	//��wchar_t ����ת�����ַ�������
						//����˺���ͬ
						if (strAccountNameCompare == tempAccountName) {
							accountIfOk = false;
						}
					}
					fileAccount.close();
				}

				if (accountIfOk == true) {
					ifFinishAccountInput = true;
					setfillcolor(0x55FF55);		//���������ɫ����ɫ
					solidcircle(470, 190, 20);
				}
				else
				{
					setfillcolor(0x0000AA);		//���������ɫ����ɫ
					solidcircle(470, 190, 20);
				}
			}
		}
		//��������
		else if ((m.x > 35) && (m.x < 500) && (m.y > 300) && (m.y < 325))
		{
			//���СԲ��
			setfillcolor(0x55FF55);	//��ɫ
			solidcircle(20, 310, 20);
			//�ұ�СԲ��
			solidcircle(530, 310, 20);

			//������¼��� �����˺�����
			//���������������Ϣ������������ˣ�
			if (m.uMsg == WM_LBUTTONUP) {
				bool ifAccount;		//�ж��û�����������Ƿ���ȷ��
				ifAccount = InputBox(passWord, 10, L"Please input the password:", L"Enter the password", NULL, 0, 0, false);
				//�������ֵΪ�棬��˵���û����ˡ�ȷ����
				if (ifAccount) {
					//��һ�����ο򸲸�֮ǰ������˺�
					setfillcolor(0xd8dbdc);		//���õ�ǰ�����ɫ �� ��ɫ
					solidrectangle(150, 350, 549, 420);

					//��ʾ�˺ŵ���Ļ��
					settextcolor(0xFF55FF);		//����������ɫ:�ۺ�
					setbkcolor(0xd8dbdc);		//�������ñ���ɫ����ɫ
					setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������
					settextstyle(20, 20, _T("����"));
					outtextxy(210, 395, passWord);
					ifFinishPasswordInput = true;		//����������
				}
				//����ֵΪ�٣�˵���û����ˡ�ȡ����
				else
				{
				}

				setfillcolor(0x55FF55);	//�������ɫ����ɫ
				solidcircle(470, 390, 20);	//��Բ
			}
		}
		//ȷ��ע��
		else if ((m.x > 200) && (m.x < 300) && (m.y > 475) && (m.y < 500))
		{
			if (ifFinishAccountInput == true && ifFinishPasswordInput == true) {
				// Start
				//���СԲ��
				setfillcolor(0x55FF55);	//��ɫ
				solidcircle(175, 485, 20);
				//�ұ�СԲ��
				solidcircle(360, 485, 20);

				//������¼��� Start�� ע���˺Ż�ʼ��Ϸ
				//���������������Ϣ������������ˣ�
				if (m.uMsg == WM_LBUTTONUP) {

					//����˺���Ч
					if (accountIfOk == true) {
						//�����˺�
						//������ļ����������ļ�β���λ��----ios_base:;app
						fstream fileAccount;
						fileAccount.open(fileAccountName, ios_base::out | ios_base::app);
						//����Ҫ�� wchar_t ���͵� accountName ת���� string ���͵��ַ�����д���ļ��У�����д���������
						Wchar_tToString(strAccountNameInput, accountName);
						fileAccount << strAccountNameInput;
						fileAccount << "\n";
						fileAccount.close();
						//�����˺Ÿ���
						fileAccount.open(fileAccountNumber, ios_base::out);
						accountNumber++;
						fileAccount << accountNumber;
						fileAccount.close();

						//������Ӧ������
						fileAccount.open(fileAccountPassword, ios_base::out | ios_base::app);
						Wchar_tToString(strAccountPassword, passWord);
						fileAccount << strAccountPassword;
						fileAccount << "\n";
						fileAccount.close();

						HWND hwnd2;
						hwnd2 = GetHWnd(); // ��ȡ��ǰ���ھ��
						MessageBox(hwnd2, _T("ע��ɹ����뷵�ؽ��е�¼��"), _T("���"), MB_OK | MB_ICONEXCLAMATION);
						break;
					}
				}

			}

		}
		//������һ���˵�
		else if ((m.x > 395) && (m.x < 495) && (m.y > 545) && (m.y < 570))
		{
			// Back
			//���СԲ��
			setfillcolor(0x55FF55);	//��ɫ
			solidcircle(375, 557, 20);
			//�ұ�СԲ��
			solidcircle(520, 557, 20);

			//������¼��� Back
			//���������������Ϣ������������ˣ�
			if (m.uMsg == WM_LBUTTONUP) {
				setbkcolor(0xFFFFFF);	//���ñ���ɫ
				cleardevice();			//�����Ļ���ݣ��õ�ǰ����ɫ�����Ļ����
				ifBack = true;			//��ʾ�����˷��ؼ�
				break;					//ִ��break��˵��������ѭ������ Register���� ִ����ϣ����������� ifBack �����жϣ����Ƿ����¼���������
			}
		}
		//������������ط������СԲ��
		else
		{
			setbkcolor(0xd8dbdc);	//��ɫ
			setfillcolor(0xd8dbdc);	//�ñ���ɫ���
			solidcircle(20, 110, 20);
			solidcircle(530, 110, 20);
			solidcircle(20, 310, 20);
			solidcircle(530, 310, 20);
			solidcircle(175, 485, 20);
			solidcircle(360, 485, 20);
			solidcircle(375, 557, 20);
			solidcircle(520, 557, 20);

		}

	}
}

int Shap::myLogIn()
{
	wchar_t accountName[15];
	wchar_t passWord[15];
	string toStringAccountName;
	string toStringPassWord;		//ת�����ַ������͵��û����������
	string psaawordCompare;			//���ļ��ж�ȡ�������û������������бȽϵ����루�ļ������е����룩
	bool accountIfOk = false;		//�ж��û���¼ʱ������˺��Ƿ���Ч,Ĭ��Ϊ false
	bool passwordIfOk = false;		//�ж��û���¼ʱ����������Ƿ���Ч
	//�Ƿ�������˺ŵ����룬Ӧ���������˺����������룬��ΪҪ�������˺ź󣬵õ����˻��±꣬�����ж������Ƿ���ȷ
	//����Ҫ���˺�������ȷʱ�����ܼ�����������
	bool ifFinishAccountInput = false;		//�Ƿ������˺�
	bool ifFinishPasswordInput = false;		//�Ƿ���������
	int accountNumber;				//�˺Ÿ���
	int accountIndex;				//�û���ǰ������˺����ļ��е��±꣨��������ȷ����¼���룩
	ifStartGame = false;		//��ʼ��

	loadingRight();
	//������߾��ο�
	setfillcolor(0xd8dbdc);		//��߿����õ�ǰ�����ɫ �� ��ɫ
	fillrectangle(0, 0, 550, 744);		//�����ο�,4�������ֱ�Ϊ�������µ�����
	//solidrectangle(0, 0, 550, 600);

	//����ַ���
	settextcolor(0x0000AA);		//����������ɫ:��ɫ
	setbkcolor(0xd8dbdc);		//�������ñ���ɫ����ɫ
	setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������
	//settextstyle(80, 55, _T("����"), 0, 0, FW_EXTRABOLD, false, false, false);		//����������ʽ���������������ƣ�//��3�����غ���

	settextstyle(20, 20, _T("����"));
	settextcolor(0);		//����������ɫ:��ɫ
	TCHAR sRegister0[] = _T("Log in!");		//�����˺�����
	outtextxy(15, 20, sRegister0);		//��ָ��λ������ַ�����x�� y�� �ַ���

	settextstyle(25, 25, _T("����"));
	settextcolor(0x0000AA);		//����������ɫ:��ɫ
	TCHAR sRegister1[] = _T("Enter account name");		//�����˺�����
	outtextxy(35, 100, sRegister1);		//��ָ��λ������ַ�����x�� y�� �ַ���

	TCHAR sRegister2[] = _T("Enter the password");		//��������
	outtextxy(35, 300, sRegister2);		//��ָ��λ������ַ�����x�� y�� �ַ���

	settextcolor(0xFF55FF);		//����������ɫ:��ɫ
	TCHAR sRegister3[] = _T("Start");		//��������
	outtextxy(200, 475, sRegister3);		//��ָ��λ������ַ�����x�� y�� �ַ���

	settextcolor(0);		//����������ɫ:��ɫ
	TCHAR sRegister4[] = _T("Back");		//  Back
	outtextxy(395, 545, sRegister4);		//��ָ��λ������ַ�����x�� y�� �ַ���

	//����»���
	settextcolor(0);		//����������ɫ:��ɫ
	TCHAR sRegister5[] = _T("_________");		//�����˺ŵ��»���
	outtextxy(150, 200, sRegister5);		//��ָ��λ������ַ�����x�� y�� �ַ���
	outtextxy(150, 400, sRegister5);


	MOUSEMSG m;		// ���������Ϣ
	while (true)
	{
		m = GetMouseMsg();

		//�����˺�����
		if ((m.x > 35) && (m.x < 500) && (m.y > 100) && (m.y < 125)) {
			char ch;
			//�����ʾСԲ��,���СԲ��
			setfillcolor(0x55FF55);
			solidcircle(20, 110, 20);
			//�ұ�СԲ��
			solidcircle(530, 110, 20);

			//������¼��� �����˺�����
			//���������������Ϣ������������ˣ�
			if (m.uMsg == WM_LBUTTONUP) {
				//�����û�������룬��Ϊ�û��˺������ظ�֮��accountIfOk��ֵΪ false �����û��ٴε������ʱ������accountIfOK��ֵ��
				//�ٴ��ж��û��Ƿ�������ȷ
				accountIfOk = false;		//��������������������ļ��д��ڸ��˻��ģ�˵���Ѿ�ע��ɹ����� accountIfOK ��Ϊ ture��
				bool ifAccount;	//�ж��û�����������Ƿ���ȷ��
				string tempAccountName;
				ifAccount = InputBox(accountName, 10, L"Please input the account:", L"Enter account name", NULL, 0, 0, false);
				//�������ֵΪ�棬��˵���û����ˡ�ȷ����
				if (ifAccount) {
					//��һ�����ο򸲸�֮ǰ������˺�
					setfillcolor(0xd8dbdc);		//���õ�ǰ�����ɫ �� ��ɫ
					solidrectangle(150, 170, 549, 220);

					//��ʾ�˺ŵ���Ļ��
					settextcolor(0xFF55FF);		//����������ɫ:�ۺ�
					setbkcolor(0xd8dbdc);		//�������ñ���ɫ����ɫ
					setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������
					settextstyle(20, 20, _T("����"));
					outtextxy(210, 195, accountName);
				}
				//����ֵΪ�٣�˵���û����ˡ�ȡ����
				else
				{
				}

				//�õ��˺Ÿ���
				fstream fileAccount;
				//���û�и��ļ��򴴽�һ��
				fileAccount.open(fileAccountNumber, ios_base::out | ios_base::app);
				fileAccount.close();
				fileAccount.open(fileAccountNumber, ios_base::in);
				ch = fileAccount.get();
				fileAccount.close();
				//���Ϊ�յĻ�����ô����EOF�����ұ�ʾ���ø���Ϊ0
				if (ch == EOF) {
					accountNumber = 0;
				}
				else
				{
					fileAccount.open(fileAccountNumber, ios_base::in);
					//ʹ����ȡ��������ļ�����ȡ����
					fileAccount >> accountNumber;
					fileAccount.close();
				}

				//�����жϸ��˺��Ƿ���Ч��˵���û���¼ʱ������˺���Ч
				if (accountNumber == 0) {
					//����˺Ÿ���0��˵��δע�ᣬ�϶�����Ч��
					accountIfOk = false;
				}
				else
				{
					accountIndex = 0;
					fileAccount.open(fileAccountName, ios_base::in);
					for (int i = 0; i < accountNumber; i++) {
						accountIndex++;
						getline(fileAccount, tempAccountName, '\n');
						Wchar_tToString(toStringAccountName, accountName);	//��wchar_t ����ת�����ַ�������
						//����˺���ͬ,˵���Ѿ�ע���ˣ��˺���Ч
						if (toStringAccountName == tempAccountName) {
							accountIfOk = true;
							break;		//����forѭ��
						}

					}
					fileAccount.close();
				}

				//����СԲ��
				if (accountIfOk == true) {
					ifFinishAccountInput = true;		//������˺ŵ����룬����������ȷ
					setfillcolor(0x55FF55);		//���������ɫ����ɫ
					solidcircle(470, 190, 20);
				}
				else
				{
					setfillcolor(0x0000AA);		//���������ɫ����ɫ
					solidcircle(470, 190, 20);
				}
			}
		}
		//��������
		else if ((m.x > 35) && (m.x < 500) && (m.y > 300) && (m.y < 325))
		{
			//ֻ���û�����˺ŵ����벢��������ȷ��������������
			if (ifFinishAccountInput == true) {
				//���СԲ��
				setfillcolor(0x55FF55);	//��ɫ
				solidcircle(20, 310, 20);
				//�ұ�СԲ��
				solidcircle(530, 310, 20);

				//������¼��� ��������
				//���������������Ϣ������������ˣ�
				if (m.uMsg == WM_LBUTTONUP) {
					passwordIfOk = false;
					bool ifAccount;		//�ж��û�����������Ƿ���ȷ��
					ifAccount = InputBox(passWord, 10, L"Please input the password:", L"Enter the password", NULL, 0, 0, false);
					//�������ֵΪ�棬��˵���û����ˡ�ȷ����
					if (ifAccount) {
						//��һ�����ο򸲸�֮ǰ������˺�
						setfillcolor(0xd8dbdc);		//���õ�ǰ�����ɫ �� ��ɫ
						solidrectangle(150, 350, 549, 420);

						//��ʾ�˺ŵ���Ļ��
						settextcolor(0xFF55FF);		//����������ɫ:�ۺ�
						setbkcolor(0xd8dbdc);		//�������ñ���ɫ����ɫ
						setbkmode(OPAQUE);			//�ñ���ɫ������ֵı�������ͼ������������
						settextstyle(20, 20, _T("����"));
						outtextxy(210, 395, passWord);
					}
					//����ֵΪ�٣�˵���û����ˡ�ȡ����
					else
					{
					}

					fstream fileAccount;
					fileAccount.open(fileAccountPassword, ios_base::in);
					for (int i = 1; i <= accountNumber; i++) {
						//����⵽�û������˺Ŷ�Ӧ������±�ʱ�����бȶ�
						if (i == accountIndex) {
							getline(fileAccount, psaawordCompare, '\n');
							Wchar_tToString(toStringPassWord, passWord);	//��wchar_t ����ת�����ַ�������
						//���������ͬ
							if (psaawordCompare == toStringPassWord) {
								passwordIfOk = true;
							}
							break;		//����forѭ��
						}
						getline(fileAccount, psaawordCompare, '\n');

					}
					fileAccount.close();

					if (passwordIfOk == true) {
						ifFinishPasswordInput = true;		//��������ȷ������
						setfillcolor(0x55FF55);	//�������ɫ����ɫ
						solidcircle(470, 390, 20);	//��Բ
					}
					else {
						setfillcolor(0x0000AA);	//�������ɫ����ɫ
						solidcircle(470, 390, 20);	//��Բ
					}

				}
			}

		}
		//ȷ�ϵ�¼
		else if ((m.x > 200) && (m.x < 300) && (m.y > 475) && (m.y < 500))
		{
			if (ifFinishAccountInput == true && ifFinishPasswordInput == true) {
				// Start
				//���СԲ��
				setfillcolor(0x55FF55);
				solidcircle(175, 485, 20);
				//�ұ�СԲ��
				solidcircle(360, 485, 20);

				//������¼��� Start�� ע���˺Ż�ʼ��Ϸ
				//���������������Ϣ������������ˣ�
				if (m.uMsg == WM_LBUTTONUP) {

					//����˺���Ч
					if (accountIfOk == true && passwordIfOk == true) {
						ifStartGame = true;		//��ʾ��������ʼ��Ϸ
						return accountIndex;		//���ظ��˻��±꣬��������Ϸ�м�¼��߷�
					}
				}
			}
		}
		//������һ���˵�
		else if ((m.x > 395) && (m.x < 495) && (m.y > 545) && (m.y < 570))
		{
			// Back
			//���СԲ��
			setfillcolor(0x5fe1f2);
			solidcircle(375, 557, 20);
			//�ұ�СԲ��
			solidcircle(520, 557, 20);

			//������¼��� Back
			//���������������Ϣ������������ˣ�
			if (m.uMsg == WM_LBUTTONUP) {
				setbkcolor(0xFFFFFF);	//���ñ���ɫ
				cleardevice();			//�����Ļ���ݣ��õ�ǰ����ɫ�����Ļ����
				ifBack = true;			//��ʾ�����˷��ؼ�
				return -1;		//�������أ� Register���� ִ����ϣ����������� ifBack �����жϣ����Ƿ����¼���������

			}
		}
		//������������ط������СԲ��
		else
		{
			setbkcolor(0xd8dbdc);	//��ɫ
			setfillcolor(0xd8dbdc);	//�ñ���ɫ���
			solidcircle(20, 110, 20);
			solidcircle(530, 110, 20);
			solidcircle(20, 310, 20);
			solidcircle(530, 310, 20);
			solidcircle(175, 485, 20);
			solidcircle(360, 485, 20);
			solidcircle(375, 557, 20);
			solidcircle(520, 557, 20);
		}
	}
}

void Shap::myAbout()
{
	setfillcolor(0xd8dbdc);		//��߿����õ�ǰ�����ɫ �� ��ɫ
	fillrectangle(0, 0, 550, 744);		//�����ο�,4�������ֱ�Ϊ�������µ�����
	settextcolor(0);
	outtextxy(50, 50, _T("������Ϣ:"));
	outtextxy(100, 100, _T("��������: ����˹����С��Ϸ"));
	outtextxy(100, 150, _T("������: �ֿ�"));
	outtextxy(100, 200, _T("GitHub ID��LinSir12138��Դ�����ϴ�����ӭ���ģ�"));
	outtextxy(100, 250, _T("�汾��: 4.32"));
	outtextxy(100, 300, _T("���ʱ��: 2019��6�³�"));
	outtextxy(100, 350, _T("�༶: ��1809��"));
	outtextxy(100, 400, _T("ѧ��: 8002118244"));
	outtextxy(50, 450, _T("����˵��:"));
	outtextxy(100, 500, _T("A ���� �� �����ƶ�"));
	outtextxy(350, 500, _T("W ���� �� ��ת����"));
	outtextxy(100, 550, _T("D ���� �� �����ƶ�"));
	outtextxy(350, 550, _T("S ���� �� �����ƶ�"));
	outtextxy(100, 600, _T("P ��ͣ��,��ͣ״̬���ٴΰ��� P �����ָ���Ϸ"));
	outtextxy(100, 650, _T("B  ���ؼ�"));
	settextcolor(0xFF5555);
	settextstyle(30, 25, _T("����"), 0, 0, FW_EXTRABOLD, false, false, false);
	outtextxy(240, 690, _T("����"));

	MOUSEMSG m;		// ���������Ϣ

	while (true)
	{
		m = GetMouseMsg();
		if (m.x > 240 && m.x < 340 && m.y > 690 && m.y < 720)
		{
			setfillcolor(0x55FF55);
			solidcircle(200, 705, 20);
			solidcircle(380, 705, 20);
			if (m.uMsg == WM_LBUTTONUP) {
				break;
			}
		}
		else
		{
			setfillcolor(0xd8dbdc);
			solidcircle(200, 705, 20);
			solidcircle(380, 705, 20);
		}

	}
}

void Shap::myExit()
{
	closegraph();		//�ر�ͼ�λ���
	exit(-1);		//�˳������� ����-����-����-���Խ���ֵ�Զ��رտ���̨���� ������һ�£���ô����̨���ڻ��Զ��ر�
}

string Shap::getFlag() const
{
	return string(flag);
}

bool Shap::getIfBack() const
{
	return ifBack;
}

bool Shap::getIfStartGame() const
{
	return ifStartGame;
}