#include "stdafx.h"
#include "NewHouseCorp.h"
#include <iostream>
using namespace std;
CNewHouseCorp::CNewHouseCorp(CHouse* pHouse):CNewCorp(pHouse)
{
}


CNewHouseCorp::~CNewHouseCorp()
{
}

void CNewHouseCorp::MakeMney()
{
	this->CNewCorp::MakeMoney();
	cout << "房地产公司太赚钱了。。。" << endl;
}
