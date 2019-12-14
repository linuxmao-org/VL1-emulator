#include <stdio.h>
#include <string.h>
#include <math.h>

#include "GlobalData.h"
#include "Utils.h"
#include "EventManager.h"
#include "Sequencer.h"
#include "Rhythm.h"
#include "Clock.h"
#include "VoiceManager.h"
#include "DemoSong.h"


#ifndef __VL1_H__
#include "VL1.h"
#endif

#ifndef __AEffEditor__
#include "AEffEditor.hpp"
#endif


/*
Period time is for lowest G with octave set to low.

Piano (10ms), duty-cycle = 11/16 = 68.75%
   -----------
	|           |     |
               -----

Violin (10ms)
   ----   ---   --   -   -   
	|    | |   | |  | | | | | |
        -     -    -   -   -

Flute (10ms), Fantasy (5ms), duty-cycle = 50%
   -
	| | |
     -

Guitar 1 (20ms)
   -        -
	| |      | |        |
     ------   --------

Guitar 2 (20ms)
   -   ----    --
	| | |    |  |  |      |
     -      --    ------

English horn (20ms), duty-cycle = 1/8 = 12.5%
   -
	| |       |
     -------

Electro 1 is octave modulated piano.
Electro 2 is octave modulated fantasy.
Electro 3 is octave modulated violin.

Piano, flute, fantasy & horn: pwm
Violin, guitar 1 & guitar 2: pulse train
*/


//enum
//{
	//kNumFrequencies = 128,	// 128 midi notes
	//kWaveSize = 4096		// samples (must be power of 2 here)
//};


//const double gMidiScaler = (1. / 127.);
//static double gWave[kWaveSize];


#include <stdio.h>
void DumpToFile(char *pFilePath, float *pData, ULONG dataSize)
{
	FILE *f = fopen(pFilePath,"wt");
	if (f)
	{
		for (int i=0; i<dataSize; i++)
		{
			fprintf(f,"%f,",pData[i]);
		}
		fclose(f);
	}
}


CVL1::CVL1(audioMasterCallback audioMaster) :
	m_bIgnoreNextEvent(FALSE),
	m_bOneKeyPlay(FALSE),
	m_bDemoSong(FALSE),
	AudioEffectX(audioMaster,kNumPrograms,kNumParams)
{
	// init
	if (getDirectory())
	{
		strcpy(m_iniFile,(char*)getDirectory());
	}
	else
	{
		strcpy(m_iniFile,GetCommandLine());
		char *p = strchr(m_iniFile,' ');
		if (p) *p = '\0';
	}
	char *p = strchr(m_iniFile,'.');
	if (p) *p = '\0';
	strcat(m_iniFile,".ini");
	if (m_iniFile[0]=='"') memmove(&m_iniFile[0],&m_iniFile[1],strlen(m_iniFile));

	//Serialize(TRUE);

	m_tuneScaler = 1.0f;

	// Create synthesizer voices.
	// Create dynamic because it references CVL1
	// and has to be destroyed when CVL1 is destroyed.
	gpVoices1 = new CVoiceManager;
	if (gpVoices1 && gpVoices1->Create(1,8,this))
	{
		gEventManager.Register((CEventInput*)gpVoices1,0);
	}

	/*// Create rhythm voices.
	if (gVoices2.Create(3))
	{
		gEventManager.Register((CEventInput*)&gVoices2,1);
	}*/

#define kFftSize  kDefaultOversampling*kWaveTableSize
	float f[kFftSize];
	gFFT.do_fft(f,gWavePiano.Get());
	DumpToFile("FftPiano.csv",f,kFftSize);
	gFFT.do_fft(f,gWaveFantasy.Get());
	DumpToFile("FftFantasy.csv",f,kFftSize);
	gFFT.do_fft(f,gWaveViolin.Get());
	DumpToFile("FftViolin.csv",f,kFftSize);
	gFFT.do_fft(f,gWaveFlute.Get());
	DumpToFile("FftFlute.csv",f,kFftSize);
	gFFT.do_fft(f,gWaveGuitar1.Get());
	DumpToFile("FftGuitar1.csv",f,kFftSize);
	gFFT.do_fft(f,gWaveGuitar2.Get());
	DumpToFile("FftGuitar2.csv",f,kFftSize);
	gFFT.do_fft(f,gWaveEnglishHorn.Get());
	DumpToFile("FftEnglishHorn.csv",f,kFftSize);

	CWave sinc;
	float os = gOversampling;
	gOversampling = kDefaultOversampling;
	sinc.Create(kSinc,1024,0.0625);
	gOversampling = os;

	memset(&m_state,0,sizeof(m_state));
	m_state.version = kVL1StateVersion;

	LoadFactoryPresets();
	LoadAdsrPreset();
	setParameter(kMode,1.0f); // off
	setParameter(kProgram,0.0f); // piano
	setParameter(kOctave,0.51f); // middle
	setParameter(kBalance,0.5f); // 50-50
	setParameter(kVolume,0.8f); // 80%
	setParameter(kTempo,0.725f); // tempo = 4
	setParameter(kTune,0.5f); // 50%
	
	if (audioMaster)
	{
		setNumInputs(0); // no inputs
		setNumOutputs(kNumOutputs);	// one output for synth, one for rhythm
		canProcessReplacing();
		hasVu(false);
		hasClip(false);
		isSynth();
		setUniqueID('cpv1'); // UniqueID, registered with Steinberg
		programsAreChunks(true);
	}

	initProcess();
	suspend();

	TRACE("==== CVL1::Constructor done ===============================\n");
}


