#pragma once
#include <iostream>
#include <set>
#include <string>
using namespace std;
/////////////////////抽象模式定义
class CObservable;
//观察者，纯虚基类
class CObserver
{
public:
	CObserver() {};
	virtual ~CObserver() {};
	//当被观察的目标发生变化时，通知调用该方法
	//来自被观察者pObs, 扩展参数为pArg
	virtual void Update(CObservable* pObs, void* pArg = NULL) = 0;
};