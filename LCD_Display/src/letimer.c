/*
 * sleep.c
 *
 *  Created on: Jan 30, 2018
 *      Author: monish
 */

/***** Credit for the Sleep functions and Letimer functions goes to Silicon Labs *****/
/***** Note: All the functions defined in the following files used in my code were developed by Silicon Labs ->
sleep.h, em_letimer.h, em_emu.h, em_core.h, em_cmu.h, em_assert.h*****/
#include "letimer.h"


void letimer_init(void)
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
	cmu_letimer_init(1);
	LETIMER_CompareSet(LETIMER0,1,Total_time_value);
	LETIMER_CompareSet(LETIMER0,1,ON_time_value);
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
	uint8_t i=0;
	CORE_ATOMIC_IRQ_DISABLE();
	letimer_period_selection = LETIMER_IntGet(LETIMER0);
	if(letimer_period_selection & LETIMER_IF_COMP0)
		{
			LETIMER_IntClear(LETIMER0, LETIMER_IFC_COMP0);
			gecko_external_signal(1);
	    }
	    else if(letimer_period_selection & LETIMER_IF_COMP1)
	    {
	    	LETIMER_IntClear(LETIMER0, LETIMER_IFC_COMP1);
	    	gecko_external_signal(1);
	    }
	    else
	    {
	    	LETIMER_IntClear(LETIMER0,LETIMER_IFC_UF|LETIMER_IFC_COMP1|LETIMER_IFC_COMP0);
	    }
	gecko_cmd_le_connection_get_rssi(BLE_CONNECT);
    CORE_ATOMIC_IRQ_ENABLE();
}
