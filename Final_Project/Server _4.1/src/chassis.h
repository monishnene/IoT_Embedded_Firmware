/*
 * chassis.h
 *
 *  Created on: Apr 17, 2018
 *      Author: sanika
 */


#include "native_gecko.h"
#include "black_box.h"
//Motor Pins
#define PORTA gpioPortA
#define MOTOR_LEFT_RED (5)
#define MOTOR_LEFT_RED_default false

#define PORTB gpioPortB
#define MOTOR_LEFT_BLACK (11)
#define MOTOR_LEFT_BLACK_default false


#define MOTOR_RIGHT_RED  (12)
#define MOTOR_RIGHT_RED_default false

#define MOTOR_RIGHT_BLACK  (13)
#define MOTOR_RIGHT_BLACK_default false

void move_motors(movement_command movement);
void motor_test(void);
