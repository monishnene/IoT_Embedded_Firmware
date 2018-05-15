/*
 * chassis.c
 *
 *  Created on: Apr 17, 2018
 *      Author: Sanika & Monish
 */


#include "chassis.h"

void move_motors(movement_command movement)
{
	switch(movement)
	{
	case right:
		GPIO_PinModeSet(PORTA, MOTOR_LEFT_RED, gpioModePushPull,1);
		GPIO_PinModeSet(PORTB, MOTOR_LEFT_BLACK, gpioModePushPull,0);
		GPIO_PinModeSet(PORTB, MOTOR_RIGHT_RED,gpioModePushPull ,1);
		GPIO_PinModeSet(PORTB, MOTOR_RIGHT_BLACK, gpioModePushPull,0);
		break;

	case left:
		GPIO_PinModeSet(PORTA, MOTOR_LEFT_RED,  gpioModePushPull,0);
	    GPIO_PinModeSet(PORTB, MOTOR_LEFT_BLACK, gpioModePushPull,1);
		GPIO_PinModeSet(PORTB, MOTOR_RIGHT_RED, gpioModePushPull,0);
		GPIO_PinModeSet(PORTB, MOTOR_RIGHT_BLACK, gpioModePushPull,1);
		break;

	case behind:
		GPIO_PinModeSet(PORTA, MOTOR_LEFT_RED,  gpioModePushPull,1);
		GPIO_PinModeSet(PORTB, MOTOR_LEFT_BLACK,  gpioModePushPull,0);
		GPIO_PinModeSet(PORTB, MOTOR_RIGHT_RED,  gpioModePushPull,0);
		GPIO_PinModeSet(PORTB, MOTOR_RIGHT_BLACK,  gpioModePushPull,1);
		break;

	case front:
		GPIO_PinModeSet(PORTA, MOTOR_LEFT_RED, gpioModePushPull,0);
		GPIO_PinModeSet(PORTB, MOTOR_LEFT_BLACK, gpioModePushPull,1);
		GPIO_PinModeSet(PORTB, MOTOR_RIGHT_RED, gpioModePushPull,1);
		GPIO_PinModeSet(PORTB, MOTOR_RIGHT_BLACK,gpioModePushPull,0);
		break;

	case stop:
		GPIO_PinModeSet(PORTA, MOTOR_LEFT_RED, gpioModePushPull,0);
		GPIO_PinModeSet(PORTB, MOTOR_LEFT_BLACK, gpioModePushPull,0);
		GPIO_PinModeSet(PORTB, MOTOR_RIGHT_RED, gpioModePushPull,0);
		GPIO_PinModeSet(PORTB, MOTOR_RIGHT_BLACK,gpioModePushPull,0);
		break;
	}
	GRAPHICS_Clear();
	black_box_update(movement);
}

void motor_test(void)
{
	static uint8_t move=0;
	static uint16_t move_counter = 4000;
	if(move_counter == 4000)
	{
	move_motors(move);
	move++;
	move=move%5;
	move_counter=0;
	}
	else
	{
		move_counter++;
	}
}
