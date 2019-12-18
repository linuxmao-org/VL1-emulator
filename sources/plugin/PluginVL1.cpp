#include "PluginVL1.h"
#include "Calculator.h"
#include "LcdBuffer.h"
#include "Sequencer.h"
#include "Rhythm.h"
#include "EventManager.h"
#include "VoiceManager.h"
#include "Clock.h"
#include "DemoSong.h"
#include "MidiDefs.h"
#include "VL1Program.h"
#include <chrono>
#include <thread>
#include <string.h>
#include <math.h>
#include <assert.h>
namespace cro = std::chrono;

// -----------------------------------------------------------------------

PluginVL1::PluginVL1()
	: Plugin(kNumParams, kNumPrograms, 0), // paramCount param(s), presetCount program(s), 0 states
	  m_calculator(new CCalculator),
	  m_lcdBuffer(new CLcdBuffer),
	  m_lcdScreenData(new tLcdScreenData),
	  m_waves(new CWaveSet),
	  m_sequencer(new CSequencer),
	  m_rhythm(new CRhythm),
	  m_eventManager(new CEventManager),
	  m_voices1(new CVoiceManager),
	  m_clock(new CClock),
	  m_parameterRanges(new tParameterRange[kNumParams]),
	  m_parameterHints(new uint32_t[kNumParams])
{
	for (uint32_t p=0; p<kNumParams; ++p)
	{
		Parameter parameter;
		SharedVL1::InitParameter(p, parameter);
		tParameterRange &range = m_parameterRanges[p];
		range.def = parameter.ranges.def;
		range.min = parameter.ranges.min;
		range.max = parameter.ranges.max;
		m_parameterHints[p] = parameter.hints;
	}

	m_sharedData.sampleRate = kDefaultSampleRate;
	m_sharedData.oversampling = kDefaultOversampling;
	m_sharedData.clock = m_clock.get();
	m_sharedData.LCD = m_lcdBuffer.get();
	m_sharedData.waves = m_waves.get();
	m_sharedData.pVoices1 = m_voices1.get();
	m_sharedData.rhythm = m_rhythm.get();
	m_sharedData.sequencer = m_sequencer.get();
	m_sharedData.calculator = m_calculator.get();
	m_sharedData.eventManager = m_eventManager.get();
	m_sharedData.screenData = m_lcdScreenData.get();
	m_sharedData.parameterRanges = m_parameterRanges.get();
	m_sharedData.parameterHints = m_parameterHints.get();

	memset(m_lcdScreenData.get(), 0, sizeof(tLcdScreenData));

	sampleRateChanged(getSampleRate());

	m_eventManager->Register(m_voices1.get());

	for (uint32_t p=0; p<kNumParams; ++p)
	{
		setParameterValue(p, m_parameterRanges[p].def);
	}
}

PluginVL1::~PluginVL1()
{
}

// -----------------------------------------------------------------------
// Init

void PluginVL1::initAudioPort(bool input, uint32_t index, AudioPort& port)
{
	SharedVL1::InitAudioPort(input, index, port);
}

void PluginVL1::initParameter(uint32_t index, Parameter &parameter)
{
	SharedVL1::InitParameter(index, parameter);
}

/**
  Set the name of the program @a index.
  This function will be called once, shortly after the plugin is created.
*/
void PluginVL1::initProgramName(uint32_t index, String &programName)
{
	DISTRHO_SAFE_ASSERT_RETURN(index < kNumPrograms, );

	const CVL1Program &program = SharedVL1::GetFactoryPresets()[index];

	programName = program.GetName();
}

// -----------------------------------------------------------------------
// Internal data

/**
  Optional callback to inform the plugin about a sample rate change.
*/
void PluginVL1::sampleRateChanged(double newSampleRate)
{
	m_sharedData.sampleRate = newSampleRate;

	m_lcdBuffer->Setup(&m_sharedData);
	m_waves->Setup(&m_sharedData);
	m_sequencer->Setup(&m_sharedData);
	m_rhythm->Setup(&m_sharedData);
	m_voices1->Create(1, 8, &m_sharedData);
	m_clock->Setup(&m_sharedData);
	m_lp1.SetCutoff(800.0f,newSampleRate);
	m_lp2.SetCutoff(65.0f,newSampleRate);
}

