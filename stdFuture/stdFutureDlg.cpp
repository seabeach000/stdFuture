
// stdFutureDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "stdFuture.h"
#include "stdFutureDlg.h"
#include "afxdialogex.h"
#include <boost/thread/thread.hpp>
#include "StaticTest.h"
#include "PlusPlus11.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CstdFutureDlg 对话框



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
END_MESSAGE_MAP()


// CstdFutureDlg 消息处理程序

BOOL CstdFutureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	WCHAR   szBuf[100];
	GetConsoleTitle(szBuf, 100);
	HWND hwnd = ::FindWindow(NULL, szBuf);
	HMENU hmenu = ::GetSystemMenu(hwnd,FALSE);
	RemoveMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CstdFutureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CstdFutureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/////////////////////////////////////////////////////////////////////////
void CstdFutureDlg::print_int(std::future<int>& fut)
{
	//当promise::set_value()设置了promise的共享状态值后，fut将会通过future::get()获得该共享状态值，若promise没有设置该值那么fut.get()将会阻塞线程直到共享状态值被promise设置
	int x = fut.get();
	std::cout << "value:" << x << '\n';
}

void CstdFutureDlg::OnBnClickedButtonfuture()
{
	// TODO: 在此添加控件通知处理程序代码
	//创建一个promise对象
	std::promise<int> prom;
	std::future<int> fut = prom.get_future(); // 获取promise内部的future，fut将和promise共享promise中的共享状态，该共享状态用于返回计算结果
	CstdFutureDlg futuretest;
	std::thread th1(&CstdFutureDlg::print_int, &futuretest, std::ref(fut));
	prom.set_value(10);

	th1.join();

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
	//对于参数要使用占位符 std::placeholders::_1 
	fpi f = std::bind(&CstdFutureDlg::A_fun_int, this, std::placeholders::_1);
	f(5);
}

void CstdFutureDlg::OnBnClickedButtonfunction()
{
	// TODO: 在此添加控件通知处理程序代码
	//绑定到全局函数
	fp f2 = fp(&g_fun);
	f2();

	//绑定到类的静态成员
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	std::vector<int> ivec;
	const int MAX_COUNT = 10;
	for (size_t i = 0; i < MAX_COUNT; i++)
	{
		ivec.push_back(i);
		ivec.push_back(MAX_COUNT - i);
	}

	std::cout << "initialize:";
	for_each(ivec.begin(), ivec.end(), Printer());
	transform(ivec.begin(), ivec.end(), ivec.begin(), std::negate<int>()); //将所有元素求反值
	std::cout << "\n After negate:";
	for_each(ivec.begin(), ivec.end(), Printer());
	transform(ivec.begin(), ivec.end(), ivec.begin(), std::negate<int>()); //将所有元素求反值

	std::cout << "\n After negate twice:";
	for_each(ivec.begin(), ivec.end(), Printer());
	//删除掉vector中小于5的所有元素，注意remove_if并不改变容器的大小，所以还需要调用erase来删除
	std::vector<int>::iterator iter = std::remove_if(ivec.begin(), ivec.end(), std::bind2nd(std::less<int>(), 5));
	ivec.erase(iter, ivec.end());
	std::cout << "\nafter remove_if[ < 5 ] : ";
	for_each(ivec.begin(), ivec.end(), Printer());

	//将集合中所有等于6的元素值改为60.
	std::replace_if(ivec.begin(), ivec.end(), std::bind2nd(std::equal_to<int>(), 6), 60);
	std::cout << "\nafter replace_if[ 6 --> 60 ] : ";
	for_each(ivec.begin(), ivec.end(), Printer());

	std::cout << std::endl;

	system("Pause");

	return ;
}   


void CstdFutureDlg::OnBnClickedButtonBthread()
{
	// TODO: 在此添加控件通知处理程序代码
	m_BoostClassTest.FileParser(_T(""));


	m_BoostClassTest.simpleThread();

	//用类内部函数在类外创建线程
	std::string str = ("Hello World, I'm a thread!");
	boost::thread thrd(boost::bind(&CBoostClasstest::helloWorld, &m_BoostClassTest, str));
	thrd.join();

	//system("pause");
}


void CstdFutureDlg::OnBnClickedButtonlambada()
{
	// TODO: 在此添加控件通知处理程序代码
	m_lambdaTest.lambadaTest();
}


void CstdFutureDlg::OnBnClickedButtonStaticvariable()
{
	// TODO: 在此添加控件通知处理程序代码
	CStaticTest staticVariableTest1;
	staticVariableTest1.localStatic();
	CStaticTest staticVariableTest2;
	staticVariableTest2.localStatic();
}


void CstdFutureDlg::OnBnClickedButtoncplus()
{
	// TODO: 在此添加控件通知处理程序代码
	CPlusPlus11 cllTest;
	cllTest.stdmove();
	cllTest.autoTest();
	cllTest.decltypeTest();

}
