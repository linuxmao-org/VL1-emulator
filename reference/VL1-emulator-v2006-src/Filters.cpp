#include "Filters.h"
#include "math.h"


const float p4 = (float)1.0e-24; // Pentium 4 denormal problem elimination
const float _PI_ = (float)(4.0*atan(1));
const float _2PI_ = (float)(8.0*atan(1));
const float kEpsilon = 1.0e-15f;


#define Denormalize(a) if (fabsf(a)<kEpsilon) a = 0.0f


CCascadedResonantLpHp::CCascadedResonantLpHp()
{
	m_delay1 = 0.0f;
	m_delay2 = 0.0f;
	m_delay3 = 0.0f;
	m_delay4 = 0.0f;
}


CCascadedResonantLpHp::~CCascadedResonantLpHp()
{
}


float CCascadedResonantLpHp::Clock(float sample, float lpc, float lpr, float hpc, float hpr)
{
	float fb_lp = lpr + lpr/(1.0f-lpc);
	float fb_hp = hpr + hpr/(1.0f-lpc);
	//double fb_hp = hpr + hpr/(1.0f-hpc);
	m_delay1 = m_delay1 + lpc*(sample-m_delay1+fb_lp*(m_delay1-m_delay2)) + p4;
	m_delay2 = m_delay2 + lpc*(m_delay1-m_delay2);
	m_delay3 = m_delay3 + hpc*(m_delay2-m_delay3+fb_hp*(m_delay3-m_delay4)) + p4;
	m_delay4 = m_delay4 + hpc*(m_delay3-m_delay4);
	return m_delay2 - m_delay4;
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


CIIR1::CIIR1() :
	m_k(1.0f),
	m_l(0.0f),
	m_delay(0.0f)
{
}


void CIIR1::SetCutoff(float fc, float sampleRate)
{
	m_k = 1.0f- expf(-1.0f*_2PI_*fc/sampleRate);
	m_l = 1.0f - m_k;
}


float CIIR1::Clock(float sample)
{
	/*double out = m_k*m_delay;
	if (fabs(out)<p4) out = 0.0;
	m_delay = m_delay - out + sample;
	return out;*/
	m_delay = m_l*m_delay + m_k*sample;
	if (fabs(m_delay)<p4) m_delay = 0.0f;
	return m_delay;
}



//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


CIIR2::CIIR2() :
	m_a0(1.0),
	m_a1(0.0),
	m_a2(0.0),
	m_b1(0.0),
	m_b2(0.0),
	m_i1(0.0),
	m_i2(0.0),
	m_o1(0.0),
	m_o2(0.0)
{
}


float CIIR2::Clock(float sample)
{
	float s = m_a0*sample + m_a1*m_i1 + m_a2*m_i2 - m_b1*m_o1 - m_b2*m_o2;
	m_i2 = m_i1;
	m_i1 = sample;
	m_o2 = m_o1;
	m_o1 = s;
	return s;
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


CBiquad::CBiquad() :
	m_a1(0.0f),
	m_a2(0.0f),
	m_b0(1.0f),
	m_b1(0.0f),
	m_b2(0.0f),
	m_xn1(0.0f),
	m_xn2(0.0f),
	m_yn1(0.0f),
	m_yn2(0.0f),
	m_Q(1.0f),
	m_A(1.0f),
	m_S(1.0f),
	m_w0(_PI_),
	m_cosw0(-1.0f),
	m_sinw0(0.0f),
	m_alpha(0.0f),
	m_dbGain(0.0f)
{
}


void CBiquad::SetCutoff(float fc, float sampleRate)
{
	// Precalculate some values.
	m_A = sqrtf(powf(10.0f,0.05f*m_dbGain));
	m_w0 = _2PI_*fc/sampleRate;
	m_cosw0 = cosf(m_w0);
	m_sinw0 = sinf(m_w0);
	m_alpha = m_sinw0/2.0f*m_Q;
}


float CBiquad::Clock(float in)
{
	float out = m_b0*in + m_b1*m_xn1 + m_b2*m_xn2 - m_a1*m_yn1 - m_a2*m_yn2;
	Denormalize(out);
	m_xn2 = m_xn1;
	m_xn1 = in;
	m_yn2 = m_yn1;
	m_yn1 = out;
	return out;
}


void CBiquadLpf::SetCutoff(float fc, float sampleRate)
{
	// H(s) = 1 / (s^2 + s/Q + 1)

	// Call base class to calculate some intermediate values.
	CBiquad::SetCutoff(fc,sampleRate);

	// Calculate the coefficients.
	float oneOverA0 = 1.0f/(1.0f + m_alpha);
	m_a1 = oneOverA0*(-2.0f*m_cosw0);
	Denormalize(m_a1);
	m_a2 = oneOverA0*(1.0f - m_alpha);
	Denormalize(m_a2);
	m_b1 = oneOverA0*(1.0f - m_cosw0);
	Denormalize(m_b1);
	m_b0 = 0.5f*m_b1;
	Denormalize(m_b0);
	m_b2 = m_b0;
}


void CBiquadLpf::SetChebychef1()
{
	m_a1 = -1.4349003f;
	m_a2 = 0.579397f;
	m_b1 = 2.0f;
	m_b2 = 1.0f;
	m_gain = 0.068983672f;
}


void CBiquadLpf::SetChebychef2()
{
	m_a1 = -1.2931325f;
	m_a2 = 0.8200644f;
	m_b1 = 2.0f;
	m_b2 = 1.0f;
	m_gain = 0.068983672f;
}


void CBiquadLpf::SetButterworth1()
{
	m_a1 = -0.8553979f;
	m_a2 = 0.2097154f;
	m_b1 = 2.0f;
	m_b2 = 1.0f;
	m_gain = 0.10104198f;
}


void CBiquadLpf::SetButterworth2()
{
	m_a1 = -1.1130298f;
	m_a2 = 0.5740619f;
	m_b1 = 2.0f;
	m_b2 = 1.0f;
	m_gain = 0.10104198f;
}


float CBiquadLpf::Clock2(float xn)
{
	float yn = m_gain*(xn + m_b1*m_xn1 + m_b2*m_xn2) - m_a1*m_yn1 - m_a2*m_yn2;
	Denormalize(yn);
	m_xn2 = m_xn1;
	m_xn1 = xn;
	m_yn2 = m_yn1;
	m_yn1 = yn;
	return yn;
}
