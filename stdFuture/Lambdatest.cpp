#include "stdafx.h"
#include "Lambdatest.h"
#include <vector>
#include <memory>

//��������Ǵ���ģ�lambda���ܷ��ʾ�̬�洢����
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

	//�޺�����������������1 2
	{
		for_each(vctTemp.begin(), vctTemp.end(), [](int v) {std::cout << v << std::endl; });
	}

	// ��ֵ��ʽ���������������пɼ��ľֲ�����������this���������11 12
	{
		int a = 10;
		for_each(vctTemp.begin(), vctTemp.end(), [=](int v) { std::cout << v + a << std::endl; });
	}

	// �����÷�ʽ���������������пɼ��ľֲ�����������this���������11 13 12
	{
		int a = 10;
		for_each(vctTemp.begin(), vctTemp.end(), [&](int v)mutable { std::cout << v + a << std::endl; a++; });
		std::cout << a << std::endl;
	}
	// ��ֵ��ʽ���ݾֲ�����a�������11 13 10
	{
		int a = 10;
		for_each(vctTemp.begin(), vctTemp.end(), [a](int v)mutable { std::cout << v + a << std::endl; a++; });
		std::cout << a << std::endl;
	}

	// �����÷�ʽ���ݾֲ�����a�������11 13 12
	{
		int a = 10;
		for_each(vctTemp.begin(), vctTemp.end(), [&a](int v) { std::cout << v + a << std::endl; a++; });
		std::cout << a << std::endl;
	}

	// ����this�������21 22
	{
		for_each(vctTemp.begin(), vctTemp.end(), [this](int v) { std::cout << v + m_nData << std::endl; });
	}

	// ��b�����ô����⣬��������ֵ���ݣ������11 12 17
	{
		int a = 10;
		int b = 15;
		for_each(vctTemp.begin(), vctTemp.end(), [=, &b](int v) { std::cout << v + a << std::endl; b++; });
		std::cout << b << std::endl;
	}

	// ���������غ������������ô��ݣ������2 3
	{
		for_each(vctTemp.begin(), vctTemp.end(), [](int &v) { v++; });
		for_each(vctTemp.begin(), vctTemp.end(), [](int v) { std::cout << v << std::endl; });
	}

	// �յ�Lambda���ʽ
	{
		[]() {}();
		[] {}();
	}

	//std::shared_ptr<void> crt_log(nullptr, [](int h) { h = 5; });  //����lambda����������
	
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
