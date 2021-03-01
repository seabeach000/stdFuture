#include "stdafx.h"
#include "ConditionVar.h"
#include <chrono>

using namespace std::chrono;

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

void ConditionVar::mainTest2()
{
	std::thread threads[10];
	// spawn 10 threads:
	for (int i = 0; i < 10; ++i)
		threads[i] = std::thread(&ConditionVar::print_id, this,i);

	std::cout << "10 threads ready to race...\n";
	go();                       // go!

	for (auto& th : threads) th.join();

}

void ConditionVar::print_id(int id)
{
	uint64_t currentTime = (uint64_t)duration_cast<milliseconds>((system_clock::now() + seconds{ 0 }).time_since_epoch()).count();
	std::unique_lock<std::mutex> lck(mutex_);
	std::cout << "before thread id " << id << std::endl;

	while (!ready)
		condVar.wait(lck);

	uint64_t currentTime01 = (uint64_t)duration_cast<milliseconds>((system_clock::now() + seconds{ 0 }).time_since_epoch()).count();
	while (currentTime01 - currentTime < 10*id)
	{
		currentTime01 = (uint64_t)duration_cast<milliseconds>((system_clock::now() + seconds{ 0 }).time_since_epoch()).count();
		std::cout << " id  " << id << std::endl;
	}
	lck.unlock();  //如果这里提前释放了锁，那么下面一句话就会混乱输出
	std::cout << "after thread id " << id << " current time " << currentTime01 << std::endl;
}

void ConditionVar::go()
{
	std::unique_lock<std::mutex> lck(mutex_);
	ready = true;
	condVar.notify_all();
}
