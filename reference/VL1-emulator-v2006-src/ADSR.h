#ifndef __ADSR_H__
#define __ADSR_H__


#include "Utils.h"
#include "Filters.h"
#include "LineInTime.h"
#include "VL1Defs.h"


enum
{
	kAdsrIdle = 0,
	kAdsrAttack,
	kAdsrDecay,
	kAdsrSustain,
	kAdsrRelease,
};


class CAdsr
{
public:
	CAdsr();

	void Reset();

	void SetAttack(float value) { m_attack = value; }
	void SetDecay(float value) { m_decay = value; }
	void SetSustainLevel(float value) { m_sustainLevel = value; }
	void SetSustainSlope(float value) { m_sustainSlope = value; }
	void SetRelease(float value) { m_release = value; }

	inline BOOL IsIdle() { return (m_phase==kAdsrIdle); }
	void Gate(BOOL bGate);

	float Clock();

	//void Mute()  { Reset(); m_phase = kAdsrIdle; }

private:
	//inline float MsToSamples(float time) { return 0.001f*time*m_sampleRate; }
	void InitializePhase(int phase, const tEnvelopePhaseInfo *pInfo, const tEnvelopePhaseInfo *pInfo2=NULL);
	void Interpolate(float v, const tEnvelopePhaseInfo *pInfo, tEnvelopePhaseInfo& out);

	float m_attack;
	float m_decay;
	float m_sustainLevel;
	float m_sustainSlope;
	float m_release;
	BOOL m_bGate;
	float m_adsr;
	float m_adsrMin;
	float m_adsrMax;
	int m_phase;
	BOOL m_bScheduleRelease;

	CLineInTime m_envelope;
};


#endif // __ADSR_H__
