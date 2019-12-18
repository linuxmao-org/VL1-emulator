#include "SharedVL1.h"
#include "VL1Program.h"
#include <array>
#include <math.h>

typedef std::array<CVL1Program, kNumPrograms> tFactoryPresets;

static tFactoryPresets CreateFactoryPresets()
{
	tFactoryPresets presets;

	for (uint i = 0; i < kNumPrograms; i++)
	{
		presets[i].LoadPreset(gVL1PresetNames[i],gVL1Preset[i]);
	}

	return presets;
}

const CVL1Program *SharedVL1::GetFactoryPresets()
{
	static tFactoryPresets presets = CreateFactoryPresets();
	return presets.data();
}

void SharedVL1::InitAudioPort(bool input, uint32_t index, AudioPort &port)
{
	if (input)
	{
		DISTRHO_SAFE_ASSERT(false);
	}
	else
	{
		switch (index)
		{
			case 0:
				port.symbol = "Left";
				port.name = "Left";
				break;
			case 1:
				port.symbol = "Right";
				port.name = "Right";
				break;
			default:
				DISTRHO_SAFE_ASSERT(false);
				break;
		}
	}
}

void SharedVL1::InitParameter(uint32_t index, Parameter &parameter)
{
	DISTRHO_SAFE_ASSERT_RETURN(index < kNumParams, );

	parameter.ranges = GetParameterRange(index);
	parameter.hints = GetParameterHints(index);

	switch (index)
	{
		case kMode:
			parameter.symbol = "Mode";
			parameter.name = "Mode";
			break;
		case kVolume:
			parameter.symbol = "Volume";
			parameter.name = "Volume";
			break;
		case kBalance:
			parameter.symbol = "Balance";
			parameter.name = "Balance";
			break;
		case kOctave:
			parameter.symbol = "Octave";
			parameter.name = "Octave";
			break;
		case kTune:
			parameter.symbol = "Tune";
			parameter.name = "Tune";
			break;
		case kSound:
			parameter.symbol = "Sound";
			parameter.name = "Sound";
			break;
		case kAttack:
			parameter.symbol = "Attack";
			parameter.name = "Attack";
			break;
		case kDecay:
			parameter.symbol = "Decay";
			parameter.name = "Decay";
			break;
		case kSustainLevel:
			parameter.symbol = "SustainLevel";
			parameter.name = "Sustain level";
			break;
		case kSustainTime:
			parameter.symbol = "SustainTime";
			parameter.name = "Sustain time";
			break;
		case kRelease:
			parameter.symbol = "Release";
			parameter.name = "Release";
			break;
		case kVibrato:
			parameter.symbol = "Vibrato";
			parameter.name = "Vibrato";
			break;
		case kTremolo:
			parameter.symbol = "Tremolo";
			parameter.name = "Tremolo";
			break;
		case kTempo:
			parameter.symbol = "Tempo";
			parameter.name = "Tempo";
			break;
		default:
			DISTRHO_SAFE_ASSERT_RETURN(false, );
	}

	//fprintf(stderr, "Parameter \"%s\" default %f\n", parameter.name.buffer(), parameter.ranges.def);
}

ParameterRanges SharedVL1::GetParameterRange(uint32_t index)
{
	ParameterRanges range;

	switch (index)
	{
		case kMode:
			range = ParameterRanges{0.0, 0.0, 1.0}; // play
			break;
		case kVolume:
			range = ParameterRanges{0.8, 0.0, 1.0}; // 80%
			break;
		case kBalance:
			range = ParameterRanges{0.5, 0.0, 1.0}; // 50%
			break;
		case kOctave:
			range = ParameterRanges{0.51, 0.0, 1.0}; // middle
			break;
		case kTune:
			range = ParameterRanges{0.5, 0.0, 1.0}; // 50%
			break;
		case kSound:
			range = ParameterRanges{0.0, 0.0, 1.0};
			break;
		case kAttack:
			range = ParameterRanges{0.0, 0.0, 1.0};
			break;
		case kDecay:
			range = ParameterRanges{0.4, 0.0, 1.0};
			break;
		case kSustainLevel:
			range = ParameterRanges{0.5, 0.0, 1.0};
			break;
		case kSustainTime:
			range = ParameterRanges{0.3, 0.0, 1.0};
			break;
		case kRelease:
			range = ParameterRanges{0.2, 0.0, 1.0};
			break;
		case kVibrato:
			range = ParameterRanges{0.0, 0.0, 1.0};
			break;
		case kTremolo:
			range = ParameterRanges{0.0, 0.0, 1.0};
			break;
		case kTempo:
			range = ParameterRanges{0.725, 0.0, 1.0}; // 4
			break;
		default:
			DISTRHO_SAFE_ASSERT(false);
	}

	return range;
}

uint32_t SharedVL1::GetParameterHints(uint32_t index)
{
	uint32_t hints = kParameterIsAutomable;

	switch (index)
	{
		case kMode:
			break;
		case kVolume:
			break;
		case kBalance:
			break;
		case kOctave:
			break;
		case kTune:
			break;
		case kSound:
			break;
		case kAttack:
			break;
		case kDecay:
			break;
		case kSustainLevel:
			break;
		case kSustainTime:
			break;
		case kRelease:
			break;
		case kVibrato:
			break;
		case kTremolo:
			break;
		case kTempo:
			break;
		default:
			DISTRHO_SAFE_ASSERT(false);
	}

	return hints;
}

float SharedVL1::ParameterValueFrom01(uint32_t index, float value)
{
	const ParameterRanges range = GetParameterRange(index);
	const uint32_t hints = GetParameterHints(index);

	const float extent = range.max - range.min;
	value = value * extent + range.min;

	if (hints & kParameterIsInteger)
		value = roundf(value);

	value = (value < range.min) ? range.min : value;
	value = (value > range.max) ? range.max : value;

	return value;
}

float SharedVL1::ParameterValueTo01(uint32_t index, float value)
{
	const ParameterRanges range = GetParameterRange(index);
	const uint32_t hints = GetParameterHints(index);

	if (hints & kParameterIsInteger)
		value = roundf(value);

	const float extent = range.max - range.min;
	value = (value - range.min) / extent;

	value = (value < 0.0f) ? 0.0f : value;
	value = (value > 1.0f) ? 1.0f : value;

	return value;
}
