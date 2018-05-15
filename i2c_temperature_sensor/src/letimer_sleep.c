/*
 * sleep.c
 *
 *  Created on: Jan 30, 2018
 *      Author: monish
 */

/***** Credit for the Sleep functions and Letimer functions goes to Silicon Labs *****/
/***** Note: All the functions defined in the following files used in my code were developed by Silicon Labs ->
sleep.h, em_letimer.h, em_emu.h, em_core.h, em_cmu.h, em_assert.h*****/
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
#include "letimer_sleep.h"
#include "sleep.h"
#include "temperature_i2c.h"

void letimer_sleep_init(void)
{
	const LETIMER_Init_TypeDef letimer_init_parameter=
	{
		.enable = true,         /**< Start counting when init completed. */
		.debugRun = false,       /**< Counter shall keep running during debug halt. */
		#if defined(LETIMER_CTRL_RTCC0TEN)
		.rtcComp0Enable = false, /**< Start counting on RTC COMP0 match. */
		.rtcComp1Enable = false, /**< Start counting on RTC COMP1 match. */
		#endif
		.comp0Top = true,       /**< Load COMP0 register into CNT when counter underflows. */
		.bufTop = false,         /**< Load COMP1 into COMP0 when REP0 reaches 0. */
		.out0Pol = false,        /**< Idle value for output 0. */
		.out1Pol = false,       /**< Idle value for output 1. */
		.ufoa0 = letimerUFOANone,          /**< Underflow output 0 action. */
		.ufoa1 = letimerUFOANone,          /**< Underflow output 1 action. */
		.repMode = letimerRepeatFree,        /** Repeat mode. */
	};
	LETIMER_CompareSet(LETIMER0,0,LED_Total_time_value);
	LETIMER_CompareSet(LETIMER0,1,LED_ON_time_value);
	LETIMER_IntClear(LETIMER0,LETIMER_IFC_UF|LETIMER_IFC_COMP1|LETIMER_IFC_COMP0);
	LETIMER_IntEnable(LETIMER0,LETIMER_IEN_COMP1|LETIMER_IEN_COMP0);
	while (LETIMER0->SYNCBUSY);
	NVIC_EnableIRQ(LETIMER0_IRQn);
	LETIMER_Init(LETIMER0,&letimer_init_parameter);
	LETIMER_Enable(LETIMER0, true);
	return;
}

void LETIMER0_IRQHandler(void)
{

	CORE_ATOMIC_IRQ_DISABLE();
	letimer_period_selection = LETIMER_IntGet(LETIMER0);
	if(letimer_period_selection & LETIMER_IF_COMP0)
		{
			LETIMER_IntClear(LETIMER0, LETIMER_IFC_COMP0);
			get_temperature();
			Load_Power_Management(false);
	    }
	    else if(letimer_period_selection & LETIMER_IF_COMP1)
	    {
	    	LETIMER_IntClear(LETIMER0, LETIMER_IFC_COMP1);
	    	Load_Power_Management(true);
	    }
	    else
	    {
	    	LETIMER_IntClear(LETIMER0,LETIMER_IFC_UF|LETIMER_IFC_COMP1|LETIMER_IFC_COMP0);
	    }
    CORE_ATOMIC_IRQ_ENABLE();
}

void unblock_sleep_mode(sleep_em em_mode)
{
	CORE_ATOMIC_IRQ_DISABLE();
	sleep_modes_available[em_mode]--;
	CORE_ATOMIC_IRQ_ENABLE();
	return;
}

void block_sleep_mode(sleep_em em_mode)
{
	CORE_ATOMIC_IRQ_DISABLE();
	sleep_modes_available[em_mode]++;
	CORE_ATOMIC_IRQ_ENABLE();
	return;
}

void sleep(void)
{
	if(sleep_modes_available[0]>0)
	{
		return; //staying EM0
	}
	else if(sleep_modes_available[1]>0)
	{
		return; //EM1 is blocked, so go into EM0
	}
	else if(sleep_modes_available[2]>0)
	{
		EMU_EnterEM1(); //EM2 is blocked, so go into EM1
	}
	else if(sleep_modes_available[3]>0)
	{
		EMU_EnterEM2(true); //EM3 is blocked, so go into EM2
	}
	else
	{
		EMU_EnterEM3(true); //Don't go into EM4
	}
	return;
}
