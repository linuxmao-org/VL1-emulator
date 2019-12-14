#include "MidiManager.h"


// The global MIDI handler.
CMidiManager gMidi;


CMidiManager::CMidiManager() :
	m_pClass(NULL)
{
}


CMidiManager::~CMidiManager()
{
	m_pClass = NULL;
}


void CMidiManager::Register(CMidiInput *pClass, int channel)
{
	m_pClass = pClass;
}


BOOL CMidiManager::AddEvent(long timestamp, unsigned char *pMidiData, int dataSize)
{
	tMidiEvent event;
	event.type = kEventNone;
	event.channel = pMidiData[0] & 0x0f;
	event.timestamp = timestamp;

	long status = pMidiData[0] & 0xf0;

	//TRACE("<CMidiManager::AddEvent> Event %02x %02x %02x %02x\n",pMidiData[0],pMidiData[1],pMidiData[2],pMidiData[3]);

	switch (status)
	{
		case kNoteOff:
		{
			event.type = kEventNoteOff;
			event.value1 = pMidiData[1] & 0x7f; // note
			event.value2 = pMidiData[2] & 0x7f; // velocity
		}
		break;

		case kNoteOn:
		{
			event.type = kEventNoteOn;
			event.value1 = pMidiData[1] & 0x7f; // note
			event.value2 = pMidiData[2] & 0x7f; // velocity
		}
		break;

		case kPolyphonicKeyPressure:
		{
			event.type = kEventNoteOn;
			event.value1 = pMidiData[1] & 0x7f; // note
			event.value2 = pMidiData[2] & 0x7f; // aftertouch
		}
		break;

		case kControlChange:
		{
			char function = pMidiData[1];

			switch (function)
			{
				case 0x01: // Modulation wheel.
				{
					event.type = kEventModulation;
					event.value1 = (float)pMidiData[2];
				}
				break;

				case 0x02: // Breath control.
				{
					event.type = kEventBreathControl;
					event.value1 = (float)pMidiData[2];
				}
				break;

				case 0x07: // Channel volume.
				{
					event.type = kEventChannelVolume;
					event.value1 = (float)pMidiData[2];
				}
				break;

				case 0x40: // Damper pedal on/off.
				{
					event.type = kEventPedal;
					event.value1 = (float)pMidiData[2];
				}
				break;

				case 0x78: // All sound off.
				case 0x79: // Reset all controllers.
				case 0x7a: // Local control on/off.
				case 0x7b: // All notes off.
				case 0x7c: // Omni mode off (+ all notes off).
				case 0x7d: // Omni mode on (+ all notes off).
				case 0x7e: // Poly mode off (+ all notes off).
				case 0x7f: // Poly mode on (+ all notes off).
				{
					event.type = kEventAllNotesOff;
					event.value1 = -1.0;
				}
				break;
			}
		}
		break;

		case kProgramChange:
		{
			event.type = kEventProgramChange;
			event.value1 = (float)pMidiData[1];
		}
		break;

		case kChannelPressure:
		{
			event.type = kEventChannelPressure;
			event.value1 = (float)pMidiData[1]; // Aftertouch.
		}
		break;

		case kPitchBend:
		{
			event.type = kEventPitchBend;
			event.value1 = (float)(pMidiData[2]*128 + pMidiData[1]);
		}
		break;
	}

	if (event.type!=kEventNone)
	{
		AddEventSorted(event);
		return TRUE;
	}
	else return FALSE;
}


void CMidiManager::AddEventSorted(tMidiEvent& event)
{
	if (m_eventFifo.size())
	{
		if (m_eventFifo.back().timestamp>event.timestamp)
		{
			// Insert the event at the right position.
			//TRACE("<CMidiManager::AddEventSorted> Inserting event\n");
			for (int i=0; i<m_eventFifo.size(); i++)
			{
				if (m_eventFifo[i].timestamp<=event.timestamp)
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
}


void CMidiManager::Clock(long time)
{
	do
	{
		if (!m_eventFifo.size()) break; // Break on fifo empty.
		else
		{
			tMidiEvent event = m_eventFifo.front();
			if (event.timestamp>time) break; // Break if event is in the (near) future.
			else
			{
				// Event is now.
				HandleEvent(event);
				m_eventFifo.pop_front(); // Remove event from fifo.
			}
		}
	}
	while (1);
}


void CMidiManager::HandleEvent(tMidiEvent& event)
{
	switch (event.type)
	{
		case kEventNone:
		break;

		case kEventNoteOn:
			if (m_pClass) m_pClass->NoteOn(event.value1,event.value2);
		break;

		case kEventNoteOff:
			if (m_pClass) m_pClass->NoteOff(event.value1,event.value2);
		break;

		case kEventAllNotesOff:
			if (m_pClass) m_pClass->NoteOff(event.value1,event.value2);
		break;

		case kEventPedal:
		break;

		case kEventProgramChange:
		break;

		case kEventPitchBend:
		break;

		case kEventModulation:
		break;

		case kEventVolume:
		break;

		case kEventChannelVolume:
		break;
	}
}


void CMidiManager::AdjustTime(long time)
{
	if (m_eventFifo.size())
	{
		if (m_eventFifo.front().timestamp>=time)
		{
			//TRACE("<CMidiManager::AdjustTime> Events are in future\n");
			tEventDeque::iterator pEvent;
			for (pEvent=m_eventFifo.begin(); pEvent!=m_eventFifo.end(); pEvent++)
			{
				pEvent->timestamp -= time;
			}
		}
	}
}
