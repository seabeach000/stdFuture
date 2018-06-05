// memberPtr.cpp : 定义控制台应用程序的入口点。
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
	int MyClass::*dp; // 指向MyClass 中整数类型成员变量的指针
	void (MyClass::*fp)(int x);//指向MyClass 中成员函数的指针

	dp = &MyClass::sum;       //获得成员变量的地址
	fp = &MyClass::sum_it;    //获得成员函数的地址

	MyClass c;
	(c.*fp)(7); //计算	1 到 7 相加的和
	cout << "summation \
		of 7 is " << c.*dp << endl;

	//使用指针的情况
	MyClass *d = &c;
	(d->*fp)(8); //计算	1 到 8 相加的和
	cout << "summation  of 8 is " << d->*dp << endl;

    return 0;

	//运行输出： summation of 7 is 28

	//	在上面程序中，创建了两个成员指针 dp 和 fp 。其中 dp 指向了成员变量 sum ，fp 指向了函数 sum_it() 。
	//	需要注意指针的声明语法：在声明中使用了作用域解析运算符来指定指针指向的成员属于那个类。
	//	当使用对象或对象引用来访问对象的成员时，必须使用.*运算符，如程序中的 c.*fp 和 c.*dp 这种用法。
	//  如果使用指向对象的指针来访问对象的成员，那么必须使用->*运算符
}

