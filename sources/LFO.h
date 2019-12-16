#ifndef __LFO_H__
#define __LFO_H__


#include "Utils.h"


class CSharedData;


#define kLfoBaseFreq  35.0f


class CLfo
{
public:
	CLfo();
	~CLfo();

	void Setup(CSharedData *pShared);

	void SetFrequency(float freq);
	void SetDcLevel(float dc) { m_dc = dc; }

	void Reset();
	void Enable(bool bEnable) { m_bEnable = bEnable; }
	bool IsEnabled() { return m_bEnable; }

	float Clock();

private:
	//float oversampling;
	float m_frequency;
	float m_sin;
	float m_cos;
	float m_a;
	float m_dc;
	bool m_bEnable;

	CSharedData *m_pShared;

	void ResetSine();
	float ClockSine();
};


#endif // __LFO_H__
