
// stdFuture.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CstdFutureApp: 
// �йش����ʵ�֣������ stdFuture.cpp
//

class CstdFutureApp : public CWinApp
{
public:
	CstdFutureApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CstdFutureApp theApp;