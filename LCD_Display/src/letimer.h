/*
 * sleep.h
 *
 *  Created on: Jan 30, 2018
 *      Author: monish
 */
/***** Note: All the functions defined in the following files used in my code were developed by Silicon Labs ->
sleep.h, em_letimer.h, em_emu.h, em_core.h, em_cmu.h, em_assert.h*****/

#ifndef LETIMER_SLEEP_H_
#define LETIMER_SLEEP_H_
#include <stdint.h>
#include "main.h"
#include "gpio.h"
#include "cmu.h"
#include "em_letimer.h"
#include <stdint.h>
#include "em_emu.h"
#include "em_core.h"
#include "em_cmu.h"
#include "em_assert.h"
#include <stdbool.h>
#include "sleep.h"
#include "native_gecko.h"
#include "graphics.h"
#define Total_time_value (10000) //mS
#define ON_time_value (5000)	//mS
static volatile uint8_t letimer_period_selection = 0, accelerometer_flag;
uint8_t BLE_CONNECT;

void LETIMER0_IRQHandler(void);
void letimer_init(void);
#endif /* LETIMER_SLEEP_H_ */
