//***********************************************************************************
// Include files
//***********************************************************************************
#include "main.h"
#include "em_gpio.h"
#include <stdbool.h>
//***********************************************************************************
// defined files
//***********************************************************************************

// LED0 pin is
#define	LED0_port gpioPortF
#define LED0_pin 4
#define LED0_default	false	// off
// LED1 pin is
#define LED1_port gpioPortF
#define LED1_pin 5
#define LED1_default	false	// off
#define LED_ON true
#define LED_OFF false

// ADC pin
#define	ADC0_port gpioPortA
#define ADC0_pin (0)
#define ADC0_default	false 	// off

// CS pin
#define	CS_port gpioPortC
#define CS_pin (9)
#define CS_default	true 	// off

// SCLK pin
#define	SCLK_port gpioPortC
#define SCLK_pin (8)
#define SCLK_default	true 	// off

// MISO pin
#define	MISO_port gpioPortC
#define MISO_pin (7)
#define MISO_default	false 	// off

// MOSI pin
#define	MOSI_port gpioPortC
#define MOSI_pin (6)
#define MOSI_default	true 	// true

// PB1
#define	PB1_port gpioPortF
#define PB1_pin (7)
#define PB1_default	true 	// true

// PB0
#define	PB0_port gpioPortF
#define PB0_pin (6)
#define PB0_default	true 	// true



//***********************************************************************************
// global variables
//***********************************************************************************


//***********************************************************************************
// function prototypes
//***********************************************************************************
void gpio_init(void);