/**
  Get the current value of a parameter.
*/
float PluginVL1::getParameterValue(uint32_t index) const
{
	float value = 0;

	switch (index)
	{
		case kMode:
			value = m_modeI/3.0f;
			break;
		case kVolume:
			value = m_volume;
			break;
		case kBalance:
			value = m_balance;
			break;
		case kOctave:
			value = m_octave;
			break;
		case kTune:
			value = m_tune;
			break;
		case kSound:
			value = m_adsr[0];
			break;
		case kAttack:
			value = m_adsr[1];
			break;
		case kDecay:
			value = m_adsr[2];
			break;
		case kSustainLevel:
			value = m_adsr[3];
			break;
		case kSustainTime:
			value = m_adsr[4];
			break;
		case kRelease:
			value = m_adsr[5];
			break;
		case kVibrato:
			value = m_adsr[6];
			break;
		case kTremolo:
			value = m_adsr[7];
			break;
		case kTempo:
			value = m_tempo;
			break;
		default:
			DISTRHO_SAFE_ASSERT_RETURN(false, 0);
	}

	value = SharedVL1::ParameterValueFrom01(index, value);

	return value;
}

/**
  Change a parameter value.
*/
void PluginVL1::setParameterValue(uint32_t index, float value)
{
	value = SharedVL1::ParameterValueTo01(index, value);

	switch (index)
	{
		case kMode:
			OnMode((int)lroundf(3.0f*value));
			break;
		case kVolume:
			m_volume = value;
			break;
		case kBalance:
			m_balance = value;
			break;
		case kOctave:
			m_octave = value;
			break;
		case kTune:
			m_tune = value;
			break;
		case kSound:
			m_adsr[0] = value;
			break;
		case kAttack:
			m_adsr[1] = value;
			break;
		case kDecay:
			m_adsr[2] = value;
			break;
		case kSustainLevel:
			m_adsr[3] = value;
			break;
		case kSustainTime:
			m_adsr[4] = value;
			break;
		case kRelease:
			m_adsr[5] = value;
			break;
		case kVibrato:
			m_adsr[6] = value;
			break;
		case kTremolo:
			m_adsr[7] = value;
			break;
		case kTempo:
			m_tempo = value;
			m_clock->SetTempo((int)lroundf(18.0f*m_tempo)-9);
			m_lcdBuffer->SetTempo(m_clock->GetTempo());
			break;
		default:
			DISTRHO_SAFE_ASSERT(false);
			break;
	}

	m_voices1->SetParameter(index, value);
}

/**
  Load a program.
  The host may call this function from any context,
  including realtime processing.
*/
void PluginVL1::loadProgram(uint32_t index)
{
	DISTRHO_SAFE_ASSERT_RETURN(index < kNumPrograms, );

	const CVL1Program &program = SharedVL1::GetFactoryPresets()[index];

	for (uint32_t param = 0; param < kNumParams; ++param)
	{
		float value = program.GetParameter(param, HUGE_VALF);
		if (value == HUGE_VALF)
			value = m_parameterRanges[param].def;
		else
			value = SharedVL1::ParameterValueFrom01(param, value);
		setParameterValue(param, value);
	}
}

// -----------------------------------------------------------------------
// Process

void PluginVL1::activate()
{
	Reset();
	fIsActive = true;
}

void PluginVL1::deactivate()
{
	fIsActive = false;
}

