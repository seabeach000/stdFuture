#include "stdafx.h"
#include "NewCorp.h"


CNewCorp::CNewCorp(Iproduct* pproduct)
{
	this->m_pProduct = pproduct;
}


CNewCorp::~CNewCorp()
{
}

void CNewCorp::MakeMoney()
{
	//每个公司都一样，先生产
	this->m_pProduct->BeProducted();
	//然后再销售
	this->m_pProduct->BeSelled();
}
