#pragma once
#include "Observer.h"

//���۲��ߣ���Subject
class CObservable
{
public:
	CObservable() : m_bChanged(false) {};
	virtual ~CObservable() {};
	void Attach(CObserver* pObs);   //ע��۲���
	void Detach(CObserver* pObs);   //ע���۲���
	void DetachAll();               //ע�����й۲���
	void Notify(void* pArg = NULL); //��״̬�仯��������۲��ߣ����֪ͨ����
	bool HasChanged();              //����Ŀ��״̬�Ƿ�仯
	int GetObserversCount();        //��ȡ�۲�������
protected:
	void SetChanged();              //����״̬�仯!!!����̳�CObservable��������Ŀ��״̬
	void ClearChanged();            //��ʼ��Ŀ��Ϊδ�仯״̬
private:
	bool m_bChanged;                //״̬
	set<CObserver*> m_setObs;       //set��֤Ŀ��Ψһ��
};

/////////////////////����Ӧ���ඨ���ʵ��
//bloger�Ƿ����ߣ������۲���(subject)
class CBloger : public CObservable
{
public:
	void Publish(const string &strContent) {
		cout << "bloger publish, content: " << strContent << endl;
		SetChanged();
		Notify(const_cast<char*>(strContent.c_str()));
	}
};

//portal�Ƿ����ߣ������۲���(subject)
class CPortal : public CObservable
{
public:
	void Publish(const string &strContent) {
		cout << "portal publish, content: " << strContent << endl;
		SetChanged();
		Notify(const_cast<char*>(strContent.c_str()));
	}
};

//RSS�Ķ������۲���
class CRSSReader : public CObserver
{
public:
	CRSSReader(const string &strName) : m_strName(strName) {}
	virtual void Update(CObservable* pObs, void* pArg = NULL) {
		char* pContent = static_cast<char*>(pArg);
		//�۲���Ŀ��
		if (dynamic_cast<CBloger*>(pObs)) {
			cout << m_strName << " updated from bloger, content: " << pContent << endl;
		}
		else if (dynamic_cast<CPortal*>(pObs)) {
			cout << m_strName << " updated from portal, content: " << pContent << endl;
		}
	}
private:
	string m_strName;
};

//Mail�Ķ������۲���
class CMailReader : public CObserver
{
public:
	CMailReader(const string &strName) : m_strName(strName) {}
	virtual void Update(CObservable* pObs, void* pArg = NULL) {
		char* pContent = static_cast<char*>(pArg);
		if (dynamic_cast<CBloger*>(pObs)) {
			cout << m_strName << " updated from bloger, content: " << pContent << endl;
		}
		if (dynamic_cast<CPortal*>(pObs)) {
			cout << m_strName << " updated from portal, content: " << pContent << endl;
		}
	}
private:
	string m_strName;
};