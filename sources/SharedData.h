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

struct CSharedData
{
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
