#include "PluginVL1.hpp"
#include <math.h>

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

PluginVL1::PluginVL1() : Plugin(paramCount, presetCount, 0) // paramCount param(s), presetCount program(s), 0 states
{
	sampleRateChanged(getSampleRate());
	if (presetCount > 0)
	{
		loadProgram(0);
	}
}

// -----------------------------------------------------------------------
// Init

void PluginVL1::initParameter(uint32_t index, Parameter &parameter)
{
	DISTRHO_SAFE_ASSERT_RETURN(index < paramCount, );

	parameter.ranges.min = 0.0f;
	parameter.ranges.max = 1.0f;
	parameter.ranges.def = 0.1f;
	parameter.hints = kParameterIsAutomable | kParameterIsLogarithmic;

	switch (index)
	{
	case paramVolumeLeft:
		parameter.name = "Volume L";
		parameter.symbol = "volume_l";
		break;
	case paramVolumeRight:
		parameter.name = "Volume R";
		parameter.symbol = "volume_r";
		break;
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
	DISTRHO_SAFE_ASSERT_RETURN(index < presetCount, );

	programName = factoryPresets[index].name;
}

// -----------------------------------------------------------------------
// Internal data

/**
  Optional callback to inform the plugin about a sample rate change.
*/
void PluginVL1::sampleRateChanged(double newSampleRate)
{
	fSampleRate = newSampleRate;
}

/**
  Get the current value of a parameter.
*/
float PluginVL1::getParameterValue(uint32_t index) const
{
	return fParams[index];
}

/**
  Change a parameter value.
*/
void PluginVL1::setParameterValue(uint32_t index, float value)
{
	DISTRHO_SAFE_ASSERT_RETURN(index < paramCount, );

	fParams[index] = value;

	switch (index)
	{
	case paramVolumeLeft:
		// do something when volume_r param is set
		break;
	case paramVolumeRight:
		// same for volume_r param
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
	DISTRHO_SAFE_ASSERT_RETURN(index < presetCount, );

	for (uint32_t i = 0; i < paramCount; i++)
	{
		setParameterValue(i, factoryPresets[index].params[i]);
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

	// get the left and right audio inputs
	const float *const inpL = inputs[0];
	const float *const inpR = inputs[1];

	// get the left and right audio outputs
	float *const outL = outputs[0];
	float *const outR = outputs[1];

	// apply gain against all samples
	for (uint32_t i = 0; i < frames; ++i)
	{
		outL[i] = inpL[i] * fParams[paramVolumeLeft];
		outR[i] = inpR[i] * fParams[paramVolumeRight];
	}
}

// -----------------------------------------------------------------------

Plugin *createPlugin()
{
	return new PluginVL1();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
