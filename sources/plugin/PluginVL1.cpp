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
	  m_voiceManager(new CVoiceManager),
	  m_clock(new CClock)
{
	m_sharedData.sampleRate = kDefaultSampleRate;
	m_sharedData.oversampling = kDefaultOversampling;
	m_sharedData.clock = m_clock.get();
	m_sharedData.LCD = m_lcdBuffer.get();
	m_sharedData.waves = m_waves.get();
	m_sharedData.pVoices1 = m_voiceManager.get();
	m_sharedData.rhythm = m_rhythm.get();
	m_sharedData.sequencer = m_sequencer.get();
	m_sharedData.calculator = m_calculator.get();
	m_sharedData.eventManager = m_eventManager.get();
	m_sharedData.screenData = m_lcdScreenData.get();

	memset(m_lcdScreenData.get(), 0, sizeof(tLcdScreenData));

	sampleRateChanged(getSampleRate());

	m_eventManager->Register(m_voiceManager.get(), 0);

	loadProgram(0);
}

PluginVL1::~PluginVL1()
{
}

// -----------------------------------------------------------------------
// Init

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
	m_voiceManager->Create(1, 8, &m_sharedData);
	m_clock->Setup(&m_sharedData);
}

/**
  Get the current value of a parameter.
*/
float PluginVL1::getParameterValue(uint32_t index) const
{
#pragma message("TODO implement me")

	return 0;
}

/**
  Change a parameter value.
*/
void PluginVL1::setParameterValue(uint32_t index, float value)
{
	DISTRHO_SAFE_ASSERT_RETURN(index < kNumParams, );

#pragma message("TODO implement me")
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
		setParameterValue(param, program.GetParameter(param));
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
#pragma message("TODO implement me")
	memset(outputs[0], 0, frames * sizeof(float));
	memset(outputs[1], 0, frames * sizeof(float));
}

// -----------------------------------------------------------------------

Plugin *DISTRHO::createPlugin()
{
	return new PluginVL1();
}

// -----------------------------------------------------------------------
