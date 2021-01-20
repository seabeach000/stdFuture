#include "stdafx.h"
#include "CThreadLocal.h"

#include <thread>

#include <mutex>

#include <iostream>


namespace wwxxgg {
	namespace threadlocal {

		thread_local call_context context;

		//这是一个静态成员函数，可以通过类名直接调用，static thread_local 和 thread_local 声明是等价的，所以访问的就是静态数据成员
		call_context& call_context::for_thread() { return context; }

		std::wstring call_context::to_string() const
		{
			if (video_channel == -1)
				return L"[]";
			if (layer == -1)
				return L"[ch=" + std::to_wstring(video_channel) + L"]";
			return L"[ch=" + std::to_wstring(video_channel) + L"; layer=" + std::to_wstring(layer) + L"]";
		}


		thread_local int g_n = 1;

		void f()
		{
			g_n++;
			printf("id=%d, n=%d\n", std::this_thread::get_id(), g_n);
		}

		void foo()
		{
			thread_local int i = 0;
			printf("id=%d, n=%d\n", std::this_thread::get_id(), i);
			i++;
		}

		void f2()
		{
			foo();
			foo();
		}

		ThreadLocal::ThreadLocal()
		{

		}

		ThreadLocal::~ThreadLocal()
		{

		}

		void thread_func(const std::string& thread_name);
		void ThreadLocal::test()
		{
			g_n++;   //修改操作并不影响g_n在线程t2和t3中的初始值(值为1)
			f();
			std::thread t1(f);
			std::thread t2(f);
			t1.join();
			t2.join();

			f2();
			std::thread t4(f2);
			std::thread t5(f2);
			t4.join();
			t5.join();

			/////////////////////////////////////
			std::thread t11(thread_func, "t11");
			std::thread t12(thread_func, "t12");
			t11.join();
			t12.join();

			//////////////////////////////////////
			//thread_local 每启动一个线程就会初始化一次
			std::thread t21([]() {
				{
					//同一个线程内scoped_call_context 和call_context::for_thread()共享同一个thread_local call_context
					scoped_call_context save;
					std::cout << " t21 " << call_context::for_thread().video_channel << std::endl;
					call_context::for_thread().video_channel = 1;
					call_context::for_thread().layer = 10;
					std::cout << " t21 " << call_context::for_thread().video_channel << std::endl;
				}
				std::cout << " t21 " << call_context::for_thread().video_channel << std::endl;
			});
			
			int ret = [](int index)
			{
				int aa = index+=11;
				return aa;
			}(200);


			std::thread t22([]() {
				call_context::for_thread().video_channel = 2;
				call_context::for_thread().layer = 20;
			});

			t21.join();
			t22.join();
		}




		std::mutex cout_mutex;
		//定义类
		class A {
		public:
			A() {
				std::lock_guard<std::mutex> lock(cout_mutex);
				std::cout << "create A" << std::endl;
			}

			~A() {
				std::lock_guard<std::mutex> lock(cout_mutex);
				std::cout << "destroy A" << std::endl;
			}

			int counter = 0;
			int get_value() {
				return counter++;
			}
		};
		void thread_func(const std::string& thread_name) {
			for (int i = 0; i < 3; ++i) {
				thread_local A* a = new A();
				std::lock_guard<std::mutex> lock(cout_mutex);
				std::cout << "thread[" << thread_name.c_str() << "]: a.counter:" << a->get_value() << std::endl;
			}
			return;
		}

	}
}

/*
输出的前3行打印能帮助解答thread_local变量是如何初始化的，可以看到每个线程都会进行一次初始化，例子中的g_n在主线程中最早被初始化为1，
随后被修改为2和3，但这些修改操作并不影响g_n在线程t2和t3中的初始值(值为1)，虽然t2和t3线程启动的时候主线程中的变量值已经被更新为3，
所以主线程、thread1、thread2打印结果分别为3，2，2。

后6行打印说明了一个事实，声明为thread_local的本地变量在线程中是持续存在的，不同于普通临时变量的生命周期，它具有static变量一样的初始化特征和生命周期，
虽然它并没有被声明为static。例子中foo函数中的thread_local变量 i 在每个线程第一次执行到的时候初始化，在每个线程各自累加，在线程结束时释放。

b_key 是 thread_local，虽然其也是 static 的，但是每个线程中有一个，每次线程中的所有调用共享这个变量。b_static 是真正的 static，全局只有一个，所有线程共享这个变量。
*/