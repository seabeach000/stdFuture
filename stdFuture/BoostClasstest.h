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
	void helloWorld(int str,std::string& str1,std::string& str2);
	void helloWorld(int str, std::string& str1);
	int  simpleThread();
	void  FileParser(const std::wstring& strFileName);
	void  Convert16StringTodata();
	void  thread_specific_ptrClassTest();
	//使用共享内存做为一个匿名内存块池
	int share_memory_001();
	int hardware();
	void boostFormatString();
	void boostFileOperation();
	void boostexception();
	void boostOptionalregex();
};

