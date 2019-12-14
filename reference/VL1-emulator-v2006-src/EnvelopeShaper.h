#ifndef __ENVELOPE_SHAPER_H__
#define __ENVELOPE_SHAPER_H__


class CEnvelopeShaper
{
public:
	CEnvelopeShaper();

	float Clock(float in);

private:
	float m_cap;
	float m_vCap;
	float m_rCharge;
	float m_rDischarge;
};


#endif // __ENVELOPE_SHAPER_H__
