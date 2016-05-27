#include "stdafx.h"
#include "StaticTest.h"
#include <iostream>

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
