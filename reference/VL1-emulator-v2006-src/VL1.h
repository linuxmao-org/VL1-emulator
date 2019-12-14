#ifndef __VL1_H__
#define __VL1_H__


#pragma warning(disable:4786)


#ifndef __audioeffectx__
#include "audioeffectx.h"
#endif

#include "Filters.h"
#include "VL1Program.h"
#include "LCD.h"
#include "Calculator.h"
#include "Clock.h"
#include "Sequencer.h"


#define kVL1StateVersion  1000

typedef struct
{
	long version;
	long curProgram;
	float mode;
	float program;
	float octave;
	float balance;
	float volume;
	float tempo;
	float tune;
	tLcdState lcd;
	tCalculatorState calculator;
	tClockState clock;
	tSequencerState sequencer;
}
tVL1State;


class CVL1 : public AudioEffectX
{
public:
	CVL1(audioMasterCallback audioMaster);
	~CVL1();

	virtual void process(float **ppInputs, float **ppOutputs, long sampleframes);
	virtual void processReplacing(float **ppInputs, float **ppOutputs, long sampleFrames);
	virtual long processEvents(VstEvents *pEvents);

	virtual void setProgram(long program);
	virtual void setProgramName(char *pName);
	virtual void getProgramName(char *pName);
	virtual bool getProgramNameIndexed(long category, long index, char* text);
	virtual bool copyProgram(long destination);

	virtual bool string2parameter(long index, char* pText);
	virtual void setParameter(long index, float value);
	virtual float getParameter(long index);
	virtual void getParameterLabel(long index, char *pLabel);
	virtual void getParameterDisplay(long index, char *pText);
	virtual void getParameterName(long index, char *pText);
	virtual long getChunk(void **ppData, bool isPreset);
	virtual long setChunk(void *pData, long byteSize, bool isPreset);

	virtual void setSampleRate(float sampleRate);
	virtual void setBlockSize(long blockSize);
	
	virtual void resume();

	virtual bool getOutputProperties(long index, VstPinProperties *pProperties);
	virtual VstPlugCategory getPlugCategory();

	virtual long canDo(char *pText);

	virtual long getMidiProgramName(long channel, MidiProgramName *pMidiProgramName);
	virtual long getCurrentMidiProgram(long channel, MidiProgramName *pCurrentProgram);
	virtual long getMidiProgramCategory(long channel, MidiProgramCategory *pCategory);
	virtual bool hasMidiProgramsChanged(long channel);
	virtual bool getMidiKeyName(long channel, MidiKeyName *pKeyName);
	
	void Reset();
	inline int GetModeI() { return m_modeI; }

	void LoadFactoryPresets();
	void LoadAdsrPreset();
	void HandleKey(int key, float value);

	void ResetAutoPowerOffWatchdog(long timeout=360 /* seconds*/);

private:
	void initProcess();
	void fillProgram(long channel, long prg, MidiProgramName *pMpn);

	CVL1Program m_programs[kNumPrograms];
	//CVL1Program m_bank;

	tVL1State m_state;
	float m_sound;
	float m_attack;
	float m_decay;
	float m_sustainLevel;
	float m_sustainTime;
	float m_release;
	float m_vibrato;
	float m_tremolo;
	//float m_volume;
	//float m_program;
	//float m_balance;
	//float m_octave;
	//float m_tempo;
	//float m_tune;
	//float m_mode;

	int m_modeI;
	BOOL m_bDemoSong;
	BOOL m_bOneKeyPlay;
	BOOL m_bIgnoreNextEvent;
	char m_iniFile[128];

	void OnMode(float value);
	void OnReset();
	void OnDel();
	void OnTempoUp();
	void OnTempoDown();
	void OnRhythm(float value);
	void OnMlc();
	void OnMusic();
	void OnAutoPlay();
	void OnOneKeyPlayDotDot(float value);
	void OnOneKeyPlayDot(float value);

	void TempoUpDown(BOOL bUp);
	void Calculator(int key);
	void AutoPlay();
	void OneKeyPlay();
	void SendKey(int noteOnOff, int note, int velocity);
	BOOL Serialize(BOOL bRead);
	tVL1State *GetState(long& size);
	void SetState(tVL1State *pState);
	void ResetSound();

	double m_scaler;
	double m_phase;
	double m_tuneScaler;

	long m_currentNote;
	long m_currentVelocity;
	long m_currentDelta;
	bool m_bNoteIsOn;

	CIIR1 m_lp1;
	CIIR1 m_lp2;

	//CMidiManager *m_pMidi;
	//tPMidiManager m_pMidi;
	//CVoiceManager m_voices1;
	//CVoiceManager m_voices2;
};


#endif // __VL1_H__
