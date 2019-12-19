/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#ifndef __ADSR_H__
#define __ADSR_H__


#include "Utils.h"
#include "Filters.h"
#include "LineInTime.h"
#include "VL1Defs.h"


class CSharedData;


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

	void Setup(CSharedData *pShared);

	void Reset();

	void SetAttack(float value) { m_attack = value; }
	void SetDecay(float value) { m_decay = value; }
	void SetSustainLevel(float value) { m_sustainLevel = value; }
	void SetSustainSlope(float value) { m_sustainSlope = value; }
	void SetRelease(float value) { m_release = value; }

	inline bool IsIdle() { return (m_phase==kAdsrIdle); }
	void Gate(bool bGate);

	float Clock();

	//void Mute()  { Reset(); m_phase = kAdsrIdle; }

private:
	//inline float MsToSamples(float time) { return 0.001f*time*m_sampleRate; }
	void InitializePhase(int phase, const tEnvelopePhaseInfo *pInfo, const tEnvelopePhaseInfo *pInfo2=nullptr);
	void Interpolate(float v, const tEnvelopePhaseInfo *pInfo, tEnvelopePhaseInfo& out);

	float m_attack;
	float m_decay;
	float m_sustainLevel;
	float m_sustainSlope;
	float m_release;
	bool m_bGate;
	float m_adsr;
	float m_adsrMin;
	float m_adsrMax;
	int m_phase;
	bool m_bScheduleRelease;

	CLineInTime m_envelope;
};


#endif // __ADSR_H__
