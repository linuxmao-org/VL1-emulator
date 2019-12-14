#include "EnvelopeShaper.h"
#include "GlobalData.h"


CEnvelopeShaper::CEnvelopeShaper() :
	m_cap(3.3e-6f),
	m_rCharge(1.0f/600.0f), // 1/R to prevent divides.
	m_rDischarge(1.0f/33000.0f), // 1/R to prevent divides.
	m_vCap(0.0f)
{
}


// Quadratic approximation of measured transfer curve.
// vOut = a*vIn^2 + b*vIn + c
const float a = 0.131033183f;
const float b = 0.246632173f;
const float c = -0.219399434f;


float CEnvelopeShaper::Clock(float in)
{
	float iCharge;
	float vIn = in*5.0f - 0.6f;
	if (vIn>m_vCap)
	{
		iCharge = (vIn-m_vCap)*m_rCharge;
	}
	else
	{
		iCharge = -m_vCap*m_rDischarge;
	}

	// sneller?
	/*iCharge = (vIn-m_vCap)/m_rCharge;
	if (iCharge<0)
	{
		iCharge = -m_vCap/m_rDischarge;
	}*/

	// i = C*(dV/dt) -> V = (1/C)INTEGRALE(i*dt)
	m_vCap += iCharge/(gSampleRate*gOversampling*m_cap);

	//float vOut = m_vCap;
	float vOut = a*m_vCap*m_vCap + b*m_vCap + c;
	if (vOut<0.0f) vOut = 0.0f;

	return vOut;
}