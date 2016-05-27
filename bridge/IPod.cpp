#include "stdafx.h"
#include "IPod.h"
#include <iostream>
using namespace std;
CIPod::CIPod()
{
}


CIPod::~CIPod()
{
}

void CIPod::BeProducted()
{
	cout << "生产出的ipod是这个样子的..." << endl;
}

void CIPod::BeSelled()
{
	cout << "生产出的ipod卖出去了..." << endl;
}
