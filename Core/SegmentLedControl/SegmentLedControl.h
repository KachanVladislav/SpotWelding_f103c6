#pragma once
#include "../PinDescription.h"
#include <array>

namespace SegmentLedControl
{
	using MASK_TYPE = uint8_t;

	const unsigned SEGMENT_QTTY = 8;
	constexpr std::array<PIN_DESCRIPTION, SEGMENT_QTTY> SEGMENT_PINS{{
		{GPIOB, GPIO_PIN_4},
		{GPIOA, GPIO_PIN_8},
		{GPIOB, GPIO_PIN_7},
		{GPIOB, GPIO_PIN_9},
		{GPIOB, GPIO_PIN_5},
		{GPIOA, GPIO_PIN_15},
		{GPIOB, GPIO_PIN_6},
		{GPIOB, GPIO_PIN_8}
	}};

	#define setSegment(pinDescription)\
		HAL_GPIO_WritePin(pinDescription.port, pinDescription.pin, GPIO_PIN_RESET)

	#define unsetSegment(pinDescription)\
		HAL_GPIO_WritePin(pinDescription.port, pinDescription.pin, GPIO_PIN_SET)

	const unsigned DIGIT_QTTY = 4;
	constexpr std::array<PIN_DESCRIPTION, DIGIT_QTTY> CHANNEL_PINS{{
		{GPIOB, GPIO_PIN_3},
		{GPIOA, GPIO_PIN_10},
		{GPIOA, GPIO_PIN_9},
		{GPIOB, GPIO_PIN_15}
	}};

	#define selectChannel(pinDescription)\
		HAL_GPIO_WritePin(pinDescription.port, pinDescription.pin, GPIO_PIN_SET)

	#define unselectChannel(pinDescription)\
		HAL_GPIO_WritePin(pinDescription.port, pinDescription.pin, GPIO_PIN_RESET)

	const unsigned CUSTOM_CHARACTERS_QTTY = 10;
	constexpr std::array<MASK_TYPE, CUSTOM_CHARACTERS_QTTY> CUSTOM_CHARACTER_MASK
	{
		0b00111111, /*digit - 0*/
		0b00000110, /*digit - 1*/
		0b01011011, /*digit - 2*/
		0b01001111, /*digit - 3*/
		0b01100110, /*digit - 4*/
		0b01101101, /*digit - 5*/
		0b01111101, /*digit - 6*/
		0b00000111, /*digit - 7*/
		0b01111111, /*digit - 8*/
		0b01101111, /*digit - 9*/
	};

	void setNumber(uint32_t number);
	void setCustomCharacter(unsigned position, unsigned customCharacterIndex);
	void appendDigitalPoint(unsigned position);
	void setCharacter(unsigned position, MASK_TYPE characterMask);
	void clearCharacter(unsigned position);

	void processRedraw();
}
