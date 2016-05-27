#pragma once
class Iproduct
{
public:
	Iproduct();
	virtual ~Iproduct();
	virtual void BeProducted() = 0;
	virtual void BeSelled() = 0;
};

