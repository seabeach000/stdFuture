#include "stdafx.h"
#include "CThreadLocal.h"

#include <thread>

#include <mutex>

#include <iostream>


namespace wwxxgg {
	namespace threadlocal {

		thread_local call_context context;

		//����һ����̬��Ա����������ͨ������ֱ�ӵ��ã�static thread_local �� thread_local �����ǵȼ۵ģ����Է��ʵľ��Ǿ�̬���ݳ�Ա
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
			g_n++;   //�޸Ĳ�������Ӱ��g_n���߳�t2��t3�еĳ�ʼֵ(ֵΪ1)
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
			//thread_local ÿ����һ���߳̾ͻ��ʼ��һ��
			std::thread t21([]() {
				{
					//ͬһ���߳���scoped_call_context ��call_context::for_thread()����ͬһ��thread_local call_context
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
		//������
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
�����ǰ3�д�ӡ�ܰ������thread_local��������γ�ʼ���ģ����Կ���ÿ���̶߳������һ�γ�ʼ���������е�g_n�����߳������类��ʼ��Ϊ1��
����޸�Ϊ2��3������Щ�޸Ĳ�������Ӱ��g_n���߳�t2��t3�еĳ�ʼֵ(ֵΪ1)����Ȼt2��t3�߳�������ʱ�����߳��еı���ֵ�Ѿ�������Ϊ3��
�������̡߳�thread1��thread2��ӡ����ֱ�Ϊ3��2��2��

��6�д�ӡ˵����һ����ʵ������Ϊthread_local�ı��ر������߳����ǳ������ڵģ���ͬ����ͨ��ʱ�������������ڣ�������static����һ���ĳ�ʼ���������������ڣ�
��Ȼ����û�б�����Ϊstatic��������foo�����е�thread_local���� i ��ÿ���̵߳�һ��ִ�е���ʱ���ʼ������ÿ���̸߳����ۼӣ����߳̽���ʱ�ͷš�

b_key �� thread_local����Ȼ��Ҳ�� static �ģ�����ÿ���߳�����һ����ÿ���߳��е����е��ù������������b_static �������� static��ȫ��ֻ��һ���������̹߳������������
*/