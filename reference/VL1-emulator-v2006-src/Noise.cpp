#include "Noise.h"


CNoise::CNoise() :
	m_shiftRegister(0),
	m_length(0),
	m_mask(0)
{
	Set(16,0x1d87);
}


void CNoise::Set(int length, int mask)
{
	m_length = length;
	m_mask = mask;
}


int CNoise::Clock()
{
	/*int noise = m_shiftRegister&0x8000? 1 : 0;
	m_shiftRegister <<= 1;
	m_shiftRegister ^= m_mask;
	m_shiftRegister &= 0xffff;
	return noise;*/

	/*while (m_shiftRegister&0x8000)
	{
		m_shiftRegister <<= 1;
		m_shiftRegister ^= m_mask;
		m_shiftRegister &= 0xffff;
	}
	return m_shiftRegister&1;*/

	int newBit = m_shiftRegister & 0x8000? 1 : 0;
	newBit ^= m_shiftRegister & 0x4000? 1 : 0;
	newBit ^= m_shiftRegister & 0x1000? 1 : 0;
	newBit ^= m_shiftRegister & 0x0008? 1 : 0;
	newBit = newBit? 0 : 1;

	m_shiftRegister <<= 1;
	m_shiftRegister |= newBit;
	m_shiftRegister &= 0xffff;
	return m_shiftRegister&0x8000? 1 : 0;
}

