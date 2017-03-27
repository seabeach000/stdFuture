
// stdFutureDlg.h : ͷ�ļ�
//

#pragma once

#include <iostream>
#include <functional>
#include <thread>
#include <future>
#include<algorithm>
#include "BoostClasstest.h"
#include "Lambdatest.h"
#include "BoostSharedMemory.h"
//startȫ�ֶ��庯����д������
typedef std::function<void ()> fp;

//end

// CstdFutureDlg �Ի���
class CstdFutureDlg : public CDialogEx
{
// ����
public:
	CstdFutureDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STDFUTURE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CBoostClasstest m_BoostClassTest;
	CBoostSharedMemory m_BoostShareMem;
	CLambdatest m_lambdaTest;
public:
	//future
	afx_msg void OnBnClickedButtonfuture();
	void print_int(std::future<int>& fut);

	//std function
	afx_msg void OnBnClickedButtonfunction();
	static void A_fun_static() { std::cout << "A_fun_static()" << std::endl; }
	void A_fun() { std::cout << "A_fun()" << std::endl; }
	void A_fun_int(int i) { std::cout << "A_fun_int()" << std::endl; }
	void init();
	void init2();

	afx_msg void OnBnClickedButtonfunctor();
	afx_msg void OnBnClickedButtonfunctor2();
	afx_msg void OnBnClickedButtonBthread();
	afx_msg void OnBnClickedButtonlambada();
	afx_msg void OnBnClickedButtonStaticvariable();
	afx_msg void OnBnClickedButtoncplus();
};
