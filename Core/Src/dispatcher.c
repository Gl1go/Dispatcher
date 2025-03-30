/*
 * dispatcher.c
 *
 *  Created on: Mar 30, 2025
 *      Author: david
 */

#include "main.h"

/* ---------------------------- FUNCTION PROTORYPES ---------------------------- */
void blinkLed1(void);
void blinkLed2(void);
void dispatch(void);

/* ---------------------------------- DEFINES ---------------------------------- */
typedef void(*TaskSelection)(void);

/* --------------------------------- VARIABLES --------------------------------- */
TaskSelection taskList[] = {blinkLed1, blinkLed2};
#define No_TASKS	(sizeof(taskList) / sizeof(TaskSelection));
uint8_t currentTask = 0;

/* -------------------------- FUNCTION TO BLINK LED 1 -------------------------- */
void blinkLed1(void){
	static uint32_t lastTick = 0;

	if(HAL_GetTick()-lastTick >= 200){
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
		lastTick = HAL_GetTick();
	}
}

/* -------------------------- FUNCTION TO BLINK LED 2 -------------------------- */
void blinkLed2(void){
	static uint32_t lastTick = 0;

	if(HAL_GetTick()-lastTick >= 1000){
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
		lastTick = HAL_GetTick();
	}
}

/* --------------------------------- DISPATCHER --------------------------------- */
void dispatch(void){
	taskList[currentTask]();
	currentTask = (currentTask + 1) % No_TASKS;
}
