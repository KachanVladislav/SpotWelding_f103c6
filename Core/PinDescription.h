#pragma once
#include <cstdint>
#include "stm32f1xx_hal.h"

struct PIN_DESCRIPTION
{
	GPIO_TypeDef* port;
	uint16_t pin;
};
