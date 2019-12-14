#include "PluginVL1.h"
#include "VL1Program.h"
#include <string.h>
#include <math.h>

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

PluginVL1::PluginVL1() : Plugin(kNumParams, kNumPrograms, 0) // paramCount param(s), presetCount program(s), 0 states
{
	sampleRateChanged(getSampleRate());
	loadProgram(0);
}

// -----------------------------------------------------------------------
// Init

void PluginVL1::initParameter(uint32_t index, Parameter &parameter)
{
	DISTRHO_SAFE_ASSERT_RETURN(index < kNumParams, );

#pragma message("TODO implement me")

	parameter.ranges.min = 0.0f;
	parameter.ranges.max = 1.0f;
	parameter.ranges.def = 0.0f;
	parameter.hints = kParameterIsAutomable;

	switch (index)
	{
	default:
		DISTRHO_SAFE_ASSERT_RETURN(false, );
	}
}

/**
  Set the name of the program @a index.
  This function will be called once, shortly after the plugin is created.
*/
void PluginVL1::initProgramName(uint32_t index, String &programName)
{
	DISTRHO_SAFE_ASSERT_RETURN(index < kNumPrograms, );

	const CVL1Program &program = GetFactoryPresets()[index];

	programName = program.GetName();
}

// -----------------------------------------------------------------------
// Internal data

/**
  Optional callback to inform the plugin about a sample rate change.
*/
void PluginVL1::sampleRateChanged(double newSampleRate)
{
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

	const CVL1Program &program = GetFactoryPresets()[index];

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

Plugin *createPlugin()
{
	return new PluginVL1();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
