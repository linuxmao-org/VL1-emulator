#pragma once
#include "WaveSet.h"
#include <stdint.h>

class CClock;
class CLcdBuffer;
//class FFTReal;
class CVoiceManager;
class CRhythm;
class CSequencer;
class CCalculator;
class CEventManager;
struct tLcdScreenData;
struct tParameterRange;

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
	const tParameterRange *parameterRanges;
	const uint32_t *parameterHints;
};
