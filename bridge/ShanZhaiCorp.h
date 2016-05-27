#pragma once
#include "NewCorp.h"
#include "Iproduct.h"
class CShanZhaiCorp :
	public CNewCorp
{
public:
	CShanZhaiCorp(Iproduct* pproduct);
	virtual ~CShanZhaiCorp();
	void MakeMoney();
};

