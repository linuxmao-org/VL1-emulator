#ifndef __RHYTHM_H__
#define __RHYTHM_H__


#include "VL1Defs.h"


class CSharedData;


typedef struct
{
	int sound; // One of the great rhythm sounds.
	int length; // In musical notation 1, 1/4, 1/8, etc..
	float velocity; // Future expansion...
}
tRhythmEvent;


typedef struct
{
	int maxBeat;
	const tRhythmEvent *pRhythm;
}
tRhythm;


class CRhythm
{
public:
	CRhythm();
	~CRhythm();

	void Setup(CSharedData *pShared);

	void Reset();

	inline void SelectRhythm(int rhythm) { m_rhythm = rhythm; }
	void SetBeat(int beat);
	void Play(int startAtBeat=0);
	inline void Stop() { m_bScheduleStop = true; }
	inline void Trigger() { m_bTrigger = true; }
	float Clock();

private:
	int m_time;
	bool m_bTrigger;
	int m_triggerCounter;
	int m_rhythm;
	int m_sound;
	int m_beat;
	bool m_bIsPlaying;
	bool m_bScheduleStop;

	bool MakeBlip(float frequency, int periods);
	int m_blipSize;
	float *m_pBlip;

	bool MakeNoise(float oversampling);
	int m_noiseSize;
	float *m_pNoise;

	CSharedData *m_pShared;
};


#endif // __RHYTHM_H__
