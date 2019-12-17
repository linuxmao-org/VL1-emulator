#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__


#include "Utils.h"
#include <vector>


typedef struct
{
	unsigned char midiData[4];
}
tMidiEvent;

typedef struct
{
	tMidiEvent midiEvent;
	//long int program;
}
tEvent;


class CEventInput
{
public:
	virtual bool ProcessEvent(const tEvent &event) = 0;
};


class CEventManager
{
public:
	CEventManager();
	~CEventManager();

	void Register(CEventInput *pListener);

	void SendEvent(const tEvent &event);

private:
	std::vector<CEventInput *> m_pListener;

	//void Initialize();
};


#endif // __EVENT_MANAGER_H__