CVL1::~CVL1()
{
	if (gpVoices1)
	{
		delete gpVoices1;
		gpVoices1 = NULL;
	}
	//Serialize(FALSE);
}


void CVL1::LoadFactoryPresets()
{
	for (int i=0; i<kNumPrograms; i++)
	{
		m_programs[i].LoadPreset(gVL1PresetNames[i],gVL1Preset[i]);
	}
}


void CVL1::LoadAdsrPreset()
{
	tVL1Preset adsr;
	memset(adsr,0,sizeof(adsr));
	if (gCalculator.GetM())
	{
		CVL1String str = gCalculator.GetMAsString();
		str.StripDot();
		int j = 7;
	
		for (int i=str.Length()-1; i>=0, j>=0; i--)
		{
			char ch = str.GetAt(i);
			if (ch<'0' || ch>'9') break;
			//adsr[j+10] = 0.01f*(float)ch;
			adsr[j--] = 0.1f*(ch-'0');
		}
	}
	m_programs[kProgramAdsr].LoadPreset(gVL1PresetNames[kProgramAdsr],adsr);
}


void CVL1::setProgram(long program)
{
	if (program>=0 && program<kNumPrograms)
	{
		TRACE("setProgram(%d)\n",program);

		curProgram = program;

		if (curProgram==kProgramAdsr)
		{
			LoadAdsrPreset();
		}

		for (int i=0; i<kNumParams; i++)
		{
			// Not all parameters are part of a preset.
			float v = m_programs[curProgram].GetParameter(i);
			if (v>=0.0f) setParameter(i,v);
		}

		if ((long)floorf(5.0f*m_state.program)!=program)
		{
			// Call did not come from setParameter.
			// We have to call it to update UI.
			// Will not cause recursion.
			setParameter(kProgram,0.2f*(float)program);
		}

		// Tell the host that it should update its GUI.
		updateDisplay();
	}
}


void CVL1::setProgramName(char *pName)
{
	strcpy(m_programs[curProgram].GetName(),pName);
}


void CVL1::getProgramName(char *pName)
{
	strcpy(pName,m_programs[curProgram].GetName());
}


bool CVL1::getProgramNameIndexed(long category, long index, char *pText)
{
	if (index<kNumPrograms)
	{
		strcpy(pText,m_programs[index].GetName());
		return true;
	}
	return false;
}


bool CVL1::copyProgram(long destination)
{
	if (destination>=0 && destination<kNumPrograms)
	{
		m_programs[destination] = m_programs[curProgram];
		return true;
	}
	return false;
}


bool CVL1::string2parameter(long index, char* pText)
{
	if (pText)
	{
		float value = (float) atof(pText);
		setParameter(index,value);
	}
	return true;
}


