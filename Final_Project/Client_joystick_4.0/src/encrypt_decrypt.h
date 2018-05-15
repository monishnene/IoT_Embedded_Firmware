/*
 * encrypt_decrypt.h
 *
 *  Created on: Apr 21, 2018
 *      Author: monish
 */

#ifndef SRC_ENCRYPT_DECRYPT_H_
#define SRC_ENCRYPT_DECRYPT_H_

#include "em_crypto.h"
#include <stdint.h>
#include "cmu.h"

static uint8_t encrypt_key[16]={141,14,42,66,56,112,86,97,235,133,31,43,99,77,60,165};
static uint32_t decrypt_key[8]={3945626059, 1922119292, 3074798766, 1297618938, 0, 0, 0, 0};
static CRYPTO_KeyBuf_TypeDef AppSecurityKeyDecrypt;

#define encrypt (1)
#define decrypt (0)

uint8_t encrypt_decrypt_test(void);
void generate_decrypt_key(void);
void decrypt_data(uint8_t* data_in, uint8_t* data_out, uint8_t data_words);
void encrypt_data(uint8_t* data_in, uint8_t* data_out, uint8_t data_words);
void encrypt_decrypt_init(void);

#endif /* SRC_ENCRYPT_DECRYPT_H_ */
