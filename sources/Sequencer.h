#ifndef __SEQUENCER_H__
#define __SEQUENCER_H__


#include "Utils.h"
#include "EventManager.h"
#include "Clock.h"


extern float gSampleRate;


// Sequencer constants
enum
{
	// Flags.
	kTimeInMs = 0x00000001,

	// Constants
	kMaxSongLength = 100,
};



typedef struct
{
	float time; // in ms or in note length
	unsigned char midi[4];
	unsigned int flags;
}
tSequencerEvent;


typedef struct
{
	tSequencerEvent data[kMaxSongLength+1];
	int maxEvents;
	int currentEvent;
	int lastEvent;
}
tSequencerEventArrayState;


class CSequencerEventArray
{
public:
	CSequencerEventArray(int maxEvents=kMaxSongLength);
	~CSequencerEventArray();

	void Clear();
	bool AddEvent(tSequencerEvent event);
	bool RemoveCurrentEvent();

	inline bool IsEmpty() { return m_state.lastEvent==0; }
	inline bool IsFull() { return m_state.lastEvent>=m_state.maxEvents; }
	inline int GetSize() { return m_state.lastEvent; }

	inline tSequencerEvent *GetData() { return m_state.data; }

	void Retime(int start, float newTime);
	void MoveInTime(int first, int last, float timeShift);

	void GetState(tSequencerEventArrayState& state) { state = m_state; }
	void SetState(tSequencerEventArrayState& state) { m_state = state; }

	inline void SetCurrentEventPointer(int i) { m_state.currentEvent = i; }

	void TraceEvents(int start=0);

private:
	tSequencerEventArrayState m_state;
};



typedef struct
{
	bool bIsPlaying;
	bool bPaused;
	int songPointer;
	//long time;
	//long startTime;
	tSequencerEventArrayState song;
}
tSequencerState;



class CSequencer
{
public:
	CSequencer();
	~CSequencer();

	void Setup(CEventManager* pEventManager);

	void Reset();
	inline void Clear()
		{
			m_song.Clear();
			SetDirty(false);
			SetRecording(true);
		}

	inline bool IsDirty() { return m_bDirty; }
	inline void SetDirty(bool bDirty) { m_bDirty = bDirty; }

	bool AddEvent(tSequencerEvent& event);
	bool RemoveEvents(int count);

	inline bool IsRecording() { return m_bRecording; }
	inline void SetRecording(bool bRecording) { m_bRecording = bRecording; }

	inline int GetSize() { return m_song.GetSize(); }
	inline bool IsFull() { return m_song.IsFull(); }
	inline bool IsEmpty() { return m_song.IsEmpty(); }

	void LoadSong(tSequencerEvent *pSong=nullptr);

	void Play();
	inline bool IsPlaying() { return m_state.bIsPlaying; }
	void Pause(bool bPause);
	inline void SetPause(bool bPause) { m_state.bPaused = bPause; }
	inline bool IsPaused() { return m_state.bPaused; }
	void Stop();
	void Rewind();

	bool Clock();
	void SetTime(long time) { m_time = time; }
	bool Step(bool bRetime=false);

	void DoEvent(const tSequencerEvent& event);
	bool GotoEvent(int event, bool bWrap=true);
	void StopEvent(tSequencerEvent& event);

	void GetState(tSequencerState& state);
	void SetState(tSequencerState& state);

	inline int GetSongPointer() { return m_state.songPointer; }
	inline tSequencerEvent& GetEvent(int i) { return (m_song.GetData())[i]; }

private:
	CSequencerEventArray m_song;
	tSequencerState m_state;
	bool m_bDirty;
	bool m_bRecording;

	inline int ScaleTime(float time, bool bInMs)
	{
		if (bInMs) return (int)(0.001f*time*gSampleRate); // to samples
		else return (int)(time*(float)gClock.GetTempoPeriod());
	}

	//inline void ResetRecTime() { m_state.startTime = gClock.GetTickCount(); }
	inline void ResetRecTime() { m_startTime = gClock.GetMsCount(); }

	inline float GetRecTime() // In ms.
	{
		//return 1000.0f*(gClock.GetTickCount()-m_state.startTime)/gSampleRate;
		return (gClock.GetMsCount()-m_startTime);
	}

	inline void IncSongPointer()
		{ SetSongPointer(m_state.songPointer+1); }

	inline void DecSongPointer()
		{ SetSongPointer(m_state.songPointer-1); }

	inline void SetSongPointer(int i)
		{
			m_state.songPointer = i>=0? i : 0;
			m_song.SetCurrentEventPointer(m_state.songPointer);
			TRACE("song pointer = %d\n",m_state.songPointer);
		}

	long m_time;
	long m_startTime;
	tSequencerEvent *m_pSong;
	tEvent m_event;

	CEventManager* m_pEventManager;
};


#endif // __SEQUENCER_H__
