#include "Rhythm.h"
#include "GlobalData.h"
#include "Noise.h"


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
	m_pBlip(NULL),
	m_pNoise(NULL),
	m_noiseSize(0)
{
	Reset();
	MakeBlip(780,30);
	MakeNoise(50000.0f/gSampleRate);
}


void CRhythm::Reset()
{
	m_time = 0;
	m_beat = 0;
	m_bIsPlaying = FALSE;
	m_bScheduleStop = FALSE;
	m_bTrigger = FALSE;
	m_triggerCounter = 0;
}


BOOL CRhythm::MakeBlip(float frequency, int periods)
{
	int halfPeriod = ((int)(gSampleRate/frequency) + 1) >> 1;

	m_blipSize = periods*2*halfPeriod;
	if (m_pBlip) delete [] m_pBlip;
	m_pBlip = new float[m_blipSize];
	if (!m_pBlip) return FALSE;

	float level = 1.0f;
	float *pBlip = m_pBlip;

	for (int p=0; p<periods/2; p++)
	{
		// Two periods per level.
		for (int i=0; i<2; i++)
		{
			for (int j=0; j<halfPeriod; j++)
			{
				*(pBlip++) = level;
			}
			for (j=0; j<halfPeriod; j++)
			{
				*(pBlip++) = 0.0f;
			}
		}
		level -= 1.0f/15.0f;
	}

	return TRUE;
}


BOOL CRhythm::MakeNoise(float oversampling)
{
	if (m_pNoise) delete [] m_pNoise;

	float l1 = 8*0.005f; // 8 levels of 5 ms.
	float l2 = 6*0.02f; // 6 levels of 20 ms.
	int s1 = (int)(gSampleRate*oversampling*l1);
	int s2 = (int)(gSampleRate*oversampling*l2);
	m_noiseSize = s1+s2+1;
	m_pNoise = new float[m_noiseSize];
	if (!m_pNoise) return FALSE;

	for (int i=0; i<m_noiseSize; i++)
	{
		m_pNoise[i] = 0.0f;
	}

	float level = 1.0f;
	CNoise noise;
	float *pNoise = m_pNoise;

	int len = (int)(gSampleRate*(float)oversampling*0.005f + 0.5f);
	int p = 8;

	for (i=0; i<p; i++)
	{
		for (int j=0; j<len; j++)
		{
			*(pNoise++) = level*(float)noise.Clock();
		}
		level -= 1.0f/15.0f;
	}

	len = (int)(gSampleRate*(float)oversampling*0.020f + 0.5f);
	p = 6;

	for (i=0; i<p; i++)
	{
		for (int j=0; j<len; j++)
		{
			pNoise[i*len+j] = level*(float)noise.Clock();
		}
		level -= 1.0f/15.0f;
	}

	return TRUE;
}


void CRhythm::SetBeat(int beat)
{ 
	m_beat = beat>=gRhythms[m_rhythm].maxBeat? 0 : beat; 
}


void CRhythm::Play(int startAtBeat)
{ 
	SetBeat(startAtBeat);
	//m_triggerCounter = 1;
	m_triggerCounter = gpVoices1? gpVoices1->GetTrigger() : 1;
	m_bScheduleStop = FALSE;
	m_bIsPlaying = TRUE;
}


float CRhythm::Clock()
{
	if (!m_bIsPlaying) return 0.0f;

	m_time++;
	
	if (m_bTrigger)
	{
		m_bTrigger = FALSE;

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
