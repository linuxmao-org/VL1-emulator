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

static void InitEnumValues(
	ParameterEnumerationValues &ev,
	std::initializer_list<std::pair<float, const char *>> args)
{
	ParameterEnumerationValue *values = new ParameterEnumerationValue[args.size()];
	ev.values = values;
	size_t i = 0;
	for (std::pair<float, const char *> arg : args)
	{
		values[i].value = arg.first;
		values[i].label = arg.second;
		++i;
	}
}

void SharedVL1::InitParameter(uint32_t index, Parameter &parameter)
{
	DISTRHO_SAFE_ASSERT_RETURN(index < kNumParams, );

	tParameterRange range = GetParameterRange(index);
	parameter.ranges.def = range.def;
	parameter.ranges.min = range.min;
	parameter.ranges.max = range.max;

	parameter.hints = GetParameterHints(index);

	switch (index)
	{
		case kMode:
			parameter.symbol = "Mode";
			parameter.name = "Mode";
			InitEnumValues(parameter.enumValues,
			{
				{kVL1Play, "Play"},
				{kVL1Rec, "Rec"},
				{kVL1Cal, "Cal"},
				{kVL1Off, "Off"},
			});
			parameter.enumValues.restrictedMode = true;
			break;
		case kVolume:
			parameter.symbol = "Volume";
			parameter.name = "Volume";
			parameter.unit = "%";
			break;
		case kBalance:
			parameter.symbol = "Balance";
			parameter.name = "Balance";
			parameter.unit = "%";
			break;
		case kOctave:
			parameter.symbol = "Octave";
			parameter.name = "Octave";
			InitEnumValues(parameter.enumValues,
			{
				{0.0, "Low"},
				{1.0, "Middle"},
				{2.0, "High"},
			});
			parameter.enumValues.restrictedMode = true;
			break;
		case kTune:
			parameter.symbol = "Tune";
			parameter.name = "Tune";
			parameter.unit = "%";
			break;
		case kSound:
			parameter.symbol = "Sound";
			parameter.name = "Sound";
			InitEnumValues(parameter.enumValues,
			{
				{kPiano, gVL1SoundNames[kPiano]},
				{kFantasy, gVL1SoundNames[kFantasy]},
				{kViolin, gVL1SoundNames[kViolin]},
				{kFlute, gVL1SoundNames[kFlute]},
				{kGuitar1, gVL1SoundNames[kGuitar1]},
				{kGuitar2, gVL1SoundNames[kGuitar2]},
				{kEnglishHorn, gVL1SoundNames[kEnglishHorn]},
				{kElectro1, gVL1SoundNames[kElectro1]},
				{kElectro2, gVL1SoundNames[kElectro2]},
				{kElectro3, gVL1SoundNames[kElectro3]},
			});
			parameter.enumValues.restrictedMode = true;
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

tParameterRange SharedVL1::GetParameterRange(uint32_t index)
{
	tParameterRange range;

	switch (index)
	{
		case kMode:
			range = tParameterRange{0.0, 0.0, 3.0};
			break;
		case kVolume:
			range = tParameterRange{80.0, 0.0, 100.0}; // 80%
			break;
		case kBalance:
			range = tParameterRange{50.0, 0.0, 100.0}; // 50%
			break;
		case kOctave:
			range = tParameterRange{1.0, 0.0, 2.0}; // middle
			break;
		case kTune:
			range = tParameterRange{50.0, 0.0, 100.0}; // 50%
			break;
		case kSound:
			range = tParameterRange{0.0, 0.0, kNumSounds};
			break;
		case kAttack:
			range = tParameterRange{0.0, 0.0, 9.0};
			break;
		case kDecay:
			range = tParameterRange{4.0, 0.0, 9.0};
			break;
		case kSustainLevel:
			range = tParameterRange{5.0, 0.0, 9.0};
			break;
		case kSustainTime:
			range = tParameterRange{3.0, 0.0, 9.0};
			break;
		case kRelease:
			range = tParameterRange{2.0, 0.0, 9.0};
			break;
		case kVibrato:
			range = tParameterRange{0.0, 0.0, 9.0};
			break;
		case kTremolo:
			range = tParameterRange{0.0, 0.0, 9.0};
			break;
		case kTempo:
			range = tParameterRange{4.0, -9.0, +9.0}; // 4
			break;
		default:
			DISTRHO_SAFE_ASSERT(false);
			range = tParameterRange{0.0, 0.0, 1.0};
			break;
	}

	return range;
}

uint32_t SharedVL1::GetParameterHints(uint32_t index)
{
	uint32_t hints = kParameterIsAutomable;

	switch (index)
	{
		case kMode:
			hints |= kParameterIsInteger;
			break;
		case kVolume:
			break;
		case kBalance:
			break;
		case kOctave:
			hints |= kParameterIsInteger;
			break;
		case kTune:
			break;
		case kSound:
			hints |= kParameterIsInteger;
			break;
		case kAttack:
			hints |= kParameterIsInteger;
			break;
		case kDecay:
			hints |= kParameterIsInteger;
			break;
		case kSustainLevel:
			hints |= kParameterIsInteger;
			break;
		case kSustainTime:
			hints |= kParameterIsInteger;
			break;
		case kRelease:
			hints |= kParameterIsInteger;
			break;
		case kVibrato:
			hints |= kParameterIsInteger;
			break;
		case kTremolo:
			hints |= kParameterIsInteger;
			break;
		case kTempo:
			hints |= kParameterIsInteger;
			break;
		default:
			DISTRHO_SAFE_ASSERT(false);
	}

	return hints;
}

float SharedVL1::ParameterValueFrom01(uint32_t index, float value)
{
	const tParameterRange range = GetParameterRange(index);
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
	const tParameterRange range = GetParameterRange(index);
	const uint32_t hints = GetParameterHints(index);

	if (hints & kParameterIsInteger)
		value = roundf(value);

	const float extent = range.max - range.min;
	value = (value - range.min) / extent;

	value = (value < 0.0f) ? 0.0f : value;
	value = (value > 1.0f) ? 1.0f : value;

	return value;
}
