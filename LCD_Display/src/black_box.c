/*
 * black_box.c
 *
 *  Created on: Apr 2, 2018
 *      Author: monish and sanika
 */
#include "black_box.h"

/***********************************************************************
 * @brief data_transfer()
 * Function to shift previous signals
 ***********************************************************************/
void data_transfer(void)
{
	uint8_t i=0;
	for(i=1;i<DATA_ARRAY_SIZE;i++)
	{
		persistent_memory_load(&temporary_data,data_address_array[DATA_ARRAY_SIZE-i-1]);
		persistent_memory_save(&temporary_data,data_address_array[DATA_ARRAY_SIZE-i]);
	}
	return;
}

/***********************************************************************
 * @brief black_box_update()
 * Function to update information
 ***********************************************************************/
void black_box_update(uint8_t data)
{
	temporary_data.data[0] = data;
 	persistent_memory_save(&temporary_data,data_address_array[0]);
	data_transfer();
 	previous_signals_display();
 	return;
}

/***********************************************************************
 * @brief black_box_init()
 * Initialize the black box
 ***********************************************************************/
void black_box_init(void)
{
    temporary_data.len = 1;
    previous_signals_display();
}

/***********************************************************************
 * @brief previous_signals_display()
 * Function to display previous signals on LCD screen
 ***********************************************************************/
void previous_signals_display(void)
{
	uint8_t i=0,signal=0;
	for(i=1;i<DATA_ARRAY_SIZE;i++)
	{
		persistent_memory_load(&temporary_data,data_address_array[i]);
		signal = temporary_data.data[0];
		switch (signal)
		{
			case front:
			{
				GRAPHICS_AppendString("Front");
				break;
			}
			case behind:
			{
				GRAPHICS_AppendString("Behind");
				break;
			}
			case left:
			{
				GRAPHICS_AppendString("Left");
				break;
			}
			case right:
			{
				GRAPHICS_AppendString("Right");
				break;
			}
			case stop:
			{
				GRAPHICS_AppendString("Stop");
				break;
			}
			default:
			{
				GRAPHICS_AppendString("Error");
				break;
			}
		}
	}
	GRAPHICS_Update();
}
