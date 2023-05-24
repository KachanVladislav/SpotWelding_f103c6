#pragma once
#include <cstdint>

class FireTimeControl
{
	uint32_t currentTime_ms = 10;
	const uint32_t MAX_TIME = 9900;
	uint32_t getDeltaForCurrentTimeIncrement()
	{
		return getDeltaForTimeDirectioned(currentTime_ms + 1);
	}
	uint32_t getDeltaForCurrentTimeDecrement()
	{
		return getDeltaForTimeDirectioned(currentTime_ms - 1);
	}
	uint32_t getDeltaForTimeDirectioned(uint32_t timeDirection)
	{
		if(timeDirection < 200)
			return 10;
		if(timeDirection < 500)
			return 20;
		if(timeDirection < 1000)
			return 50;
		return 100;
	}
public:
	void incrementTime()
	{
		currentTime_ms += getDeltaForCurrentTimeIncrement();
		if(currentTime_ms > MAX_TIME)
			currentTime_ms = MAX_TIME;
	}
	void decrementTime()
	{
		auto delta = getDeltaForCurrentTimeDecrement();
		if(currentTime_ms < delta)
			currentTime_ms = 0;
		else
			currentTime_ms -= delta;
	}
	uint32_t getCurrentTime_ms()
	{
		return currentTime_ms;
	}
};
