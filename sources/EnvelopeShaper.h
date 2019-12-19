/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#ifndef __ENVELOPE_SHAPER_H__
#define __ENVELOPE_SHAPER_H__


class CSharedData;


class CEnvelopeShaper
{
public:
	CEnvelopeShaper();

	void Setup(CSharedData *pShared);
	float Clock(float in);

private:
	float m_cap;
	float m_vCap;
	float m_rCharge;
	float m_rDischarge;

	CSharedData *m_pShared;
};


#endif // __ENVELOPE_SHAPER_H__