void PluginVL1::run(const float **inputs, float **outputs, uint32_t frames, const MidiEvent *midiEvents,
                    uint32_t midiEventCount)
{
	(void)inputs;

	std::unique_lock<std::mutex> runLock(fRunMutex, std::defer_lock);

	float* pOut1 = outputs[0];
	float* pOut2 = outputs[1];

	uint32_t midiIndex = 0;
	uint32_t midiInterval = 64;

	int mode = GetModeI();

	if (const tSynchronousCallback *sc = fSynchronousCallback.exchange(nullptr))
	{
		(*sc)();
		fSynchronousCompletion.store(true);
	}

	if ((mode==kVL1Off) || (mode==kVL1Cal) || !runLock.try_lock())
	{
		memset(pOut1,0,sizeof(float)*frames);
		memset(pOut2,0,sizeof(float)*frames);
		return;
	}

	auto sendMidi = [this](const MidiEvent &midiEvent)
	{
		if (midiEvent.size <= 4)
		{
			tEvent event;
			memcpy(event.midiEvent.midiData, midiEvent.data, 4);
			m_eventManager->SendEvent(event);
		}
	};

	uint32_t time = 0;

	while (time<frames)
	{
		if (!m_clock->Tick())
		{
			// Auto power-off.
			//setParameter(kMode,1.0f);
			//return;
		}

		if (time%midiInterval==0)
		{
			while (midiIndex<midiEventCount && time<=midiEvents[midiIndex].frame)
				sendMidi(midiEvents[midiIndex++]);
		}

		float out1 = 0.0f;
		float out2 = 0.0f;

		float balance = 0.5f*(m_balance - 0.5f);
		out1 = (0.5f+balance)*m_voices1->Clock();
		// Simulate the VL1's melody frequency response.
		out1 = m_lp1.Clock(out1);
		out1 -= m_lp2.Clock(out1);
		// Rhythm is a bit less loud than the melody (measured ratio of 63 to 55 mVtt).
		out2 = m_rhythm->Clock();
		out1 += (0.5f-balance)*out2;

		(*pOut1++) = m_volume*out1;
		(*pOut2++) = m_volume*out1; //out2; temporarily shut off out2

		time++;
	}

	while (midiIndex < midiEventCount)
		sendMidi(midiEvents[midiIndex++]);
}

// -----------------------------------------------------------------------


void PluginVL1::HandleKey(int key, float value)
{
	//ResetAutoPowerOffWatchdog();

	if (m_sequencer->IsPlaying() && ((!m_sequencer->IsPaused()) || m_bDemoSong)) return;

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


void PluginVL1::SendKey(int noteOnOff, int note, int velocity)
{
	if (m_modeI==kVL1Rec)
	{
		if (m_sequencer->IsDirty())
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
		m_sequencer->AddEvent(seqEvent);
	}

	tEvent event;
	memset(&event,0,sizeof(event));
	event.midiEvent.midiData[0] = (char)noteOnOff;
	event.midiEvent.midiData[1] = (char)note;
	event.midiEvent.midiData[2] = (char)velocity;
	m_eventManager->SendEvent(event);
}


void PluginVL1::Reset()
{
	m_bDemoSong = false;
	m_bOneKeyPlay = false;
	m_bIgnoreNextEvent = false;
	m_voices1->Reset();
	m_sequencer->Reset();
	m_rhythm->Reset();
	m_clock->Reset();
	m_calculator->Clear(true,false);
	m_lcdBuffer->SetMode(m_modeI);

	// jpc: cannot do this in LV2
	//LoadAdsrPreset();
	//setProgram(curProgram);
}


void PluginVL1::OnMode(int mode)
{
	switch (mode)
	{
		default:
		case 0:
			m_modeI = kVL1Play;
			break;

		case 1:
			m_modeI = kVL1Rec;
			break;

		case 2:
			m_modeI = kVL1Cal;
			break;

		case 3:
			m_modeI = kVL1Off;
			break;
	}

	Reset();
}


void PluginVL1::OnReset()
{
	if (m_modeI==kVL1Play || m_modeI==kVL1Rec)
	{
		Reset();
		if (m_modeI==kVL1Rec && m_sequencer->IsDirty())
		{
			m_sequencer->SetRecording(false);
		}
	}
	else if (m_modeI==kVL1Cal)
	{
		Calculator(kKeyReset);
	}
}


void PluginVL1::OnDel()
{
	if (m_modeI==kVL1Rec)
	{
		if ((!m_sequencer->IsPlaying() || m_sequencer->IsPaused()) && !m_sequencer->IsEmpty())
		{
			if (m_sequencer->IsRecording())
			{
				// TODO: handle delete while recording.
				// The next note after a delete should get the deleted note's start time.
			}
			// TODO: LongHighBeep();
			// One note is two events.
			m_sequencer->RemoveEvents(2);
			// Scroll the LCD one note to the right.
			int note = 0;
			int i = m_sequencer->GetSongPointer();
			if (i==0)
			{
				// Show tempo if all notes before the song pointer were deleted.
				m_lcdBuffer->SetTempo(m_clock->GetTempo());
			}
			else if (i>0)
			{
				// The song pointer points to the next event.
				// Skip two notes (a note is two events).
				tSequencerEvent event = m_sequencer->GetEvent(i-5);
				note = event.midi[1]&0x7f;
				m_lcdBuffer->ScrollRight(note);
			}
		}
	}
	else if (m_modeI==kVL1Cal)
	{
		Calculator(kKeyDel);
	}
}


void PluginVL1::OnRhythm(float value)
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

		m_rhythm->SelectRhythm(rhythm);
		m_rhythm->Play();
	}
}


