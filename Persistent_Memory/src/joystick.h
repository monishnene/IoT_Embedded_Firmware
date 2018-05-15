/*
 * joystick.h
 *
 *  Created on: Mar 30, 2018
 *      Author: monish
 */

#ifndef SRC_JOYSTICK_H_
#define SRC_JOYSTICK_H_
#include "graphics.h"
#include "em_adc.h"
#include "em_core.h"
#include "gpio.h"
#include "black_box.h"
#include "native_gecko.h"
#include "cmu.h"
#include <stdint.h>
#include <stdlib.h>

typedef enum
{
	none = 0,
	ahead,
	back,
	left,
	right,
	stop,
}signals;

#define ADC_FREQUENCY (10)
#define SAMPLING_RATE (200)
#define AHEAD_MAX (3530)
#define AHEAD_MIN (3510)
#define BACK_MAX (2065)
#define BACK_MIN (2045)
#define RIGHT_MAX (3160)
#define RIGHT_MIN (3140)
#define LEFT_MAX (2475)
#define LEFT_MIN (2455)
#define STOP_MAX (70)

void joystick_Init(void);
void ADC0_IRQHandler(void);
void joystick_read(void);


#endif /* SRC_JOYSTICK_H_ */
