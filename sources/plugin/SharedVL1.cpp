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

	parameter.ranges = ParameterRanges(0.0, 0.0, 1.0);
	parameter.hints = kParameterIsAutomable;

	const CVL1Program &program = SharedVL1::GetFactoryPresets()[0];
	float valueFromProgram = program.GetParameter(index, HUGE_VALF);

	if (valueFromProgram != HUGE_VALF)
		parameter.ranges.def = valueFromProgram;

	switch (index)
	{
		case kMode:
			parameter.symbol = "Mode";
			parameter.name = "Mode";
			parameter.ranges.def = 0.0; // play
			break;
		case kVolume:
			parameter.symbol = "Volume";
			parameter.name = "Volume";
			parameter.ranges.def = 0.8; // 80%
			break;
		case kBalance:
			parameter.symbol = "Balance";
			parameter.name = "Balance";
			parameter.ranges.def = 0.5; // 50-50
			break;
		case kOctave:
			parameter.symbol = "Octave";
			parameter.name = "Octave";
			parameter.ranges.def = 0.51; // middle
			break;
		case kTune:
			parameter.symbol = "Tune";
			parameter.name = "Tune";
			parameter.ranges.def = 0.5; // 50%
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
			parameter.ranges.def = 0.725; // 4
			break;
		default:
			DISTRHO_SAFE_ASSERT_RETURN(false, );
	}

	//fprintf(stderr, "Parameter \"%s\" default %f\n", parameter.name.buffer(), parameter.ranges.def);
}
