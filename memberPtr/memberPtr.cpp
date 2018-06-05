// memberPtr.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;

class MyClass
{
public:
	MyClass();
	~MyClass();

public:
	int sum;
	void sum_it(int x);

};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}

void MyClass::sum_it(int x)
{
	sum = 0;
	for (int i = x;i;i--)
	{
		sum += i;
	}
}

int main()
{
	int MyClass::*dp; // ָ��MyClass ���������ͳ�Ա������ָ��
	void (MyClass::*fp)(int x);//ָ��MyClass �г�Ա������ָ��

	dp = &MyClass::sum;       //��ó�Ա�����ĵ�ַ
	fp = &MyClass::sum_it;    //��ó�Ա�����ĵ�ַ

	MyClass c;
	(c.*fp)(7); //����	1 �� 7 ��ӵĺ�
	cout << "summation \
		of 7 is " << c.*dp << endl;

	//ʹ��ָ������
	MyClass *d = &c;
	(d->*fp)(8); //����	1 �� 8 ��ӵĺ�
	cout << "summation  of 8 is " << d->*dp << endl;

    return 0;

	//��������� summation of 7 is 28

	//	����������У�������������Աָ�� dp �� fp ������ dp ָ���˳�Ա���� sum ��fp ָ���˺��� sum_it() ��
	//	��Ҫע��ָ��������﷨����������ʹ��������������������ָ��ָ��ָ��ĳ�Ա�����Ǹ��ࡣ
	//	��ʹ�ö����������������ʶ���ĳ�Աʱ������ʹ��.*�������������е� c.*fp �� c.*dp �����÷���
	//  ���ʹ��ָ������ָ�������ʶ���ĳ�Ա����ô����ʹ��->*�����
}