void CVL1::setParameter(long index, float value)
{
	TRACE("setParameter(%d,%f)\n",index,value);

	ResetAutoPowerOffWatchdog();

	// value = [0,1]
	value = Clipf(0.0f,value,1.0f);

	switch (index)
	{
		case kSound: 
			m_sound = value; 
			break;

		case kAttack: 
			m_attack = value; 
			break;

		case kDecay: 
			m_decay = value; 
			break;

		case kSustainLevel: 
			m_sustainLevel = value; 
			break;

		case kSustainTime: 
			m_sustainTime = value; 
			break;

		case kRelease: 
			m_release = value; 
			break;

		case kVibrato: 
			m_vibrato = value; 
			break;

		case kTremolo: 
			m_tremolo = value; 
			break;

		case kVolume: 
			m_state.volume = value; 
			break;

		case kProgram:
			m_state.program = value; 
			setProgram(floorf(5.0f*m_state.program));
			break;

		case kBalance: 
			m_state.balance = value; 
			break;

		case kOctave: 
			m_state.octave = value; 
			break;
		
		case kMode: 
			OnMode(value); 
			break;

		case kTempo:
			m_state.tempo = value;
			gClock.SetTempo((int)floorf(18.0f*m_state.tempo)-9);
			gLCD.SetTempo(gClock.GetTempo());
			break;

		case kTune: 
			m_state.tune = value; 
			break;

		// Next follow parameters that are not part of a program.
		case kKeyReset:
			OnReset();
			return;

		case kKeyDel:
			OnDel();
			return;

		case kKeyTempoUp:
			OnTempoUp();
			return;

		case kKeyTempoDown:
			OnTempoDown();
			return;

		case kKeyRhythm:
			OnRhythm(value);
			return;

		case kKeyMLC:
			OnMlc();
			return;

		case kKeyMusic:
			OnMusic();
			return;

		case kKeyAutoPlay:
			OnAutoPlay();
			return;

		case kKeyOneKeyPlayDotDot:
			OnOneKeyPlayDotDot(value);
			return;

		case kKeyOneKeyPlayDot:
			OnOneKeyPlayDot(value);
			return;

		default:
			return;
	}

	m_programs[curProgram].SetParameter(index,value);
	if (gpVoices1) gpVoices1->SetParameter(index,value);
}


float CVL1::getParameter(long index)
{
	float value = 0.0f;

	switch (index)
	{
		case kSound: value = m_sound; break;
		case kAttack: value = m_attack; break;
		case kDecay: value = m_decay; break;
		case kSustainLevel: value = m_sustainLevel; break;
		case kSustainTime: value = m_sustainTime; break;
		case kRelease: value = m_release; break;
		case kVibrato: value = m_vibrato; break;
		case kTremolo: value = m_tremolo; break;
		case kVolume: value = m_state.volume; break;
		case kProgram: value = m_state.program; break;
		case kBalance: value = m_state.balance; break;
		case kOctave: value = m_state.octave; break;
		case kMode: value = m_state.mode; break;
		case kTempo: value = m_state.tempo; break;
		case kTune: value = m_state.tune; break;
	}
	return value;
}


void CVL1::getParameterName(long index, char *pLabel)
{
	switch (index)
	{
		case kSound:        strcpy(pLabel,"    Sound    "); break;
		case kAttack:       strcpy(pLabel,"   Attack    "); break;
		case kDecay:        strcpy(pLabel,"    Decay    "); break;
		case kSustainLevel: strcpy(pLabel,"Sustain level"); break;
		case kSustainTime:  strcpy(pLabel,"Sustain time "); break;
		case kRelease:      strcpy(pLabel,"   Release   "); break;
		case kVibrato:      strcpy(pLabel,"   Vibrato   "); break;
		case kTremolo:      strcpy(pLabel,"   Tremolo   "); break;
		case kVolume:       strcpy(pLabel,"   Volume    "); break;
		case kProgram:      strcpy(pLabel,"   Program   "); break;
		case kBalance:      strcpy(pLabel,"   Balance   "); break;
		case kOctave:       strcpy(pLabel,"   Octave    "); break;
		case kMode:         strcpy(pLabel,"    Mode     "); break;
		case kTempo:        strcpy(pLabel,"    Tempo    "); break;
		case kTune:         strcpy(pLabel,"    Tune     "); break;
		default: strcpy(pLabel,"");
	}
}


