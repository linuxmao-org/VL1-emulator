/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#ifndef __NOISE_H__
#define __NOISE_H__


class CNoise
{
public:
	CNoise();

	void Set(int length=16 /*bits*/, int mask=0x1d87);
	int Clock();

private:
	unsigned int m_shiftRegister;
	int m_length;
	int m_mask;
};


#endif // __NOISE_H__
