
// stdFutureDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "stdFuture.h"
#include "stdFutureDlg.h"
#include "afxdialogex.h"
#include <boost/thread/thread.hpp>
#include "StaticTest.h"
#include "PlusPlus11.h"
#include "ConditionVar.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CstdFutureDlg �Ի���



CstdFutureDlg::CstdFutureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STDFUTURE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CstdFutureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CstdFutureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_future, &CstdFutureDlg::OnBnClickedButtonfuture)
	ON_BN_CLICKED(IDC_BUTTON_function, &CstdFutureDlg::OnBnClickedButtonfunction)
	ON_BN_CLICKED(IDC_BUTTON_functor, &CstdFutureDlg::OnBnClickedButtonfunctor)
	ON_BN_CLICKED(IDC_BUTTON_functor2, &CstdFutureDlg::OnBnClickedButtonfunctor2)
	ON_BN_CLICKED(IDC_BUTTON_BThread, &CstdFutureDlg::OnBnClickedButtonBthread)
	ON_BN_CLICKED(IDC_BUTTON_lambada, &CstdFutureDlg::OnBnClickedButtonlambada)
	ON_BN_CLICKED(IDC_BUTTON_StaticVariable, &CstdFutureDlg::OnBnClickedButtonStaticvariable)
	ON_BN_CLICKED(IDC_BUTTONCPlus, &CstdFutureDlg::OnBnClickedButtoncplus)
	ON_BN_CLICKED(IDC_BUTTON_specficPTR, &CstdFutureDlg::OnBnClickedButtonspecficptr)
	ON_BN_CLICKED(IDC_BUTTON3, &CstdFutureDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CstdFutureDlg ��Ϣ�������

BOOL CstdFutureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	WCHAR   szBuf[100];
	GetConsoleTitle(szBuf, 100);
	HWND hwnd = ::FindWindow(NULL, szBuf);
	HMENU hmenu = ::GetSystemMenu(hwnd,FALSE);
	RemoveMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CstdFutureDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CstdFutureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CstdFutureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/////////////////////////////////////////////////////////////////////////
void CstdFutureDlg::print_int(std::future<int>& fut)
{
	//��promise::set_value()������promise�Ĺ���״ֵ̬��fut����ͨ��future::get()��øù���״ֵ̬����promiseû�����ø�ֵ��ôfut.get()���������߳�ֱ������״ֵ̬��promise����
	int x = fut.get();
	std::cout << "value:" << x << '\n';
}

// a non-optimized way of checking for prime numbers:
bool
is_prime(int x)
{
	for (int i = 2; i < x; ++i)
		if (x % i == 0)
			return false;
	return true;
}

void CstdFutureDlg::OnBnClickedButtonfuture()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����һ��promise����
	std::promise<int> prom;
	std::future<int> fut = prom.get_future(); // ��ȡpromise�ڲ���future��fut����promise����promise�еĹ���״̬���ù���״̬���ڷ��ؼ�����
	CstdFutureDlg futuretest;
	std::thread th1(&CstdFutureDlg::print_int, &futuretest, std::ref(fut));
	{
		Sleep(10);
	}
	prom.set_value(10);
	th1.join();

	//wxg20160908
	// call is_prime(313222313) asynchronously:
	std::future<bool> fut01 = std::async(is_prime, 313222313);

	std::cout << "Checking whether 313222313 is prime.\n";
	// ...

	// do something while waiting for function to set future:
	std::cout << "checking, please wait";
	std::chrono::milliseconds span(100);
	while (fut01.wait_for(span) == std::future_status::timeout)
		std::cout << '.';
	bool ret = false;
	//ret = fut01.get();      // waits for is_prime to return
	std::shared_future<bool> result;
	if (fut01.valid())
	{
		result = fut01.share();
	}
	ret = result.get();
	if (ret) std::cout << "It is prime!\n";
	else std::cout << "It is not prime.\n";

	//std::shared_future �� std::future ���ƣ����� std::shared_future ���Կ�������� std::shared_future ���Թ���ĳ������״̬�����ս��(������״̬��ĳ��ֵ�����쳣)��
	//shared_future ����ͨ��ĳ�� std::future ������ʽת�����μ� std::shared_future �Ĺ��캯����������ͨ�� std::future::share() ��ʾת������������ת������ת�����Ǹ� 
	//std::future ���󶼻��Ϊ not-valid.

}

////////////////////////////////////////////////////////////////////////////
void g_fun()
{
	std::cout << "g_fun()" << std::endl;
}

void CstdFutureDlg::init()
{
	fp  fp1 = std::bind(&CstdFutureDlg::A_fun, this);
	fp1();
}

void CstdFutureDlg::init2()
{
	typedef std::function<void(int)> fpi;
	//���ڲ���Ҫʹ��ռλ�� std::placeholders::_1 
	fpi f = std::bind(&CstdFutureDlg::A_fun_int, this, std::placeholders::_1);
	f(5);
}

void CstdFutureDlg::OnBnClickedButtonfunction()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�󶨵�ȫ�ֺ���
	fp f2 = fp(&g_fun);
	f2();

	//�󶨵���ľ�̬��Ա
	fp f1 = fp(&CstdFutureDlg::A_fun_static);
	f1();

	this->init();
	this->init2();

	typedef std::function<int(int)> functional01;
	auto lambda = [](int a)->int {return a; };
	functional01 fun = lambda;
	int result = fun(20);


	//AfxMessageBox(L"Done");
}
/////////////////////////////////////////////////////////////////////////////
// this is a functor
struct add_x {
	add_x(int x) : x(x) {}
	int operator()(int y) { return x + y; }
private:
	int x;
};

