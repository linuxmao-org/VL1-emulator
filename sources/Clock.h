/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#ifndef __CLOCK_H__
#define __CLOCK_H__


#include "VL1Defs.h"


class CSharedData;


enum
{
	kClockSequencer = 1,
};


typedef struct
{
	bool bClockSequencer;
	bool bShowTempo;
}
tClockState;


class CClock
{
public:
	CClock();

	void Setup(CSharedData *pShared);

	void Reset();

	inline long GetTickCount() { return m_tickCounter; }
	inline long GetMsCount() { return m_msCounter; }

	float SetTempo(float tempo);
	inline float GetTempo() { return m_tempo; }
	inline int GetTempoPeriod() { return m_tempoPeriod; }

	long Tick();

	void EnableClock(int function, bool bEnable);
	void DisableAllClocks();

	void GetState(tClockState& state) { state = m_state; }
	void SetState(tClockState& state) { m_state = state; }

private:
	long m_msCounter;
	long m_tickCounter;
	//long m_lastTickCounter;
	//long m_tempoTimer;
	float m_tempo;
	int m_tempoPeriod;
	float m_tickAccu;
	float m_tickPeriod;
	float m_tickStep;

	tClockState m_state;

	CSharedData *m_pShared;
};


#endif // __CLOCK_H__
