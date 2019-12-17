#include "EventManager.h"
#include <string.h>
#include <assert.h>


CEventManager::CEventManager()
{
	//Initialize();
}


CEventManager::~CEventManager()
{
	//Destroy();
}


void CEventManager::Register(CEventInput *pListener)
{
	assert(pListener);
	m_pListener.push_back(pListener);
}


void CEventManager::SendEvent(const tEvent &event)
{
	for (CEventInput *listener : m_pListener)
	{
		listener->ProcessEvent(event);
	}
}
