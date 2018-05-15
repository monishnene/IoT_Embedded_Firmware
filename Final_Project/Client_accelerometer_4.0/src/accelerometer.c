/*
 * accelerometer.c
 *
 *  Created on: Apr 9, 2018
 *      Author: Sanika
 */



#include "accelerometer.h"

/***********************************************************************
 * @brief spi_setup()
 * setup spi for accelerometer
 ***********************************************************************/
void spi_setup()
{

	USART_InitSync_TypeDef spiInit =
	{
			  /** Specifies whether TX and/or RX shall be enabled when init completed. */
			  .enable = usartDisable,
			  /**
			   * USART/UART reference clock assumed when configuring baudrate setup. Set
			   * it to 0 if currently configurated reference clock shall be used.
			   */
			  .refFreq = 0,
			  /** Desired baudrate. */
			  .baudrate = 100000,
			  /** Number of databits in frame. */
			  .databits = usartDatabits8,
			  /** Select if to operate in master or slave mode. */
			  .master = true,
			  /** Select if to send most or least significant bit first. */
			  .msbf =  true,
			  /** Clock polarity/phase mode. */
			  .clockMode = usartClockMode3,
			  .autoTx = false,
			   /** Auto CS enabling */
			  .autoCsEnable = true,
			  .autoCsHold = 1,
			  .autoCsSetup = 1,
	};
	GPIO_PinModeSet(CS_port, CS_pin,gpioModePushPull,CS_default);
	GPIO_PinModeSet(SCLK_port, SCLK_pin,gpioModePushPull,SCLK_default);
	GPIO_PinModeSet(MOSI_port,MOSI_pin,gpioModePushPull,MOSI_default);
	GPIO_PinModeSet(MISO_port,MISO_pin,gpioModePushPull,MISO_default);
	USART_InitSync(USART1, &spiInit);
	USART1->ROUTELOC0 |= USART_ROUTELOC0_CLKLOC_LOC11 | USART_ROUTELOC0_TXLOC_LOC11 | USART_ROUTELOC0_RXLOC_LOC11 | USART_ROUTELOC0_CSLOC_LOC11;
	USART1->ROUTEPEN |= USART_ROUTEPEN_CLKPEN | USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_CSPEN;
	USART_Enable(USART1, usartEnable);
}

/***********************************************************************
 * @brief accelerometer_read()
 * read data from accelerometer on usart
 * @param usart usart number
 * @param address address of the accelerometer register
 * @return value read
 ***********************************************************************/
uint8_t accelerometer_read(USART_TypeDef *usart, uint8_t address)
{
	uint16_t data_value;
	uint32_t temporary_variable;
	data_value = 0x0080;
	data_value = data_value | address;
	while (!(usart->STATUS & USART_STATUS_TXBL));
	usart->TXDOUBLE = (uint32_t)data_value;
	while (!(usart->STATUS & USART_STATUS_TXC));
	temporary_variable = usart->RXDOUBLE;
	temporary_variable = temporary_variable >> 8;
	return (uint8_t)temporary_variable;
}

/***********************************************************************
 * @brief accelerometer_on()
 * turn on accelerometer
************************************************************************/
void accelerometer_on()
{
	for(int i=0;i<200;i++)
	{
	   GPIO_PinModeSet(LED0_port, LED0_pin, gpioModePushPull, LED_OFF);
	}
	return;
}

/***********************************************************************
 * @brief acceleration_calculate_value()
 * read value from accelerometer and generate command
 * @return command generated
 ***********************************************************************/
uint8_t acceleration_calculate_value()
{
	uint8_t acceleration_x=0,acceleration_y=0,acceleration_z=0,i=0;
	acceleration_x = accelerometer_read(USART1, X_AXIS_BMA280);
	acceleration_y = accelerometer_read(USART1, Y_AXIS_BMA280);
	acceleration_z = accelerometer_read(USART1, Z_AXIS_BMA280);
	i++;
	if(((acceleration_x>0)&&(acceleration_x<20))&&((acceleration_y>30)&&(acceleration_y<60))&&((acceleration_z>30)&&(acceleration_z<60)))
	{
		intantaneous_command = front;
	}
	else if(((acceleration_x>0)&&(acceleration_x<20))&&((acceleration_y>210)&&(acceleration_y<250))&&((acceleration_z>30)&&(acceleration_z<60)))
	{
		intantaneous_command = behind;
	}
	else if(((acceleration_x>20)&&(acceleration_x<60))&&((acceleration_y>250)||(acceleration_y<10))&&((acceleration_z>20)&&(acceleration_z<60)))
	{
		intantaneous_command = right;
	}
	else if(((acceleration_x>200)&&(acceleration_x<250))&&((acceleration_y>250)||(acceleration_y<10))&&((acceleration_z>20)&&(acceleration_z<60)))
	{
		intantaneous_command = left;
	}
	else if(((acceleration_x>250)||(acceleration_x<10))&&((acceleration_y>250)||(acceleration_y<10))&&((acceleration_z>60)&&(acceleration_z<70)))
	{
		intantaneous_command = stop;
	}
	else if(((acceleration_x>20)&&(acceleration_x<40))&&((acceleration_y>20)&&(acceleration_y<60))&&((acceleration_z>20)&&(acceleration_z<60)))
	{
		intantaneous_command = right_ahead;
	}
	else if(((acceleration_x>210)&&(acceleration_x<250))&&((acceleration_y>20)&&(acceleration_y<60))&&((acceleration_z>20)&&(acceleration_z<60)))
	{
		intantaneous_command = left_ahead;
	}
	else if(((acceleration_x>210)&&(acceleration_x<250))&&((acceleration_y>210)&&(acceleration_y<250))&&((acceleration_z>20)&&(acceleration_z<60)))
	{
		intantaneous_command = left_back;
	}
	else if(((acceleration_x>20)&&(acceleration_x<60))&&((acceleration_y>210)&&(acceleration_y<250))&&((acceleration_z>20)&&(acceleration_z<60)))
	{
		intantaneous_command = right_back;
	}
	return intantaneous_command;
}