void CVL1::getParameterDisplay(long index, char *pText)
{
	switch (index)
	{
		case kSound: strcpy(pText,gVL1SoundNames[(int)(10.0f*m_sound)]); break;
		case kAttack: long2string(FloatToInt(m_attack,0,9),pText); break;
		case kDecay: long2string(FloatToInt(m_decay,0,9),pText); break;
		case kSustainLevel: long2string(FloatToInt(m_sustainLevel,0,9),pText); break;
		case kSustainTime: long2string(FloatToInt(m_sustainTime,0,9),pText); break;
		case kRelease: long2string(FloatToInt(m_release,0,9),pText); break;
		case kVibrato: long2string(FloatToInt(m_vibrato,0,9),pText); break;
		case kTremolo: long2string(FloatToInt(m_tremolo,0,9),pText); break;
		case kVolume: dB2string(m_state.volume,pText); break;
		case kProgram: strcpy(pText,gVL1PresetNames[FloatToInt(m_state.program,0,5)]); break;
		case kBalance: float2string((m_state.balance-0.5f)*100.0f,pText); break;

		case kOctave:
			if (m_state.octave<0.5f) strcpy(pText,"Low");
			else if (m_state.octave<1.0f) strcpy(pText,"Middle");
			else strcpy(pText,"High");
			break;

		case kMode:
			if (m_state.mode<1.0f/3.0f) strcpy(pText,"Play");
			else if (m_state.mode<2.0f/3.0f) strcpy(pText,"Rec");
			else if (m_state.mode<1.0f) strcpy(pText,"Cal");
			else strcpy(pText,"Off");
			break;

		case kTempo: long2string(FloatToInt(m_state.tempo,0,18)-9,pText); break;
		case kTune: float2string((m_state.tune-0.5f)*100.0f,pText); break;
		default: strcpy(pText,"");
	}
}


void CVL1::getParameterLabel(long index, char *pLabel)
{
	switch (index)
	{
		case kSound: strcpy(pLabel,""); break;
		case kAttack: strcpy(pLabel,""); break;
		case kDecay: strcpy(pLabel,""); break;
		case kSustainLevel: strcpy(pLabel,""); break;
		case kSustainTime: strcpy(pLabel,""); break;
		case kRelease: strcpy(pLabel,""); break;
		case kVibrato: strcpy(pLabel,""); break;
		case kTremolo: strcpy(pLabel,""); break;
		case kVolume: strcpy(pLabel,"dB"); break;
		case kProgram: strcpy(pLabel,""); break;
		case kBalance: strcpy(pLabel,"%"); break;
		case kOctave: strcpy(pLabel,""); break;
		case kMode: strcpy(pLabel,""); break;
		case kTempo: strcpy(pLabel,""); break;
		case kTune: strcpy(pLabel,"%"); break;
		default: strcpy(pLabel,""); break;
	}
}


bool CVL1::getOutputProperties(long index, VstPinProperties *pProperties)
{
	if (index<kNumOutputs)
	{
		sprintf(pProperties->label,"VL-Tone %1d",index+1);
		pProperties->flags = kVstPinIsActive;
		//if (index<2) pProperties->flags |= kVstPinIsStereo;	// make channel 1+2 stereo
		return true;
	}
	return false;
}


VstPlugCategory CVL1::getPlugCategory()
{
	return kPlugCategSynth;
}


long CVL1::canDo(char *pText)
{
	if (!strcmp(pText,"receiveVstEvents")) return 1;
	if (!strcmp(pText,"receiveVstMidiEvent")) return 1;
	if (!strcmp(pText,"midiProgramNames")) return 1;
	return -1;	// explicitly can't do; 0 => don't know
}


long CVL1::getMidiProgramName (long channel, MidiProgramName *pMpn)
{
	if (!pMpn) return 0;

	long prg = pMpn->thisProgramIndex;

	// We have two channels: sounds (channel 0) & rhythm (channel 9).
	// On channel 0 there are six programs, on channel 9 just one.
	switch (channel)
	{
		case 0:
			if (prg<0 || prg>=kNumPrograms) return 0;
			fillProgram(channel,prg,pMpn);
			return kNumPrograms;

		case 9:
			if (prg!=0) return 0;
			fillProgram(channel,prg,pMpn);
			return 1;

		default:
			return 0;
	}

	return 0;
}


long CVL1::getCurrentMidiProgram(long channel, MidiProgramName *pMpn)
{
	long prg = GetInterval(m_state.program,5.0f);
	pMpn->thisProgramIndex = prg;
	if (getMidiProgramName(channel,pMpn))
	{
		return prg;
	}
	return 0;
}


void CVL1::fillProgram(long channel, long prg, MidiProgramName *pMpn)
{
	pMpn->midiBankMsb = -1;
	pMpn->midiBankLsb = -1;
	pMpn->reserved = 0;
	pMpn->flags = 0;
	pMpn->parentCategoryIndex = -1;

	if (channel==0)  // The 6 VL-Tone sounds
	{
		strcpy(pMpn->name,gVL1PresetNames[prg]);
		pMpn->midiProgram = (char)prg;
	}
	else if (channel==9)	// drums ;o)
	{
		strcpy(pMpn->name,"Rhythm");
		pMpn->midiProgram = 0;
	}
}


long CVL1::getMidiProgramCategory(long channel, MidiProgramCategory *pCat)
{
	pCat->parentCategoryIndex = -1;	// -1:no parent category
	return 0;
}


