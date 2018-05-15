//***********************************************************************************
// Include files
//***********************************************************************************
#include "cmu.h"
/***** Note: All the functions defined in the following files used in my code were developed by Silicon Labs ->
em_cmu.h*****/
//***********************************************************************************
// defined files
//***********************************************************************************


//***********************************************************************************
// global variables
//***********************************************************************************


//***********************************************************************************
// function prototypes
//***********************************************************************************
/***********************************************************************
 * @brief cmu_init()
 * Initialize clock
 ***********************************************************************/
void cmu_init(void){
	// Peripheral clocks enabled
	CMU_ClockEnable(cmuClock_GPIO, true);
	CMU_ClockEnable(cmuClock_CORELE, true);
	return;
}

/***********************************************************************
 * @brief cmu_letimer_init()
 * Initialize clock for letimer
 ***********************************************************************/
void cmu_letimer_init(CMU_ClkDiv_TypeDef prescaler)
{
	CMU_OscillatorEnable(cmuOsc_LFXO,true,true);
	CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);
	CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_ULFRCO);
	CMU_ClockEnable(cmuClock_LETIMER0, true);
	CMU_ClockEnable(cmuClock_GPIO, true);
	CMU_ClockDivSet(cmuClock_LETIMER0,prescaler);
	return;
}

/***********************************************************************
 * @brief cmu_i2c_init()
 * Initialize clock for i2c
 ***********************************************************************/
void cmu_i2c_init(CMU_ClkDiv_TypeDef prescaler)
{
	CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(cmuClock_I2C0, true);
	return;
}

/***********************************************************************
 * @brief cmu_adc_init()
 * Initialize clock for adc
 ***********************************************************************/
void cmu_adc_init(void)
{
	CMU_AUXHFRCOBandSet(CMU_AUXHFRCO_MIN);
	CMU_OscillatorEnable(cmuOsc_AUXHFRCO, true, true);
	CMU_ClockSelectSet(cmuClock_AUX,cmuSelect_AUXHFRCO);
	ADC0->CTRL |= ADC_CTRL_ADCCLKMODE_ASYNC | ADC_CTRL_ASYNCCLKEN_ASNEEDED;
	CMU->ADCCTRL  = CMU_ADCCTRL_ADC0CLKSEL_AUXHFRCO;
	CMU_ClockSelectSet(cmuClock_ADC0,cmuSelect_AUXHFRCO);
	CMU_ClockEnable(cmuClock_ADC0, true);
	return;
}

