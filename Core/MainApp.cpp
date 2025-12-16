#include "MainApp.h"
#include "SegmentLedControl/SegmentLedControl.h"
#include "EncoderControl/EncoderControl.h"
#include "ButtonControl/ButtonInterruptControl.h"
#include "FireTimeControl.h"
#include "FireControlWithZeroDetecter.h"
#include "ZeroDetecterPulseMiddleFinder.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

#define REMOVE_ZERO_DETECTOR

FireTimeControl fireTimeValue;
void firePressed();
ButtonInterruptControl buttonFireController({GPIOB, GPIO_PIN_11}, firePressed);

class FireControlWithoutZeroDetector
{
	PIN_DESCRIPTION firePin;
	enum class FIRE_STAGE
	{
		IDLE,
		FIERING
	} fireState = FIRE_STAGE::IDLE;
	uint32_t fireTimeDuration_ms{};
	uint32_t fireTimePassed_ms{};
public:
	FireControlWithoutZeroDetector(PIN_DESCRIPTION firePin) : firePin(firePin) {}
	void fire(uint32_t fireTime_ms)
	{
		if(fireState == FIRE_STAGE::IDLE)
		{
			fireTimeDuration_ms = fireTime_ms;
			fireState = FIRE_STAGE::FIERING;
			fireTimePassed_ms = 0;
			HAL_GPIO_WritePin(firePin.port, firePin.pin, GPIO_PIN_SET);
		}
	}
	void update_1ms()
	{
		if(fireState != FIRE_STAGE::FIERING)
			return;
		fireTimePassed_ms += 1;
		if(fireTimePassed_ms >= fireTimeDuration_ms)
		{
			HAL_GPIO_WritePin(firePin.port, firePin.pin, GPIO_PIN_RESET);
			fireState = FIRE_STAGE::IDLE;
		}
	}
};
#ifndef REMOVE_ZERO_DETECTOR
FireControlWithZeroDetecter fireController({GPIOB, GPIO_PIN_0});

PIN_DESCRIPTION zeroDetecterPin{GPIOA, GPIO_PIN_7};
void zeroDetecterMidlePulseCallback();
ZeroDetecterPulseMiddleFinder zeroDetecterPulseMiddleFinder(zeroDetecterMidlePulseCallback);
PIN_DESCRIPTION zeroDetecterLEDStatePin{GPIOC, GPIO_PIN_13};
#else
FireControlWithoutZeroDetector fireControllerWithoutZeroDetector({GPIOB, GPIO_PIN_0});
#endif

void MainApp()
{

	HAL_TIM_Base_Start_IT(&htim2);//1ms timer
	HAL_TIM_Base_Start_IT(&htim3);//0.1ms timer
	SegmentLedControl::setNumber(fireTimeValue.getCurrentTime_ms());
	while(1)
	{
		HAL_Delay(500);
	}
}

void firePressed()
{
#ifndef REMOVE_ZERO_DETECTOR
	fireController.fire(fireTimeValue.getCurrentTime_ms());
#else
	fireControllerWithoutZeroDetector.fire(fireTimeValue.getCurrentTime_ms());
#endif
}

void EncoderControl::counterclockwiseCallback()
{
	fireTimeValue.decrementTime();
	SegmentLedControl::setNumber(fireTimeValue.getCurrentTime_ms());
}

void EncoderControl::clockwiseCallback()
{
	fireTimeValue.incrementTime();
	SegmentLedControl::setNumber(fireTimeValue.getCurrentTime_ms());
}

#ifndef REMOVE_ZERO_DETECTOR
bool isZeroDetected = false;
void zeroDetecterMidlePulseCallback()
{
	fireController.handleIRQZeroDetecter();
	isZeroDetected = true;
}
#endif

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_10)//encoder
	{
		EncoderControl::processPinAFallingEdgeInterrupt();
	}
	else if(GPIO_Pin == GPIO_PIN_11)//buttonFire
	{
		buttonFireController.proccesIRQFalinEdge();
	}
#ifndef REMOVE_ZERO_DETECTOR
	else if(GPIO_Pin == zeroDetecterPin.pin)//zeroDetecter
	{
		if(HAL_GPIO_ReadPin(zeroDetecterPin.port, zeroDetecterPin.pin) == GPIO_PIN_SET)
			zeroDetecterPulseMiddleFinder.handleRisingEdge();
		else
			zeroDetecterPulseMiddleFinder.handleFallinEdge();
	}
#endif
}

#ifndef REMOVE_ZERO_DETECTOR
void processZeroDetecterStateLed_1ms();
#endif
void processSegmentLedUpdate_1ms();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim2)//1ms
	{
#ifndef REMOVE_ZERO_DETECTOR
		processZeroDetecterStateLed_1ms();
#else
		fireControllerWithoutZeroDetector.update_1ms();
#endif
		processSegmentLedUpdate_1ms();
		buttonFireController.procesTimeout();
		EncoderControl::processTimerElapsed1ms();
	}
#ifndef REMOVE_ZERO_DETECTOR
	else if(htim == &htim3)//0.1ms
	{
		zeroDetecterPulseMiddleFinder.handle01msIRQ();
	}
#endif
}

#ifndef REMOVE_ZERO_DETECTOR
unsigned timeLastZeroDetected = 0;
const unsigned ZERO_DETECTER_MAX_TIME = 30;
void processZeroDetecterStateLed_1ms()
{
	if(isZeroDetected)
	{
		HAL_GPIO_WritePin(zeroDetecterLEDStatePin.port, zeroDetecterLEDStatePin.pin, GPIO_PIN_RESET);//turn on
		timeLastZeroDetected = 0;
		isZeroDetected = false;
	}
	if(++timeLastZeroDetected >= ZERO_DETECTER_MAX_TIME)
	{
		HAL_GPIO_WritePin(zeroDetecterLEDStatePin.port, zeroDetecterLEDStatePin.pin, GPIO_PIN_SET);//turn off
	}
}
#endif

unsigned timeFromLastScreenUpdate = 0;
const unsigned LED_PERIOD_UPDATE_MS = 1;
void processSegmentLedUpdate_1ms()
{
	if(++timeFromLastScreenUpdate >= LED_PERIOD_UPDATE_MS)
	{
		timeFromLastScreenUpdate = 0;
		SegmentLedControl::processRedraw();

	}
}
