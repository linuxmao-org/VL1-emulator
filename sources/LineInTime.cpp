#include "LineInTime.h"
#include "SharedData.h"
#include "Utils.h"
#include "VL1Defs.h"


CLineInTime::CLineInTime() :
	m_t0(0.0f),
	m_t1(0.0f),
	m_tRes(0.0f),
	m_s(0.0f),
	m_ds(0.0f),
	m_sStep(0.0f),
	m_y(0.0f),
	m_dy(0.0f),
	m_y0(0.0f),
	m_y1(0.0f),
	m_yRes(0.0f),
	m_yAcc(0.0f),
	m_bUp(true),
	m_bDone(false)
{
}


//static int gi = 0;


void CLineInTime::Setup(CSharedData *pShared)
{
	m_pShared = pShared;
}


void CLineInTime::Initialize(float t0, float y0, float t1, float y1, bool bReset)
{
	float sampleRate = m_pShared->sampleRate;
	int oversampling = m_pShared->oversampling;

	m_t0 = Minf(t0,t1); // In ms.
	m_t1 = Maxf(t0,t1); // In ms.
	m_ds = 1.0f; // In samples.
	m_s = 0; // In samples.
	m_sStep = 0.001f*m_tRes*sampleRate*oversampling; // In samples.

	m_y0 = Minf(y0,y1);
	m_y1 = Maxf(y0,y1);
	m_dy = (m_y1-m_y0)/(0.001f*(m_t1-m_t0)*sampleRate*oversampling);

	m_bUp = (y1>=y0);
	if (bReset) m_yAcc = m_bUp? m_y0 : m_y1;
	m_y = m_yAcc;

	//gi = 0;
}


float CLineInTime::Clock()
{
	if (m_bDone) return m_yAcc;

	m_s += m_ds;

	float sampleRate = m_pShared->sampleRate;
	int oversampling = m_pShared->oversampling;

	if (m_bUp)
	{
		if (m_y<m_y1)
		{
			m_y += m_dy;

			if (m_sStep>0) m_sStep -= m_ds;
			else
			{
				m_sStep = 0.001f*m_tRes*sampleRate*oversampling;

				if (m_yAcc<m_y)
				{
					while (m_yAcc<m_y) m_yAcc += m_yRes;
					//TRACE("%d: %f, %f, %f\n",gi,m_yAcc,m_y,m_yRes);
				}
			}
		}
		else
		{
			m_yAcc = m_y1;
			m_bDone = true;
		}
	}
	else
	{
		if (m_y>m_y0)
		{
			m_y -= m_dy;

			if (m_sStep>0) m_sStep -= m_ds;
			else
			{
				m_sStep = 0.001f*m_tRes*sampleRate*oversampling;

				if (m_yAcc>m_y)
				{
					while (m_yAcc>m_y) m_yAcc -= m_yRes;
					//TRACE("%d: %f, %f, %f\n",gi,m_yAcc,m_y,m_yRes);
				}
			}
		}
		else
		{
			m_yAcc = m_y0;
			m_bDone = true;
		}
	}

	//gi++;

	return m_yAcc;
}
