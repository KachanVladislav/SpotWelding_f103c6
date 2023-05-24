#pragma once
#include "stm32f1xx_hal.h"
#include "../PinDescription.h"

class ButtonInterruptControl
{
	PIN_DESCRIPTION pinDescription;
	bool zeroStatePressed = true;
	const uint32_t filterTime = 3;
	uint32_t currentFilterTime = 3;
	void(*pressedCallback)();

public:
	ButtonInterruptControl(PIN_DESCRIPTION pinDescription, void(*pressedCallback)())
				: pinDescription(pinDescription),
				  pressedCallback(pressedCallback){}

	void proccesIRQFalinEdge()
	{
		currentFilterTime = 0;
	}

	void procesTimeout()
	{
		if(currentFilterTime < filterTime)
		{
			if(++currentFilterTime == filterTime)
			{
				if(isButtonPressed())
				{
					pressedCallback();
				}
			}
		}
	}

private:
	bool isButtonPressed()
	{
		if(zeroStatePressed)
			return HAL_GPIO_ReadPin(pinDescription.port, pinDescription.pin) == GPIO_PIN_RESET;
		else
			return HAL_GPIO_ReadPin(pinDescription.port, pinDescription.pin) == GPIO_PIN_SET;
	}
};
