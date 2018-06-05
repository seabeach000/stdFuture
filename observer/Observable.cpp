#include "stdafx.h"
#include "Observable.h"


/////////////////////抽象模式实现
void CObservable::Attach(CObserver* pObs) {
	if (!pObs) return;
	m_setObs.insert(pObs);
}
void CObservable::Detach(CObserver* pObs) {
	if (!pObs) return;
	m_setObs.erase(pObs);
}
void CObservable::DetachAll() {
	m_setObs.clear();
}
void CObservable::SetChanged() {
	m_bChanged = true;
}
void CObservable::ClearChanged() {
	m_bChanged = false;
}
bool CObservable::HasChanged() {
	return m_bChanged;
}
int CObservable::GetObserversCount() {
	return m_setObs.size();
}
void CObservable::Notify(void* pArg /* = NULL */) {
	if (!HasChanged()) return;
	cout << "notify observers…" << endl;
	ClearChanged();
	set<CObserver*>::iterator itr = m_setObs.begin();
	for (; itr != m_setObs.end(); itr++) {
		(*itr)->Update(this, pArg);
	}
}
