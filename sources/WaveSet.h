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
