#ifndef __LINE_IN_TIME_H__
#define __LINE_IN_TIME_H__


#include "Utils.h"


class CLineInTime
{
public:
	CLineInTime();

	void Initialize(float t0/*ms*/, float y0, float t1/*ms*/, float y1, BOOL bReset);
	void SetResolution(float tRes/*ms*/, float yRes) { m_tRes = tRes; m_yRes = yRes; }
	void LoadAccumulator(float acc) { m_y = m_yAcc = acc; }

	float Clock();

	inline void Start() { m_bDone = FALSE; }
	inline BOOL IsFinished() { return m_bDone; }

private:
	float m_t0;
	float m_t1;
	float m_tRes;

	float m_s;
	float m_ds;
	float m_sStep;

	float m_y;
	float m_dy;
	float m_y0;
	float m_y1;
	float m_yRes;
	float m_yAcc;

	BOOL m_bUp;
	BOOL m_bDone;
	//void CalculateDy() { m_dy = (m_y0-m_y1)/((m_t0-m_t1)*m_sampleRate); }
};


#endif // __LINE_IN_TIME_H__
