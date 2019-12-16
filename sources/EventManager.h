#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__


#include "Utils.h"


typedef struct
{
	unsigned char midiData[4];
	unsigned frameTime;
}
tMidiEvent;

typedef struct
{
	tMidiEvent midiEvent;
	//long int program;
}
tEvent;


#include <deque>
using namespace std;
typedef	deque<tEvent> tEventDeque;


class CEventInput
{
public:
	virtual bool ProcessEvent(tEvent& event) = 0;
};


#define kMaxListeners  16 // For 16 midi channels.


class CEventManager
{
public:
	CEventManager();
	~CEventManager();

	void Register(CEventInput *pListener, char channel);

	bool AddEvent(tEvent& event);
	void AdjustTime(long time);
	void Clock(long time);

private:
	tEventDeque m_eventFifo;
	bool AddEventSorted(tEvent& event);
	bool HandleEvent(tEvent& event);
	CEventInput *m_pListener[kMaxListeners];

	//void Initialize();
};


#endif // __EVENT_MANAGER_H__
