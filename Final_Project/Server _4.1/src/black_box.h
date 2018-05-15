/*
 * black_box.h
 *
 *  Created on: Apr 2, 2018
 *      Author: monish
 */

#ifndef SRC_BLACK_BOX_H_
#define SRC_BLACK_BOX_H_
#include "graphics.h"
#include "persistent_memory.h"
#include "stdint.h"
#define DATA_ARRAY_SIZE (13)
#define black_box_data_1 (0x4006)
#define black_box_data_2 (0x4007)
#define black_box_data_3 (0x4008)
#define black_box_data_4 (0x4009)
#define black_box_data_5 (0x400A)
#define black_box_data_6 (0x400B)
#define black_box_data_7 (0x400C)
#define black_box_data_8 (0x400D)
#define black_box_data_9 (0x400E)
#define black_box_data_10 (0x400F)
#define black_box_data_11 (0x4010)
#define black_box_data_12 (0x4011)
#define black_box_data_13 (0x4012)
static uint16_t data_address_array[]={
black_box_data_1,
black_box_data_2,
black_box_data_3,
black_box_data_4,
black_box_data_5,
black_box_data_6,
black_box_data_7,
black_box_data_8,
black_box_data_9,
black_box_data_10,
black_box_data_11,
black_box_data_12,
black_box_data_13,
};

typedef enum
{
	behind,
	front,
	right,
	left,
	stop,
	right_ahead,
	left_ahead,
	right_back,
	left_back,
}movement_command;

typedef enum
{
	led_0_on,
	led_1_on,
	both_on,
	none_on,
}on_leds;

uint8array temporary_data;
uint8_t data_current_head;
void black_box_update(uint8_t data);
void black_box_init(void);
void previous_signals_display(void);
void data_transfer(void);
#endif /* SRC_BLACK_BOX_H_ */
