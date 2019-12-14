#ifndef __VOICE_MANAGER_H__
#define __VOICE_MANAGER_H__


#include "VL1Defs.h"
#include "Voice.h"
#include "EventManager.h"


class CVL1;


class CVoiceManager : public CEventInput
{
public:
	CVoiceManager();
	CVoiceManager(int numVoices);
	~CVoiceManager();

	BOOL Create(int numVoices, long int adsr=0, CVL1 *pEffect=NULL);
	void Destroy();
	void SetParameter(int param, float value);
	void Reset();
	BOOL IsIdle();
	float Clock();
	void Trigger();
	int GetTrigger() { return m_triggerCounter; }

	// Implementation of CMidiInput class.
	BOOL ProcessEvent(tEvent& event);

private:
	void Initialize();

	CVL1 *m_pEffect;
	float m_srScaler;
	int m_maxVoice;
	CVoice *m_pVoice;
	int m_maxNote;
	float *m_pNote;
	float m_midiScaler;
	int m_triggerCounter;

	BOOL NoteOn(char note, char velocity);
	BOOL NoteOff(char note, char velocity);
};


#endif // __VOICE_MANAGER_H__
