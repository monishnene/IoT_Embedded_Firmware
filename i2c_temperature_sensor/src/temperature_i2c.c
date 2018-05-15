/*
 * temperature_i2c.c
 *
 *  Created on: Feb 6, 2018
 *      Author: monish
 */


/***** Note: All the functions defined in the following files used in my code were developed by Silicon Labs ->
em_gpio.h, em_i2c.h, sleep.h *****/

#include "cmu.h"
#include "em_i2c.h"
#include "em_gpio.h"
#include "sleep.h"
#include "letimer_sleep.h"
#include "gpio.h"
//#include "i2cspm.h"
#include "temperature_i2c.h"

void temp_i2c_init(void)
{
	GPIO_PinOutSet(SI7021_Enable_Port, SI7021_Enable_Pin);
	cmu_temperature_i2c_init(cmuClkDiv_1);
	I2C0->ROUTEPEN = (I2C_ROUTEPEN_SDAPEN | I2C_ROUTEPEN_SCLPEN);
	I2C0->ROUTELOC0 = I2C_ROUTELOC0_SCLLOC_LOC14 | I2C_ROUTELOC0_SDALOC_LOC16;
	I2C_Init_TypeDef i2c_init_parameter = I2C_INIT_DEFAULT;
	I2C_Init(I2C0,&i2c_init_parameter);
	i2c_bus_reset();
	return;
}

void Enable_Temp_Sensor(void)
{
	GPIO_PinModeSet(SI7021_Enable_Port, SI7021_Enable_Pin,gpioModePushPull,1);
	return;
}

void Disable_Temp_Sensor(void)
{
	GPIO_PinModeSet(I2C0_SCL_PORT, I2C0_SCL_PIN, gpioModeDisabled, 1);
	GPIO_PinModeSet(I2C0_SDA_PORT, I2C0_SDA_PIN, gpioModeDisabled, 1);
	GPIO_PinModeSet(SI7021_Enable_Port, SI7021_Enable_Pin,gpioModePushPull,0);
	unblock_sleep_mode(EM3);
	unblock_sleep_mode(EM2);
	return;
}

void i2c_slave_clear(void)
{
	for (int i = 0; i < 9; i++)
	{
		GPIO_PinOutClear(I2C0_SCL_PORT, I2C0_SCL_PIN);
		GPIO_PinOutSet(I2C0_SCL_PORT, I2C0_SCL_PIN);
	}
	return;
}


void i2c_bus_reset(void)
{
	if (I2C0->STATE & I2C_STATE_BUSY)
	{
		I2C0->CMD = I2C_CMD_ABORT;
	}
	return;
}

void temperature_check(uint16_t temperature)
{
	//temperatureCode = ((((17572 * temperatureCode) >> 16) - 4685)>>2)/25;
	temperature = 0.002681 * temperature - 46.85;
	if(temperature < temperature_threshold)
	{
		GPIO_PinModeSet(LED1_port, LED1_pin, gpioModePushPull, LED_ON);
	}
	else
	{
		GPIO_PinModeSet(LED1_port, LED1_pin, gpioModePushPull, LED_OFF);
	}
	return;
}

void get_temperature(void)
{
	block_sleep_mode(EM3);
	block_sleep_mode(EM2);
	GPIO_PinModeSet(I2C0_SCL_PORT, I2C0_SCL_PIN, gpioModeWiredAnd, 1);
	GPIO_PinModeSet(I2C0_SDA_PORT, I2C0_SDA_PIN, gpioModeWiredAnd, 1);
	i2c_bus_reset();
	i2c_slave_clear();
	I2C_IntClear(I2C0, (I2C_IFC_START | I2C_IFC_RSTART | I2C_IFC_ADDR | I2C_IFC_TXC | I2C_IFC_ACK | I2C_IFC_NACK | I2C_IFC_MSTOP | I2C_IFC_ARBLOST | I2C_IFC_BUSERR | I2C_IFC_BUSHOLD |I2C_IFC_TXOF | I2C_IFC_RXUF | I2C_IFC_BITO | I2C_IFC_CLTO | I2C_IFC_SSTOP | I2C_IFC_RXFULL | I2C_IFC_CLERR));
	I2C_IntDisable(I2C0, (I2C_IEN_START | I2C_IEN_RSTART | I2C_IEN_ADDR | I2C_IEN_TXC | I2C_IEN_ACK | I2C_IEN_NACK | I2C_IEN_MSTOP | I2C_IEN_ARBLOST | I2C_IEN_BUSERR | I2C_IEN_BUSHOLD |I2C_IEN_TXOF | I2C_IEN_RXUF | I2C_IEN_BITO | I2C_IEN_CLTO | I2C_IEN_SSTOP | I2C_IEN_RXFULL | I2C_IEN_CLERR));
	I2C0->IFC = 0x7FF;
	I2C0->IEN |= (I2C_IEN_ACK | I2C_IEN_RXDATAV);
	I2C_Enable(I2C0,true);
	uint16_t temperature_raw_data=0;
	send_byte_i2c(TEMP_SENSOR_ADDRESS,TEMP_SENSOR_MEASURE_TEMP);
	temperature_raw_data = receive_byte_i2c(TEMP_SENSOR_ADDRESS);
	temperature_raw_data = temperature_raw_data << 8;
	temperature_raw_data |= receive_next_byte_i2c();
	end_i2c_transfer();
	temperature_check(temperature_raw_data);
	return;
}

void send_byte_i2c(uint8_t address,uint8_t data)
{
	I2C0->TXDATA = (address << 1) & WRITE;
	I2C0->CMD = I2C_CMD_START;
	while((I2C0->IF & I2C_IF_ACK) == 0);
	I2C0->IFC = I2C_IFC_ACK;
	I2C0->TXDATA = data;
	while((I2C0->IF & I2C_IF_ACK) == 0);
	I2C0->IFC = I2C_IFC_ACK;
	return;
}

uint8_t receive_byte_i2c(uint8_t address)
{
	I2C0->CMD = I2C_CMD_START;
	I2C0->TXDATA = (address << 1) | READ;
	while((I2C0->IF & I2C_IF_ACK) == 0);
	I2C0->IFC = I2C_IFC_ACK;
	while((I2C0->IF & I2C_IF_RXDATAV ) == 0);
	return I2C0->RXDATA;
}

uint8_t receive_next_byte_i2c(void)
{
	I2C0->CMD = I2C_CMD_ACK;
	//while((I2C0->IF & I2C_IF_RXDATAV ) == 0);
	return (I2C0->RXDATA);
}

void end_i2c_transfer(void)
{
	I2C0->CMD = I2C_CMD_NACK;
	I2C0->CMD = I2C_CMD_STOP;
	return;
}

void Load_Power_Management(bool Enable_Disable_Status)
{
	if (Load_Power_Mangament_Status)
	{
		if(Enable_Disable_Status)
		{
			Enable_Temp_Sensor();
		}
		else
		{
			Disable_Temp_Sensor();
		}
	}
	return;
}
