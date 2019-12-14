#include "Clock.h"
#include "GlobalData.h"


CClock::CClock() :
	m_msCounter(0),
	m_tickCounter(0),
	//m_lastTickCounter(0),
	m_tickAccu(0.0f),
	m_tickPeriod(0.001f),
	m_tickStep(1.0f/44100.0f),
	m_tempo(4.0f)
{
	Reset();
}


void CClock::Reset()
{
	m_msCounter = 0;
	m_tickCounter = 0;
	//m_lastTickCounter = 0;
	//m_tempoTimer = 1;
	m_state.bClockSequencer = FALSE;
	SetTempo(m_tempo);
	m_state.bShowTempo = TRUE;
}


long CClock::Tick()
{
	// Called at sample rate.
	m_tickCounter++;
	if (gAutoPowerOffWatchdog) gAutoPowerOffWatchdog--;

	m_tickAccu += m_tickStep;
	if (m_tickAccu>=m_tickPeriod)
	{
		// 1 ms timer

		m_msCounter++;

		m_tickAccu -= m_tickPeriod;

		//long deltaTick = m_tickCounter - m_lastTickCounter;
		//m_lastTickCounter = m_tickCounter;

		if (m_state.bClockSequencer)
		{
			if (!gSequencer.Clock())
			{
				gRhythm.Stop();
				gSequencer.Stop();
				m_state.bShowTempo = TRUE;
			}
		}

		if (m_state.bShowTempo)
		{
			if (gpVoices1 && gpVoices1->IsIdle())
			{
				m_state.bShowTempo = FALSE;
				gLCD.SetTempo(m_tempo);
			}
		}

		if (gpVoices1) gpVoices1->Trigger();
		gRhythm.Trigger();
		gLCD.Tick();
	}

	gEventManager.Clock(0);

	return gAutoPowerOffWatchdog;
}


float CClock::SetTempo(float tempo)
{
	if (tempo>9.0f) m_tempo = 9.0f;
	else if (tempo<-9.0f) m_tempo = -9.0f;
	else m_tempo = tempo;

	// A measure is divided in 32 beats.
	//m_tempoPeriod = (int)(gSampleRate*(kMinTempoPeriod+(9.0f-m_tempo)*kTempoUnit)/32.0f);
	//m_tempoPeriod = (int)(1000.0f*(kMinTempoPeriod+(9.0f-m_tempo)*kTempoUnit)/32.0f); // ms
	m_tempoPeriod = 1; // ms

	m_tickStep = 1.0f/gSampleRate;
	m_tickPeriod = 0.0055f+(9.0f-m_tempo)*0.00098f; // ms
	//m_tickPeriod = 0.0055f+(9.0f-m_tempo)*0.002f; // ms

	return m_tempo;
}


void CClock::EnableClock(int function, BOOL bEnable)
{
	switch (function)
	{
		case kClockSequencer:
			m_state.bClockSequencer = bEnable;
			break;
	}
}


void CClock::DisableAllClocks()
{
	m_state.bClockSequencer = FALSE;
	m_state.bShowTempo = TRUE;
}

