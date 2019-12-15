#ifndef __ENVELOPE_SHAPER_H__
#define __ENVELOPE_SHAPER_H__


class CEnvelopeShaper
{
public:
	CEnvelopeShaper();

	void Setup(float sampleRate, int oversampling);
	float Clock(float in);

private:
	float m_cap;
	float m_vCap;
	float m_rCharge;
	float m_rDischarge;

	float m_sampleRate;
	int m_oversampling;
};


#endif // __ENVELOPE_SHAPER_H__
