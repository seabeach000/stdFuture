// bridge.cpp : �������̨Ӧ�ó������ڵ㡣
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
	std::cout << "----------���ز���˾���������е�----------" << endl;
	CHouse house;
	CNewHouseCorp newHouseCorp(&house);
	newHouseCorp.MakeMoney();
	std::cout << endl;

	std::cout << "----------ɽկ��˾���������е�----------" << endl;
	CClothes clothes;
	CShanZhaiCorp shanZhaiCorp(&clothes);
	shanZhaiCorp.MakeMoney();
	std::cout << endl;
}
void DoNewRun2()
{
	cout << "----------���ز���˾���������е�----------" << endl;
	CHouse house;
	CNewHouseCorp newHouseCorp(&house);
	newHouseCorp.MakeMoney();
	cout << endl;

	cout << "----------ɽկ��˾���������е�----------" << endl;
	CIPod ipod;
	CShanZhaiCorp shanZhaiCorp(&ipod);
	shanZhaiCorp.MakeMoney();
	cout << endl;
}
int main()
{
	//ֻ�����ҹ�˾��һ���Ƿ��ز���˾����һ�ҹ�˾���·�׬Ǯ�������·�
	DoNewRun1();

	//ֻ�����ҹ�˾��һ���Ƿ��ز���˾����һ�ҹ�˾��ipod׬Ǯ������ipod
	DoNewRun2();

	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	_CrtDumpMemoryLeaks();
	system("pause");
    return 0;
}

