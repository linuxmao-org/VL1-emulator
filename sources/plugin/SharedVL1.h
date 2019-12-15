#pragma once
#include "VL1Defs.h"
#include "DistrhoPlugin.hpp"

class CVL1Program;

namespace SharedVL1
{
	const CVL1Program *GetFactoryPresets();
	void InitParameter(uint32_t index, Parameter &parameter);
}
