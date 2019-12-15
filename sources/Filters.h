#ifndef __FILTERS_H__
#define __FILTERS_H__


#include "Utils.h"


class CCascadedResonantLpHp
{
public:
	CCascadedResonantLpHp();
	~CCascadedResonantLpHp();

	float Clock(float sample, float lpc, float lpr, float hpc, float hpr);

private:
	float m_delay1;
	float m_delay2;
	float m_delay3;
	float m_delay4;
};


class CIIR1
{
public:
	CIIR1();

	void SetCutoff(float fc, float sampleRate);
	inline void Initialize(float value) { m_delay = value; }
	float Clock(float sample);

private:
	float m_delay;
	float m_k;
	float m_l;
};


class CIIR2
{
public:
	CIIR2();

	float Clock(float sample);

	float m_a0;
	float m_a1;
	float m_a2;
	float m_b1;
	float m_b2;

private:
	float m_i1;
	float m_i2;
	float m_o1;
	float m_o2;
};


class CBiquad
{
public:
	CBiquad();

	virtual void SetCutoff(float fc, float sampleRate);
	virtual void SetQ(float Q) { m_Q = Q; }
	virtual void SetGain(float gain) { m_dbGain = gain; }
	virtual void SetShelve(float S) { m_S = S; }

	virtual float Clock(float sample);

protected:
	float m_a1;
	float m_a2;
	float m_b0;
	float m_b1;
	float m_b2;
	float m_xn1;
	float m_xn2;
	float m_yn1;
	float m_yn2;
	float m_Q;
	float m_A;
	float m_S;
	float m_w0;
	float m_cosw0;
	float m_sinw0;
	float m_alpha;
	float m_dbGain;
	float m_gain;
};


class CBiquadLpf : public CBiquad
{
public:
	void SetCutoff(float fc, float sampleRate);
	void SetChebychef1();
	void SetChebychef2();
	void SetButterworth1();
	void SetButterworth2();
	float Clock2(float xn);
};


#endif // __FILTERS_H__
