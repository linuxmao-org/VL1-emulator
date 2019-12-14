#include "LFO.h"
#include "GlobalData.h"
#include <math.h>


CLfo::CLfo() :
	m_bEnable(FALSE),
	m_dc(0.0f)
{
	SetFrequency(kLfoBaseFreq);
}


CLfo::~CLfo()
{
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
	m_a = 2.0f*sinf(kPi*m_frequency/(gSampleRate*gOversampling));
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
