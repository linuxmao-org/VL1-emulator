#include "LFO.h"
#include "VL1Defs.h"
#include <math.h>


CLfo::CLfo() :
	m_dc(0.0f),
	m_bEnable(false),
	m_sampleRate(kDefaultSampleRate),
	m_oversampling(kDefaultOversampling)
{
	SetFrequency(kLfoBaseFreq);
}


CLfo::~CLfo()
{
}


void CLfo::Setup(float sampleRate, int oversampling)
{
	m_sampleRate = sampleRate;
	m_oversampling = oversampling;
}


void CLfo::SetFrequency(float freq)
{
	m_frequency = freq;
	Reset();
}


void CLfo::Reset()
{
	ResetSine();
}


void CLfo::ResetSine()
{
	float kPi = M_PI;
	m_a = 2.0f*sinf(kPi*m_frequency/(m_sampleRate*m_oversampling));
	m_sin = 1.0f;
	m_cos = 0.0f;
}


float CLfo::Clock()
{
	if (!m_bEnable) return m_dc;
	return ClockSine();
}


float CLfo::ClockSine()
{
	// Approximation of scale = 1.0/sqrt(m_sin*m_sin+m_cos*m_cos);
	float scale = 1.5f - 0.5f*(m_sin*m_sin+m_cos*m_cos);
	m_sin = (m_sin - m_a*m_cos)*scale;
	m_cos = (m_cos + m_a*m_sin)*scale;
	return m_sin;
}
