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
void cmu_init(void){
	// Peripheral clocks enabled
	CMU_ClockEnable(cmuClock_GPIO, true);
	CMU_ClockEnable(cmuClock_CORELE, true);
	return;
}

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

void cmu_temperature_i2c_init(CMU_ClkDiv_TypeDef prescaler)
{
	//CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_HFRCO);
	//CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_HFXO);
	CMU_ClockEnable(cmuClock_HFPER, true);
	//CMU_ClockDivSet(cmuClock_HFPER,prescaler);
	CMU_ClockEnable(cmuClock_I2C0, true);
	return;
}
