#pragma once
#include "Iproduct.h"
class CClothes :
	public Iproduct
{
public:
	CClothes();
	virtual ~CClothes();
	void BeProducted();
	void BeSelled();
};

