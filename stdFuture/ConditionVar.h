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
		//���̱߳�����ʱ���ú������Զ����� lck.unlock() �ͷ�����ʹ���������������������ϵ��̵߳��Լ���ִ��
		//���⣬һ����ǰ�̻߳��֪ͨ(notified��ͨ��������ĳ���̵߳��� notify_* �����˵�ǰ�߳�)��wait()����Ҳ���Զ����� lck.lock()��ʹ��lck��״̬�� wait ����������ʱ��ͬ
		//�ڵڶ�������£��������� Predicate����ֻ�е� pred ����Ϊfalse ʱ���� wait() �Ż�������ǰ�̣߳��������յ������̵߳�֪ͨ��ֻ�е� pred Ϊ true ʱ�Żᱻ�������
		//wait_for wait_until
		condVar.wait(lck, [this] {return dataReady; });
		doTheWork();
		std::cout << "Work done." << std::endl;
	}

	void setDataReady() {
		//std::lock_guard��ʵ���Ǽ򵥵�RAII��װ���ڹ��캯���н��м��������������н��н������������Ա�֤�����˳�ʱ����һ�����ͷš�
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

