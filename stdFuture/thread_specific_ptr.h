#pragma once
//#include <mutex>

#include <boost/thread.hpp>
#include <boost/thread/tss.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>
#include <algorithm>
using namespace boost;
using namespace std;
namespace thread_ptr
{
	//日志消息
	class logmsg
	{
	public:
		logmsg(time_t t, string tid, string tmsg)
			:timeinfo(t), id(tid), msg(tmsg)
		{
		}
		~logmsg()
		{}
		//通过时间比较两条日志消息
		bool operator < (const logmsg& other)
		{
			return timeinfo < other.timeinfo;
		}
		string tostring()
		{
			struct tm* ltime = nullptr;
			localtime_s(ltime, &timeinfo);
			string text(asctime(ltime));
			text += " " + id + ":" + msg;
			return text;
		}
	private:
		time_t timeinfo; //时间
		string id;   //线程id
		string msg;  //内容

	};

	//日志文件
	class logfile
	{
	public:
		logfile()
		{}
		logfile(int tid)
		{
			ostringstream o;
			o << tid;
			id = o.str();
			cout << id << endl;
		}
		~logfile()
		{
			cout << "destructor" << endl;
		}
	public:
		//记录一条日志消息到文件
		void log(string text)
		{
			logs.push_back(logmsg(gettime(), id, text));
		}
		//将另外一个日志文件消息合并到本文件
		void combin(logfile* other)
		{
			logs.insert(logs.end(), other->logs.begin(), other->logs.end());
		}
		//显示所有日志消息
		void display()
		{
			//对所有消息按照时间排序
			std::sort(logs.begin(), logs.end());
			for (auto it = logs.begin(); it != logs.end(); it++)
			{
				cout << (*it).tostring() << endl;
			}
		}
	private:
		//获取当前时间
		time_t gettime()
		{
			return time(nullptr);
		}
	private:
		//线程ID
		string id;
		//所有日志消息
		vector<logmsg> logs;
	};


	//boost::mutex m_;
	//boost::shared_ptr<logfile> cmblog(new logfile);
	// 这是thread_specific_ptr的清理函数，负责清理它所管理的资源
	// 他会在线程退出时被自动调用，所以我们可以在这里将这个线程记录的日志
	// 合并到全局的最终日志文件中，并delete掉线程管理的日志文件
	//void cmb(logfile* log)
	//{
	//	boost::mutex::scoped_lock lk(m_);
	//	// 合并日志
	//	cmblog->combin(log);
	//	// 释放掉thread_specific_ptr管理的资源
	//	delete log;
	//}
	// 全局的thread_specific_ptr对象，用他来管理需要共享访问的全局对象
	// cmb是它的释放资源的函数
	//thread_specific_ptr<logfile> plog(cmb);//

	class thread_specific_ptrClass
	{
	public:
		friend class logfile;
		thread_specific_ptrClass();
		virtual ~thread_specific_ptrClass();
		boost::thread_specific_ptr<logfile>& get_thread_logfile();
		//线程函数
		void run(int id);
		// 这是thread_specific_ptr的清理函数，负责清理它所管理的资源
		// 他会在线程退出时被自动调用，所以我们可以在这里将这个线程记录的日志
		// 合并到全局的最终日志文件中，并delete掉线程管理的日志文件
		void cmb(logfile* log);
	public:
		boost::mutex m;
		boost::shared_ptr<logfile> cmblog;
		logfile* p = new logfile();

		// 全局的thread_specific_ptr对象，用他来管理需要共享访问的全局对象
		// cmb是它的释放资源的函数
		//static thread_specific_ptr<logfile> plog;// (this->cmb);//
	};
}
