#ifndef __GLOBAL_DATA_H__
#define __GLOBAL_DATA_H__


extern float gSampleRate;
extern float gOversampling;
extern long gAutoPowerOffWatchdog;


#include "Clock.h"
extern CClock gClock;

#include "LCD.h"
extern CLcdBuffer gLCD;

#include "Wave.h"
extern CWave gWavePiano;
extern CWave gWaveFantasy;
extern CWave gWaveViolin;
extern CWave gWaveFlute;
extern CWave gWaveGuitar1;
extern CWave gWaveGuitar2;
extern CWave gWaveEnglishHorn;

#include "FFTReal.h"
extern FFTReal gFFT;

#include "VoiceManager.h"
extern CVoiceManager *gpVoices1;

#include "Rhythm.h"
extern CRhythm gRhythm;

#include "Sequencer.h"
extern CSequencer gSequencer;

#include "Calculator.h"
extern CCalculator gCalculator;

#include "EventManager.h"
extern CEventManager gEventManager;


#endif // __GLOBAL_DATA_H__
