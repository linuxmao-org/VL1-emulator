#pragma once
#include "VL1Defs.h"
#include "DistrhoPlugin.hpp"

class CVL1Program;

namespace SharedVL1
{
	const CVL1Program *GetFactoryPresets();
	void InitAudioPort(bool input, uint32_t index, AudioPort &port);
	void InitParameter(uint32_t index, Parameter &parameter);
}
