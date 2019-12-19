/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

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
