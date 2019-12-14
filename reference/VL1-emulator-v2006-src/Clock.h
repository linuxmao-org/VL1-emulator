#ifndef __CLOCK_H__
#define __CLOCK_H__


#include "VL1Defs.h"


enum
{
	kClockSequencer = 1,
};


typedef struct
{
	BOOL bClockSequencer;
	BOOL bShowTempo;
}
tClockState;


class CClock
{
public:
	CClock();

	void Reset();

	inline long GetTickCount() { return m_tickCounter; }
	inline long GetMsCount() { return m_msCounter; }

	float SetTempo(float tempo);
	inline float GetTempo() { return m_tempo; }
	inline int GetTempoPeriod() { return m_tempoPeriod; }

	long Tick();

	void EnableClock(int function, BOOL bEnable);
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
};


extern CClock gClock;


#endif // __CLOCK_H__
