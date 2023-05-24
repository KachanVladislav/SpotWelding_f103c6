#include "MainApp.h"
#include "SegmentLedControl/SegmentLedControl.h"
#include "EncoderControl/EncoderControl.h"
#include "ButtonControl/ButtonInterruptControl.h"
#include "FireTimeControl.h"
#include "FireControlWithZeroDetecter.h"
#include "ZeroDetecterPulseMiddleFinder.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

FireTimeControl fireTimeValue;
void firePressed();
ButtonInterruptControl buttonFireController({GPIOB, GPIO_PIN_11}, firePressed);
FireControlWithZeroDetecter fireController({GPIOB, GPIO_PIN_0});

PIN_DESCRIPTION zeroDetecterPin{GPIOA, GPIO_PIN_7};
void zeroDetecterMidlePulseCallback();
ZeroDetecterPulseMiddleFinder zeroDetecterPulseMiddleFinder(zeroDetecterMidlePulseCallback);
PIN_DESCRIPTION zeroDetecterLEDStatePin{GPIOC, GPIO_PIN_13};

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
	fireController.fire(fireTimeValue.getCurrentTime_ms());
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

bool isZeroDetected = false;
void zeroDetecterMidlePulseCallback()
{
	fireController.handleIRQZeroDetecter();
	isZeroDetected = true;
}

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
	else if(GPIO_Pin == zeroDetecterPin.pin)//zeroDetecter
	{
		if(HAL_GPIO_ReadPin(zeroDetecterPin.port, zeroDetecterPin.pin) == GPIO_PIN_SET)
			zeroDetecterPulseMiddleFinder.handleRisingEdge();
		else
			zeroDetecterPulseMiddleFinder.handleFallinEdge();
	}
}

void processZeroDetecterStateLed_1ms();
void processSegmentLedUpdate_1ms();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim2)//1ms
	{
		processZeroDetecterStateLed_1ms();
		processSegmentLedUpdate_1ms();
		buttonFireController.procesTimeout();
		EncoderControl::processTimerElapsed1ms();
	}
	else if(htim == &htim3)//0.1ms
	{
		zeroDetecterPulseMiddleFinder.handle01msIRQ();
	}
}

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
