//***********************************************************************************
// Include files
//***********************************************************************************
#include "main.h"
#include "em_cmu.h"

/***** Credit for the Sleep functions and Letimer functions goes to Silicon Labs *****/
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
void cmu_init(void);
void cmu_letimer_init(CMU_ClkDiv_TypeDef prescaler);
void cmu_temperature_i2c_init(CMU_ClkDiv_TypeDef prescaler);
