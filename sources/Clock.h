#pragma once

#pragma message("TODO fake Clock object, implement it later")

#define gClock (CClock::Instance())

class CClock
{
public:
	static CClock &Instance()
	{
		static CClock clock;
		return clock;
	}

	float GetTempo() const
	{
		return 0;
	}
};
