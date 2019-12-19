/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#ifndef __WAVE_H__
#define __WAVE_H__


class CSharedData;


class CWave
{
public:
	CWave();
	CWave(int type, int size, CSharedData *pShared);
	~CWave();

	void Create(int type, int size, CSharedData *pShared, float width=0.25f);

	float *Get() { return m_pData; }
	long GetSize() { return m_size; }
	float GetPitchScale() { return m_pitchScale; }

	void DumpToFile(const char *pFilePath);

private:
	float *m_pData;
	long m_size;
	float m_pitchScale;
	//char *m_pName;

	void MakeSinc(float width);
	void MakePulse(float dutyCycle);
	void MakePiano();
	void MakeFantasy();
	void MakeViolin();
	void MakeFlute();
	void MakeGuitar1();
	void MakeGuitar2();
	void MakeEnglishHorn();
	//void MakeNoise();
};


extern char *gpWaveNames[10];


#endif // __WAVE_H__
