/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#include "WaveSet.h"
#include "VL1Defs.h"

void CWaveSet::Setup(CSharedData *pShared)
{
	wavePiano.Create(kPiano,kWaveTableSize,pShared);
	waveFantasy.Create(kFantasy,kWaveTableSize,pShared);
	waveViolin.Create(kViolin,kWaveTableSize,pShared);
	waveFlute.Create(kFlute,kWaveTableSize,pShared);
	waveGuitar1.Create(kGuitar1,kWaveTableSize,pShared);
	waveGuitar2.Create(kGuitar2,kWaveTableSize,pShared);
	waveEnglishHorn.Create(kEnglishHorn,kWaveTableSize,pShared);
}
