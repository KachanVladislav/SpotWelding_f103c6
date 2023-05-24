#include "EncoderControl.h"

namespace EncoderControl
{
	unsigned encoderFilterCounter = ENCODER_FILTER_MS;

	void processPinAFallingEdgeInterrupt()
	{
		encoderFilterCounter = 0;
	}

	static void processFilteredFallingEdge();
	void processTimerElapsed1ms()
	{
		if(encoderFilterCounter < ENCODER_FILTER_MS)
		{
			if(++encoderFilterCounter >= ENCODER_FILTER_MS)
			{
				if(HAL_GPIO_ReadPin(PINA.port, PINA.pin) == GPIO_PIN_RESET)
				{
					processFilteredFallingEdge();
				}
			}
		}
	}

	void processFilteredFallingEdge()
	{
		if(HAL_GPIO_ReadPin(PINB.port, PINB.pin) == GPIO_PIN_RESET)
			clockwiseCallback();
		else
			counterclockwiseCallback();
	}
}

