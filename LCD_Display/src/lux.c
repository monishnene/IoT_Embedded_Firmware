/*
 * lux.c
 *
 *  Created on: Apr 18, 2018
 *      Author: monish
 */

#include "lux.h"

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

void i2c_init(void)
{
	cmu_i2c_init(cmuClkDiv_1);
	I2C0->ROUTEPEN = (I2C_ROUTEPEN_SDAPEN | I2C_ROUTEPEN_SCLPEN);
	I2C0->ROUTELOC0 = I2C_ROUTELOC0_SCLLOC_LOC14 | I2C_ROUTELOC0_SDALOC_LOC16;
	I2C_Init_TypeDef i2c_init_parameter = I2C_INIT_DEFAULT;
	I2C_Init(I2C0,&i2c_init_parameter);
	i2c_bus_reset();
	GPIO_PinModeSet(I2C0_SCL_PORT, I2C0_SCL_PIN, gpioModeWiredAnd, 1);
	GPIO_PinModeSet(I2C0_SDA_PORT, I2C0_SDA_PIN, gpioModeWiredAnd, 1);
	i2c_bus_reset();
	i2c_slave_clear();
	I2C_IntClear(I2C0, (I2C_IFC_START | I2C_IFC_RSTART | I2C_IFC_ADDR | I2C_IFC_TXC | I2C_IFC_ACK | I2C_IFC_NACK | I2C_IFC_MSTOP | I2C_IFC_ARBLOST | I2C_IFC_BUSERR | I2C_IFC_BUSHOLD |I2C_IFC_TXOF | I2C_IFC_RXUF | I2C_IFC_BITO | I2C_IFC_CLTO | I2C_IFC_SSTOP | I2C_IFC_RXFULL | I2C_IFC_CLERR));
	I2C_IntDisable(I2C0, (I2C_IEN_START | I2C_IEN_RSTART | I2C_IEN_ADDR | I2C_IEN_TXC | I2C_IEN_ACK | I2C_IEN_NACK | I2C_IEN_MSTOP | I2C_IEN_ARBLOST | I2C_IEN_BUSERR | I2C_IEN_BUSHOLD |I2C_IEN_TXOF | I2C_IEN_RXUF | I2C_IEN_BITO | I2C_IEN_CLTO | I2C_IEN_SSTOP | I2C_IEN_RXFULL | I2C_IEN_CLERR));
	I2C0->IFC = 0x7FF;
	I2C0->IEN |= (I2C_IEN_ACK | I2C_IEN_RXDATAV);
	I2C_Enable(I2C0,true);
	return;
}

void i2c_stop(void)
{
	I2C0->CMD = I2C_CMD_STOP;
	return;
}

void i2c_ack(void)
{
	I2C0->IFC = I2C_IFC_ACK;
	return;
}

void i2c_nack(void)
{
	I2C0->CMD = I2C_CMD_NACK;
	return;
}

void i2c_start(void)
{
	I2C0->CMD = I2C_CMD_START;
	return;
}

void i2c_write_byte(uint8_t data_byte)
{
	I2C0->TXDATA = data_byte;
	while((I2C0->IF & I2C_IF_ACK) == 0);
}

uint8_t i2c_read_byte()
{
	while((I2C0->IF & I2C_IF_RXDATAV ) == 0);
	return I2C0->RXDATA;
}

void lux_init(void)
{
	uint8_t address=0;
	i2c_init();
	address  |= device_address_mask;
	address = address << 1;
	address &= write_mask;
	i2c_start();
	i2c_write_byte(address);
    i2c_ack();
	i2c_write_byte(power_on_command_address);
	i2c_ack();
	i2c_write_byte(power_on_command);
	i2c_ack();
	i2c_stop();
	return;
}

uint8_t read_channel(uint8_t channel_address)
{
	uint8_t data_byte=0,address=0,address_read=0,address_write=0;
	address |= device_address_mask;
	address_read = address << 1;
	address_write = address << 1;
	address_write &= write_mask;
	address_read |= read_mask;
	i2c_start();
	i2c_write_byte(address_write);
	i2c_ack();
	i2c_write_byte(channel_address);
	i2c_ack();
	i2c_start();
	i2c_write_byte(address_read);
	i2c_ack();
	data_byte=i2c_read_byte();
	i2c_nack();
	i2c_stop();
	return data_byte;
}

uint8_t lux_read(void)
{
	uint16_t channel_0_data=0,channel_1_data=0;
	channel_0_data = read_channel(channel_0_upper_address);
	channel_0_data = channel_0_data<<8;
	channel_0_data|= read_channel(channel_0_lower_address);
	channel_1_data = read_channel(channel_1_upper_address);
	channel_1_data = channel_1_data<<8;
	channel_1_data|= read_channel(channel_1_lower_address);
	if(1*channel_0_data > 100*channel_1_data)
	{
		return 9;
	}
	else if(10*channel_0_data > 100*channel_1_data)
	{
		return 8;
	}
	else if(20*channel_0_data > 100*channel_1_data)
	{
		return 7;
	}
	else if(30*channel_0_data > 100*channel_1_data)
	{
		return 6;
	}
	else if(40*channel_0_data > 100*channel_1_data)
	{
		return 5;
	}
	else if(50*channel_0_data > 100*channel_1_data)
	{
		return 4;
	}
	else if((61*channel_0_data) > (100*channel_1_data))
	{
		return 3;
	}
	else if((8*channel_0_data) > (10*channel_1_data))
	{
		return 2;
	}
	else if((13*channel_0_data) > (10*channel_1_data))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void lux_test(void)
{
	uint8_t lux_value=0;
	lux_value=lux_read();
	GRAPHICS_AppendString("Brightness");
	print_number(lux_value);
	if(lux_value<3)
	{
		GPIO_PinModeSet(LED0_port,LED0_pin,gpioModePushPull,LED_ON);
	}
	else
	{
		GPIO_PinModeSet(LED0_port,LED0_pin,gpioModePushPull,LED_OFF);
	}
	if(lux_value<5)
	{
		GPIO_PinModeSet(LED1_port,LED1_pin,gpioModePushPull,LED_ON);
	}
	else
	{
		GPIO_PinModeSet(LED1_port,LED1_pin,gpioModePushPull,LED_OFF);
	}
	return;
}
