#include "GlobalData.h"


float gSampleRate = kDefaultSampleRate;
float gOversampling = kDefaultOversampling;
long gAutoPowerOffWatchdog = 360000; // in ms (6 minutes)

CClock gClock;
CLcdBuffer gLCD;
CVoiceManager *gpVoices1 = NULL;
CRhythm gRhythm;
CSequencer gSequencer;
CCalculator gCalculator;
CEventManager gEventManager;

// Waves (samples)
CWave gWavePiano(kPiano,kWaveTableSize);
CWave gWaveFantasy(kFantasy,kWaveTableSize);
CWave gWaveViolin(kViolin,kWaveTableSize);
CWave gWaveFlute(kFlute,kWaveTableSize);
CWave gWaveGuitar1(kGuitar1,kWaveTableSize);
CWave gWaveGuitar2(kGuitar2,kWaveTableSize);
CWave gWaveEnglishHorn(kEnglishHorn,kWaveTableSize);

FFTReal gFFT(kDefaultOversampling*kWaveTableSize);

//float gTune = 0.0f;
//int gMode = kVL1Off;
//CVoiceManager gVoices2;
//CKeyboard gKeyboard;
//CSequencer gRecordedSong;
//CSequencer gDemoSong;
