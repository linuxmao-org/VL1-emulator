#ifndef __VOICE_H__
#define __VOICE_H__


#include "Utils.h"
#include "Wave.h"
#include "ADSR.h"
#include "LFO.h"
#include "Filters.h"
#include "EnvelopeShaper.h"


class CSharedData;


class CVoice
{
public:
	CVoice();

	void Setup(CSharedData *pShared);

	void Reset();
	void SetParameter(int param, float value);
	inline bool IsIdle() { return m_vca.IsIdle(); }
	void NoteOn(float frequency, float velocity);
	void NoteOff();

	float Clock();
	void Trigger();

	//inline void Mute() { m_vca.Mute(); }

private:
	void Initialize();
	void SetOutputBuffer();

	bool m_bModulate;
	float m_modulation;
	float m_tune;
	float m_octave;
	float m_phase;
	float m_phaseInc;
	float m_velocity;
	float m_lastSample;
	float m_vibratoScale;

	CWave *m_pWave;
	CAdsr m_vca;
	CLfo m_lfoVibrato;
	CLfo m_lfoTremolo;
	CEnvelopeShaper m_envelopeShaper;

	CBiquadLpf m_lpf;
	CBiquadLpf m_lpf2;
	//CIIR1 m_antialias;

	CSharedData *m_pShared;
};


#endif // __VOICE_H__
