/*
 * encrypt_decrypt.c
 *
 *  Created on: Apr 21, 2018
 *      Author: monish
 */
#include "encrypt_decrypt.h"

/***********************************************************************
 * @brief encrypt_decrypt_init
 * enable clock for encryption and decryption
 ***********************************************************************/
void encrypt_decrypt_init(void)
{
	cmu_encrypt_decrypt();
	return;
}

/***********************************************************************
 * @brief encrypt_data()
 * Function to display previous signals on LCD screen
 * @param data_in data to be encrypted
 * @param data_out encrypted data
 * @param data_words number of data words
 ***********************************************************************/
void encrypt_data(uint8_t* data_in, uint8_t* data_out, uint8_t data_words)
{
	CRYPTO_AES_ECB128(CRYPTO, data_out, data_in, 16*data_words, encrypt_key, encrypt);
	return;;
}

/***********************************************************************
 * @brief decrypt_data()
 * Function to display previous signals on LCD screen
 * @param data_in data to be decrypted
 * @param data_out decrypted data
 * @param data_words number of data words
 ***********************************************************************/
void decrypt_data(uint8_t* data_in, uint8_t* data_out, uint8_t data_words)
{
	CRYPTO_AES_ECB128(CRYPTO, data_out, data_in, 16*data_words, (uint8_t*)decrypt_key, decrypt);
	return;
}

/***********************************************************************
 * @brief generate_decrypt_key()
 * Generate the latest decrypt key
 ***********************************************************************/
void generate_decrypt_key(void)
{
	CRYPTO_KeyRead(CRYPTO, AppSecurityKeyDecrypt, 128);
	return;
}

/***********************************************************************
 * @brief encrypt_decrypt_test()
 * Function to display previous signals on LCD screen
 * @return encrypt_decypt_test
 ***********************************************************************/
uint8_t encrypt_decrypt_test(void)
{
	uint8_t data_original[16] = {12,32,43,54,55,66,77,254,66,123,43,234,167,153,55,78};
	uint8_t i=0,result=1,data_encrypted[16],data_decrypted[16];
	encrypt_data(data_original,data_encrypted,1);
	generate_decrypt_key();
	decrypt_data(data_encrypted,data_decrypted,1);
	for(i=0;i<16;i++)
	{
		if(data_original[i]!= data_decrypted[i])
		{
			result=0;
		}
	}
	return result;
}
