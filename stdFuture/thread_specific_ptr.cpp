#include "stdafx.h"
#include "thread_specific_ptr.h"

namespace thread_ptr
{
	thread_specific_ptrClass::thread_specific_ptrClass()
	{
		cmblog = boost::make_shared<logfile>();
	}

	thread_specific_ptrClass::~thread_specific_ptrClass()
	{
	}

	boost::thread_specific_ptr<logfile>& thread_specific_ptrClass::get_thread_logfile()
	{
		static thread_specific_ptr<logfile> plog;//
		return plog;
	}

	void thread_specific_ptrClass::run(int id)
	{
		// 为每个线程new一个对象，交给thread_specific_ptr进行管理
		get_thread_logfile().reset(new logfile(id));
		// 记录一条日志到这个线程本地存储的logfile
		get_thread_logfile()->log("线程启动");

		random::uniform_int_distribution<int>  wt(100, 5000);
		random::mt19937 gen;

		boost::posix_time::milliseconds worktime(wt(gen));
		boost::this_thread::sleep(worktime);

		get_thread_logfile()->log("线程结束");
		// 在线程结束的时候，默认情况下，它会自动delete它所管理的资源，如果我们在构造函数中提高了资源清理函数，例如这里的cmb函数，则会自动调用这个函数来完成清理工作。

		// 另外，我们也可以调用它的release()函数返回它所管理的资源，自己进行处理，它不再负责资源的清理
	}

	void thread_specific_ptrClass::cmb(logfile* log)
	{
		boost::mutex::scoped_lock lk(m);
		// 合并日志
		cmblog->combin(log);
		// 释放掉thread_specific_ptr管理的资源
		delete log;
	}
}