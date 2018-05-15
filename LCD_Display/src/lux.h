/*
 * lux.h
 *
 *  Created on: Apr 18, 2018
 *      Author: monish
 */

#ifndef SRC_LUX_H_
#define SRC_LUX_H_

#include "cmu.h"
#include "em_i2c.h"
#include "em_gpio.h"
#include "sleep.h"
#include "letimer.h"
#include "gpio.h"
#include "persistent_memory.h"

#define device_address_mask (0x39)
#define device_address_mask_2 (0xAF)
#define read_mask (0x01)
#define write_mask (0xFE)
#define LSB_high_mask (0x01)
#define LSB_low_mask (0xFE)
#define power_on_command_address (0xA0)
#define power_on_command (0x03)
#define channel_0_lower_address (0xAC)
#define channel_0_upper_address (0xAD)
#define channel_1_lower_address (0xAE)
#define channel_1_upper_address (0xAF)
#define I2C0_SCL_PIN 	AF_I2C0_SCL_PIN(_I2C_ROUTELOC0_SCLLOC_LOC14)
#define I2C0_SDA_PIN 	AF_I2C0_SDA_PIN(_I2C_ROUTELOC0_SDALOC_LOC16)
#define I2C0_SCL_PORT	AF_I2C0_SCL_PORT(_I2C_ROUTELOC0_SCLLOC_LOC14)
#define I2C0_SDA_PORT 	AF_I2C0_SDA_PORT(_I2C_ROUTELOC0_SDALOC_LOC16)


void i2c_slave_clear(void);
void i2c_bus_reset(void);
void i2c_init(void);
void i2c_stop(void);
void i2c_ack(void);
void i2c_nack(void);
void i2c_start(void);
void i2c_write_byte(uint8_t data_byte);
uint8_t i2c_read_byte();
void lux_test(void);
uint8_t lux_read(void);
uint8_t read_channel(uint8_t channel_address);
void lux_init(void);

#endif /* SRC_LUX_H_ */
