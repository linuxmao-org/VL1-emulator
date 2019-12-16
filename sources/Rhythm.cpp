#include "Rhythm.h"
#include "Noise.h"
#include "VoiceManager.h"
#include "SharedData.h"
#include <stdio.h>


const tRhythmEvent gMarch[2] =
{
	{ kPock, kWhole, 1.0f },
	{ kNoise, kWhole, 1.0f },
};


const tRhythmEvent gWaltz[3] =
{
	{ kPock, kWhole, 1.0f },
	{ kNoise, kWhole, 1.0f },
	{ kNoise, kWhole, 1.0f },
};


const tRhythmEvent g4Beat[4] =
{
	{ kPock, kWhole, 1.0f },
	{ kNoise, kWhole, 1.0f },
	{ kNoise, kWhole, 1.0f },
	{ kNoise, kWhole, 1.0f },
};


const tRhythmEvent gSwing[3] =
{
	{ kPeek, kWhole, 1.0f },
	{ kNoise, 3*kQuarter, 1.0f },
	{ kPeek, kQuarter, 1.0f },
};


const tRhythmEvent gRock1[8] =
{
	{ kPock, kHalf, 1.0f },
	{ kPeek, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPock, kHalf, 1.0f },
	{ kPeek, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPeek, kHalf, 1.0f },
};


const tRhythmEvent gRock2[9] =
{
	{ kPock, kHalf, 1.0f },
	{ kPeek, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPeek, kQuarter, 1.0f },
	{ kPock, kQuarter, 1.0f },
	{ kPock, kHalf, 1.0f },
	{ kPock, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPeek, kHalf, 1.0f },
};


const tRhythmEvent gBossanova[16] =
{
	{ kPeek, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPeek, kHalf, 1.0f },
	{ kPock, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPeek, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPock, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPeek, kHalf, 1.0f },
	{ kPock, kHalf, 1.0f },
	{ kPock, kHalf, 1.0f },
	{ kPeek, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPock, kHalf, 1.0f },
};


