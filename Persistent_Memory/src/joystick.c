/*
 * joystick.c
 *
 *  Created on: Mar 30, 2018
 *      Author: monish and sanika
 */

#include "joystick.h"

uint16_t adc_cmp_gt = 30;
uint16_t adc_cmp_lt = 3550;                 /* ~0.5V for 3.3V AVDD */



/***********************************************************************
 * @brief ADC0_IRQHandler()
 * Interrupt handler for ADC interrupt
 ***********************************************************************/
void ADC0_IRQHandler(void)
{
	uint32_t Flag = ADC_IntGet(ADC0);
	CORE_ATOMIC_IRQ_DISABLE();
	/*Clear the interrupting flags*/
	ADC_IntClear(ADC0, Flag);
	gecko_external_signal(1);
	/*Clear FIFO*/
	CORE_ATOMIC_IRQ_ENABLE();
}

/***********************************************************************
 * @brief joystick_read()
 * Read the instantaneous value of joystick with ADC
 ***********************************************************************/
void joystick_read(void)
{
	static uint8_t previous_signal = none;
	uint32_t ADC_data=0;
	ADC0->SINGLEFIFOCLEAR |= ADC_SINGLEFIFOCLEAR_SINGLEFIFOCLEAR;
	ADC_data = ADC_DataSingleGet(ADC0);
	if((ADC_data < AHEAD_MAX)&&(ADC_data > AHEAD_MIN))
	{
		if(previous_signal != ahead)
		{
			black_box_update(ahead);
		}
		previous_signal = ahead;
	}
	else if((ADC_data < BACK_MAX)&&(ADC_data > BACK_MIN))
	{
		if(previous_signal != back)
		{
			black_box_update(back);
		}
		previous_signal = back;
	}
	else if(( ADC_data < LEFT_MAX)&&(ADC_data > LEFT_MIN))
	{
		if(previous_signal != left)
		{
			black_box_update(left);
		}
		previous_signal = left;
	}
	else if((ADC_data < RIGHT_MAX)&&(ADC_data > RIGHT_MIN))
	{
		if(previous_signal != right)
		{
			black_box_update(right);
		}
		previous_signal = right;
	}
	else if(ADC_data<STOP_MAX)
	{
		if(previous_signal != stop)
		{
			black_box_update(stop);
		}
		previous_signal = stop;
	}
	GRAPHICS_Clear();
}

/***********************************************************************
 * @brief joystick_Init()
 * Initial Configuration for using joystick with ADC interrupt
 ***********************************************************************/
void joystick_Init(void)
{
	NVIC_DisableIRQ(ADC0_IRQn);
	cmu_adc_init();
	GPIO_PinModeSet(ADC0_port, ADC0_pin, gpioModeDisabled, ADC0_default);
	/*Over voltage disable for analog pin PortA pin 0 for more accurate ADC measurement*/
	GPIO->P[gpioPortA].OVTDIS = 0x0001;
	ADC0->SINGLEFIFOCLEAR = ADC_SINGLEFIFOCLEAR_SINGLEFIFOCLEAR;
	ADC_Init_TypeDef Init =
	{
			  .ovsRateSel = adcOvsRateSel2,
			  .timebase = ADC_TimebaseCalc(0),
			  .em2ClockConfig = adcEm2ClockAlwaysOn,
			  .prescale = ADC_FREQUENCY,
		      .tailgate = false,
			  .warmUpMode = adcWarmupNormal,
	};

	ADC_InitSingle_TypeDef singleInit =
	{
			 .posSel = adcPosSelAPORT3XCH8,
			 .reference = adcRefVDD,
			 .acqTime = adcAcqTime32,
			 .rep = true,
			 .fifoOverwrite = true,
			 .prsEnable = false,
			 .negSel=adcNegSelVSS,
			 .diff = false,
			 //.resolution = adcRes12Bit,
			 .prsSel = adcPRSSELCh0,
			 .singleDmaEm2Wu = false,
			 .leftAdjust = false ,
	};

	ADC0->BIASPROG |= ADC_BIASPROG_GPBIASACC_LOWACC | ADC_BIASPROG_ADCBIASPROG_SCALE8;
	ADC_Init(ADC0, &Init);
	ADC_InitSingle(ADC0, &singleInit);
	GPIO_PinModeSet(gpioPortA,0,gpioModeDisabled,0);
	ADC0->SINGLECTRL |= ADC_SINGLECTRL_CMPEN;
	ADC0->SCANCTRL |= _ADC_SCANCTRL_REF_VDD;
	ADC0->SCANCTRLX |= _ADC_SCANCTRLX_VREFSEL_VDDXWATT;
	ADC0->CMPTHR = _ADC_CMPTHR_RESETVALUE;
	ADC0->CMPTHR = (adc_cmp_gt << _ADC_CMPTHR_ADGT_SHIFT);
	ADC0->CMPTHR |= (adc_cmp_lt << _ADC_CMPTHR_ADLT_SHIFT);
	//ADC0->SINGLECTRL |=  ADC_SINGLECTRL_CMPEN;
	ADC_IntEnable(ADC0, ADC_IEN_SINGLECMP );
	NVIC_ClearPendingIRQ(ADC0_IRQn);
	NVIC_EnableIRQ(ADC0_IRQn);
	ADC_Start(ADC0, adcStartSingle);
    CORE_ATOMIC_IRQ_ENABLE();
}