bool CVL1::hasMidiProgramsChanged(long channel)
{
	// User cannot change program names.
	return false;
}


bool CVL1::getMidiKeyName(long channel, MidiKeyName *pKey)
// struct will be filled with information for 'thisProgramIndex' and 'thisKeyNumber'
// if keyName is "" the standard name of the key will be displayed.
// if false is returned, no MidiKeyNames defined for 'thisProgramIndex'.
{
	if (channel==9 && pKey->thisProgramIndex==0)
	{
		switch (pKey->thisKeyNumber)	// 0 - 127. fill struct for this key number.
		{
			case 60:
				strcpy(pKey->keyName,"Low bleep");
				return true;

			case 62:
				strcpy(pKey->keyName,"High bleep");
				return true;

			case 64:
				strcpy(pKey->keyName,"Noise");
				return true;

			default:
				pKey->keyName[0] = 0;
				return true;
		}
	}

	return false;
}


void CVL1::setSampleRate(float sampleRate)
{
	gSampleRate = sampleRate;
	gOversampling = kDefaultOversampling;
	AudioEffectX::setSampleRate(sampleRate);
	m_lp1.SetCutoff(800.0f,sampleRate);
	m_lp2.SetCutoff(65.0f,sampleRate);
}


void CVL1::setBlockSize(long blockSize)
{
	AudioEffectX::setBlockSize(blockSize);
	// you may need to have to do something here...
}


void CVL1::resume()
{
	wantEvents();
}


void CVL1::initProcess()
{
}


void CVL1::process(float** ppInputs, float** ppOutputs, long sampleFrames)
{
	processReplacing(ppInputs,ppOutputs,sampleFrames);
}


void CVL1::processReplacing(float** ppInputs, float** ppOutputs, long sampleFrames)
{
	if (!gpVoices1) return;

	float* pOut1 = ppOutputs[0];
	float* pOut2 = ppOutputs[1];

	int mode = GetModeI();
	if ((mode==kVL1Off) || (mode==kVL1Cal))
	{
		memset(pOut1,0,sizeof(float)*sampleFrames);
		memset(pOut2,0,sizeof(float)*sampleFrames);
		return;
	}

	long time = 0;

	while (time<sampleFrames)
	{
		if (!gClock.Tick())
		{
			// Auto power-off.
			//setParameter(kMode,1.0f);
			//return;
		}
			
		float out1 = 0.0f;
		float out2 = 0.0f;

		float balance = 0.5f*(m_state.balance - 0.5f);
		out1 = (0.5f+balance)*gpVoices1->Clock(); 
		// Simulate the VL1's melody frequency response.
		out1 = m_lp1.Clock(out1);
		out1 -= m_lp2.Clock(out1);
		// Rhythm is a bit less loud than the melody (measured ratio of 63 to 55 mVtt).
		out2 = gRhythm.Clock();
		out1 += (0.5f-balance)*out2;

		(*pOut1++) = m_state.volume*out1;
		(*pOut2++) = m_state.volume*out1; //out2; temporarily shut off out2

		time++;
	}
}


long CVL1::processEvents(VstEvents *pEv)
{
	for (long i=0; i<pEv->numEvents; i++)
	{
		if ((pEv->events[i])->type==kVstMidiType)
		{
			tEvent event;
			event.midiEvent = *(VstMidiEvent*)pEv->events[i];
			//event.program = -1;
			if (GetModeI()!=kVL1Off)
			{
				ResetAutoPowerOffWatchdog();
				gEventManager.AddEvent(event);
			}
		}
	}
	return 1;	// want more
}


void CVL1::Reset()
{
	m_bDemoSong = FALSE;
	m_bOneKeyPlay = FALSE;
	m_bIgnoreNextEvent = FALSE;
	if (gpVoices1) gpVoices1->Reset();
	gSequencer.Reset();
	gRhythm.Reset();
	gClock.Reset();
	gCalculator.Clear(TRUE,FALSE);
	gLCD.SetMode(m_state.mode);
	LoadAdsrPreset();
	setProgram(curProgram);
}


void CVL1::OnMode(float value)
{
	m_state.mode = value;

	Reset();

	switch ((int)floorf(3.0f*m_state.mode))
	{
		case 0: 
			m_modeI = kVL1Play;
			resume();
			break;

		case 1: 
			m_modeI = kVL1Rec;
			resume();
			break;

		case 2: 
			m_modeI = kVL1Cal;
			suspend();
			break;

		case 3: 
			m_modeI = kVL1Off;
			suspend();
			break;
	}
}


