#include "PluginVL1.h"
#include "Calculator.h"
#include "LcdBuffer.h"
#include "Sequencer.h"
#include "Rhythm.h"
#include "EventManager.h"
#include "VoiceManager.h"
#include "Clock.h"
#include "VL1Program.h"
#include <string.h>
#include <math.h>

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
	  m_parameterRanges(new ParameterRanges[kNumParams])
{
	for (uint32_t p=0; p<kNumParams; ++p)
	{
		Parameter parameter;
		SharedVL1::InitParameter(p, parameter);
		m_parameterRanges[p] = parameter.ranges;
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

	memset(m_lcdScreenData.get(), 0, sizeof(tLcdScreenData));

	sampleRateChanged(getSampleRate());

	m_eventManager->Register(m_voices1.get(), 0);

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
#pragma message("TODO implement me: the other parameters")

	switch (index)
	{
		case kVolume:
			return m_volume;
		case kBalance:
			return m_balance;
		default:
			DISTRHO_SAFE_ASSERT_RETURN(false, 0);
	}
}

/**
  Change a parameter value.
*/
void PluginVL1::setParameterValue(uint32_t index, float value)
{
#pragma message("TODO implement me: the other parameters")

	switch (index)
	{
		case kVolume:
			m_volume = value;
			break;
		case kBalance:
			m_balance = value;
			break;
		default:
			DISTRHO_SAFE_ASSERT(false);
			break;
	}
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
		float value = program.GetParameter(param, m_parameterRanges[param].def);
		setParameterValue(param, value);
	}
}

// -----------------------------------------------------------------------
// Process

void PluginVL1::activate()
{
	// plugin is activated
}

void PluginVL1::run(const float **inputs, float **outputs, uint32_t frames, const MidiEvent *midiEvents,
                    uint32_t midiEventCount)
{
	float* pOut1 = outputs[0];
	float* pOut2 = outputs[1];

	uint32_t midiIndex = 0;
	uint32_t midiInterval = 64;

	int mode = GetModeI();
	if ((mode==kVL1Off) || (mode==kVL1Cal))
	{
		memset(pOut1,0,sizeof(float)*frames);
		memset(pOut2,0,sizeof(float)*frames);
		return;
	}

	auto addEvent = [this](const MidiEvent &midiEvent)
	{
		if (midiEvent.size <= 4)
		{
			tEvent event;
			event.midiEvent.frameTime = midiEvent.frame;
			memcpy(event.midiEvent.midiData, midiEvent.data, 4);
			m_eventManager->AddEvent(event);
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

		if (mode!=kVL1Off && time%midiInterval==0)
		{
			while (midiIndex<midiEventCount && time<=midiEvents[midiIndex].frame)
				addEvent(midiEvents[midiIndex++]);
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
		addEvent(midiEvents[midiIndex++]);
}

// -----------------------------------------------------------------------

Plugin *DISTRHO::createPlugin()
{
	return new PluginVL1();
}

// -----------------------------------------------------------------------
