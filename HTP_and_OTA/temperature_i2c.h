/*
 * I2C.h
 *
 *  Created on: Feb 6, 2018
 *      Author: monish
 */

/***** Note: All the functions defined in the following files used in my code were developed by Silicon Labs ->
em_gpio.h, em_i2c.h, i2cspm.h, cmu.h, sleep.h *****/

#ifndef TEMPERATURE_I2C_H_
#define TEMPERATURE_I2C_H_
#include<stdint.h>
#include "cmu.h"
#include "em_i2c.h"
#include "em_gpio.h"
#include "sleep.h"
#include "letimer_sleep.h"
#include "gpio.h"

#define I2C0_MIN_SLEEPMODE (EM1)
#define TEMP_SENSOR_ADDRESS 	(0x40)
#define IO_EXPANDER_ADDRESS		(0x90)
#define TEMP_SENSOR_MEASURE_TEMP (0xE3)
#define WRITE	(0xFE)
#define READ	(0x01)
#define TEMP_SENSOR_HEATER_OFF	(0x00)
#define SI7021_Enable_Port gpioPortD
#define SI7021_Enable_Pin (9)
#define I2C0_SCL_PIN 	AF_I2C0_SCL_PIN(_I2C_ROUTELOC0_SCLLOC_LOC14)
#define I2C0_SDA_PIN 	AF_I2C0_SDA_PIN(_I2C_ROUTELOC0_SDALOC_LOC16)
#define I2C0_SCL_PORT	AF_I2C0_SCL_PORT(_I2C_ROUTELOC0_SCLLOC_LOC14)
#define I2C0_SDA_PORT 	AF_I2C0_SDA_PORT(_I2C_ROUTELOC0_SDALOC_LOC16)


static uint8_t temperature_threshold=15;
static bool Load_Power_Mangament_Status = true;
void Enable_Temp_Sensor(void);
void Disable_Temp_Sensor(void);
void temp_i2c_init(void);
void Load_Power_Management(bool Enable_Disable_Status);
void i2c_slave_clear(void);
void temperature_check(uint16_t temperature);
uint16_t get_temperature(void);
void send_byte_i2c(uint8_t address,uint8_t data);
uint8_t receive_byte_i2c(uint8_t address);
void i2c_bus_reset(void);
uint8_t receive_next_byte_i2c(void);
void end_i2c_transfer(void);
#endif /* TEMPERATURE_I2C_H_ */
