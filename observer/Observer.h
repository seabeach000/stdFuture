#pragma once
#include <iostream>
#include <set>
#include <string>
using namespace std;
/////////////////////����ģʽ����
class CObservable;
//�۲��ߣ��������
class CObserver
{
public:
	CObserver() {};
	virtual ~CObserver() {};
	//�����۲��Ŀ�귢���仯ʱ��֪ͨ���ø÷���
	//���Ա��۲���pObs, ��չ����ΪpArg
	virtual void Update(CObservable* pObs, void* pArg = NULL) = 0;
};