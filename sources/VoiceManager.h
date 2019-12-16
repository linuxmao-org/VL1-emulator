#ifndef __VOICE_MANAGER_H__
#define __VOICE_MANAGER_H__


#include "VL1Defs.h"
#include "Voice.h"
#include "EventManager.h"
#include "WaveSet.h"


class CLcdBuffer;
class CRhythm;


class CVoiceManager : public CEventInput
{
public:
	CVoiceManager();
	CVoiceManager(int numVoices, float sampleRate, int oversampling);
	~CVoiceManager();

	void Setup(CLcdBuffer *lcd, CRhythm *rhythm);

	bool Create(int numVoices, long int adsr, float sampleRate, int oversampling);
	void Destroy();
	void SetParameter(int param, float value);
	void Reset();
	bool IsIdle();
	float Clock();
	void Trigger();
	int GetTrigger() { return m_triggerCounter; }

	// Implementation of CMidiInput class.
	bool ProcessEvent(tEvent& event);

private:
	void Initialize();

	float m_srScaler;
	int m_maxVoice;
	CVoice *m_pVoice;
	int m_maxNote;
	float *m_pNote;
	float m_midiScaler;
	int m_triggerCounter;
	CWaveSet *m_waveSet;
	CLcdBuffer *m_LCD;
	CRhythm *m_rhythm;

	bool NoteOn(char note, char velocity);
	bool NoteOff(char note, char velocity);
};


#endif // __VOICE_MANAGER_H__
