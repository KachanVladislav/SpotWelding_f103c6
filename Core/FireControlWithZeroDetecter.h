#pragma once
#include "PinDescription.h"

class FireControlWithZeroDetecter
{
	PIN_DESCRIPTION firePin;
	enum class FIRE_STAGE
	{
		IDLE,
		WAIT_ZERO,
		FIERING
	} fireState = FIRE_STAGE::IDLE;
	uint32_t fireTime;
	uint32_t timePassed;
	const uint32_t ZERO_DETECTER_PERIOD = 10;
public:
	FireControlWithZeroDetecter(PIN_DESCRIPTION firePin) : firePin(firePin)
	{

	}
	void handleIRQZeroDetecter()
	{
		if(fireState == FIRE_STAGE::FIERING)
		{
			timePassed += ZERO_DETECTER_PERIOD;
			if(timePassed >= fireTime)
			{
				HAL_GPIO_WritePin(firePin.port, firePin.pin, GPIO_PIN_RESET);
				fireState = FIRE_STAGE::IDLE;
			}
		}
		else if(fireState == FIRE_STAGE::WAIT_ZERO)
		{
			fireState = FIRE_STAGE::FIERING;
			timePassed = 0;
			HAL_GPIO_WritePin(firePin.port, firePin.pin, GPIO_PIN_SET);
		}
	}
	void fire(uint32_t fireTime_ms)
	{
		if(fireState == FIRE_STAGE::IDLE)
		{
			fireTime = fireTime_ms;
			fireState = FIRE_STAGE::WAIT_ZERO;
		}
	}
};
