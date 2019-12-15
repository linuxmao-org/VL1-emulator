#include "SharedVL1.h"
#include "VL1Program.h"
#include <array>

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

void SharedVL1::InitParameter(uint32_t index, Parameter &parameter)
{
	DISTRHO_SAFE_ASSERT_RETURN(index < kNumParams, );

	parameter.ranges = ParameterRanges(0.0, 0.0, 1.0);
	parameter.hints = kParameterIsAutomable;

	switch (index)
	{
		case kProgram:
			parameter.symbol = "Program";
			parameter.name = "Program";
			break;
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
}
