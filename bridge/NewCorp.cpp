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
	//ÿ����˾��һ����������
	this->m_pProduct->BeProducted();
	//Ȼ��������
	this->m_pProduct->BeSelled();
}
