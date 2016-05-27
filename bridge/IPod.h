#pragma once
#include "Iproduct.h"
class CIPod :
	public Iproduct
{
public:
	CIPod();
	virtual ~CIPod();
	void BeProducted();
	void BeSelled();
};

