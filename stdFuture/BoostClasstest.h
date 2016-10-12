#pragma once
#include <iostream>
class CBoostClasstest
{
public:
	CBoostClasstest();
	virtual ~CBoostClasstest();
public:
	void hello();
	void helloWorld(std::string& str);
	int  simpleThread();
	void  FileParser(const std::wstring& strFileName);
	void  Convert16StringTodata();
};

