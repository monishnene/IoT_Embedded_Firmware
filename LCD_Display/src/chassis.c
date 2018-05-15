/*
 * chassis.c
 *
 *  Created on: Apr 17, 2018
 *      Author: Sanika & Monish
 */


#include "chassis.h"

void move_motors(controls movement)
{
	switch(movement)
	{
	case behind:
		GPIO_PinModeSet(PORTA, MOTOR_LEFT_RED, gpioModePushPull,1);
		GPIO_PinModeSet(PORTB, MOTOR_LEFT_BLACK, gpioModePushPull,0);
		GPIO_PinModeSet(PORTB, MOTOR_RIGHT_RED,gpioModePushPull ,1);
		GPIO_PinModeSet(PORTB, MOTOR_RIGHT_BLACK, gpioModePushPull,0);
		break;

	case front:
		GPIO_PinModeSet(PORTA, MOTOR_LEFT_RED,  gpioModePushPull,0);
	    GPIO_PinModeSet(PORTB, MOTOR_LEFT_BLACK, gpioModePushPull,1);
		GPIO_PinModeSet(PORTB, MOTOR_RIGHT_RED, gpioModePushPull,0);
		GPIO_PinModeSet(PORTB, MOTOR_RIGHT_BLACK, gpioModePushPull,1);
		break;

	case left:
		GPIO_PinModeSet(PORTA, MOTOR_LEFT_RED,  gpioModePushPull,1);
		GPIO_PinModeSet(PORTB, MOTOR_LEFT_BLACK,  gpioModePushPull,0);
		GPIO_PinModeSet(PORTB, MOTOR_RIGHT_RED,  gpioModePushPull,0);
		GPIO_PinModeSet(PORTB, MOTOR_RIGHT_BLACK,  gpioModePushPull,1);
		break;

	case right:
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
