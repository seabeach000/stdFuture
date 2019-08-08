
// stdFuture.cpp : ����Ӧ�ó��������Ϊ��
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


// CstdFutureApp ����

CstdFutureApp::CstdFutureApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CstdFutureApp ����

CstdFutureApp theApp;


// CstdFutureApp ��ʼ��
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
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//wxg20151125 �������̨����
	FILE *streamOut;
	FILE *streamIn;
	AllocConsole();
	SetConsoleTitle(_T("wxg test"));
	freopen_s(&streamOut,"CONOUT$", "w", stdout); // �ض������
	freopen_s(&streamIn,"CONIN$", "r+t", stdin); // �����

	//wxg20180508
	DWORD_PTR processAffinityMask = -1;
	DWORD_PTR systemAffinityMask = -1;
	bool ret = GetProcessAffinityMask(GetCurrentProcess(), &processAffinityMask, &systemAffinityMask);
	std::cout << "GetProcessAffinityMask " << std::setbase(16) << processAffinityMask << "  " << systemAffinityMask << std::endl;
	ret = SetProcessAffinityMask(GetCurrentProcess(), processAffinityMask);
	std::cout << "SetProcessAffinityMask " << std::setbase(16) << processAffinityMask << std::endl;
	//������64�˵�Ӧ�ö�������
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
	//�������һֱʧ��
	ret = SetThreadGroupAffinity(thd.native_handle(), &GroupAffinity, &previousAffinity);

	//ProcessMemoryPriority ProcessInformationClassMax
	//SetProcessInformation();����������

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
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CstdFutureApp::ExitInstance()
{
	FreeConsole();//�ͷſ���̨
	return CWinApp::ExitInstance();
}