void PluginVL1::OnMusic()
{
	if (m_modeI==kVL1Play || m_modeI==kVL1Rec)
	{
		Reset();

		// jpc: tempo set in editor after pushing the button
		//setParameter(kTempo,0.725f); // tempo = 4

		m_sequencer->LoadSong((tSequencerEvent*)gDemoSongData);
		m_bDemoSong = true;
		m_sequencer->Play();
	}
	else if (m_modeI==kVL1Cal)
	{
		Calculator(kKeyMusic);
	}
}

void PluginVL1::OnAutoPlay()
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


void PluginVL1::OnOneKeyPlayDotDot(float value)
{
	if (m_modeI==kVL1Play || m_modeI==kVL1Rec)
	{
		OneKeyPlay();
	}
	else if (m_modeI==kVL1Cal && value>0.0f)
	{
		Calculator(kKeyOneKeyPlayDotDot);
		if (m_editingAdsr)
		{
			MemorizeAdsrPresetFromCalculator();
		}
	}
}


void PluginVL1::OnOneKeyPlayDot(float value)
{
	(void)value;

	if (m_modeI==kVL1Play || m_modeI==kVL1Rec)
	{
		OneKeyPlay();
	}
}


void PluginVL1::Calculator(int key)
{
	CVL1String result = m_calculator->Input(key);
	m_lcdBuffer->ShowString(result,m_calculator->GetOperator(),m_calculator->GetError(),m_calculator->GetM(),m_calculator->GetK());
}


void PluginVL1::AutoPlay()
{
	m_voices1->Reset();

	if (m_sequencer->IsDirty() && m_sequencer->IsRecording())
	{
		// Pressed auto-play while recording.
		m_sequencer->SetRecording(false);
	}

	if (m_sequencer->IsPlaying() && m_bDemoSong)
	{
		Reset(); // Stop immediately.
		m_sequencer->LoadSong();
		//setParameter(kProgram,m_program);
	}

	if (!m_sequencer->IsPlaying())
	{
		// Not playing -> start song.
		m_lcdBuffer->Clear();
		m_sequencer->Rewind();
		m_sequencer->Play();
	}
	else if (!m_sequencer->IsPaused())
	{
		// Playing and not paused -> pause.
		m_sequencer->Pause(true);
		//m_sequencer->GotoEvent(kNoteOn);
	}
	else
	{
		// Playing but paused -> continue playing.
		m_sequencer->GotoEvent(kNoteOn);
		if (m_bOneKeyPlay)
		{
			m_bOneKeyPlay = false;
		}
		m_sequencer->Pause(false);
	}
}


