#pragma once
#include <iostream>
#include <string>
using namespace std;

//����˹������Ϸ����ı�������
class Background
{
public:
	Background();
	~Background();
	void backgroundInitialization();		//��ʼ����������������ʼ��Ϸʱ���õ�
	void setBackgroundTrue(int deviationX, int deviationY);
	void setBackgroundFalse(int deviationX, int deviationY);
	void setXY(int newX, int newY, int number);			//����XY�����Ӧ������
	void setColors(int deviationX, int deviationY, string s);
	string getColors(int deviationX, int deviationY) const;

	int getXY(int newX, int newY) const;		//�õ�xy�����Ӧ������
	bool ifEmpty(int deviationX, int deviationY);		//�жϸ������Ƿ�Ϊ�գ�û��С���飩
	bool ifFull(int deviationX, int deviationY);
private:
	//��Ϸ������23�У�13�У����ǿ��ǵ��߽磬background ����Ϊ24�У�15��
	int XY[24][15];		//23�У�13��		//��ÿһ��С��������Ͻǵ�����(���������ָ����ƫ����)�������С���������
	string colors[24][15];		//�����洢ÿһ�����������ɫ
};

