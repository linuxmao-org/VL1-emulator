/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#pragma once
#include "WaveSet.h"

class CClock;
class CLcdBuffer;
//class FFTReal;
class CVoiceManager;
class CRhythm;
class CSequencer;
class CCalculator;
class CEventManager;
struct tLcdScreenData;

class CSharedData
{
public:
	float sampleRate;
	int oversampling;
	CClock *clock;
	CLcdBuffer *LCD;
	CWaveSet *waves;
	//FFTReal *FFT;
	CVoiceManager *pVoices1;
	CRhythm *rhythm;
	CSequencer *sequencer;
	CCalculator *calculator;
	CEventManager *eventManager;
	tLcdScreenData *screenData;
};