void CVL1::OnReset()
{
	if (m_modeI==kVL1Play || m_modeI==kVL1Rec)
	{
		Reset();
		if (m_modeI==kVL1Rec && gSequencer.IsDirty())
		{
			gSequencer.SetRecording(FALSE);
		}
	}
	else if (m_modeI==kVL1Cal)
	{
		Calculator(kKeyReset);
	}
}

			
void CVL1::OnDel()
{
	if (m_modeI==kVL1Rec)
	{
		if ((!gSequencer.IsPlaying() || gSequencer.IsPaused()) && !gSequencer.IsEmpty())
		{
			if (gSequencer.IsRecording())
			{
				// TODO: handle delete while recording.
				// The next note after a delete should get the deleted note's start time.
			}
			// TODO: LongHighBeep();
			// One note is two events.
			gSequencer.RemoveEvents(2);
			// Scroll the LCD one note to the right.
			int note = 0;
			int i = gSequencer.GetSongPointer();
			if (i==0)
			{
				// Show tempo if all notes before the song pointer were deleted.
				gLCD.SetTempo(gClock.GetTempo());
			}
			else if (i>0)
			{
				// The song pointer points to the next event.
				// Skip two notes (a note is two events).
				tSequencerEvent event = gSequencer.GetEvent(i-5);
				note = event.midi[1]&0x7f;
				gLCD.ScrollRight(note);
			}
		}
	}
	else if (m_modeI==kVL1Cal)
	{
		Calculator(kKeyDel);
	}
}


void CVL1::OnTempoUp()
{
	if (m_modeI==kVL1Play || m_modeI==kVL1Rec)
	{
		TempoUpDown(TRUE);
	}
	else if (m_modeI==kVL1Cal)
	{
		Calculator(kKeyTempoUp);
	}
}


void CVL1::OnTempoDown()
{
	if (m_modeI==kVL1Play || m_modeI==kVL1Rec)
	{
		TempoUpDown(FALSE);
	}
	else if (m_modeI==kVL1Cal)
	{
		Calculator(kKeyTempoDown);
	}
}


void CVL1::OnRhythm(float value)
{
	if (m_modeI==kVL1Play || m_modeI==kVL1Rec)
	{
		int rhythm = kBeguine;

		if (value<0.1) rhythm = kMarch;
		else if (value<0.2) rhythm = kWaltz;
		else if (value<0.3) rhythm = k4Beat;
		else if (value<0.4) rhythm = kSwing;
		else if (value<0.5) rhythm = kRock1;
		else if (value<0.6) rhythm = kRock2;
		else if (value<0.7) rhythm = kBossanova;
		else if (value<0.8) rhythm = kSamba;
		else if (value<0.9) rhythm = kRhumba;

		gRhythm.SelectRhythm(rhythm);
		gRhythm.Play();
	}
}


void CVL1::OnMlc()
{
	if (m_modeI==kVL1Rec)
	{
		if (!m_bDemoSong)
		{
			Reset();
			gSequencer.Clear();
			setParameter(kTempo,0.5f); // tempo = 0
		}
	}
	else if (m_modeI==kVL1Cal)
	{
		Calculator(kKeyMLC);
	}
}


void CVL1::OnMusic()
{
	if (m_modeI==kVL1Play || m_modeI==kVL1Rec)
	{
		Reset();
		setParameter(kTempo,0.725f); // tempo = 4
		gSequencer.LoadSong((tSequencerEvent*)gDemoSongData);
		m_bDemoSong = TRUE;
		gSequencer.Play();
	}
	else if (m_modeI==kVL1Cal)
	{
		Calculator(kKeyMusic);
	}
}


void CVL1::OnAutoPlay()
{
	if (m_modeI==kVL1Play || m_modeI==kVL1Rec)
	{
		AutoPlay();
	}
	else if (m_modeI==kVL1Cal)
	{
		Calculator(kKeyAutoPlay);
	}
}


void CVL1::OnOneKeyPlayDotDot(float value)
{
	if (m_modeI==kVL1Play || m_modeI==kVL1Rec) 
	{
		OneKeyPlay();
	}
	else if (m_modeI==kVL1Cal && value>0.0f) 
	{
		Calculator(kKeyOneKeyPlayDotDot);
	}
}


void CVL1::OnOneKeyPlayDot(float value)
{
	if (m_modeI==kVL1Play || m_modeI==kVL1Rec)
	{
		OneKeyPlay();
	}
}


