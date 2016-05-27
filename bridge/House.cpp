#include "stdafx.h"
#include "House.h"
#include <iostream>
using namespace std;
CHouse::CHouse()
{
}


CHouse::~CHouse()
{
}

void CHouse::BeProducted()
{
	cout << "生产出的房子是这个样子的。。。" << endl;
}

void CHouse::BeSelled()
{
	cout << "生产出的房子卖出去了。。。" << endl;
}
