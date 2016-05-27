#pragma once
#include "Iproduct.h"
class CHouse :
	public Iproduct
{
public:
	CHouse();
	virtual ~CHouse();
	void BeProducted();
	void BeSelled();
};

