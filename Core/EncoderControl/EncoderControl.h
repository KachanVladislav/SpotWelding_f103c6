#pragma once
#include "../PinDescription.h"

namespace EncoderControl
{
	constexpr PIN_DESCRIPTION PINA{GPIOB, GPIO_PIN_10};
	constexpr PIN_DESCRIPTION PINB{GPIOB, GPIO_PIN_1};

	unsigned const ENCODER_FILTER_MS = 2;

	void processPinAFallingEdgeInterrupt();
	void processTimerElapsed1ms();

	void counterclockwiseCallback();
	void clockwiseCallback();
}
