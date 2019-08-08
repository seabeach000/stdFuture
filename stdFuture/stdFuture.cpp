
// stdFuture.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "stdFuture.h"
#include "stdFutureDlg.h"
#include<iomanip>  

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CstdFutureApp

BEGIN_MESSAGE_MAP(CstdFutureApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CstdFutureApp 构造

CstdFutureApp::CstdFutureApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CstdFutureApp 对象

CstdFutureApp theApp;


// CstdFutureApp 初始化
void printInfo()
{
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);

	printf(" "
		"dwNumberOfProcessors=%u, dwActiveProcessorMask=%u, wProcessorLevel=%u, "
		"wProcessorArchitecture=%u, dwPageSize=%u ",
		SystemInfo.dwNumberOfProcessors, SystemInfo.dwActiveProcessorMask, SystemInfo.wProcessorLevel,
		SystemInfo.wProcessorArchitecture, SystemInfo.dwPageSize
	);
}

BOOL CstdFutureApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	//wxg20151125 加入控制台程序
	FILE *streamOut;
	FILE *streamIn;
	AllocConsole();
	SetConsoleTitle(_T("wxg test"));
	freopen_s(&streamOut,"CONOUT$", "w", stdout); // 重定向输出
	freopen_s(&streamIn,"CONIN$", "r+t", stdin); // 申请读

	//wxg20180508
	DWORD_PTR processAffinityMask = -1;
	DWORD_PTR systemAffinityMask = -1;
	bool ret = GetProcessAffinityMask(GetCurrentProcess(), &processAffinityMask, &systemAffinityMask);
	std::cout << "GetProcessAffinityMask " << std::setbase(16) << processAffinityMask << "  " << systemAffinityMask << std::endl;
	ret = SetProcessAffinityMask(GetCurrentProcess(), processAffinityMask);
	std::cout << "SetProcessAffinityMask " << std::setbase(16) << processAffinityMask << std::endl;
	//不超过64核的应该都能满足
	UCHAR NodeNumber;
	ret = GetNumaProcessorNode(0, &NodeNumber);
	std::cout << "GetNumaProcessorNode(0, &NodeNumber)   " << std::setbase(16) << (int)NodeNumber << std::endl;
	ret = GetNumaProcessorNode(16, &NodeNumber);
	std::cout << "GetNumaProcessorNode(16, &NodeNumber)   " << std::setbase(16) << (int)NodeNumber << std::endl;
	ret = GetNumaProcessorNode(32, &NodeNumber);
	std::cout << "GetNumaProcessorNode(32, &NodeNumber)   " << std::setbase(16) << (int)NodeNumber << std::endl;
	ULONGLONG processMask = 0;
	ret = GetNumaNodeProcessorMask(0, &processMask);
	std::cout << "GetNumaNodeProcessorMask(0, &processMask)   " << std::setbase(16) << processMask << std::endl;
	processMask = 0;
	ret = GetNumaNodeProcessorMask(1, &processMask);
	std::cout << "GetNumaNodeProcessorMask(1, &processMask)   " << std::setbase(16) << processMask << std::endl;
	/////////////////////////////////////////////////////////////
	USHORT groupCnt;
	USHORT groupAry;
	ret = GetProcessGroupAffinity(GetCurrentProcess(), &groupCnt, &groupAry);
	std::cout << "GetProcessGroupAffinity   " << "groupAry   " << groupAry << "  groupCnt   " << groupCnt << std::endl;

	std::thread thd(printInfo);
	GROUP_AFFINITY GroupAffinity;
	GROUP_AFFINITY previousAffinity;
	KAFFINITY  groupMask = 1;
	GroupAffinity.Mask = groupMask;
	GroupAffinity.Group = 0;
	//这个函数一直失败
	ret = SetThreadGroupAffinity(thd.native_handle(), &GroupAffinity, &previousAffinity);

	//ProcessMemoryPriority ProcessInformationClassMax
	//SetProcessInformation();都不能满足

	DWORD_PTR retmask;
	DWORD_PTR mask = 0x70;
	retmask = SetThreadAffinityMask(thd.native_handle(), mask);
	if (thd.joinable())
	{
		thd.join();
	}
	//---------------------------------------------------------------------------
	CstdFutureDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

int CstdFutureApp::ExitInstance()
{
	FreeConsole();//释放控制台
	return CWinApp::ExitInstance();
}

