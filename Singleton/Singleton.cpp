// Singleton.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Emperor.h"

void DoIt()

{
	CEmperor *pEmperor1 = CEmperor::GetInstance();
	pEmperor1->SetEmperorTag("95");
	pEmperor1->EmperorInfo();

	CEmperor *pEmperor2 = CEmperor::GetInstance();
	pEmperor2->EmperorInfo();

	CEmperor *pEmperor3 = CEmperor::GetInstance();
	pEmperor3->EmperorInfo();

	CEmperor *pEmperor4 = pEmperor3;
	pEmperor4->EmperorInfo();

	CEmperor *pEmperor5 = NULL;
	pEmperor5 = pEmperor4;
	pEmperor5->EmperorInfo();

	CEmperor::ReleaseInstance();

}
int main()
{
	DoIt();
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}

