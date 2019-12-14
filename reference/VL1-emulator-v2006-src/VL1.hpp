//-------------------------------------------------------------------------------------------------------
// VSTPlug GUI AppWizard - VL1
//
// Code is based on example from Steinberg VST SDK 2.3
//-------------------------------------------------------------------------------------------------------

#ifndef __VL1__
#define __VL1__

#pragma warning(disable:4786)

#ifndef __audioeffectx__
#include "audioeffectx.h"
#endif

//#define kVersion  1000

//#include "MidiManager.h"
//#include "VoiceManager.h"
#include "Filters.h"
#include "VL1Program.h"


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
	
	void SetMode(float mode);
	int GetModeI();

private:
	void initProcess();
	void fillProgram(long channel, long prg, MidiProgramName *pMpn);

	CVL1Program m_programs[kNumPrograms];
	//long m_channelPrograms[16];

	float m_sound;
	float m_attack;
	float m_decay;
	float m_sustainLevel;
	float m_sustainTime;
	float m_release;
	float m_vibrato;
	float m_tremolo;
	float m_volume;
	float m_program;
	float m_balance;
	float m_octave;
	float m_tempo;
	float m_tune;
	float m_mode;

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


#endif
