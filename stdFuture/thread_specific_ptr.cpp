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
		// Ϊÿ���߳�newһ�����󣬽���thread_specific_ptr���й���
		get_thread_logfile().reset(new logfile(id));
		// ��¼һ����־������̱߳��ش洢��logfile
		get_thread_logfile()->log("�߳�����");

		random::uniform_int_distribution<int>  wt(100, 5000);
		random::mt19937 gen;

		boost::posix_time::milliseconds worktime(wt(gen));
		boost::this_thread::sleep(worktime);

		get_thread_logfile()->log("�߳̽���");
		// ���߳̽�����ʱ��Ĭ������£������Զ�delete�����������Դ����������ڹ��캯�����������Դ�����������������cmb����������Զ�������������������������

		// ���⣬����Ҳ���Ե�������release()�������������������Դ���Լ����д��������ٸ�����Դ������
	}

	void thread_specific_ptrClass::cmb(logfile* log)
	{
		boost::mutex::scoped_lock lk(m);
		// �ϲ���־
		cmblog->combin(log);
		// �ͷŵ�thread_specific_ptr�������Դ
		delete log;
	}
}