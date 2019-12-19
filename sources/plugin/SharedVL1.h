/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#pragma once
#include "VL1Defs.h"
#include "DistrhoPlugin.hpp"

class CVL1Program;

namespace SharedVL1
{
	const CVL1Program *GetFactoryPresets();
	void InitAudioPort(bool input, uint32_t index, AudioPort &port);
	void InitParameter(uint32_t index, Parameter &parameter);

	tParameterRange GetParameterRange(uint32_t index);
	uint32_t GetParameterHints(uint32_t index);

	float ParameterValueFrom01(uint32_t index, float value);
	float ParameterValueTo01(uint32_t index, float value);
}
