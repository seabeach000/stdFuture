#pragma once
#include "NewCorp.h"
#include "House.h"
class CNewHouseCorp :
	public CNewCorp
{
public:
	CNewHouseCorp(CHouse *pHouse);
	virtual ~CNewHouseCorp();
	void MakeMney();
};

