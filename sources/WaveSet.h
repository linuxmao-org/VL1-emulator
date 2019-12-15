#pragma once
#include "Wave.h"

struct CWaveSet
{
	void Setup(float sampleRate, int oversampling);

	CWave wavePiano;
	CWave waveFantasy;
	CWave waveViolin;
	CWave waveFlute;
	CWave waveGuitar1;
	CWave waveGuitar2;
	CWave waveEnglishHorn;
};

inline void CWaveSet::Setup(float sampleRate, int oversampling)
{
	CWave *all[] =
	{
		&wavePiano,
		&waveFantasy,
		&waveViolin,
		&waveFlute,
		&waveGuitar1,
		&waveGuitar2,
		&waveEnglishHorn,
	};
	for (CWave *wave : all)
	{
		wave->Setup(sampleRate, oversampling);
	}
}
