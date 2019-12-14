#include "LineInTime.h"
#include "GlobalData.h"


CLineInTime::CLineInTime() :
	m_tRes(0.0f),
	m_yRes(0.0f),
	m_bUp(TRUE),
	m_s(0.0f),
	m_t0(0.0f),
	m_t1(0.0f),
	m_ds(0.0f),
	m_sStep(0.0f),
	m_y(0.0f),
	m_y0(0.0f),
	m_y1(0.0f),
	m_dy(0.0f),
	m_yAcc(0.0f),
	m_bDone(FALSE)
{
}


static int gi = 0;


void CLineInTime::Initialize(float t0, float y0, float t1, float y1, BOOL bReset)
{ 
	m_t0 = min(t0,t1); // In ms.
	m_t1 = max(t0,t1); // In ms.
	m_ds = 1.0f; // In samples.
	m_s = 0; // In samples.
	m_sStep = 0.001f*m_tRes*gSampleRate*gOversampling; // In samples.

	m_y0 = min(y0,y1);
	m_y1 = max(y0,y1);
	m_dy = (m_y1-m_y0)/(0.001f*(m_t1-m_t0)*gSampleRate*gOversampling);

	m_bUp = (y1>=y0);
	if (bReset) m_yAcc = m_bUp? m_y0 : m_y1;
	m_y = m_yAcc;

	gi = 0;
}


float CLineInTime::Clock()
{
	if (m_bDone) return m_yAcc;

	m_s += m_ds;

	if (m_bUp)
	{
		if (m_y<m_y1)
		{
			m_y += m_dy;

			if (m_sStep>0) m_sStep -= m_ds;
			else
			{
				m_sStep = 0.001f*m_tRes*gSampleRate*gOversampling;

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
			m_bDone = TRUE;
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
				m_sStep = 0.001f*m_tRes*gSampleRate*gOversampling;

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
			m_bDone = TRUE;
		}
	}

	gi++;

	return m_yAcc;
}
