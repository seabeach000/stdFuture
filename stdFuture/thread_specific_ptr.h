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
	//��־��Ϣ
	class logmsg
	{
	public:
		logmsg(time_t t, string tid, string tmsg)
			:timeinfo(t), id(tid), msg(tmsg)
		{
		}
		~logmsg()
		{}
		//ͨ��ʱ��Ƚ�������־��Ϣ
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
		time_t timeinfo; //ʱ��
		string id;   //�߳�id
		string msg;  //����

	};

	//��־�ļ�
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
		//��¼һ����־��Ϣ���ļ�
		void log(string text)
		{
			logs.push_back(logmsg(gettime(), id, text));
		}
		//������һ����־�ļ���Ϣ�ϲ������ļ�
		void combin(logfile* other)
		{
			logs.insert(logs.end(), other->logs.begin(), other->logs.end());
		}
		//��ʾ������־��Ϣ
		void display()
		{
			//��������Ϣ����ʱ������
			std::sort(logs.begin(), logs.end());
			for (auto it = logs.begin(); it != logs.end(); it++)
			{
				cout << (*it).tostring() << endl;
			}
		}
	private:
		//��ȡ��ǰʱ��
		time_t gettime()
		{
			return time(nullptr);
		}
	private:
		//�߳�ID
		string id;
		//������־��Ϣ
		vector<logmsg> logs;
	};


	//boost::mutex m_;
	//boost::shared_ptr<logfile> cmblog(new logfile);
	// ����thread_specific_ptr�����������������������������Դ
	// �������߳��˳�ʱ���Զ����ã��������ǿ��������ｫ����̼߳�¼����־
	// �ϲ���ȫ�ֵ�������־�ļ��У���delete���̹߳������־�ļ�
	//void cmb(logfile* log)
	//{
	//	boost::mutex::scoped_lock lk(m_);
	//	// �ϲ���־
	//	cmblog->combin(log);
	//	// �ͷŵ�thread_specific_ptr�������Դ
	//	delete log;
	//}
	// ȫ�ֵ�thread_specific_ptr����������������Ҫ������ʵ�ȫ�ֶ���
	// cmb�������ͷ���Դ�ĺ���
	//thread_specific_ptr<logfile> plog(cmb);//

	class thread_specific_ptrClass
	{
	public:
		friend class logfile;
		thread_specific_ptrClass();
		virtual ~thread_specific_ptrClass();
		boost::thread_specific_ptr<logfile>& get_thread_logfile();
		//�̺߳���
		void run(int id);
		// ����thread_specific_ptr�����������������������������Դ
		// �������߳��˳�ʱ���Զ����ã��������ǿ��������ｫ����̼߳�¼����־
		// �ϲ���ȫ�ֵ�������־�ļ��У���delete���̹߳������־�ļ�
		void cmb(logfile* log);
	public:
		boost::mutex m;
		boost::shared_ptr<logfile> cmblog;
		logfile* p = new logfile();

		// ȫ�ֵ�thread_specific_ptr����������������Ҫ������ʵ�ȫ�ֶ���
		// cmb�������ͷ���Դ�ĺ���
		//static thread_specific_ptr<logfile> plog;// (this->cmb);//
	};
}
