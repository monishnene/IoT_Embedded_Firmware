/*
 * persistent_memory.h
 *
 *  Created on: Mar 31, 2018
 *      Author: monish
 */

#ifndef SRC_PERSISTENT_MEMORY_H_
#define SRC_PERSISTENT_MEMORY_H_
#include "bg_types.h"
#include "native_gecko.h"
#include "graphics.h"

void print_number(uint32_t number);
void persistent_memory_load(uint8array* data_array, uint16_t persistent_memory_location);
void persistent_memory_save(uint8array* data_array, uint16_t persistent_memory_location);
void persistent_memory_erase(uint16_t persistent_memory_location);
void persistent_memory_erase_all(void);
#endif /* SRC_PERSISTENT_MEMORY_H_ */
