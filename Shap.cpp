#include "Shap.h"

const string fileAccountNumber = "res\\AccountNumber.txt";
const string fileAccountName = "res\\AccountName.txt";
const string fileAccountPassword = "res\\AccountPassword.txt";
const string fileMaxScore = "res\\MaxScore.txt";


Shap::Shap()
{
	//初始化640 * 480 的绘图屏幕,并禁用关闭窗口按钮
	initgraph(800, 744, NOCLOSE);

	// 设置背景色为白色
	setbkcolor(0xFFFFFF);
	// 用背景色清空屏幕
	cleardevice();

	HWND hwnd;
	// 1.设置窗口句柄变量保存窗口信息
	hwnd = GetHWnd();
	// 2.获取窗口句柄
	SetWindowText(hwnd, _T("俄罗斯方块"));
}


Shap::~Shap()
{
	_getch();			//按任意键继续
	closegraph();		//关闭绘图窗口
}

//初始化
void Shap::Initialization()
{
	//初始化640 * 480 的绘图屏幕,并禁用关闭窗口按钮
	//初始化绘图窗口在 Tetris.cpp 文件中初始化
	//initgraph(800, 744, SHOWCONSOLE | NOCLOSE);
	// 设置背景色为白色
	background.backgroundInitialization();		//背景初始化
	setbkcolor(0xFFFFFF);
	// 用背景色清空屏幕
	cleardevice();
	//设置左边矩形框
	setfillcolor(0xd8dbdc);		//左边框设置当前填充颜色 ： 灰色
	fillrectangle(0, 0, 550, 744);		//画矩形框,4个参数分别为左上右下的坐标
	setfillcolor(0x5fe1f2);		//右边框设置当前填充颜色 ：黄色
	fillrectangle(550, 0, 800, 744);
	//游戏边框
	setfillcolor(0xEDECEC);		//比灰白更白一点,游戏内框的颜色
	solidrectangle(73, 0, 476, 744);		//宽：13格，每格24
	setfillcolor(0xd8dbdc);
	solidrectangle(0, 713, 550, 744);

	//完成背景的生成后，重新定义坐标原点
	setorigin(73 - 31, 0);		//定义坐标原点,考虑到方块的移动和旋转，坐标原点的x坐标要向左偏移一格，即31

	settextstyle(25, 20, _T("宋体"), 0, 0, FW_EXTRABOLD, false, false, false);		//设置字体样式：长，宽，字体名称，//有3个重载函数
	settextcolor(0);
	setbkcolor(0x5fe1f2);		//右边框设置当前填充颜色 ：黄色
	setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观
	//字体y坐标再减 30
	outtextxy(530, 20, _T("Hello:"));
	outtextxy(530, 120, _T("Next:"));
	setfillcolor(0xFFFFFF);
	solidrectangle(560, 180, 720, 340);		//覆盖 hello 下面的字体
	outtextxy(530, 370, _T("MaxScore:"));
	outtextxy(530, 470, _T("NowScore:"));
	outtextxy(530, 570, _T("Lines:"));
	settextcolor(0xFF5555);		//亮蓝色
	settextstyle(20, 15, _T("宋体"), 0, 0, FW_EXTRABOLD, false, false, false);		//设置字体样式：长，宽，字体名称，//有3个重载函数
	outtextxy(520, 670, _T("暂停(P)"));
	outtextxy(650, 670, _T("退出(B)"));
	settextcolor(0);

	//初始化右边框的分数
	setfillcolor(0x5fe1f2);
	//用背景色矩形框覆盖
	solidrectangle(520, 405, 799, 465);		//覆盖 maxScore 下面的数字
	solidrectangle(520, 505, 799, 565);		//覆盖 nextScore 下面的数字
	solidrectangle(520, 605, 799, 665);		//覆盖 lines 下面的数字
	eliminateLine = 0;		//初始化消除的总行数
	sumScore = 0;		//初始化总分数
	wchar_t tempSumScore[15];
	wchar_t tempEliminateLine[15];
	_stprintf_s(tempSumScore, _T("%d"), sumScore);	// 将变量值格式化写入到中间变量 tempSumScore 中， _T("")是 unicode 的用法
	_stprintf_s(tempEliminateLine, _T("%d"), eliminateLine);
	settextstyle(25, 20, _T("宋体"), 0, 0, FW_EXTRABOLD, false, false, false);		//设置字体样式：长，宽，字体名称，//有3个重载函数
	outtextxy(580, 520, tempSumScore);
	outtextxy(580, 620, tempEliminateLine);

	setfillcolor(0xFF5555);
	solidcircle(3, 3, 2);
	accountIndex = 0;		//该下标从1开始，即第一个学生的下标为1
	gameoverChooseFlag = 0;		//初始化为 0，避免上一次对gameoverChooseFlag的赋值对后面程序的影响
}

