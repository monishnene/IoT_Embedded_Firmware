/*
 * accelerometer.h
 *
 *  Created on: Apr 9, 2018
 *      Author: Sanika
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include "em_usart.h"
#include "gpio.h"
#include "em_cmu.h"
#include "graphics.h"
#include "persistent_memory.h"
#include "black_box.h"
#include "cmu.h"

#define X_AXIS_BMA280 (0x03)
#define Y_AXIS_BMA280 (0x05)
#define Z_AXIS_BMA280 (0x07)

movement_command intantaneous_command;
void accelerometer_on();
uint8_t acceleration_calculate_value(void);
void spi_setup();
uint8_t accelerometer_read(USART_TypeDef *usart, uint8_t address);


#endif /* SPI_H_ */
