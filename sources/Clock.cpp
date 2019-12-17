#include "Clock.h"
#include "Sequencer.h"
#include "Rhythm.h"
#include "VoiceManager.h"
#include "EventManager.h"
#include "LcdBuffer.h"
#include "SharedData.h"


CClock::CClock() :
	m_msCounter(0),
	m_tickCounter(0),
	//m_lastTickCounter(0),
	m_tempo(4.0f),
	m_tickAccu(0.0f),
	m_tickPeriod(0.001f),
	m_tickStep(1.0f/kDefaultSampleRate),
	m_pShared(nullptr)
{
	Reset();
}


void CClock::Setup(CSharedData *pShared)
{
	m_pShared = pShared;

	m_tickStep = 1.0f/m_pShared->sampleRate;
	SetTempo(m_tempo);
}


void CClock::Reset()
{
	m_msCounter = 0;
	m_tickCounter = 0;
	//m_lastTickCounter = 0;
	//m_tempoTimer = 1;
	m_state.bClockSequencer = false;
	SetTempo(m_tempo);
	m_state.bShowTempo = true;
}


long CClock::Tick()
{
	CSequencer *sequencer = m_pShared->sequencer;
	CRhythm *rhythm = m_pShared->rhythm;
	CVoiceManager *pVoices1 = m_pShared->pVoices1;
	//CEventManager *eventManager = m_pShared->eventManager;
	CLcdBuffer *LCD = m_pShared->LCD;

	// jpc: don't use a power-off watchdog
	int gAutoPowerOffWatchdog = 1;

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
			if (!sequencer->Clock())
			{
				rhythm->Stop();
				sequencer->Stop();
				m_state.bShowTempo = true;
			}
		}

		if (m_state.bShowTempo)
		{
			if (pVoices1->IsIdle())
			{
				m_state.bShowTempo = false;
				LCD->SetTempo(m_tempo);
			}
		}

		pVoices1->Trigger();
		rhythm->Trigger();
		LCD->Tick();
	}

	//eventManager->Clock(0);

	return gAutoPowerOffWatchdog;
}


float CClock::SetTempo(float tempo)
{
	float sampleRate = m_pShared ? m_pShared->sampleRate : kDefaultSampleRate;

	if (tempo>9.0f) m_tempo = 9.0f;
	else if (tempo<-9.0f) m_tempo = -9.0f;
	else m_tempo = tempo;

	// A measure is divided in 32 beats.
	//m_tempoPeriod = (int)(gSampleRate*(kMinTempoPeriod+(9.0f-m_tempo)*kTempoUnit)/32.0f);
	//m_tempoPeriod = (int)(1000.0f*(kMinTempoPeriod+(9.0f-m_tempo)*kTempoUnit)/32.0f); // ms
	m_tempoPeriod = 1; // ms

	m_tickStep = 1.0f/sampleRate;
	m_tickPeriod = 0.0055f+(9.0f-m_tempo)*0.00098f; // ms
	//m_tickPeriod = 0.0055f+(9.0f-m_tempo)*0.002f; // ms

	return m_tempo;
}


void CClock::EnableClock(int function, bool bEnable)
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
	m_state.bClockSequencer = false;
	m_state.bShowTempo = true;
}
