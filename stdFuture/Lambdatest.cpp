#include "stdafx.h"
#include "Lambdatest.h"
#include <vector>
#include <memory>

//下面代码是错误的，lambda不能访问静态存储变量
//static int g_intVal = 1;
//void S5_OutScope()
//{
//	auto outScope = [g_intVal] {std::cout << "Lambda: " << ++g_intVal << std::endl; };
//	outScope();
//}

CLambdatest::CLambdatest():m_nData(20)
{
}


CLambdatest::~CLambdatest()
{
}

void CLambdatest::lambadaTest()
{
	std::vector<int> vctTemp;
	vctTemp.push_back(1);
	vctTemp.push_back(2);

	//无函数对象参数，输出：1 2
	{
		for_each(vctTemp.begin(), vctTemp.end(), [](int v) {std::cout << v << std::endl; });
	}

	// 以值方式传递作用域内所有可见的局部变量（包括this），输出：11 12
	{
		int a = 10;
		for_each(vctTemp.begin(), vctTemp.end(), [=](int v) { std::cout << v + a << std::endl; });
	}

	// 以引用方式传递作用域内所有可见的局部变量（包括this），输出：11 13 12
	{
		int a = 10;
		for_each(vctTemp.begin(), vctTemp.end(), [&](int v)mutable { std::cout << v + a << std::endl; a++; });
		std::cout << a << std::endl;
	}
	// 以值方式传递局部变量a，输出：11 13 10
	{
		int a = 10;
		for_each(vctTemp.begin(), vctTemp.end(), [a](int v)mutable { std::cout << v + a << std::endl; a++; });
		std::cout << a << std::endl;
	}

	// 以引用方式传递局部变量a，输出：11 13 12
	{
		int a = 10;
		for_each(vctTemp.begin(), vctTemp.end(), [&a](int v) { std::cout << v + a << std::endl; a++; });
		std::cout << a << std::endl;
	}

	// 传递this，输出：21 22
	{
		for_each(vctTemp.begin(), vctTemp.end(), [this](int v) { std::cout << v + m_nData << std::endl; });
	}

	// 除b按引用传递外，其他均按值传递，输出：11 12 17
	{
		int a = 10;
		int b = 15;
		for_each(vctTemp.begin(), vctTemp.end(), [=, &b](int v) { std::cout << v + a << std::endl; b++; });
		std::cout << b << std::endl;
	}

	// 操作符重载函数参数按引用传递，输出：2 3
	{
		for_each(vctTemp.begin(), vctTemp.end(), [](int &v) { v++; });
		for_each(vctTemp.begin(), vctTemp.end(), [](int v) { std::cout << v << std::endl; });
	}

	// 空的Lambda表达式
	{
		[]() {}();
		[] {}();
	}

	//std::shared_ptr<void> crt_log(nullptr, [](int h) { h = 5; });  //后面lambda是析构函数
	
	{
		int x = 1;
		int y = 1;
		int z;
		std::cout << "x1: " << x << "/t y1: " << y << std::endl;
		z = [=]() mutable -> int
		{
			int n = x + y;
			++x;
			++y;
			std::cout << "x2: " << x << "/t y2: " << y << std::endl;
			return n;
		}();
		std::cout << "x3: " << x << "/t y3: " << y << std::endl;
		std::cout << "z: " << z << std::endl;
	}
	{
		int intValue = 0;
		auto test2 = [=]() mutable {std::cout << "Lambda: " << ++intValue << std::endl; };
		test2();
		std::cout << "Out Lambda: " << intValue << std::endl;
	}
}
