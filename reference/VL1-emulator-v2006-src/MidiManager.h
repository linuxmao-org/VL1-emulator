#ifndef __MIDI_MANAGER_H__
#define __MIDI_MANAGER_H__


#include "Utils.h"
#include "MidiDefs.h"

#include <deque>
using namespace std;


class CMidiInput
{
public:
	virtual long NoteOn(float, float velocity) = 0;
	virtual long NoteOff(float note, float velocity) = 0;
};


enum
{
	kEventNone = 0,
	kEventNoteOn,
	kEventNoteOff,
	kEventAllNotesOff,
	kEventPedal,
	kEventProgramChange,
	kEventChannelPressure,
	kEventPitchBend,
	kEventModulation,
	kEventBreathControl,
	kEventChannelVolume,
	kEventVolume,
};


typedef struct
{
	long timestamp;
	int type;
	int channel;
	float value1;
	float value2;
}
tMidiEvent;


typedef	deque<tMidiEvent> tEventDeque;


class CMidiManager
{
public:
	CMidiManager();
	~CMidiManager();

	void Register(CMidiInput *pClass, int channel);

	BOOL AddEvent(long timestamp, unsigned char *pMidiData, int dataSize);
	void AdjustTime(long time);
	void Clock(long time);

private:
	tEventDeque m_eventFifo;
	void AddEventSorted(tMidiEvent& event);
	void HandleEvent(tMidiEvent& event);
	CMidiInput *m_pClass;
};


// The global MIDI handler.
extern CMidiManager gMidi;


typedef auto_ptr<CMidiManager> tPMidiManager;


/*class CMidiManagerPtr
{
public:
	CMidiManagerPtr() : m_pObj(NULL) { m_pObj = new CMidiManager; }
	~CMidiManagerPtr() { if (m_pObj) { delete m_pObj; m_pObj = NULL; } }
	CMidiManager *m_pObj;
};*/


#endif // __MIDI_MANAGER_H__
