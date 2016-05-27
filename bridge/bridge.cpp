// bridge.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "newhousecorp.h"
#include "ShanZhaiCorp.h"

#include "Clothes.h"
#include "House.h"
#include "IPod.h"

#include <iostream>
using namespace std;

void DoNewRun1()
{
	std::cout << "----------房地产公司是这样运行的----------" << endl;
	CHouse house;
	CNewHouseCorp newHouseCorp(&house);
	newHouseCorp.MakeMoney();
	std::cout << endl;

	std::cout << "----------山寨公司是这样运行的----------" << endl;
	CClothes clothes;
	CShanZhaiCorp shanZhaiCorp(&clothes);
	shanZhaiCorp.MakeMoney();
	std::cout << endl;
}
void DoNewRun2()
{
	cout << "----------房地产公司是这样运行的----------" << endl;
	CHouse house;
	CNewHouseCorp newHouseCorp(&house);
	newHouseCorp.MakeMoney();
	cout << endl;

	cout << "----------山寨公司是这样运行的----------" << endl;
	CIPod ipod;
	CShanZhaiCorp shanZhaiCorp(&ipod);
	shanZhaiCorp.MakeMoney();
	cout << endl;
}
int main()
{
	//只有两家公司，一家是房地产公司，另一家公司是衣服赚钱就生产衣服
	DoNewRun1();

	//只有两家公司，一家是房地产公司，另一家公司是ipod赚钱就生产ipod
	DoNewRun2();

	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	_CrtDumpMemoryLeaks();
	system("pause");
    return 0;
}