void PluginVL1::OneKeyPlay()
{
	if (m_sequencer->IsPlaying() && m_bDemoSong) return;

	if (m_bIgnoreNextEvent)
	{
		// Ignore key up at end of song.
		m_bIgnoreNextEvent = false;
		return;
	}

	if (m_sequencer->IsRecording())
	{
		// Pressing an OKP key while recording will stop the
		// rhythm, the sound and display the tempo, much like a reset.
		m_bIgnoreNextEvent = true;
		ResetSound();
		if (m_sequencer->IsDirty())
		{
			m_sequencer->SetRecording(false);
		}
		return;
	}

	if (!m_sequencer->IsPlaying())
	{
		// One key play keys only do something when the sequencer
		// is not playing or paused.
		m_bDemoSong = false;
		m_sequencer->LoadSong();
		m_sequencer->SetPause(true);
		m_sequencer->Play();
	}

	if (m_sequencer->IsPaused())
	{
		// If the sequencer is paused pressing an OKP key will advance
		// the song one position.
		if (!m_sequencer->Step(m_modeI==kVL1Rec))
		{
			// End of song.
			// When there are no more events pressing an OKP key will stop
			// the rhythm, the sound and display the tempo, much like a reset.
			m_bIgnoreNextEvent = true;
			ResetSound();
		}
		else m_bOneKeyPlay = true;
	}
}


void PluginVL1::ResetSound()
{
	m_voices1->Reset();
	m_rhythm->Stop();
	m_lcdBuffer->SetTempo(m_clock->GetTempo());
}


void PluginVL1::MemorizeAdsrPresetFromCalculator()
{
	memcpy(m_adsr, gVL1Preset[kProgramAdsr], sizeof(tVL1Preset));

	if (m_calculator->GetM())
	{
		CVL1String str = m_calculator->GetMAsString();
		str.StripDot();
		int j = 7;
		for (int i=str.Length()-1; i>=0 && j>=0; i--, j--)
		{
			char ch = str.GetAt(i);
			if (ch<'0' || ch>'9') break;
			//adsr[j+10] = 0.01f*(float)ch;
			m_adsr[j] = 0.1f*(ch-'0');
		}
	}
}


float PluginVL1::GetTempoUpDown(bool bUp) const
{
	float fTempo = (m_clock->GetTempo()+9)/18.0f;
	float delta = bUp? 1.0f/18.0f : -1.0f/18.0f;
	delta += 0.001f; // make sure to be in an interval.
	fTempo += delta;
	return Clipf(0.0f,fTempo,1.0f);
}


/*
  jpc: HACK

  The purpose of this editor-side function is to "run this code in the DSP".
  If DSP is not running, Editor will take a lock and run it itself.

  It needs the instance-access for this.

  It's so I don't have to modify program flow too deeply while I port it,
  introducing potential problems...

  // note:
  //   Original does a weird thing where control buttons are received by DSP as
  //   VST parameters coming from the editor. As VST is concerned, this works
  //   apparently, but it needs a replacement solution in the port.

  // typical stuff:
  // - set a parameter (DSP side, must go to Editor)
  // - write a string on LCD (DSP side)
  // - perform sequencer action (DSP side)
  // - ...
*/
void PluginVL1::PerformEditSynchronous(const tSynchronousCallback &fn)
{
	bool performed = false;

	if (fIsActive)
	{
		fSynchronousCompletion.store(false);
		fSynchronousCallback.store(&fn);

		cro::steady_clock::time_point tStart = cro::steady_clock::now();
		enum { timeoutMs = 100 };

		// repeatedly check for the DSP to pick up the callback until timeout
		while (!(performed = (fSynchronousCallback.load() == nullptr)))
		{
			auto elapsed = cro::steady_clock::now() - tStart;
			if (cro::duration_cast<cro::milliseconds>(elapsed).count() >= timeoutMs)
				break;
			std::this_thread::sleep_for(cro::milliseconds(5));
		}
		// if it didn't pick up, cancel, but make sure to do a final check with
		// compare-and-swap to avoid a possibility of race condition
		if (!performed)
		{
			const tSynchronousCallback *expected = &fn;
			performed = !fSynchronousCallback.compare_exchange_weak(expected, nullptr);
		}

		// if it was picked up, wait for completion
		if (performed)
		{
			while (!fSynchronousCompletion.load())
				std::this_thread::sleep_for(cro::milliseconds(5));
		}
	}

	if (!performed)
	{
		std::lock_guard<std::mutex> lock(fRunMutex);
		fn();
	}
}

// -----------------------------------------------------------------------

Plugin *DISTRHO::createPlugin()
{
	return new PluginVL1();
}

// -----------------------------------------------------------------------
