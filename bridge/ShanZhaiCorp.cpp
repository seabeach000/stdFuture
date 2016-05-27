#include "stdafx.h"
#include "ShanZhaiCorp.h"
#include <iostream>
using namespace std;
CShanZhaiCorp::CShanZhaiCorp(Iproduct* pproduct):CNewCorp(pproduct)
{
}


CShanZhaiCorp::~CShanZhaiCorp()
{
}

void CShanZhaiCorp::MakeMoney()
{
	this->CNewCorp::MakeMoney();
	cout << "ÎÒ×¬Ç®°¡¡£¡£¡£" << endl;
}
