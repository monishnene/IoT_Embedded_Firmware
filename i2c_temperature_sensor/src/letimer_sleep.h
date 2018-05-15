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
#define LED_Total_time_value (2000) //mS
#define LED_ON_time_value (80)	//mS
static uint8_t letimer_period_selection = 0;
static uint8_t sleep_modes_available[]={0,0,0,0,0};
typedef enum
{
	EM0,
	EM1,
	EM2,
	EM3,
	EM4
}sleep_em;
void unblock_sleep_mode(sleep_em em_mode);
void block_sleep_mode(sleep_em em_mode);
void sleep(void);
void LETIMER0_IRQHandler(void);
void letimer_sleep_init(void);
#endif /* LETIMER_SLEEP_H_ */
