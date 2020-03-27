#include "stdafx.h"
#include "ConditionVar.h"


ConditionVar::ConditionVar()
{
}


ConditionVar::~ConditionVar()
{
}

void ConditionVar::mainTest()
{
	std::cout << std::endl;

	std::thread t1(&ConditionVar::waitingForWork,this);
	std::thread t2(&ConditionVar::setDataReady,this);

	t1.join();
	t2.join();

	std::cout << std::endl;
}
