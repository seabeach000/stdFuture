#include "stdafx.h"
#include "StaticTest.h"
#include <iostream>
#include <map>
CStaticTest::CStaticTest()
{
}


CStaticTest::~CStaticTest()
{
}

void CStaticTest::localStatic(void)
{
	static int i = 0;
	std::cout << "i:" << i << '\n';
	i++;
}

void CStaticTest::mapTest()
{
	std::map<int, std::wstring> student;
	student.insert(std::make_pair(1, _T("zhangsan")));
	student.insert(std::make_pair(2, _T("lisi")));
	student.insert(std::make_pair(3, _T("wanger")));
	student.insert(std::make_pair(4, _T("zhaowu")));
}
