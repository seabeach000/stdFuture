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
		//在线程被阻塞时，该函数会自动调用 lck.unlock() 释放锁，使得其他被阻塞在锁竞争上的线程得以继续执行
		//另外，一旦当前线程获得通知(notified，通常是另外某个线程调用 notify_* 唤醒了当前线程)，wait()函数也是自动调用 lck.lock()，使得lck的状态和 wait 函数被调用时相同
		//在第二种情况下（即设置了 Predicate），只有当 pred 条件为false 时调用 wait() 才会阻塞当前线程，并且在收到其他线程的通知后只有当 pred 为 true 时才会被解除阻塞
		//wait_for wait_until
		condVar.wait(lck, [this] {return dataReady; });
		doTheWork();
		std::cout << "Work done." << std::endl;
	}

	void setDataReady() {
		//std::lock_guard其实就是简单的RAII封装，在构造函数中进行加锁，析构函数中进行解锁，这样可以保证函数退出时，锁一定被释放。
		std::lock_guard<std::mutex> lck(mutex_);
		dataReady = true;
		//Sleep(2000);
		std::cout << "Sender: Data is ready." << std::endl;
		condVar.notify_one();
	}

	void mainTest();
private:
	std::mutex mutex_;
	std::condition_variable condVar;
	bool dataReady = false;
};

