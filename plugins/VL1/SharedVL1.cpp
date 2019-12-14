#include "SharedVL1.hpp"
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

const CVL1Program *GetFactoryPresets()
{
	static tFactoryPresets presets = CreateFactoryPresets();
	return presets.data();
}
