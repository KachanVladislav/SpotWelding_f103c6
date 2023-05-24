#pragma once
#include <cstdint>

class ZeroDetecterPulseMiddleFinder
{
	uint32_t lastPulseTime = 10;
	uint32_t currentPulseTime = 0;
	bool isPulseGoing = false;
	bool isMidlePulseCallbackGenerated = false;
	void(*midlePulseTimeCallback)();
public:
	ZeroDetecterPulseMiddleFinder(void(*midlePulseTimeCallback)()) : midlePulseTimeCallback(midlePulseTimeCallback){}
	void handle01msIRQ()
	{
		currentPulseTime++;
		if(isPulseGoing && !isMidlePulseCallbackGenerated)
		{
			if(2 * currentPulseTime > lastPulseTime)
			{
				isMidlePulseCallbackGenerated = true;
				midlePulseTimeCallback();
			}
		}

	}
	void handleRisingEdge()
	{
		currentPulseTime = 0;
		isPulseGoing = true;
		isMidlePulseCallbackGenerated = false;
	}
	void handleFallinEdge()
	{
		isPulseGoing = false;
		lastPulseTime = currentPulseTime;
	}
};
