#include "VoiceManager.h"
#include "LcdBuffer.h"
#include "Rhythm.h"
#include "MidiDefs.h"
#include "Utils.h"
#include <math.h>


#define kMaxPrograms  7


CVoiceManager::CVoiceManager()
{
	Initialize();
}


CVoiceManager::CVoiceManager(int numVoices, float sampleRate, int oversampling)
{
	Initialize();
	Create(numVoices, 0, sampleRate, oversampling);
}


CVoiceManager::~CVoiceManager()
{
	Destroy();
}


void CVoiceManager::Setup(CLcdBuffer *lcd, CRhythm *rhythm)
{
	m_LCD = lcd;
	m_rhythm = rhythm;
}


void CVoiceManager::Initialize()
{
	m_maxVoice = 0;
	m_pVoice = NULL;
	m_maxNote = 128;
	m_pNote = NULL;
	m_midiScaler = 1.0f/127.0f;
	m_triggerCounter = 1;
	m_waveSet = new CWaveSet;
	m_LCD = nullptr;
	m_rhythm = nullptr;
}


bool CVoiceManager::Create(int numVoices, long int adsr, float sampleRate, int oversampling)
{
	Destroy();

	m_pNote = new float[m_maxNote];

	// Make note<->frequency (Hz) table
	float k = 1.059463094359f;	// 12th root of 2
	float freq = 6.875f;	// a
	freq *= k;	// a#
	freq *= k;	// b
	freq *= k;	// c, frequency of midi note 0
	for (int i=0; i<m_maxNote; i++)	// 128 midi notes
	{
		m_pNote[i] = freq;
		freq *= k;
	}

	//InitPrograms(waveSize,adsr);

	CVoice *pVoice = new CVoice[numVoices];
	m_pVoice = pVoice;
	m_maxVoice = numVoices;

	CWaveSet *waveSet = m_waveSet;
	waveSet->Setup(sampleRate, oversampling);

	for (int i=0; i<numVoices; ++i)
	{
		pVoice[i].Setup(waveSet, sampleRate, oversampling);
	}

	return true;
}


void CVoiceManager::Destroy()
{
	Reset();
	m_maxVoice = 0;
	SafeDeleteArray(m_pVoice);
	SafeDeleteArray(m_pNote);
	SafeDelete(m_waveSet);
}


void CVoiceManager::Reset()
{
	for (int i=0; i<m_maxVoice; i++)
	{
		m_pVoice[i].Reset();
	}
}


void CVoiceManager::SetParameter(int param, float value)
{
	for (int i=0; i<m_maxVoice; i++)
	{
		m_pVoice[i].SetParameter(param,value);
	}
}


float CVoiceManager::Clock()
{
	float sample = 0.0f;
	for (int i=0; i<m_maxVoice; i++)
	{
		sample += m_pVoice[i].Clock();
	}
	//sample /= (float)m_maxVoice;
	return sample;
}


void CVoiceManager::Trigger()
{
	m_triggerCounter--;
	if (!m_triggerCounter)
	{
		m_triggerCounter = 8;
		if (m_pVoice)
		{
			for (int i=0; i<m_maxVoice; i++)
			{
				m_pVoice[i].Trigger();
			}
		}
	}
}


bool CVoiceManager::NoteOn(char note, char velocity)
{
	int i = 0;
	if (velocity>0)
	{
		m_pVoice[i].NoteOn(m_pNote[(unsigned char)note],(float)velocity*m_midiScaler);
		m_LCD->ShowNote(note);
	}
	else
	{
		NoteOff(note,velocity);
	}
	return true;
}


bool CVoiceManager::NoteOff(char note, char velocity)
{
	if (note<0)
	{
		for (int i=0; i<m_maxVoice; i++)
		{
			m_pVoice[i].NoteOff();
		}
	}
	else
	{
		int i = 0;
		m_pVoice[i].NoteOff();
	}
	return true;
}


/////////////////////////////////////////////////////////////////
// Implementation of CEventInput class.
/////////////////////////////////////////////////////////////////

bool CVoiceManager::ProcessEvent(tEvent& event)
{
	unsigned char value0 = (unsigned char) event.midiEvent.midiData[0];
	unsigned char value1 = (unsigned char) event.midiEvent.midiData[1];
	unsigned char value2 = (unsigned char) event.midiEvent.midiData[2];
	//unsigned char value3 = (unsigned char) event.midiEvent.midiData[3];

	//TRACE("<CVoiceManager::ProcessEvent> Event %02x %02x %02x %02x\n",value0,value1,value2,value3);

	switch (value0&0xf0)
	{
		case kNoteOff:
			//TRACE("Note off: %02x %02x\n",value1&0x7f,value2&0x7f);
			#pragma message("TODO report note-off event to editor")
			return NoteOff(value1&0x7f,value2&0x7f);

		case kNoteOn:
			//TRACE("Note on : %02x %02x\n",value1&0x7f,value2&0x7f);
			#pragma message("TODO report note-on event to editor")
			return NoteOn(value1&0x7f,value2&0x7f);

		case kPolyphonicKeyPressure:
			value1 &= 0x7f; // note
			value2 &= 0x7f; // aftertouch
			break;

		case kControlChange:
		{
			switch (value1)
			{
				case kModulationWheel:
				{
					// use value2;
				}
				break;

				case kBreathControl:
				{
					// use value2;
				}
				break;

				case kChannelVolume:
				{
					// use value2;
				}
				break;

				case kDamperPedal:
				{
					// use value2;
				}
				break;

				case kRhythm:
				{
					m_rhythm->SelectRhythm(value2);
				}
				break;

				case kRhythmOn:
				{
					m_rhythm->Play(value2);
				}
				break;

				case kRhythmOff:
				{
					m_rhythm->Stop();
				}
				break;

				case kSequencerStart:
				{
					//m_savedProgram = GetProgram();
				}
				break;

				case kSequencerStop:
				{
					//MuteAll();
					//SetProgram(m_savedProgram);
					//m_LCD.SetTempo(gClock.GetTempo());
				}
				break;

				case kAllSoundOff: // All sound off.
				case kResetAll: // Reset all controllers.
				case kLocalControl: // Local control on/off.
				case kAllNotesOff: // All notes off.
				case kOmniOff: // Omni mode off (+ all notes off).
				case kOmniOn: // Omni mode on (+ all notes off).
				case kPolyOff: // Poly mode off (+ all notes off).
				case kPolyOn: // Poly mode on (+ all notes off).
					return NoteOff(-1,0);
			}
		}
		break;

		// jpc: disabled program change handling for LV2 support //

		/*
		case kProgramChange:
		{
			TRACE("Program change: %02x\n",value1);
			if (m_pEffect) ((CVL1Edit*)m_pEffect)->setParameter(kProgram,(float)value1/5.0f);
			//SetProgram((int)value1);
		}
		break;
		*/

		case kChannelPressure:
		{
			// use value1;
		}
		break;

		case kPitchBend:
		{
			//float value = (float)value2*128.0f + (float)value1;
		}
		break;
	}

	return false;
}


bool CVoiceManager::IsIdle()
{
	for (int i=0; i<m_maxVoice; i++)
	{
		if (!m_pVoice[i].IsIdle()) return false;
	}
	return true;
}
