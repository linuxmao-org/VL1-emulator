/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#pragma once
#include "Wave.h"


class CSharedData;


struct CWaveSet
{
	void Setup(CSharedData *pShared);

	// Waves (samples)
	CWave wavePiano;
	CWave waveFantasy;
	CWave waveViolin;
	CWave waveFlute;
	CWave waveGuitar1;
	CWave waveGuitar2;
	CWave waveEnglishHorn;
};
