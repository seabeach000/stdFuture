#pragma once
#include <mutex>

#include <boost/thread.hpp>
#include <boost/thread/tss.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>
#include <algorithm>
using namespace boost;
using namespace std;
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
		struct tm* ltime;
		localtime_s(ltime,&timeinfo);
		string text(asctime(ltime));
		text += " " + id + ":" + msg;
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

boost::shared_ptr<logfile> cmblog(new logfile);

class thread_specific_ptrClass
{
public:
	friend class logfile;
	thread_specific_ptrClass();
	virtual ~thread_specific_ptrClass();
	//线程函数
	void run(int id);
public:
	boost::mutex m;
	//boost::shared_ptr<logfile> cmblog(new logfile);
	logfile* p = new logfile();
};

