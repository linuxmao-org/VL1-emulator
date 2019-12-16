#include "Sequencer.h"
#include "SharedData.h"
#include "MidiDefs.h"
#include <string.h>


const tSequencerEvent gStopRhythm = { 0, { kControlChange, kRhythmOff, 0, 0 }, 0 };
const tSequencerEvent gStopNotes = { 0, { kControlChange, kAllNotesOff, 0, 0 }, 0 };
const tSequencerEvent gSequencerStart = { 0, { kControlChange, kSequencerStart, 0, 0 }, 0 };
const tSequencerEvent gSequencerStop = { 0, { kControlChange, kSequencerStop, 0, 0 }, 0 };


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


CSequencerEventArray::CSequencerEventArray(int maxEvents)
{
	m_state.maxEvents = maxEvents;
	Clear();
}


CSequencerEventArray::~CSequencerEventArray()
{
}


void CSequencerEventArray::Clear()
{
	m_state.currentEvent = 0;
	m_state.lastEvent = 0;
	memset(m_state.data,0,sizeof(m_state.data));
	m_state.data[m_state.maxEvents].time = -1;
	m_state.data[0].time = -1;
}


bool CSequencerEventArray::AddEvent(tSequencerEvent event)
{
	if (IsFull()) return false;

	if (m_state.currentEvent<m_state.lastEvent)
	{
		// Insert event memory-wise by shifting memory up.
		memmove(&m_state.data[m_state.currentEvent+1],&m_state.data[m_state.currentEvent],(m_state.lastEvent-m_state.currentEvent)*sizeof(tSequencerEvent));
		// Insert event time-wise.
		event.time = m_state.data[m_state.currentEvent+1].time;
		MoveInTime(m_state.currentEvent+1,m_state.lastEvent+1,50.0f);
	}
	m_state.data[m_state.currentEvent] = event;
	m_state.currentEvent++;
	m_state.lastEvent++;
	m_state.data[m_state.lastEvent].time = -1;

	TraceEvents();

	return true;
}


bool CSequencerEventArray::RemoveCurrentEvent()
{
	int prev = m_state.currentEvent - 1;
	if (prev<0) return false;
	if (prev<m_state.lastEvent)
	{
		float dt = m_state.data[m_state.currentEvent].time - m_state.data[prev].time;
		// First delete event time-wise.
		MoveInTime(m_state.currentEvent,m_state.lastEvent,-dt);
		// Delete one event by shifting memory down.
		memmove(&m_state.data[prev],&m_state.data[m_state.currentEvent],(m_state.lastEvent-m_state.currentEvent)*sizeof(tSequencerEvent));
	}
	m_state.currentEvent = prev;
	if (m_state.lastEvent>1) m_state.lastEvent -= 1;
	m_state.data[m_state.lastEvent].time = -1;

	TraceEvents();

	return true;
}


void CSequencerEventArray::Retime(int start, float newTime)
{
	float offset = newTime - m_state.data[start].time;
	for (int i=start; i<m_state.lastEvent; i++)
	{
		m_state.data[i].time += offset;
	}
}


void CSequencerEventArray::MoveInTime(int first, int last, float timeShift)
{
	for (int i=first; i<last; i++)
	{
		m_state.data[i].time += timeShift;
		if (m_state.data[i].time<0.0f) m_state.data[i].time = 0.0f;
	}
}


void CSequencerEventArray::TraceEvents(int start)
{
	TRACE("*** Begin event dump\n");
	for (int i=start; i<m_state.lastEvent; i++)
	{
		TRACE("Event %02d - %05.f: %s %d\n",i,m_state.data[i].time,m_state.data[i].midi[0]==0x90?" on":"off",m_state.data[i].midi[1]);
	}
	TRACE("*** End event dump\n");
}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


CSequencer::CSequencer() :
	m_bDirty(false),
	m_pShared(nullptr)
{
	Clear();
	Reset();
}


CSequencer::~CSequencer()
{
}


void CSequencer::Setup(CSharedData *pShared)
{
	m_pShared = pShared;
}


void CSequencer::Reset()
{
	TRACE("CSequencer::Reset\n");
	memset(&m_event,0,sizeof(m_event));
	Rewind();
	m_startTime = 0;
	m_pSong = m_song.GetData();
	m_state.bIsPlaying = false;
	m_state.bPaused = true;
}


void CSequencer::LoadSong(tSequencerEvent *pSong)
{
	if (pSong) m_pSong = pSong;
	else m_pSong = m_song.GetData();
	Rewind();
}


