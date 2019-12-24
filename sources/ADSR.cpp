/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#include "ADSR.h"
#include <math.h>


const float kAdsrTimeMin = 0.01f; // sec.
const float kAdsrTimeMax = 10.0f; // sec.


CAdsr::CAdsr() :
	m_attack(0.0f),
	m_decay(0.0f),
	m_sustainLevel(1.0f),
	m_sustainSlope(9.0f),
	m_release(4.0f),
	m_adsrMin(0.000001f),
	m_adsrMax(1.0f)
{
	Reset();
	m_envelope.SetResolution(1000.0f*kEnvelopeTimeUnit,1.0f);
}


void CAdsr::Setup(CSharedData *pShared)
{
	m_envelope.Setup(pShared);
}


void CAdsr::Reset()
{
	m_adsr = 0.0f;
	m_phase = kAdsrIdle;
	m_bGate = false;
	m_bScheduleRelease = false;
}


void CAdsr::Interpolate(float v, const tEnvelopePhaseInfo *pInfo, tEnvelopePhaseInfo& out)
{
	int a1 = (int)floorf(v);
	int a2 = (int)ceilf(v);
	out.tUnits = (v-(float)a1)*pInfo[a1].tUnits + ((float)a2-v)*pInfo[a1].tUnits;
	out.lBegin = (v-(float)a1)*pInfo[a1].lBegin + ((float)a2-v)*pInfo[a1].lBegin;
	out.lEnd = (v-(float)a1)*pInfo[a1].lEnd + ((float)a2-v)*pInfo[a1].lEnd;
}


void CAdsr::InitializePhase(int phase, const tEnvelopePhaseInfo *pInfo, const tEnvelopePhaseInfo *pInfo2)
{
	int previousPhase = m_phase;

	m_phase = phase;
	m_bScheduleRelease = false;

	float t0 = 0.0f;
	float t1 = phase==kAdsrSustain? pInfo2->tUnits : pInfo->tUnits;
	if (t1<0 && phase==kAdsrSustain)
	{
		// Infinite sustain.
		t1 = 9999999.0f;
	}
	else
	{
		t1 *= 1000.0f*kEnvelopeTimeUnit;
	}

	if (t1<=t0)
	{
		if (phase==kAdsrAttack) t1 = 18.0f;
	}

	float y0 = phase==kAdsrSustain? pInfo2->lBegin : pInfo->lBegin;
	float y1 = phase==kAdsrSustain? pInfo2->lEnd : pInfo->lEnd;

	//bool bRestart = phase==kAdsrAttack;
	bool bRestart = phase==kAdsrAttack && previousPhase==kAdsrIdle; // jpc

	m_envelope.Initialize(t0,y0,t1,y1,bRestart);
	//if (phase==kAdsrSustain) m_envelope.LoadAccumulator(pInfo->lEnd);
	m_envelope.Start();
}


void CAdsr::Gate(bool bGate)
{
	m_bGate = bGate;
	if (bGate)
	{
		//tEnvelopePhaseInfo info;
		//Interpolate(m_attack,(tEnvelopePhaseInfo*)&gAttack,info);
		//InitializePhase(kAdsrAttack,&info);
		InitializePhase(kAdsrAttack,&gAttack[(int)m_attack]);
	}
	else if (m_phase!=kAdsrIdle)
	{
		bool bDebug = false;
		if (m_phase==kAdsrAttack) m_bScheduleRelease = true; // Attack should always finish.
		else if (!bDebug)
		{
			InitializePhase(kAdsrRelease,&gRelease[(int)m_release]);
		}
	}
}


float CAdsr::Clock()
{
	m_adsr = m_envelope.Clock()*kEnvelopeStep;

	if (m_adsr>=m_adsrMax)
	{
		m_adsr = 1.0f;
	}
	else if (m_adsr<=m_adsrMin)
	{
		m_adsr = 0.0f;
		m_phase = kAdsrIdle;
	}

	switch (m_phase)
	{
		case kAdsrAttack:
			if (m_envelope.IsFinished())
			{
				if (m_bScheduleRelease)
				{
					InitializePhase(kAdsrRelease,&gRelease[(int)m_release]);
				}
				else
				{
					int d = (int)m_decay;
					if (d) InitializePhase(kAdsrDecay,&gDecay[d]);
					else
					{
						InitializePhase(kAdsrSustain,&gSustainLevel[(int)m_sustainLevel],&gSustainSlope[(int)m_sustainSlope]);
						m_envelope.LoadAccumulator(gSustainLevel[(int)m_sustainLevel].lEnd);
					}
				}
			}
			break;

		case kAdsrDecay:
			{
				float s = kEnvelopeStep*gSustainLevel[(int)m_sustainLevel].lEnd;
				if (m_adsr<=s)
				{
					InitializePhase(kAdsrSustain,&gSustainLevel[(int)m_sustainLevel],&gSustainSlope[(int)m_sustainSlope]);
				}
			}
			break;

		case kAdsrSustain:
			break;

		case kAdsrRelease:
			break;

		case kAdsrIdle:
			//return 0.0f;
			break;
	}

	return m_adsr;
}