void CVL1::TempoUpDown(BOOL bUp)
{
	float fTempo = (gClock.GetTempo()+9)/18.0f;
	float delta = bUp? 1.0f/18.0f : -1.0f/18.0f;
	delta += 0.001f; // make sure to be in an interval.
	fTempo += delta;
	setParameter(kTempo,Clipf(0.0f,fTempo,1.0f));
}


void CVL1::Calculator(int key)
{
	CVL1String result = gCalculator.Input(key);
	gLCD.ShowString(result,gCalculator.GetOperator(),gCalculator.GetError(),gCalculator.GetM(),gCalculator.GetK());
}


void CVL1::AutoPlay()
{
	if (gpVoices1) gpVoices1->Reset();

	if (gSequencer.IsDirty() && gSequencer.IsRecording())
	{
		// Pressed auto-play while recording.
		gSequencer.SetRecording(FALSE);
	}

	if (gSequencer.IsPlaying() && m_bDemoSong)
	{
		Reset(); // Stop immediately.
		gSequencer.LoadSong();
		//setParameter(kProgram,m_program);
	}

	if (!gSequencer.IsPlaying())
	{
		// Not playing -> start song.
		gLCD.Clear();
		gSequencer.Rewind();
		gSequencer.Play();
	}
	else if (!gSequencer.IsPaused())
	{
		// Playing and not paused -> pause.
		gSequencer.Pause(TRUE);
		//gSequencer.GotoEvent(kNoteOn);
	}
	else
	{
		// Playing but paused -> continue playing.
		gSequencer.GotoEvent(kNoteOn);
		if (m_bOneKeyPlay)
		{
			m_bOneKeyPlay = FALSE;
		}
		gSequencer.Pause(FALSE);
	}
}


void CVL1::OneKeyPlay()
{
	if (gSequencer.IsPlaying() && m_bDemoSong) return;

	if (m_bIgnoreNextEvent)
	{
		// Ignore key up at end of song.
		m_bIgnoreNextEvent = FALSE;
		return;
	}

	if (gSequencer.IsRecording())
	{
		// Pressing an OKP key while recording will stop the
		// rhythm, the sound and display the tempo, much like a reset.
		m_bIgnoreNextEvent = TRUE;
		ResetSound();
		if (gSequencer.IsDirty())
		{
			gSequencer.SetRecording(FALSE);
		}
		return;
	}

	if (!gSequencer.IsPlaying())
	{
		// One key play keys only do something when the sequencer 
		// is not playing or paused.
		m_bDemoSong = FALSE;
		gSequencer.LoadSong();
		gSequencer.SetPause(TRUE);
		gSequencer.Play();
	}

	if (gSequencer.IsPaused())
	{
		// If the sequencer is paused pressing an OKP key will advance 
		// the song one position.
		if (!gSequencer.Step(m_modeI==kVL1Rec))
		{
			// End of song. 
			// When there are no more events pressing an OKP key will stop
			// the rhythm, the sound and display the tempo, much like a reset.
			m_bIgnoreNextEvent = TRUE;
			ResetSound();
		}
		else m_bOneKeyPlay = TRUE;
	}
}


void CVL1::ResetSound()
{
	if (gpVoices1) gpVoices1->Reset();
	gRhythm.Stop();
	gLCD.SetTempo(gClock.GetTempo());
}


void CVL1::HandleKey(int key, float value)
{
	ResetAutoPowerOffWatchdog();

	if (gSequencer.IsPlaying() && ((!gSequencer.IsPaused()) || m_bDemoSong)) return;

	if (m_modeI==kVL1Play || m_modeI==kVL1Rec)
	{
		if (key>=kKeyPlusMin && key<=kKeyEqual)
		{
			// Black and white keys only.
			float velocity = 127.0f*value;
			int noteOnOff = velocity>0.0f? kNoteOn : kNoteOff;
			//int note = key - kKeyPlusMin + 55; // 55 = G below middle C.
			SendKey(noteOnOff,key,(int)velocity);
		}
	}
	else if (m_modeI==kVL1Cal)
	{
		// Key down only.
		if (value) Calculator(key);
	}
}


