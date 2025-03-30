/*
 * dispatcher2.c
 *
 *  Created on: Mar 31, 2025
 *      Author: david
 */

#include "main.h"

/* ---------------------------- FUNCTION PROTORYPES ---------------------------- */
void blinkLed10(void);
void blinkLed20(void);
void blinkLed30(void);
void Scheduler_Run(void);

/* ---------------------------------- DEFINES ---------------------------------- */
typedef struct {
	void(*taskFunction)(void);
	uint32_t interval;
	uint32_t lastRun;
}Task_handle;

#define NUM_TASKS (sizeof(task) / sizeof(Task_handle))


/* --------------------------------- VARIABLES --------------------------------- */
Task_handle task[] = {
		{blinkLed10, 50, 0},
		{blinkLed20, 10000, 0},
		{blinkLed30, 1000, 0}
};

/* --------------------------------- SCHEDULER --------------------------------- */
void Scheduler_Run(void){
	uint32_t time = HAL_GetTick();

	for(uint8_t i = 0; i < NUM_TASKS; i++){
		if(time - task[i].lastRun >= task[i].interval){
			task[i].taskFunction();
			task[i].lastRun = time;
		}
	}
}

/* -------------------------- FUNCTION TO BLINK LED 1 -------------------------- */
void blinkLed10(void){
	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
}

/* -------------------------- FUNCTION TO BLINK LED 2 -------------------------- */
void blinkLed20(void){
	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
}

/* -------------------------- FUNCTION TO BLINK LED 3 -------------------------- */
void blinkLed30(void){
	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
}
