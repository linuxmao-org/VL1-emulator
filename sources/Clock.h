#pragma once

#pragma message("TODO fake Clock object, implement it later")

#define gClock (CClock::Instance())

enum
{
	kClockSequencer = 1,
};

class CClock
{
public:
	static CClock &Instance()
	{
		static CClock clock;
		return clock;
	}

	long GetTickCount() { return 0; }
	long GetMsCount() { return 0; }

	float GetTempo() const { return 0; }
	int GetTempoPeriod() { return 0; }

	void EnableClock(int, bool) {}
	void DisableAllClocks() {}
};