void CVL1::SendKey(int noteOnOff, int note, int velocity)
{
	if (m_modeI==kVL1Rec)
	{
		if (gSequencer.IsDirty())
		{
			if (noteOnOff==kNoteOn)
			{
				// TODO: LongHighBeep();
			}
		}
		// Store key when in REC mode.
		tSequencerEvent seqEvent;
		memset(&seqEvent,0,sizeof(seqEvent));
		seqEvent.midi[0] = (unsigned char)noteOnOff;
		seqEvent.midi[1] = (unsigned char)note;
		seqEvent.midi[2] = (unsigned char)velocity;
		gSequencer.AddEvent(seqEvent);
	}

	tEvent event;
	memset(&event,0,sizeof(event));
	event.midiEvent.type = kVstMidiType;
	event.midiEvent.byteSize = 24;
	event.midiEvent.midiData[0] = (char)noteOnOff;
	event.midiEvent.midiData[1] = (char)note;
	event.midiEvent.midiData[2] = (char)velocity;
	gEventManager.AddEvent(event);
}


BOOL CVL1::Serialize(BOOL bRead)
{
	FILE *f = NULL;

	if (bRead)
	{
		f = fopen(m_iniFile,"r");
		if (f)
		{
			CVL1String str;

			for (int i=0; i<10; i++)
			{
				//float n;
				//fscanf(f,"%f\n",&n);
				double d;
				fscanf(f,"%lf\n",&d);
				d *= 100.0f;
				char ch = (char)d;
				str.Add(ch);
			}

			//float n;
			//fscanf(f,"%f\n",&n);
			//str.SetFromDouble(n);
			gCalculator.SetM(str);
		}
	}
	else
	{
		f = fopen(m_iniFile,"w+");
		if (f)
		{
			CVL1String str;
			str = gCalculator.GetMAsString();
			//fprintf(f,"%f\n",str.GetAsDouble());
			float d[10];

			for (int i=0; i<10; i++)
			{
				d[i] = 0.01f*(' ');
			}

			int j = str.Length() - 1;
			for (i=9; i>=0, j>=0; i--, j--)
			{
				char ch = str.GetAt(j);
				d[i] = 0.01f*ch;
			}
			for (i=0; i<10; i++)
			{
				fprintf(f,"%.2f\n",d[i]);
			}
		}
	}

	if (f)
	{
		fclose(f);
		return TRUE;
	}
	
	return FALSE;
}


void CVL1::ResetAutoPowerOffWatchdog(long timeout)
{
	gAutoPowerOffWatchdog = timeout*gSampleRate; // in samples.
}


long CVL1::getChunk(void **ppData, bool isPreset)
{
	// The host will call this to get plug data.
	// call programsAreChunks() in constructor!

	TRACE("CVL1::getChunk: isPreset=%d, curProgram=%d\n",isPreset,curProgram);

	if (isPreset)
	{
		*ppData = m_programs[curProgram].GetData();
		return m_programs[curProgram].GetDataSize();
	}
	long size;
	*ppData = GetState(size);
	return size;
}


long CVL1::setChunk(void *pData, long byteSize, bool isPreset)
{
	// The host will call this to set plug data.

	TRACE("CVL1::setChunk: %d bytes, isPreset=%d, curProgram=%d\n",byteSize,isPreset,curProgram);

	if (isPreset)
	{
		if (byteSize!=sizeof(tVL1ProgramData)) return 0;
		if (((tVL1ProgramData*)pData)->version>kVL1ProgramVersion) return 0;
		memcpy(m_programs[curProgram].GetData(),pData,byteSize);
		setProgram(curProgram); // new parameters will now kick in
	}

	if (byteSize!=sizeof(tVL1State)) return 0;
	if (((tVL1State*)pData)->version>kVL1StateVersion) return 0;
	SetState((tVL1State*)pData); // new parameters will now kick in

	return 1;
}


tVL1State *CVL1::GetState(long& size)
{
	m_state.curProgram = getProgram();
	gLCD.GetState(m_state.lcd);
	gCalculator.GetState(m_state.calculator);
	gSequencer.GetState(m_state.sequencer);
	gClock.GetState(m_state.clock);
	size = sizeof(m_state); 
	return &m_state;
}


void CVL1::SetState(tVL1State *pState)
{
	m_state = *pState;
	gCalculator.SetState(m_state.calculator);
	gSequencer.SetState(m_state.sequencer);
	setParameter(kMode,m_state.mode);
	setParameter(kProgram,m_state.program);
	setParameter(kOctave,m_state.octave);
	setParameter(kBalance,m_state.balance);
	setParameter(kVolume,m_state.volume);
	setParameter(kTempo,m_state.tempo);
	setParameter(kTune,m_state.tune);
	setProgram(m_state.curProgram);
	gClock.SetState(m_state.clock);
	gLCD.SetState(m_state.lcd);
	gLCD.Show();
	editor->postUpdate();
}