//每次开始游戏时只调用一次，生成第一个随机方块，显示用户名称和该用户最高分
void Shap::random1()
{
	int accountNumber;
	//string tempMaxScore;		//临时变量，最高分,因为getline函数读取出来的是一个字符串
	string tempAccountName;		//账号名称
	wchar_t wcharMaxScore[15];
	wchar_t wcharAccountName[15];
	fstream fileAccount;
	//首先判断是否要显示用户名字,如果该用户事账号密码登录，则显示账号名称和最高分，如果是游客登录，则不显示账号和最高分

	if (accountIndex != 0)
	{
		//得到账号个数
		fileAccount.open(fileAccountNumber, ios_base::in);
		fileAccount >> accountNumber;
		fileAccount.close();
		fileAccount.open(fileAccountName, ios_base::in);
		//因为accountIndex从1开始，即第一个学生的下标为1，注意这里是i=1，i <= accountNumber
		for (int i = 1; i <= accountNumber; i++) {
			getline(fileAccount, tempAccountName, '\n');
			if (i == accountIndex)
			{
				break;
			}
		}
		fileAccount.close();
		//显示最高分
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
	//显示账号名称
	swprintf(wcharAccountName, 100, L"%S", tempAccountName.c_str());	//注意大写,name1指向的内存区域存储这wchar_t类型的 
	swprintf(wcharMaxScore, 100, L"%S", maxScore.c_str());
	outtextxy(530, 70, wcharAccountName);
	outtextxy(580, 420, wcharMaxScore);




	srand(int(time(0)));
	blockColor1 = (rand() % 7) + 1;
	//对应的颜色分别为 红， 灰蓝， 黄， 绿，青，蓝，紫
	switch (blockColor1)
	{
	case 1:
		color1 = "0x5555FF";		//红色
		break;
	case 2:
		color1 = "0xEBACD2";		//粉色
		break;
	case 3:
		color1 = "0x55FFFF";		//黄色
		break;
	case 4:
		color1 = "0x55FF55";		//绿色
		break;
	case 5:
		color1 = "0xFFFF55";		//天青色
		break;
	case 6:
		color1 = "0xFF5555";		//深蓝色
		break;
	case 7:
		color1 = "0xAA00AA";		//紫色
		break;
	default:
		break;
	}

	blockNumber1 = (rand() % 19);		//0 ~ 18,方块编号
}

//生成后续的随机方块
void Shap::random2()
{
	srand(int(time(0)) + 1);		//防止和第一次生成的随机数一样
	blockColor2 = (rand() % 7) + 1;
	//对应的颜色分别为 红， 灰蓝， 黄， 绿，青，蓝，紫
	switch (blockColor2)
	{
	case 1:
		color2 = "0x5555FF";		//红色
		break;
	case 2:
		color2 = "0xEBACD2";		//粉色
		break;
	case 3:
		color2 = "0x55FFFF";		//黄色
		break;
	case 4:
		color2 = "0x55FF55";		//绿色
		break;
	case 5:
		color2 = "0xFFFF55";		//天青色
		break;
	case 6:
		color2 = "0xFF5555";		//深蓝色
		break;
	case 7:
		color2 = "0xAA00AA";		//紫色
		break;
	default:
		break;
	}

	blockNumber2 = (rand() % 19);		//0 ~ 18,方块编号
}

//绘画当前方块，这里的deviationX， deviationY 是4 * 4 方框的左上角的点相对于原点坐标的偏移格数，
void Shap::draw(int deviationX, int deviationY, int type, string newColor)
{
	/*
		注： deviationX， deviationY  表示包含方块的 4 * 4 方框的左上角的点相对于 原点坐标的偏移格数，
			 由 x, y 乘以每小格的长度，得到Ox， Oy，表示  4 * 4 方框的左上角的坐标
			 然后在根据方块的类型type ，以Ox， Oy 为参考，画出相应的方块
			 默认每一个小方块是 31 * 31， 考虑到美观，实现有颜色的 为 28 * 28
	*/

	//Ox， Oy，表示  4 * 4 方框的左上角的坐标
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

	//在地图上标记该点,//用每一个小方格的左上角的坐标来代替该小方块的坐标,这里记录的是偏移的格数
	//因为background中的数组是第一个元素是行，第二个元素是列，所以第一个元素对应坐标y，第二个元素对应坐标x
	background.setBackgroundTrue(deviationY + site[type][2], deviationX + site[type][1]);
	background.setBackgroundTrue(deviationY + site[type][4], deviationX + site[type][3]);
	background.setBackgroundTrue(deviationY + site[type][6], deviationX + site[type][5]);
	background.setBackgroundTrue(deviationY + site[type][8], deviationX + site[type][7]);

	cout << "draw newColor == " << color1 << endl;
	//为每一个小方块标记颜色
	background.setColors(deviationY + site[type][2], deviationX + site[type][1], newColor);
	background.setColors(deviationY + site[type][4], deviationX + site[type][3], newColor);
	background.setColors(deviationY + site[type][6], deviationX + site[type][5], newColor);
	background.setColors(deviationY + site[type][8], deviationX + site[type][7], newColor);


}

//在右侧区域画下一次即将出现的方块，更好的提示用户
void Shap::drawNextBlock(int type, string newColor)
{
	//Ox， Oy，表示  4 * 4 方框的左上角的坐标
	int Ox, Oy;
	Ox = 590;
	Oy = 210;

	//清空当前绘画区域
	setfillcolor(0xFFFFFF);
	solidrectangle(560, 180, 720, 340);		//用白色方框先覆盖该区域（作用是清空上一次的画图图像），在重新画图

	setColor(newColor);
	solidrectangle(Ox + 31 * site[type][1] + 1.5, Oy + 31 * site[type][2] + 1.5, Ox + 31 * site[type][1] + 1.5 + 28, Oy + 31 * site[type][2] + 1.5 + 28);
	solidrectangle(Ox + 31 * site[type][3] + 1.5, Oy + 31 * site[type][4] + 1.5, Ox + 31 * site[type][3] + 1.5 + 28, Oy + 31 * site[type][4] + 1.5 + 28);
	solidrectangle(Ox + 31 * site[type][5] + 1.5, Oy + 31 * site[type][6] + 1.5, Ox + 31 * site[type][5] + 1.5 + 28, Oy + 31 * site[type][6] + 1.5 + 28);
	solidrectangle(Ox + 31 * site[type][7] + 1.5, Oy + 31 * site[type][8] + 1.5, Ox + 31 * site[type][7] + 1.5 + 28, Oy + 31 * site[type][8] + 1.5 + 28);
}

//传入的参数x, y 是 4 * 4 方框的左上角的坐标,flag = 1表示左移， flag = 2表示右移,type表示方块的编号
void Shap::move(int flag, int type, int x, int y)
{
	//4 * 4 方框的左上角的点相对于原点坐标的偏移格数， 
	//cout << "x, y ==" << x << "," << y << endl;
	int deviationX, deviationY;
	deviationX = x / 31;
	deviationY = y / 31;
	bool ifempty1, ifempty2, ifempty3, ifempty4 = false;
	bool ifLeftEmpty = false;
	bool ifRightEmpty = false;
	//左移
	if (flag == 1) {
		switch (type)
		{
			ifLeftEmpty = false;		//每次进入switch的时候都要初始化ifLeftEmpty的值(重要)
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
	//右移
	else if (flag == 2)
	{
		switch (type)
		{
			ifRightEmpty = false;		//每次进入switch循环都要重置ifRightEmpty的值为false
			//以下四种情况分别表示阻挡该方块右移的位置有几个，从1 到4
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
// turn 传入的参数x, y 是 4 * 4 方框的左上角的坐标
void Shap::turn(int type, int x, int y)
{
	//4 * 4 方框的左上角的点相对于原点坐标的偏移格数， 
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

	//ifTurnIsEmpty 为真时，表示方块可以旋转
	if (ifTurnIsEmpty)
	{
		clear(deviationX, deviationY, type);
		//根据方块的编号，确定旋转之后的方块编号，进而画出旋转之后的方块
		//旋转之后，同时要改变 Shap 类中的 number
		switch (type)
		{
			//下面的是：type + 1
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
			//下面的是：type - 3
		case 3:
		case 7:
		case 11:
			blockNumber1 = type - 3;
			break;
			//下面的是：type - 1
		case 13:
		case 15:
		case 17:
			blockNumber1 = type - 1;
			break;
			//下面的是：type不变
		case 18:
			break;
		default:
			break;
		}
		draw(deviationX, deviationY, blockNumber1, color1);
	}
}

//方块自由下落
bool Shap::down()
{
	bool ifempty1, ifempty2, ifempty3, ifempty4;		//每个方块由4个小方块构成


	//竖直方向总共有24格，因为最底下一格是边界，所以是0——22，总共23格是游戏区域

	bool flagIfDown = false;		//该方块能否下落
	//然后判断该方块能否下落，如果能，则再重新画一个下落一个后的方块
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

//传入的参数是 4 * 4 方框左上角相对于原点的偏移量
void Shap::clear(int deviationX, int deviationY, int type)
{
	//在地图上标记该点,//用每一个小方格的左上角的坐标来代替该小方块的坐标,这里记录的是偏移的格数
	//因为background中的数组是第一个元素是行，第二个元素是列，所以第一个元素对应坐标y，第二个元素对应坐标x
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

//设置方块的颜色
void Shap::setColor(string newColor)
{
	//对应的颜色分别为 红， 橙， 黄， 绿，青，蓝，紫
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

//检查是否要对已经满行的方块进行消除
void Shap::inspect()
{
	//检查哪些行已经满了
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

	eliminateLine += sumLine;		//增加以消除的总行数
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

	//更改最高分MaxScore的值
	int toIntMaxScore = atoi(maxScore.c_str());
	cout << "toIntMaxScore==" << toIntMaxScore << endl;
	cout << "sumScore ==" << sumScore << endl;
	if (sumScore >= toIntMaxScore)
	{
		toIntMaxScore = sumScore;
		cout << "toIntMaxScore2 ==" << toIntMaxScore << endl;
		maxScore = to_string(sumScore);		//更改最高分对应的字符串
		cout << "StringMaxScore==" << maxScore << endl;
		//当最高分改变时，立即把最高分存进文件中去
		fstream fileAccount;
		if (accountIndex != 0)
		{
			int accountNumber;
			//得到账号个数
			fileAccount.open(fileAccountNumber, ios_base::in);
			fileAccount >> accountNumber;
			fileAccount.close();

			//更改最高分
			//从文件中读取最高分，组成一个字符串数组
			string *p = new string[accountNumber];	//动态创建字符串数组
			fileAccount.open(fileMaxScore, ios_base::in);
			for (int i = 0; i < accountNumber; i++) {
				getline(fileAccount, p[i], '\n');
			}
			fileAccount.close();
			//因为accountIndex从1开始，即第一个学生的下标为1，所以这里应该为：accountIndex - 1
			p[accountIndex - 1] = maxScore;		//将最高分赋值给字符串数组中对应的元素
			//在将该字符串数组写入文件中
			fileAccount.open(fileMaxScore, ios_base::out);
			for (int i = 0; i < accountNumber; i++)
			{
				fileAccount << p[i];
				fileAccount << endl;
			}
			fileAccount.close();		//关闭文件
		}
	}

	//更改总分SumScore，和总行数eliminateLines的值
	wchar_t tempSumScore[15];
	wchar_t tempEliminateLine[15];
	wchar_t tempMaxScore[15];
	_stprintf_s(tempSumScore, _T("%d"), sumScore);	// 将变量值格式化写入到中间变量 tempSumScore 中， _T("")是 unicode 的用法
	_stprintf_s(tempEliminateLine, _T("%d"), eliminateLine);
	cout << "aaaa" << toIntMaxScore << endl;
	_stprintf_s(tempMaxScore, _T("%d"), toIntMaxScore);
	settextstyle(25, 20, _T("宋体"), 0, 0, FW_EXTRABOLD, false, false, false);		//设置字体样式：长，宽，字体名称，//有3个重载函数
	settextcolor(0);		//黑色
	setbkcolor(0x5fe1f2);		//右边框设置当前填充颜色 ：黄色
	setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观
	outtextxy(580, 420, tempMaxScore);
	outtextxy(580, 520, tempSumScore);
	outtextxy(580, 620, tempEliminateLine);

	if (ifHaveFull == true)
	{
		//删除已经满了的一行
		for (int i = 0; i < sumLine; i++)	//需要删除多少行，该函数执行多少遍
		{

			if (i != 0)
			{
				lines[i] = lines[i] + i;		//因为是逐行消除,没消除一行之后，原来方格满了的一行下标会加一
			}
			//注意顺序，相改变颜色，在改变背景
			//改变方格的颜色
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

//游戏结束时的界面
void Shap::gameOverUI()
{
	graphdefaults();		//初始化绘图因子因为之前改变了原点坐标，对后续绘图可能会产生影响

	setfillcolor(0xEDECEC);		//比灰白更白一点
	solidrectangle(73, 0, 476, 713);		//宽：13格，每格24
	settextstyle(45, 35, _T("宋体"), 0, 0, FW_EXTRABOLD, false, false, false);		//设置字体样式：长，宽，字体名称，//有3个重载函数
	setbkcolor(0xEDECEC);		//设置字体的背景颜色（抠图）
	settextcolor(0);
	outtextxy(75, 200, _T("GAME OVER !"));
	settextcolor(0xFF5555);	//亮蓝
	outtextxy(130, 370, _T("继续游戏"));
	outtextxy(180, 500, _T("返回"));

	MOUSEMSG m;		// 定义鼠标消息
	while (true)
	{
		m = GetMouseMsg();
		if (m.x > 130 && m.x < 455 && m.y > 370 && m.y < 410)
		{
			setfillcolor(0x55FF55);
			solidcircle(100, 387, 20);
			solidcircle(440, 387, 20);

			//鼠标点击事件： 点击继续游戏
			//如果鼠标左键弹起消息（鼠标左键点击了）
			if (m.uMsg == WM_LBUTTONUP) {
				gameoverChooseFlag = 1;		//选择了继续游戏，赋值为1
				break;		//跳出循环，gameOver函数执行完毕
			}
		}
		else if (m.x > 180 && m.x < 380 && m.y > 500 && m.y < 540)
		{
			setfillcolor(0x55FF55);
			solidcircle(150, 517, 20);
			solidcircle(345, 517, 20);

			//鼠标点击事件： 点击返回（返回主界面）
			//如果鼠标左键弹起消息（鼠标左键点击了）
			if (m.uMsg == WM_LBUTTONUP) {
				gameoverChooseFlag = 2;		//选择了返回，赋值为2
				break;		//跳出循环，gameOver函数执行完毕
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

//判断游戏是否结束，当方块到达顶端时，游戏结束
bool Shap::ifGameOver(int type, string newColor)
{
	//Ox， Oy，表示  4 * 4 方框的左上角的坐标
	int Ox, Oy;
	Ox = 5 * 31;
	Oy = 0 * 31;
	int flag1, flag2, flag3, flag4;
	flag1 = background.getXY(0 + site[type][2], 5 + site[type][1]);
	flag2 = background.getXY(0 + site[type][4], 5 + site[type][3]);
	flag3 = background.getXY(0 + site[type][6], 5 + site[type][5]);
	flag4 = background.getXY(0 + site[type][8], 5 + site[type][7]);

	//如果这4个方块中有一个已经存在小方块了，说明和即将出现的方块会重叠，说明游戏结束
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
//	//初始化640 * 480 的绘图屏幕,并禁用关闭窗口按钮
//	initgraph(800, 744, SHOWCONSOLE | NOCLOSE);
//
//	// 设置背景色为白色
//	setbkcolor(0xFFFFFF);
//	// 用背景色清空屏幕
//	cleardevice();
//
//	HWND hwnd;
//	// 1.设置窗口句柄变量保存窗口信息
//	hwnd = GetHWnd();
//	// 2.获取窗口句柄
//	SetWindowText(hwnd, _T("俄罗斯方块"));
//
//	////画两个矩形框
//	//setfillcolor(0xd8dbdc);		//左边框设置当前填充颜色 ： 灰色
//	//fillrectangle(0, 0, 550, 600);		//画矩形框,4个参数分别为左上右下的坐标
//	//setfillcolor(0x5fe1f2);		//右边框设置当前填充颜色 ：黄色
//	//fillrectangle(550, 0, 800, 600);
//	////左边矩形框
//	////输出字符串
//	//settextcolor(0x0000AA);		//设置文字颜色:红色
//	//setbkcolor(0xd8dbdc);		//重新设置背景色，设置
//	//setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观
//	//settextstyle(80, 55, _T("宋体"), 0, 0, FW_EXTRABOLD, false, false, false);		//设置字体样式：长，宽，字体名称，//有3个重载函数
//	//TCHAR s1[] = _T("Tetris");
//	//outtextxy(110, 90, s1);		//在指定位置输出字符串：x， y， 字符串
//	////输出选项
//	//settextstyle(30, 30, _T("宋体"));		
//	//TCHAR s2[] = _T("Just StartGame");		//快速开始游戏
//	//outtextxy(65, 225, s2);		//在指定位置输出字符串：x， y， 字符串
//	//TCHAR s3[] = _T("Regist");		//注册
//	//outtextxy(180, 300, s3);		//在指定位置输出字符串：x， y， 字符串
//	//TCHAR s4[] = _T("Log in");		//登录
//	//outtextxy(180, 375, s4);		//在指定位置输出字符串：x， y， 字符串
//	//TCHAR s5[] = _T("Exit");		//退出
//	//outtextxy(210, 450, s5);		//在指定位置输出字符串：x， y， 字符串
//	////右边矩形框
//	//settextcolor(0xFF5555);		//设置文字颜色:亮蓝
//	//setbkcolor(0x5fe1f2);		//重新设置背景色：黄色
//	//setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观	
//	//settextstyle(20, 20, _T("宋体"));
//	//TCHAR sRight1[] = _T("Next:");
//	//outtextxy(580, 50, sRight1);
//	//TCHAR sRight2[] = _T("Score:");
//	//outtextxy(580, 250, sRight2);
//	//TCHAR sRight3[] = _T("Max Score:");
//	//outtextxy(580, 425, sRight3);
//	//MOUSEMSG m;		// 定义鼠标消息
//	//
//	//while (true)
//	//{
//	//	m = GetMouseMsg();
//	//	//圆点的y坐标同一与相对的字符串的y坐标加15
//	//	//左边圆点的x减30， 右边加30
//	//	//字体的高度为30
//	//	if ((m.x > 75) && (m.x < 500) && (m.y > 225) && (m.y < 255)) {
//	//		//输出提示，Just Start game
//	//		settextcolor(0);		//设置文字颜色:黑色
//	//		setbkcolor(0xd8dbdc);		//重新设置背景色：灰色
//	//		setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观	
//	//		TCHAR t1[] = _T("Tips:Do not need to register, quick start the game!");
//	//		settextstyle(16, 0, _T("宋体"));	//高度为默认
//	//		outtextxy(10, 50, t1);
//	//		//左边小圆点
//	//		setbkcolor(0x5fe1f2);	//黄色
//	//		setfillcolor(0x5fe1f2);
//	//		solidcircle(40, 240, 10);
//	//		//右边小圆点
//	//		solidcircle(515, 240, 10);
//	//		//鼠标点击事件
//	//		//如果鼠标左键弹起消息（鼠标左键点击了）
//	//		if (m.uMsg == WM_LBUTTONUP) {
//	//			cleardevice();
//	//		}
//	//	}
//	//	else if ((m.x > 180) && (m.x < 360) && (m.y > 300) && (m.y < 330))
//	//	{
//	//		//输出提示： Register
//	//		settextcolor(0);		//设置文字颜色:黑色
//	//		setbkcolor(0xd8dbdc);		//重新设置背景色：灰色
//	//		setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观	
//	//		TCHAR t2[] = _T("Tips:To register an account!");
//	//		settextstyle(16, 0, _T("宋体"));	//高度为默认
//	//		outtextxy(10, 50, t2);
//	//		setbkcolor(0x5fe1f2);	//黄色
//	//		setfillcolor(0x5fe1f2);
//	//		solidcircle(150, 315, 10);
//	//		solidcircle(390, 315, 10);
//	//	}
//	//	else if ((m.x > 180) && (m.x < 360) && (m.y > 375) && (m.y < 405))
//	//	{
//	//		//输出提示： Log in
//	//		settextcolor(0);		//设置文字颜色:黑色
//	//		setbkcolor(0xd8dbdc);		//重新设置背景色：灰色
//	//		setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观	
//	//		TCHAR t3[] = _T("Tips:Log in the game!");
//	//		settextstyle(16, 0, _T("宋体"));	//高度为默认
//	//		outtextxy(10, 50, t3);
//	//		setbkcolor(0x5fe1f2);	//黄色
//	//		setfillcolor(0x5fe1f2);
//	//		solidcircle(150, 390, 10);
//	//		solidcircle(390, 390, 10);
//	//	}
//	//	else if ((m.x > 180) && (m.x < 360) && (m.y > 450) && (m.y < 480))
//	//	{
//	//		//输出提示： Exit
//	//		settextcolor(0);		//设置文字颜色:黑色
//	//		setbkcolor(0xd8dbdc);		//重新设置背景色：灰色
//	//		setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观	
//	//		TCHAR t4[] = _T("Tips:To quit the game!");
//	//		settextstyle(16, 0, _T("宋体"));	//高度为默认
//	//		outtextxy(10, 50, t4);
//	//		setbkcolor(0x5fe1f2);	//黄色
//	//		setfillcolor(0x5fe1f2);
//	//		solidcircle(180, 465, 10);
//	//		solidcircle(360, 465, 10);
//	//		//鼠标点击事件
//	//		//如果鼠标左键弹起消息（鼠标左键点击了）
//	//		if (m.uMsg == WM_LBUTTONUP) {
//	//			myExit();
//	//		}
//	//	}
//	//	else
//	//	{
//	//		setbkcolor(0xd8dbdc);		//灰色
//	//		setfillcolor(0xd8dbdc);
//	//		//覆盖tips中的文字
//	//		settextcolor(0xd8dbdc);		//设置文字颜色:黑色
//	//		setbkcolor(0xd8dbdc);		//重新设置背景色：灰色
//	//		setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观	
//	//		TCHAR tClean[] = _T("                                                   ");
//	//		settextstyle(16, 0, _T("宋体"));	//高度为默认
//	//		outtextxy(10, 50, tClean);
//	//		//solidrectangle(10, 50, 550, 40);
//	//		//clearrectangle(10, 50, 550, 40);
//	//		//覆盖小圆点
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
//	//_getch();			//按任意键继续
//	//closegraph();		//关闭绘图窗口
//}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~下面的函数是选择界面，上面的函数是游戏界面~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Shap::loadingLeft()
{
	cout << "loadingLeft" << endl;
	//设置左边矩形框
	setfillcolor(0xd8dbdc);		//左边框设置当前填充颜色 ： 灰色
	fillrectangle(0, 0, 550, 744);		//画矩形框,4个参数分别为左上右下的坐标

	//输出字符串
	settextcolor(0x0000AA);		//设置文字颜色:红色
	setbkcolor(0xd8dbdc);		//重新设置背景色，设置
	setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观
	settextstyle(80, 55, _T("宋体"), 0, 0, FW_EXTRABOLD, false, false, false);		//设置字体样式：长，宽，字体名称，//有3个重载函数
	TCHAR s1[] = _T("Tetris");
	outtextxy(110, 90, s1);		//在指定位置输出字符串：x， y， 字符串
	//输出选项
	settextstyle(30, 30, _T("宋体"));
	TCHAR s2[] = _T("Just StartGame");		//快速开始游戏
	outtextxy(65, 225, s2);		//在指定位置输出字符串：x， y， 字符串
	TCHAR s3[] = _T("Register");		//注册
	outtextxy(165, 300, s3);		//在指定位置输出字符串：x， y， 字符串
	TCHAR s4[] = _T("Log in");		//登录
	outtextxy(180, 375, s4);		//在指定位置输出字符串：x， y， 字符串
	outtextxy(190, 450, _T("About"));
	settextcolor(0xFF5555);		//设置文字颜色:亮蓝
	TCHAR s5[] = _T("Exit");		//退出
	outtextxy(210, 525, s5);		//在指定位置输出字符串：x， y， 字符串

	settextcolor(0);		//设置文字颜色:黑色
	settextstyle(25, 20, _T("宋体"), 0, 0, FW_EXTRABOLD, false, false, false);
	TCHAR sCreater[] = _T("-- create by 林凯");
	outtextxy(100, 640, sCreater);
}

void Shap::loadingRight()
{
	cout << "loadingright" << endl;
	setfillcolor(0x5fe1f2);		//右边框设置当前填充颜色 ：黄色
	fillrectangle(550, 0, 800, 744);

	//右边矩形框
	settextcolor(0xFF5555);		//设置文字颜色:亮蓝
	setbkcolor(0x5fe1f2);		//重新设置背景色：黄色
	setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观	


	settextstyle(25, 20, _T("宋体"), 0, 0, FW_EXTRABOLD, false, false, false);		//设置字体样式：长，宽，字体名称，//有3个重载函数
	settextcolor(0);
	setbkcolor(0x5fe1f2);		//右边框设置当前填充颜色 ：黄色
	setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观
	//因为进入游戏界面之后，坐标原点改变了，所以在这里的横坐标x要加上坐标原点的偏移量，使得前后的图形重合
	outtextxy(530 + 42, 20, _T("Hello:"));
	outtextxy(530 + 42, 120, _T("Next:"));
	setfillcolor(0xFFFFFF);
	solidrectangle(560 + 42, 180, 720 + 42, 340);
	outtextxy(530 + 42, 370, _T("MaxScore:"));
	outtextxy(530 + 42, 470, _T("NowScore:"));
	outtextxy(530 + 42, 570, _T("Lines:"));


}

//主界面(选择操作的界面)的  鼠标移动效果  和点击事件
void Shap::mianMouse()
{
	Sleep(1000);
	MOUSEMSG m;		// 定义鼠标消息

	while (true)
	{
		m = GetMouseMsg();
		//圆点的y坐标同一与相对的字符串的y坐标加15
		//左边圆点的x减30， 右边加30
		//字体的高度为30
		// Just Start Game
		if ((m.x > 75) && (m.x < 500) && (m.y > 225) && (m.y < 255)) {
			//输出提示，Just Start Game
			settextcolor(0);		//设置文字颜色:黑色
			setbkcolor(0xd8dbdc);		//重新设置背景色：灰色
			setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观	
			TCHAR t1[] = _T("Tips:Do not need to register, quick start the game!");
			settextstyle(16, 0, _T("宋体"));	//高度为默认
			outtextxy(10, 50, t1);

			//左边小圆点
			setfillcolor(0x55FF55);		//绿色
			solidcircle(40, 240, 20);
			//右边小圆点
			solidcircle(515, 240, 20);

			//鼠标点击事件
			//如果鼠标左键弹起消息（鼠标左键点击了）
			if (m.uMsg == WM_LBUTTONUP) {
				setbkcolor(0xFFFFFF);	//设置背景色
				cleardevice();			//清空屏幕内容，用当前背景色清空屏幕内容
				flag = "Just StartGame";		//设置flag，表面点击了 Just StartGame
				break;
			}
		}
		// 注册
		else if ((m.x > 180) && (m.x < 360) && (m.y > 300) && (m.y < 330))
		{
			//输出提示： Register
			settextcolor(0);		//设置文字颜色:黑色
			setbkcolor(0xd8dbdc);		//重新设置背景色：灰色
			setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观	
			TCHAR t2[] = _T("Tips:To register an account!");
			settextstyle(16, 0, _T("宋体"));	//高度为默认
			outtextxy(10, 50, t2);

			setfillcolor(0x55FF55);
			solidcircle(145, 315, 20);
			solidcircle(430, 315, 20);

			// 鼠标点击事件  Register
				//如果鼠标左键弹起消息（鼠标左键点击了）
			if (m.uMsg == WM_LBUTTONUP) {
				setbkcolor(0xFFFFFF);	//设置背景色
				cleardevice();			//清空屏幕内容，用当前背景色清空屏幕内容
				flag = "Register";		//设置flag，表面点击了 Just StartGame
				break;
			}
		}
		//登录
		else if ((m.x > 180) && (m.x < 360) && (m.y > 375) && (m.y < 405))
		{
			//输出提示： Log in
			settextcolor(0);		//设置文字颜色:黑色
			setbkcolor(0xd8dbdc);		//重新设置背景色：灰色
			setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观	
			TCHAR t3[] = _T("Tips:Log in the game!");
			settextstyle(16, 0, _T("宋体"));	//高度为默认
			outtextxy(10, 50, t3);

			setfillcolor(0x55FF55);
			solidcircle(150, 390, 20);
			solidcircle(390, 390, 20);

			// 鼠标点击事件  Log in
			//如果鼠标左键弹起消息（鼠标左键点击了）
			if (m.uMsg == WM_LBUTTONUP) {
				setbkcolor(0xFFFFFF);	//设置背景色
				cleardevice();			//清空屏幕内容，用当前背景色清空屏幕内容
				flag = "Log in";		//设置flag，表面点击了 Just StartGame
				break;
			}
		}
		// 关于
		else if (m.x > 180 && m.x < 360 && m.y > 450 && m.y < 480)
		{
			setfillcolor(0x55FF55);
			solidcircle(150, 465, 20);
			solidcircle(390, 465, 20);

			// 鼠标点击事件  Log in
			//如果鼠标左键弹起消息（鼠标左键点击了）
			if (m.uMsg == WM_LBUTTONUP) {
				flag = "About";		//设置flag，表面点击了 Just StartGame
				break;
			}
		}
		// 退出
		else if ((m.x > 180) && (m.x < 360) && (m.y > 525) && (m.y < 555))
		{
			//输出提示： Exit
			settextcolor(0);		//设置文字颜色:黑色
			setbkcolor(0xd8dbdc);		//重新设置背景色：灰色
			setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观	
			TCHAR t4[] = _T("Tips:To quit the game!");
			settextstyle(16, 0, _T("宋体"));	//高度为默认
			outtextxy(10, 50, t4);

			//绿色
			setfillcolor(0x55FF55);
			solidcircle(180, 540, 20);
			solidcircle(360, 540, 20);

			//鼠标点击事件
			//如果鼠标左键弹起消息（鼠标左键点击了）
			if (m.uMsg == WM_LBUTTONUP) {
				cout << "aaaaa" << endl;
				myExit();
			}
		}
		else
		{
			setbkcolor(0xd8dbdc);		//灰色
			setfillcolor(0xd8dbdc);
			//覆盖tips中的文字
			settextcolor(0xd8dbdc);		//设置文字颜色:黑色
			setbkcolor(0xd8dbdc);		//重新设置背景色：灰色
			setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观	
			TCHAR tClean[] = _T("                                                   ");
			settextstyle(16, 0, _T("宋体"));	//高度为默认
			outtextxy(10, 50, tClean);
			//solidrectangle(10, 50, 550, 40);
			//clearrectangle(10, 50, 550, 40);
			//覆盖小圆点
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

//加载主界面的背景
void Shap::mainUI()
{
	loadingLeft();
	loadingRight();
	mianMouse();
}

void Shap::justStartGame(char type, int index)
{
	//设置左边矩形框
	setfillcolor(0xd8dbdc);		//左边框设置当前填充颜色 ： 灰色
	fillrectangle(0, 0, 550, 744);		//画矩形框,4个参数分别为左上右下的坐标
	setfillcolor(0x5fe1f2);		//右边框设置当前填充颜色 ：黄色
	fillrectangle(550, 0, 800, 744);
	//游戏边框
	setfillcolor(0xEDECEC);		//比灰白更白一点
	solidrectangle(0, 0, 31, 31);
	solidrectangle(0, 40, 30, 70);
	solidrectangle(73.5, 0, 476.5, 744);		//宽：13格，每格24
	setfillcolor(0xd8dbdc);
	solidrectangle(0, 713, 550, 744);
	MOUSEMSG m;		// 定义鼠标消息
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
	//下面两个变量的设置可以避免用户在没有输入账号和密码的时候点击 start 按钮
	bool ifFinishAccountInput = false;		//是否输入了账号
	bool ifFinishPasswordInput = false;		//是否输入了密码
	int accountNumber;

	loadingRight();
	//设置左边矩形框
	setfillcolor(0xd8dbdc);		//左边框设置当前填充颜色 ： 灰色
	fillrectangle(0, 0, 550, 744);		//画矩形框,4个参数分别为左上右下的坐标
	//solidrectangle(0, 0, 550, 600);

	//输出字符串
	settextcolor(0x0000AA);		//设置文字颜色:红色
	setbkcolor(0xd8dbdc);		//重新设置背景色，灰色
	setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观
	//settextstyle(80, 55, _T("宋体"), 0, 0, FW_EXTRABOLD, false, false, false);		//设置字体样式：长，宽，字体名称，//有3个重载函数

	settextstyle(20, 20, _T("宋体"));
	settextcolor(0);		//设置文字颜色:黑色
	TCHAR sRegister0[] = _T("Register a account!");		//输入账号名称
	outtextxy(15, 20, sRegister0);		//在指定位置输出字符串：x， y， 字符串

	settextstyle(25, 25, _T("宋体"));
	settextcolor(0x0000AA);		//设置文字颜色:红色
	TCHAR sRegister1[] = _T("Enter account name");		//输入账号名称
	outtextxy(35, 100, sRegister1);		//在指定位置输出字符串：x， y， 字符串

	TCHAR sRegister2[] = _T("Enter the password");		//输入密码
	outtextxy(35, 300, sRegister2);		//在指定位置输出字符串：x， y， 字符串

	settextcolor(0xFF55FF);		//设置文字颜色:粉红
	TCHAR sRegister3[] = _T("Start");		//输入密码
	outtextxy(200, 475, sRegister3);		//在指定位置输出字符串：x， y， 字符串

	settextcolor(0);		//设置文字颜色:黑色
	TCHAR sRegister4[] = _T("Back");		//  Back
	outtextxy(395, 545, sRegister4);		//在指定位置输出字符串：x， y， 字符串

	//输出下划线
	settextcolor(0);		//设置文字颜色:黑色
	TCHAR sRegister5[] = _T("_________");		//输入账号的下划线
	outtextxy(150, 200, sRegister5);		//在指定位置输出字符串：x， y， 字符串
	outtextxy(150, 400, sRegister5);


	MOUSEMSG m;		// 定义鼠标消息
	while (true)
	{
		m = GetMouseMsg();

		//输入账号名称
		if ((m.x > 35) && (m.x < 500) && (m.y > 100) && (m.y < 125)) {
			char ch;
			//输出提示小圆点,左边小圆点
			setfillcolor(0x55FF55);		//绿色
			solidcircle(20, 110, 20);
			//右边小圆点
			solidcircle(530, 110, 20);

			//鼠标点击事件： 输入账号名称
			//如果鼠标左键弹起消息（鼠标左键点击了）
			if (m.uMsg == WM_LBUTTONUP) {
				//方便用户多次输入，因为用户账号输入重复之后，accountIfOk的值为 false ，当用户再次点击输入时，重置accountIfOK的值，
				//再次判断用户是否输入正确
				accountIfOk = true;		//默认输入的账号没问题，待会遍历检查是如果发现重复的，则 accountIfOK 改为 false；
				bool ifAccount;	//判断用户在输入框中是否按了确定
				string tempAccountName;
				ifAccount = InputBox(accountName, 10, L"Please input the account:", L"Enter account name", NULL, 0, 0, false);
				//如果返回值为真，则说明用户按了“确定”
				if (ifAccount) {
					//有一个矩形框覆盖之前输入的账号
					setfillcolor(0xd8dbdc);		//设置当前填充颜色 ： 灰色
					solidrectangle(150, 170, 549, 220);

					//显示账号到屏幕上
					settextcolor(0xFF55FF);		//设置文字颜色:粉红
					setbkcolor(0xd8dbdc);		//重新设置背景色，灰色
					setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观
					settextstyle(20, 20, _T("宋体"));
					outtextxy(210, 195, accountName);


				}
				//返回值为假，说明用户按了“取消”
				else
				{
				}

				//得到账号个数
				fstream fileAccount;
				//如果没有改文件则创建一个
				fileAccount.open(fileAccountNumber, ios_base::out | ios_base::app);
				fileAccount.close();
				fileAccount.open(fileAccountNumber, ios_base::in);
				ch = fileAccount.get();
				fileAccount.close();
				//如果为空的话，那么返回EOF，并且表示正好个数为0
				if (ch == EOF) {
					accountNumber = 0;
				}
				else
				{
					fileAccount.open(fileAccountNumber, ios_base::in);
					//使用提取运算符从文件中提取数字
					fileAccount >> accountNumber;
					fileAccount.close();
				}

				//首先判断该账号是否有效
				if (accountNumber == 0) {
					accountIfOk = true;
				}
				else
				{
					fileAccount.open(fileAccountName, ios_base::in);
					for (int i = 0; i < accountNumber; i++) {
						getline(fileAccount, tempAccountName, '\n');
						Wchar_tToString(strAccountNameCompare, accountName);	//将wchar_t 类型转换成字符串类型
						//如果账号相同
						if (strAccountNameCompare == tempAccountName) {
							accountIfOk = false;
						}
					}
					fileAccount.close();
				}

				if (accountIfOk == true) {
					ifFinishAccountInput = true;
					setfillcolor(0x55FF55);		//设置填充颜色：绿色
					solidcircle(470, 190, 20);
				}
				else
				{
					setfillcolor(0x0000AA);		//设置填充颜色：红色
					solidcircle(470, 190, 20);
				}
			}
		}
		//输入密码
		else if ((m.x > 35) && (m.x < 500) && (m.y > 300) && (m.y < 325))
		{
			//左边小圆点
			setfillcolor(0x55FF55);	//绿色
			solidcircle(20, 310, 20);
			//右边小圆点
			solidcircle(530, 310, 20);

			//鼠标点击事件： 输入账号名称
			//如果鼠标左键弹起消息（鼠标左键点击了）
			if (m.uMsg == WM_LBUTTONUP) {
				bool ifAccount;		//判断用户在输入框中是否按了确定
				ifAccount = InputBox(passWord, 10, L"Please input the password:", L"Enter the password", NULL, 0, 0, false);
				//如果返回值为真，则说明用户按了“确定”
				if (ifAccount) {
					//有一个矩形框覆盖之前输入的账号
					setfillcolor(0xd8dbdc);		//设置当前填充颜色 ： 灰色
					solidrectangle(150, 350, 549, 420);

					//显示账号到屏幕上
					settextcolor(0xFF55FF);		//设置文字颜色:粉红
					setbkcolor(0xd8dbdc);		//重新设置背景色，灰色
					setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观
					settextstyle(20, 20, _T("宋体"));
					outtextxy(210, 395, passWord);
					ifFinishPasswordInput = true;		//输入了密码
				}
				//返回值为假，说明用户按了“取消”
				else
				{
				}

				setfillcolor(0x55FF55);	//设置填充色：绿色
				solidcircle(470, 390, 20);	//画圆
			}
		}
		//确认注册
		else if ((m.x > 200) && (m.x < 300) && (m.y > 475) && (m.y < 500))
		{
			if (ifFinishAccountInput == true && ifFinishPasswordInput == true) {
				// Start
				//左边小圆点
				setfillcolor(0x55FF55);	//绿色
				solidcircle(175, 485, 20);
				//右边小圆点
				solidcircle(360, 485, 20);

				//鼠标点击事件： Start， 注册账号或开始游戏
				//如果鼠标左键弹起消息（鼠标左键点击了）
				if (m.uMsg == WM_LBUTTONUP) {

					//如果账号有效
					if (accountIfOk == true) {
						//保存账号
						//打开输出文件，用于在文件尾添加位置----ios_base:;app
						fstream fileAccount;
						fileAccount.open(fileAccountName, ios_base::out | ios_base::app);
						//这里要将 wchar_t 类型的 accountName 转换成 string 类型的字符串再写入文件中，否则写入的是乱码
						Wchar_tToString(strAccountNameInput, accountName);
						fileAccount << strAccountNameInput;
						fileAccount << "\n";
						fileAccount.close();
						//更新账号个数
						fileAccount.open(fileAccountNumber, ios_base::out);
						accountNumber++;
						fileAccount << accountNumber;
						fileAccount.close();

						//保存相应的密码
						fileAccount.open(fileAccountPassword, ios_base::out | ios_base::app);
						Wchar_tToString(strAccountPassword, passWord);
						fileAccount << strAccountPassword;
						fileAccount << "\n";
						fileAccount.close();

						HWND hwnd2;
						hwnd2 = GetHWnd(); // 获取当前窗口句柄
						MessageBox(hwnd2, _T("注册成功，请返回进行登录！"), _T("完成"), MB_OK | MB_ICONEXCLAMATION);
						break;
					}
				}

			}

		}
		//返回上一级菜单
		else if ((m.x > 395) && (m.x < 495) && (m.y > 545) && (m.y < 570))
		{
			// Back
			//左边小圆点
			setfillcolor(0x55FF55);	//绿色
			solidcircle(375, 557, 20);
			//右边小圆点
			solidcircle(520, 557, 20);

			//鼠标点击事件： Back
			//如果鼠标左键弹起消息（鼠标左键点击了）
			if (m.uMsg == WM_LBUTTONUP) {
				setbkcolor(0xFFFFFF);	//设置背景色
				cleardevice();			//清空屏幕内容，用当前背景色清空屏幕内容
				ifBack = true;			//表示按下了返回键
				break;					//执行break后，说明跳出了循环，则 Register函数 执行完毕，主函数将对 ifBack 进行判断，看是否重新加载主界面
			}
		}
		//鼠标落在其他地方则清除小圆点
		else
		{
			setbkcolor(0xd8dbdc);	//灰色
			setfillcolor(0xd8dbdc);	//用背景色填充
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
	string toStringPassWord;		//转换成字符串类型的用户输入的密码
	string psaawordCompare;			//从文件中读取出来和用户输入的密码进行比较的密码（文件中已有的密码）
	bool accountIfOk = false;		//判断用户登录时输入的账号是否有效,默认为 false
	bool passwordIfOk = false;		//判断用户登录时输入的密码是否有效
	//是否完成了账号的输入，应该先输入账号在输入密码，因为要求输入账号后，得到该账户下标，进而判断密码是否正确
	//并且要求账号输入正确时，才能继续输入密码
	bool ifFinishAccountInput = false;		//是否输入账号
	bool ifFinishPasswordInput = false;		//是否输入密码
	int accountNumber;				//账号个数
	int accountIndex;				//用户当前输入的账号在文件中的下标（可以用来确定登录密码）
	ifStartGame = false;		//初始化

	loadingRight();
	//设置左边矩形框
	setfillcolor(0xd8dbdc);		//左边框设置当前填充颜色 ： 灰色
	fillrectangle(0, 0, 550, 744);		//画矩形框,4个参数分别为左上右下的坐标
	//solidrectangle(0, 0, 550, 600);

	//输出字符串
	settextcolor(0x0000AA);		//设置文字颜色:红色
	setbkcolor(0xd8dbdc);		//重新设置背景色，灰色
	setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观
	//settextstyle(80, 55, _T("宋体"), 0, 0, FW_EXTRABOLD, false, false, false);		//设置字体样式：长，宽，字体名称，//有3个重载函数

	settextstyle(20, 20, _T("宋体"));
	settextcolor(0);		//设置文字颜色:黑色
	TCHAR sRegister0[] = _T("Log in!");		//输入账号名称
	outtextxy(15, 20, sRegister0);		//在指定位置输出字符串：x， y， 字符串

	settextstyle(25, 25, _T("宋体"));
	settextcolor(0x0000AA);		//设置文字颜色:红色
	TCHAR sRegister1[] = _T("Enter account name");		//输入账号名称
	outtextxy(35, 100, sRegister1);		//在指定位置输出字符串：x， y， 字符串

	TCHAR sRegister2[] = _T("Enter the password");		//输入密码
	outtextxy(35, 300, sRegister2);		//在指定位置输出字符串：x， y， 字符串

	settextcolor(0xFF55FF);		//设置文字颜色:蓝色
	TCHAR sRegister3[] = _T("Start");		//输入密码
	outtextxy(200, 475, sRegister3);		//在指定位置输出字符串：x， y， 字符串

	settextcolor(0);		//设置文字颜色:黑色
	TCHAR sRegister4[] = _T("Back");		//  Back
	outtextxy(395, 545, sRegister4);		//在指定位置输出字符串：x， y， 字符串

	//输出下划线
	settextcolor(0);		//设置文字颜色:黑色
	TCHAR sRegister5[] = _T("_________");		//输入账号的下划线
	outtextxy(150, 200, sRegister5);		//在指定位置输出字符串：x， y， 字符串
	outtextxy(150, 400, sRegister5);


	MOUSEMSG m;		// 定义鼠标消息
	while (true)
	{
		m = GetMouseMsg();

		//输入账号名称
		if ((m.x > 35) && (m.x < 500) && (m.y > 100) && (m.y < 125)) {
			char ch;
			//输出提示小圆点,左边小圆点
			setfillcolor(0x55FF55);
			solidcircle(20, 110, 20);
			//右边小圆点
			solidcircle(530, 110, 20);

			//鼠标点击事件： 输入账号名称
			//如果鼠标左键弹起消息（鼠标左键点击了）
			if (m.uMsg == WM_LBUTTONUP) {
				//方便用户多次输入，因为用户账号输入重复之后，accountIfOk的值为 false ，当用户再次点击输入时，重置accountIfOK的值，
				//再次判断用户是否输入正确
				accountIfOk = false;		//待会遍历检查是如果发现文件中存在该账户的，说明已经注册成功，则 accountIfOK 改为 ture；
				bool ifAccount;	//判断用户在输入框中是否按了确定
				string tempAccountName;
				ifAccount = InputBox(accountName, 10, L"Please input the account:", L"Enter account name", NULL, 0, 0, false);
				//如果返回值为真，则说明用户按了“确定”
				if (ifAccount) {
					//有一个矩形框覆盖之前输入的账号
					setfillcolor(0xd8dbdc);		//设置当前填充颜色 ： 灰色
					solidrectangle(150, 170, 549, 220);

					//显示账号到屏幕上
					settextcolor(0xFF55FF);		//设置文字颜色:粉红
					setbkcolor(0xd8dbdc);		//重新设置背景色，灰色
					setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观
					settextstyle(20, 20, _T("宋体"));
					outtextxy(210, 195, accountName);
				}
				//返回值为假，说明用户按了“取消”
				else
				{
				}

				//得到账号个数
				fstream fileAccount;
				//如果没有改文件则创建一个
				fileAccount.open(fileAccountNumber, ios_base::out | ios_base::app);
				fileAccount.close();
				fileAccount.open(fileAccountNumber, ios_base::in);
				ch = fileAccount.get();
				fileAccount.close();
				//如果为空的话，那么返回EOF，并且表示正好个数为0
				if (ch == EOF) {
					accountNumber = 0;
				}
				else
				{
					fileAccount.open(fileAccountNumber, ios_base::in);
					//使用提取运算符从文件中提取数字
					fileAccount >> accountNumber;
					fileAccount.close();
				}

				//首先判断该账号是否有效，说明用户登录时输入的账号有效
				if (accountNumber == 0) {
					//如果账号个数0，说明未注册，肯定是无效的
					accountIfOk = false;
				}
				else
				{
					accountIndex = 0;
					fileAccount.open(fileAccountName, ios_base::in);
					for (int i = 0; i < accountNumber; i++) {
						accountIndex++;
						getline(fileAccount, tempAccountName, '\n');
						Wchar_tToString(toStringAccountName, accountName);	//将wchar_t 类型转换成字符串类型
						//如果账号相同,说明已经注册了，账号有效
						if (toStringAccountName == tempAccountName) {
							accountIfOk = true;
							break;		//跳出for循环
						}

					}
					fileAccount.close();
				}

				//加载小圆点
				if (accountIfOk == true) {
					ifFinishAccountInput = true;		//完成了账号的输入，并且输入正确
					setfillcolor(0x55FF55);		//设置填充颜色：绿色
					solidcircle(470, 190, 20);
				}
				else
				{
					setfillcolor(0x0000AA);		//设置填充颜色：红色
					solidcircle(470, 190, 20);
				}
			}
		}
		//输入密码
		else if ((m.x > 35) && (m.x < 500) && (m.y > 300) && (m.y < 325))
		{
			//只有用户完成账号的输入并且输入正确，才能输入密码
			if (ifFinishAccountInput == true) {
				//左边小圆点
				setfillcolor(0x55FF55);	//绿色
				solidcircle(20, 310, 20);
				//右边小圆点
				solidcircle(530, 310, 20);

				//鼠标点击事件： 输入密码
				//如果鼠标左键弹起消息（鼠标左键点击了）
				if (m.uMsg == WM_LBUTTONUP) {
					passwordIfOk = false;
					bool ifAccount;		//判断用户在输入框中是否按了确定
					ifAccount = InputBox(passWord, 10, L"Please input the password:", L"Enter the password", NULL, 0, 0, false);
					//如果返回值为真，则说明用户按了“确定”
					if (ifAccount) {
						//有一个矩形框覆盖之前输入的账号
						setfillcolor(0xd8dbdc);		//设置当前填充颜色 ： 灰色
						solidrectangle(150, 350, 549, 420);

						//显示账号到屏幕上
						settextcolor(0xFF55FF);		//设置文字颜色:粉红
						setbkcolor(0xd8dbdc);		//重新设置背景色，灰色
						setbkmode(OPAQUE);			//用背景色填充文字的背景（抠图），更加美观
						settextstyle(20, 20, _T("宋体"));
						outtextxy(210, 395, passWord);
					}
					//返回值为假，说明用户按了“取消”
					else
					{
					}

					fstream fileAccount;
					fileAccount.open(fileAccountPassword, ios_base::in);
					for (int i = 1; i <= accountNumber; i++) {
						//当检测到用户输入账号对应密码的下标时，进行比对
						if (i == accountIndex) {
							getline(fileAccount, psaawordCompare, '\n');
							Wchar_tToString(toStringPassWord, passWord);	//将wchar_t 类型转换成字符串类型
						//如果密码相同
							if (psaawordCompare == toStringPassWord) {
								passwordIfOk = true;
							}
							break;		//跳出for循环
						}
						getline(fileAccount, psaawordCompare, '\n');

					}
					fileAccount.close();

					if (passwordIfOk == true) {
						ifFinishPasswordInput = true;		//输入了正确的密码
						setfillcolor(0x55FF55);	//设置填充色：绿色
						solidcircle(470, 390, 20);	//画圆
					}
					else {
						setfillcolor(0x0000AA);	//设置填充色：红色
						solidcircle(470, 390, 20);	//画圆
					}

				}
			}

		}
		//确认登录
		else if ((m.x > 200) && (m.x < 300) && (m.y > 475) && (m.y < 500))
		{
			if (ifFinishAccountInput == true && ifFinishPasswordInput == true) {
				// Start
				//左边小圆点
				setfillcolor(0x55FF55);
				solidcircle(175, 485, 20);
				//右边小圆点
				solidcircle(360, 485, 20);

				//鼠标点击事件： Start， 注册账号或开始游戏
				//如果鼠标左键弹起消息（鼠标左键点击了）
				if (m.uMsg == WM_LBUTTONUP) {

					//如果账号有效
					if (accountIfOk == true && passwordIfOk == true) {
						ifStartGame = true;		//表示接下来开始游戏
						return accountIndex;		//返回该账户下标，用来在游戏中记录最高分
					}
				}
			}
		}
		//返回上一级菜单
		else if ((m.x > 395) && (m.x < 495) && (m.y > 545) && (m.y < 570))
		{
			// Back
			//左边小圆点
			setfillcolor(0x5fe1f2);
			solidcircle(375, 557, 20);
			//右边小圆点
			solidcircle(520, 557, 20);

			//鼠标点击事件： Back
			//如果鼠标左键弹起消息（鼠标左键点击了）
			if (m.uMsg == WM_LBUTTONUP) {
				setbkcolor(0xFFFFFF);	//设置背景色
				cleardevice();			//清空屏幕内容，用当前背景色清空屏幕内容
				ifBack = true;			//表示按下了返回键
				return -1;		//函数返回， Register函数 执行完毕，主函数将对 ifBack 进行判断，看是否重新加载主界面

			}
		}
		//鼠标落在其他地方则清除小圆点
		else
		{
			setbkcolor(0xd8dbdc);	//灰色
			setfillcolor(0xd8dbdc);	//用背景色填充
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
	setfillcolor(0xd8dbdc);		//左边框设置当前填充颜色 ： 灰色
	fillrectangle(0, 0, 550, 744);		//画矩形框,4个参数分别为左上右下的坐标
	settextcolor(0);
	outtextxy(50, 50, _T("程序信息:"));
	outtextxy(100, 100, _T("程序名称: 俄罗斯方块小游戏"));
	outtextxy(100, 150, _T("开发者: 林凯"));
	outtextxy(100, 200, _T("GitHub ID：LinSir12138，源码已上传，欢迎查阅！"));
	outtextxy(100, 250, _T("版本号: 4.32"));
	outtextxy(100, 300, _T("完成时间: 2019年6月初"));
	outtextxy(100, 350, _T("班级: 软工1809班"));
	outtextxy(100, 400, _T("学号: 8002118244"));
	outtextxy(50, 450, _T("操作说明:"));
	outtextxy(100, 500, _T("A 或者 ← 向左移动"));
	outtextxy(350, 500, _T("W 或者 ↑ 翻转方块"));
	outtextxy(100, 550, _T("D 或者 → 向右移动"));
	outtextxy(350, 550, _T("S 或者 ↓ 向下移动"));
	outtextxy(100, 600, _T("P 暂停键,暂停状态下再次按下 P 键，恢复游戏"));
	outtextxy(100, 650, _T("B  返回键"));
	settextcolor(0xFF5555);
	settextstyle(30, 25, _T("宋体"), 0, 0, FW_EXTRABOLD, false, false, false);
	outtextxy(240, 690, _T("返回"));

	MOUSEMSG m;		// 定义鼠标消息

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
	closegraph();		//关闭图形环境
	exit(-1);		//退出程序，在 设置-工具-调试-调试结束值自动关闭控制台窗口 中设置一下，那么控制台窗口会自动关闭
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