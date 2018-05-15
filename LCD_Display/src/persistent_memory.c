/*
 * persistent_memory.c
 *
 *  Created on: Mar 31, 2018
 *      Author: monish and sanika
 */

#include "persistent_memory.h"


void print_number(uint32_t number)
{
	uint8_t number_to_be_printed[20];
	itoa(number, number_to_be_printed,10);
	GRAPHICS_AppendString(number_to_be_printed);
	return;
}


 /***********************************************************************
  * @brief persistent_memory_load()
  * @param data_array structure with data and length of data to be loaded
  * @param persistent_memory_location ps address of the data to be loaded
  * Read the instantaneous value of joystick with ADC
  ***********************************************************************/
 void persistent_memory_load(uint8array* data_array, uint16_t persistent_memory_location)
{
	uint8_t i=0;
	struct gecko_msg_flash_ps_load_rsp_t* load_ptr;
	load_ptr = gecko_cmd_flash_ps_load(persistent_memory_location);
	if(load_ptr->result)
	{
		GRAPHICS_AppendString("load fail\r\n");
		GRAPHICS_Update();
		return ;
	}
	data_array-> len = load_ptr->value.len;
	for(i=0; i < data_array-> len ;i++)
	{
		data_array->data[i] = load_ptr->value.data[i];
	}
	return;
}

 /***********************************************************************
  * @brief persistent_memory_save()
  * @param data_array structure with data and length of data to be saved
  * @param persistent_memory_location ps address of the data to be saved
  * Read the instantaneous value of joystick with ADC
  ***********************************************************************/
 void persistent_memory_save(uint8array* data_array, uint16_t persistent_memory_location)
{
	struct gecko_msg_flash_ps_save_rsp_t* save_ptr;
	save_ptr = gecko_cmd_flash_ps_save( persistent_memory_location, data_array->len, (const uint8_t*) data_array -> data);
	if(save_ptr->result)
	{
		GRAPHICS_AppendString("Save failed\r\n");
		GRAPHICS_Update();
		return;
	}
	return ;
}

 /***********************************************************************
  * @brief persistent_memory_erase()
  * @param persistent_memory_location ps address of the data to be erased
  * Read the instantaneous value of joystick with ADC
  ***********************************************************************/
 void persistent_memory_erase(uint16_t persistent_memory_location)
{
	struct gecko_msg_flash_ps_erase_rsp_t * erase_ptr;
	erase_ptr = gecko_cmd_flash_ps_erase(persistent_memory_location);
	if(erase_ptr->result)
	{
		GRAPHICS_AppendString("Erase failed\r\n");
		GRAPHICS_Update();
		return;
	}
	return;
}

 /***********************************************************************
  * @brief persistent_memory_erase_all()
  * Erase all data stored in PS
  ***********************************************************************/
 void persistent_memory_erase_all(void)
{
	struct gecko_msg_flash_ps_erase_all_rsp_t * erase_all_ptr;
	erase_all_ptr = gecko_cmd_flash_ps_erase_all();
	if(erase_all_ptr->result)
	{
		GRAPHICS_AppendString("Erase all failed\r\n");
		GRAPHICS_Update();
		return;
	}
	return;
}
