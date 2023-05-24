#include "SegmentLedControl.h"
#include <cmath>

namespace SegmentLedControl
{
	std::array<MASK_TYPE, DIGIT_QTTY> currentBuffer;

	void setNumber(uint32_t number)
	{
		for(size_t digit = 0; digit < DIGIT_QTTY; digit++)
		{
			unsigned digitValue = (uint32_t)(number / pow(10, digit)) % 10;
			setCustomCharacter(DIGIT_QTTY - 1 - digit, digitValue);
		}
	}

	void setCustomCharacter(unsigned position, unsigned customCharacterIndex)
	{
		if(customCharacterIndex < CUSTOM_CHARACTERS_QTTY && position < DIGIT_QTTY)
			currentBuffer[position] = CUSTOM_CHARACTER_MASK[customCharacterIndex];
	}

	constexpr uint8_t DIGITAL_POINT_MASK = 1 << 7;
	void appendDigitalPoint(unsigned position)
	{
		if(position < DIGIT_QTTY)
			currentBuffer[position] |= DIGITAL_POINT_MASK;
	}

	void setCharacter(unsigned position, MASK_TYPE characterMask)
	{
		if(position < DIGIT_QTTY)
			currentBuffer[position] = characterMask;
	}

	void clearCharacter(unsigned position)
	{
		if(position < DIGIT_QTTY)
			currentBuffer[position] = 0;
	}

	unsigned currentDrawingDigit = 0;
	void writeCharacter(MASK_TYPE mask);
	void processRedraw()
	{
		unselectChannel(CHANNEL_PINS[currentDrawingDigit]);
		if(++currentDrawingDigit >= DIGIT_QTTY)
			currentDrawingDigit = 0;
		writeCharacter(currentBuffer[currentDrawingDigit]);
		selectChannel(CHANNEL_PINS[currentDrawingDigit]);
	}

	void writeCharacter(MASK_TYPE mask)
	{
		for(unsigned bit = 0; bit < SEGMENT_QTTY; bit++)
		{
			if((mask & (1 << bit)) == 0)
				unsetSegment(SEGMENT_PINS[bit]);
			else
				setSegment(SEGMENT_PINS[bit]);
		}
	}
}