const tRhythmEvent gSamba[16] =
{
	{ kPeek, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPeek, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPock, kHalf, 1.0f },
	{ kPock, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPeek, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPeek, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPeek, kHalf, 1.0f },
	{ kPock, kHalf, 1.0f },
	{ kPock, kHalf, 1.0f },
	{ kPock, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
};


const tRhythmEvent gRhumba[18] =
{
	{ kPeek, kHalf, 1.0f },
	{ kNoise, kQuarter, 1.0f },
	{ kNoise, kQuarter, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPeek, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPeek, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kNoise, kQuarter, 1.0f },
	{ kNoise, kQuarter, 1.0f },
	{ kPeek, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPeek, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPock, kHalf, 1.0f },
	{ kPock, kHalf, 1.0f },
};


const tRhythmEvent gBeguine[9] =
{
	{ kPock, kHalf, 1.0f },
	{ kNoise, kQuarter, 1.0f },
	{ kNoise, kQuarter, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPeek, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
	{ kPock, kHalf, 1.0f },
	{ kNoise, kHalf, 1.0f },
};


const tRhythm gRhythms[10] =
{
	{ 2, (tRhythmEvent*)&gMarch },
	{ 3, (tRhythmEvent*)&gWaltz },
	{ 4, (tRhythmEvent*)&g4Beat },
	{ 3, (tRhythmEvent*)&gSwing },
	{ 8, (tRhythmEvent*)&gRock1 },
	{ 9, (tRhythmEvent*)&gRock2 },
	{ 16, (tRhythmEvent*)&gBossanova },
	{ 16, (tRhythmEvent*)&gSamba },
	{ 18, (tRhythmEvent*)&gRhumba },
	{ 9, (tRhythmEvent*)&gBeguine },
};


CRhythm::CRhythm() :
	m_rhythm(kMarch),
	m_sound(kPock),
	m_blipSize(0),
	m_pBlip(nullptr),
	m_noiseSize(0),
	m_pNoise(nullptr),
	m_pShared(nullptr)
{
	Reset();
	MakeBlip(780,30);
	MakeNoise(50000.0f/kDefaultSampleRate);
}


CRhythm::~CRhythm()
{
	SafeDeleteArray(m_pBlip);
	SafeDeleteArray(m_pNoise);
}


void CRhythm::Setup(CSharedData *pShared)
{
	m_pShared = pShared;

	MakeBlip(780,30);
	MakeNoise(50000.0f/pShared->sampleRate);
}


void CRhythm::Reset()
{
	m_time = 0;
	m_beat = 0;
	m_bIsPlaying = false;
	m_bScheduleStop = false;
	m_bTrigger = false;
	m_triggerCounter = 0;
}


bool CRhythm::MakeBlip(float frequency, int periods)
{
	SafeDeleteArray(m_pBlip);

	float sampleRate = m_pShared ? m_pShared->sampleRate : kDefaultSampleRate;

	int halfPeriod = ((int)(sampleRate/frequency) + 1) >> 1;

	int blipSize = periods*2*halfPeriod;
	float *pBlip = new float[blipSize]();

	m_blipSize = blipSize;
	m_pBlip = pBlip;

	//
	float *pCurrent = pBlip;
	float *pEnd = pBlip + blipSize;

	float level = 1.0f;

	for (int p=0; p<periods/2; p++)
	{
		// Two periods per level.
		for (int i=0; i<2; i++)
		{
			for (int j=0; j<halfPeriod && pCurrent<pEnd; j++)
			{
				*(pCurrent++) = level;
			}
			for (int j=0; j<halfPeriod && pCurrent<pEnd; j++)
			{
				*(pCurrent++) = 0.0f;
			}
		}
		level -= 1.0f/15.0f;
	}

	if (false)
	{
		FILE *fh = fopen("/tmp/blip.dat", "w");
		for (int i=0; i<blipSize; ++i)
			fprintf(fh, "%d %f\n", i, pBlip[i]);
		fclose(fh);
	}

	return true;
}


bool CRhythm::MakeNoise(float oversampling)
{
	SafeDeleteArray(m_pNoise);

	float sampleRate = m_pShared ? m_pShared->sampleRate : kDefaultSampleRate;

	float l1 = 8*0.005f; // 8 levels of 5 ms.
	float l2 = 6*0.02f; // 6 levels of 20 ms.
	int s1 = (int)(sampleRate*oversampling*l1);
	int s2 = (int)(sampleRate*oversampling*l2);
	int noiseSize = s1+s2+1;
	float *pNoise1 = new float[noiseSize]();

	m_noiseSize = noiseSize;
	m_pNoise = pNoise1;

	float level = 1.0f;
	CNoise noise;

	int len = (int)(sampleRate*(float)oversampling*0.005f + 0.5f);
	int p = 8;

	//
	float *pCurrent = pNoise1;
	float *pEnd = pNoise1 + noiseSize;

	for (int i=0; i<p; i++)
	{
		for (int j=0; j<len && pCurrent<pEnd; j++)
		{
			*(pCurrent++) = level*(float)noise.Clock();
		}
		level -= 1.0f/15.0f;
	}

	//
	float *pNoise2 = pCurrent;

	len = (int)(sampleRate*(float)oversampling*0.020f + 0.5f);
	p = 6;

	for (int i=0; i<p; i++)
	{
		pCurrent = &pNoise2[i*len];
		for (int j=0; j<len && pCurrent<pEnd; j++)
		{
			*(pCurrent++) = level*(float)noise.Clock();
		}
		level -= 1.0f/15.0f;
	}

	if (false)
	{
		FILE *fh = fopen("/tmp/noise.dat", "w");
		for (int i=0; i<noiseSize; ++i)
			fprintf(fh, "%d %f\n", i, pNoise1[i]);
		fclose(fh);
	}

	return true;
}


void CRhythm::SetBeat(int beat)
{
	m_beat = beat>=gRhythms[m_rhythm].maxBeat? 0 : beat;
}


void CRhythm::Play(int startAtBeat)
{
	CVoiceManager *pVoices1 = m_pShared->pVoices1;

	SetBeat(startAtBeat);
	//m_triggerCounter = 1;
	m_triggerCounter = pVoices1? pVoices1->GetTrigger() : 1;
	m_bScheduleStop = false;
	m_bIsPlaying = true;
}


float CRhythm::Clock()
{
	if (!m_bIsPlaying) return 0.0f;

	m_time++;

	if (m_bTrigger)
	{
		m_bTrigger = false;

		m_triggerCounter--;
		if (!m_triggerCounter)
		{
			m_sound = gRhythms[m_rhythm].pRhythm[m_beat].sound;
			m_triggerCounter = gRhythms[m_rhythm].pRhythm[m_beat].length;

			m_beat++;
			if (m_beat>=gRhythms[m_rhythm].maxBeat)
			{
				m_beat = 0;
			}

			m_time = 0;
		}
	}

	float sample = 0.0f;

	switch (m_sound)
	{
		case kPock:
			if (m_time<m_blipSize)
			{
				sample = m_pBlip[m_time];
			}
			else if (m_bScheduleStop) Reset();
			break;

		case kPeek:
			// Peek is twice as fast as Pock.
			if (m_time<m_blipSize>>1)
			{
				sample = m_pBlip[2*m_time];
			}
			else if (m_bScheduleStop) Reset();
			break;

		case kNoise:
			if (m_time<m_noiseSize)
			{
				sample = m_pNoise[m_time];
			}
			else if (m_bScheduleStop) Reset();
			break;
	}

	return sample;
}
