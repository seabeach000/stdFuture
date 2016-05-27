#pragma once
#include "Iproduct.h"
class CNewCorp
{
public:
	CNewCorp(Iproduct* pproduct);
	~CNewCorp();
	void MakeMoney();
private:
	Iproduct *m_pProduct;
};