bool CSequencer::AddEvent(tSequencerEvent& event)
{
	if (m_song.IsFull())
	{
		return false;
	}

	// Timestamp event
	if (!m_song.GetSize()) ResetRecTime();
	event.time = GetRecTime();
	event.flags |= kTimeInMs;

	if (m_song.AddEvent(event))
	{
		// Make sure that we stay synchronised to the next event.
		IncSongPointer();
		m_time = m_pSong[m_state.songPointer].time;
		SetDirty(true);
		return true;
	}
	return false;
}


bool CSequencer::RemoveEvents(int count)
{
	if (m_song.GetSize())
	{
		for (int i=0; i<count; i++)
		{
			m_song.RemoveCurrentEvent();
			DecSongPointer();
		}
		return true;
	}
	return false;
}


void CSequencer::Play()
{
	TRACE("CSequencer::Play\n");
	if (m_pSong)
	{
		m_state.bIsPlaying = true;
		m_pShared->clock->EnableClock(kClockSequencer,true);
	}
}


void CSequencer::Pause(bool bPause)
{
	TRACE("CSequencer::Pause\n");
	m_state.bPaused = bPause;
	if (m_state.bPaused)
	{
		DoEvent((tSequencerEvent)gStopNotes);
	}
}


void CSequencer::Stop()
{
	TRACE("CSequencer::Stop\n");
	Pause(true);
	m_pShared->clock->EnableClock(kClockSequencer,false);
	Rewind();
}


void CSequencer::Rewind()
{
	TRACE("CSequencer::Rewind\n");
	m_state.bIsPlaying = false;
	m_state.bPaused = false;
	SetSongPointer(0);
	m_time = 0;
}


void CSequencer::DoEvent(const tSequencerEvent& event)
{
	TRACE("CSequencer::DoEvent\n");
	memcpy(m_event.midiEvent.midiData,event.midi,4*sizeof(char));
	m_pShared->eventManager->AddEvent(m_event);
}


bool CSequencer::GotoEvent(int event, bool bWrap)
{
	TRACE("CSequencer::GotoEvent\n");
	while (m_pSong[m_state.songPointer].midi[0]!=(unsigned char)event)
	{
		if (m_pSong[m_state.songPointer].time<0)
		{
			// End of song.
			if (!bWrap) return false;
			else Rewind();
		}
		else
		{
			IncSongPointer();
		}
	}

	//m_state.time = ScaleTime(m_pSong[m_state.songPointer].time,m_pSong[m_state.songPointer].flags&kTimeInMs);
	m_time = m_pSong[m_state.songPointer].time;

	return true;
}


bool CSequencer::Clock()
{
	if (m_state.bPaused) return true;

	m_time++;

	//while (m_state.time>=ScaleTime(m_pSong[m_state.songPointer].time,m_pSong[m_state.songPointer].flags&kTimeInMs))
	while (m_time>=m_pSong[m_state.songPointer].time)
	{
		if (!Step()) return false;
	}

	return true;
}


bool CSequencer::Step(bool bRetime)
{
	if (m_pSong[m_state.songPointer].time<0)
	{
		// End of song.
		m_state.bIsPlaying = false;
		return false;
	}

	if (bRetime)
	{
		if (m_state.songPointer==0) ResetRecTime();
		m_song.Retime(m_state.songPointer,GetRecTime());
	}

	DoEvent(m_pSong[m_state.songPointer]);
	IncSongPointer();

	return true;
}


void CSequencer::GetState(tSequencerState& state)
{
	m_song.GetState(m_state.song);
	state = m_state;
}


void CSequencer::SetState(tSequencerState& state)
{
	m_state = state;
	m_song.SetState(m_state.song);
	if (IsEmpty())
	{
		Clear();
	}
}

int CSequencer::ScaleTime(float time, bool bInMs)
{
	if (bInMs) return (int)(0.001f*time*m_pShared->sampleRate); // to samples
	else return (int)(time*(float)m_pShared->clock->GetTempoPeriod());
}

void CSequencer::ResetRecTime()
{
	//m_state.startTime = m_pShared->clock->GetTickCount();
	m_startTime = m_pShared->clock->GetMsCount();
}

float CSequencer::GetRecTime()
{
	//return 1000.0f*(m_pShared->clock->GetTickCount()-m_state.startTime)/gSampleRate;
	return (m_pShared->clock->GetMsCount()-m_startTime);
}
