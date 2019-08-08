#pragma once
#include <iostream>
class CPlusPlus11
{
public:
	CPlusPlus11();
	virtual ~CPlusPlus11();

	void decltypeTest();
	void autoTest();
	void stdmove();
	void lValueRvalue();
	void stdforward();
	void variableArray(unsigned int x, unsigned int y);
	void stdtime();
	std::wstring lrReturn();
	//1）常对象格式：const 类名 对象名
	//2）常对象只能调用常函数，不能调用普通函数
};