struct sum
{
	sum(int * t) :total(t) {};
	int * total;
	void operator()(int element)
	{
		*total += element;
	}
};

void CstdFutureDlg::OnBnClickedButtonfunctor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// usage:
	add_x add42(42); // create an instance of the functor class
	int i = add42(8); // and "call" it
	assert(i == 50); // and it added 42 to its argument
	std::vector<int> in; // assume this contains a bunch of values)
	std::vector<int> out;
	in.push_back(1);
	in.push_back(2);
	out.push_back(0);
	out.push_back(0);
	// Pass a functor to std::transform, which calls the functor on every element 
	// in the input sequence, and stores the result to the output sequence
	std::transform(in.begin(), in.end(), out.begin(), add_x(1));
	assert(out[0] == in[0] + 1); // for all i
/////////////////////////////////////////////////////////////////////////////////////////
	int total = 0;
	sum s(&total);
	int arr[] = { 0, 1, 2, 3, 4, 5 };
	std::for_each(arr, arr + 6, s);
	std::cout << total << std::endl; // prints total = 15;
}

//////////////////////////////////////////////////////////////////////////////////////////////
struct Printer
{
	template<typename T >
	void operator()(T& _val)
	{
		std::cout << _val << ", ";
	}
};

void CstdFutureDlg::OnBnClickedButtonfunctor2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	std::vector<int> ivec;
	const int MAX_COUNT = 10;
	for (size_t i = 0; i < MAX_COUNT; i++)
	{
		ivec.push_back(i);
		ivec.push_back(MAX_COUNT - i);
	}

	std::cout << "initialize:";
	for_each(ivec.begin(), ivec.end(), Printer());
	transform(ivec.begin(), ivec.end(), ivec.begin(), std::negate<int>()); //������Ԫ����ֵ
	std::cout << "\n After negate:";
	for_each(ivec.begin(), ivec.end(), Printer());
	transform(ivec.begin(), ivec.end(), ivec.begin(), std::negate<int>()); //������Ԫ����ֵ

	std::cout << "\n After negate twice:";
	for_each(ivec.begin(), ivec.end(), Printer());

	//����һ����������ʼλ�ú������ʼλ������Ӧ��ֹͣλ�á�  �����·������е�  str.begin(), str.end()
	//���һ��������
	//����һ���ص���������� �ص��������������棬�򽫵�ǰ��ָ��Ĳ������Ƶ�β�������ȶ��������ƶ�����
	//����ֵ��
	//���ƶ�������׸�Ԫ�� iterator
	//ɾ����vector��С��5������Ԫ�أ�ע��remove_if�����ı������Ĵ�С�����Ի���Ҫ����erase��ɾ��
	std::vector<int>::iterator iter = std::remove_if(ivec.begin(), ivec.end(), std::bind2nd(std::less<int>(), 5));
	ivec.erase(iter, ivec.end());
	std::cout << "\nafter remove_if[ < 5 ] : ";
	for_each(ivec.begin(), ivec.end(), Printer());

	//�����������е���6��Ԫ��ֵ��Ϊ60.
	std::replace_if(ivec.begin(), ivec.end(), std::bind2nd(std::equal_to<int>(), 6), 60);
	std::cout << "\nafter replace_if[ 6 --> 60 ] : ";
	for_each(ivec.begin(), ivec.end(), Printer());

	std::cout << std::endl;

	std::system("Pause");

	return ;
}   


void CstdFutureDlg::OnBnClickedButtonBthread()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//2020��3��27��10:55:24
	m_BoostClassTest.boostFileOperation();
	//wxg2019��8��9��09:33:11
	m_BoostClassTest.boostFormatString();
	//wxg20170215
	//m_BoostShareMem.file_mapping_test_01();//�����ڴ�����
	m_BoostClassTest.Convert16StringTodata();
	m_BoostClassTest.FileParser(_T(""));
	m_BoostClassTest.simpleThread();

	//�����ڲ����������ⴴ���߳�
	std::string str = ("Hello World, I'm a thread!");
	boost::thread thrd(boost::bind(&CBoostClasstest::helloWorld, &m_BoostClassTest, str));
	thrd.join();

	//�м����������ں���д
	boost::thread thrd1(boost::bind(&CBoostClasstest::helloWorld, &m_BoostClassTest, 13, str, str));
	thrd1.join();

	boost::bind(&CBoostClasstest::helloWorld, &m_BoostClassTest, 5, _1, _2)(str, str);
	boost::bind(&CBoostClasstest::helloWorld, &m_BoostClassTest, 12, _1, _1)(str);

	m_BoostClassTest.hardware();

	//system("pause");
}


void CstdFutureDlg::OnBnClickedButtonlambada()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_lambdaTest.lambadaTest();
}


void CstdFutureDlg::OnBnClickedButtonStaticvariable()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStaticTest staticVariableTest1;
	staticVariableTest1.localStatic();
	CStaticTest staticVariableTest2;
	staticVariableTest2.localStatic();

	//wxg20160928
	staticVariableTest2.mapTest();
	staticVariableTest2.vectorfuzhi();
}


void CstdFutureDlg::OnBnClickedButtoncplus()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//2019��10��23��16:32:29
	ConditionVar var;
	var.mainTest();


	///////////////////////////
	CPlusPlus11 cllTest;
	cllTest.stdmove();
	cllTest.autoTest();
	cllTest.decltypeTest();
	cllTest.stdtime();
	cllTest.overhide();
	cllTest.generalTest();
}


void CstdFutureDlg::OnBnClickedButtonspecficptr()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_BoostClassTest.thread_specific_ptrClassTest();
	return;

}


void CstdFutureDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_test.testAll();
}
