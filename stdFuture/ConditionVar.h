#pragma once
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

class ConditionVar
{
public:
	ConditionVar();
	~ConditionVar();

	void doTheWork() {
		std::cout << "Processing shared data." << std::endl;
	}

	void waitingForWork() {
		std::cout << "Worker: Waiting for work." << std::endl;

		std::unique_lock<std::mutex> lck(mutex_);
		condVar.wait(lck, [this] {return dataReady; });
		doTheWork();
		std::cout << "Work done." << std::endl;
	}

	void setDataReady() {
		std::lock_guard<std::mutex> lck(mutex_);
		dataReady = true;
		std::cout << "Sender: Data is ready." << std::endl;
		condVar.notify_one();
	}

	void mainTest();
private:
	std::mutex mutex_;
	std::condition_variable condVar;
	bool dataReady;
};

