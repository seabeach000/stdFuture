#include "stdafx.h"
#include "Emperor.h"

CEmperor* CEmperor::m_pEmperor = nullptr;
CEmperor::CGarbo CEmperor::m_Garbo;
HANDLE CEmperor::m_pMutex = CreateMutex(nullptr, FALSE, nullptr);
CEmperor::CEmperor()
{
	cout << "Create CEmperor Instance" << endl;
}

CEmperor::~CEmperor()
{
	cout << "Destroy CEmperor Instance and release its resource" << endl;
}

//CEmperor::CEmperor(const CEmperor&)
//{
//
//}
//
//CEmperor& CEmperor::operator=(const CEmperor&)
//{
//
//}


CEmperor* CEmperor::GetInstance()
{
	if (nullptr == m_pEmperor)
	{
		WaitForSingleObject(m_pMutex, INFINITE);
		if (nullptr == m_pEmperor)
		{
			m_pEmperor = new CEmperor();
		}
		ReleaseMutex(m_pMutex);
	}
	return m_pEmperor;
}

void CEmperor::ReleaseInstance()
{
	if (NULL != m_pEmperor)
	{
		WaitForSingleObject(m_pMutex, INFINITE);
		if (NULL != m_pEmperor)
		{
			delete m_pEmperor;
			m_pEmperor = NULL;
		}
		ReleaseMutex(m_pMutex);
	}
}

void CEmperor::EmperorInfo(void)
{
	char msgBuffer[50] = { 0 };
	sprintf_s(msgBuffer, 50, "»ÊµÛ......%s", m_pEmperorTag.c_str());
	string msg(msgBuffer);
	cout << msg.c_str() << endl;
}

void CEmperor::SetEmperorTag(string tag)
{
	m_pEmperorTag = tag;
}

