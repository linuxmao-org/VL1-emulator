#include "EventManager.h"


CEventManager::CEventManager()
{
	//Initialize();
	m_eventFifo.clear();
	memset(m_pListener,0,kMaxListeners*sizeof(CEventInput*));
}


CEventManager::~CEventManager()
{
	//Initialize();
}


/*void CEventManager::Initialize()
{
	m_eventFifo.Clear();
	memset(m_pListener,0,kMaxListeners*sizeof(CEventInput*));
}*/


void CEventManager::Register(CEventInput *pListener, char channel)
{
	m_pListener[channel&0xf] = pListener;
}


BOOL CEventManager::AddEvent(tEvent& event)
{
	return AddEventSorted(event);
}


BOOL CEventManager::AddEventSorted(tEvent& event)
{
	if (!m_eventFifo.empty())
	{
		if (m_eventFifo.back().midiEvent.deltaFrames>event.midiEvent.deltaFrames)
		{
			// Insert the event at the right position.
			//TRACE("<CEventManager::AddEventSorted> Inserting event\n");
			for (int i=0; i<m_eventFifo.size(); i++)
			{
				if (m_eventFifo[i].midiEvent.deltaFrames<=event.midiEvent.deltaFrames)
				{
					m_eventFifo.insert(m_eventFifo.end()-i,event);
					break;
				}
			}
		}
		else
		{
			// Add event to the end.
			m_eventFifo.push_back(event);
		}
	}
	else
	{
		// Add event to the end.
		m_eventFifo.push_back(event);
	}

	//TRACE("In: %d - 0x%02x 0x%02x 0x%02x\n",event.midiEvent.deltaFrames,(UCHAR)event.midiEvent.midiData[0],(UCHAR)event.midiEvent.midiData[1],(UCHAR)event.midiEvent.midiData[2]);

	return TRUE;
}


void CEventManager::Clock(long time)
{
	do
	{
		if (m_eventFifo.empty()) break; // Break on fifo empty.
		else
		{
			tEvent event = m_eventFifo.front();
			if (event.midiEvent.deltaFrames<=time)
			{
				// Event is now.
				HandleEvent(event);
				m_eventFifo.pop_front(); // Remove event from fifo.
				//TRACE("Out: 0x%02x 0x%02x 0x%02x\n",(UCHAR)event.midiEvent.midiData[0],(UCHAR)event.midiEvent.midiData[1],(UCHAR)event.midiEvent.midiData[2]);
			}
			else break; // Break if event is in the future.
		}
	}
	while (1);

	// Adjust all remaining events.
	AdjustTime(1);
}


BOOL CEventManager::HandleEvent(tEvent& event)
{
	int i = event.midiEvent.midiData[0] & 0x0f;
	if (m_pListener[i])
	{
		return m_pListener[i]->ProcessEvent(event);
	}
	return FALSE;
}


void CEventManager::AdjustTime(long time)
{
	if (!m_eventFifo.empty())
	{
		if (m_eventFifo.front().midiEvent.deltaFrames>=time)
		{
			tEventDeque::iterator pEvent;
			for (pEvent=m_eventFifo.begin(); pEvent!=m_eventFifo.end(); pEvent++)
			{
				pEvent->midiEvent.deltaFrames -= time;
			}
		}
	}
}
