/***********************************************************************************************//**
 * \file   main.c
 * \brief  Silicon Labs Empty Example Project
 *
 * This example demonstrates the bare minimum needed for a Blue Gecko C application
 * that allows Over-the-Air Device Firmware Upgrading (OTA DFU). The application
 * starts advertising after boot and restarts advertising after a connection is closed.
 ***************************************************************************************************
 * <b> (C) Copyright 2016 Silicon Labs, http://www.silabs.com</b>
 ***************************************************************************************************
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 **************************************************************************************************/
/***** Credit for the Sleep functions and Letimer functions goes to Silicon Labs *****/
/***** Note: All the functions defined in the following files used in my code were developed by Silicon Labs ->
sleep.h, em_letimer.h, em_emu.h, em_core.h, em_cmu.h, em_assert.h*****/
/* Board headers */
#include "init_mcu.h"
#include "init_board.h"
#include "ble-configuration.h"
#include "board_features.h"
#include "main.h"
#include "gpio.h"
#include "cmu.h"
#include "em_letimer.h"
/* Bluetooth stack headers */
#include "bg_types.h"
#include "native_gecko.h"
#include "gatt_db.h"
#include "em_chip.h"
#include "letimer_sleep.h"
#include "temperature_i2c.h"
/* Libraries containing default Gecko configuration values */
#include "em_emu.h"
#include "em_cmu.h"
//#include  "si7013.h"
/* Device initialization header */
#include "hal-config.h"
#include "sleep.h"
#include "infrastructure.h"
#if defined(HAL_CONFIG)
#include "bsphalconfig.h"
#else
#include "bspconfig.h"
#endif


/***********************************************************************************************//**
 * @addtogroup Application
 * @{
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup app
 * @{
 **************************************************************************************************/
#define gattdb_temp_measurement (15)
#ifndef MAX_CONNECTIONS
#define MAX_CONNECTIONS 4
#endif
#define Max_Transmit_Power	(80)
#define Min_Transmit_Power	(-260)
#define Slave_interval	(450)
#define Latency	((Slave_interval/(1.25*Connection_interval))-1)
#define Connection_interval	(75/1.25)
#define Advertise (529)
#define Timeout (480)
uint8_t bluetooth_stack_heap[DEFAULT_BLUETOOTH_HEAP(MAX_CONNECTIONS)];

// Gecko configuration parameters (see gecko_configuration.h)
static const gecko_configuration_t config = {
  .config_flags = 0,
  .sleep.flags = SLEEP_FLAGS_DEEP_SLEEP_ENABLE,
  .bluetooth.max_connections = MAX_CONNECTIONS,
  .bluetooth.heap = bluetooth_stack_heap,
  .bluetooth.heap_size = sizeof(bluetooth_stack_heap),
  .bluetooth.sleep_clock_accuracy = 100, // ppm
  .gattdb = &bg_gattdb_data,
  .ota.flags = 0,
  .ota.device_name_len = 3,
  .ota.device_name_ptr = "OTA",
#if (HAL_PA_ENABLE) && defined(FEATURE_PA_HIGH_POWER)
  .pa.config_enable = 1, // Enable high power PA
  .pa.input = GECKO_RADIO_PA_INPUT_VBAT, // Configure PA input to VBAT
#endif // (HAL_PA_ENABLE) && defined(FEATURE_PA_HIGH_POWER)
};

// Flag for indicating DFU Reset must be performed
uint8_t boot_to_dfu = 0;
//***********************************************************************************
// Include files
//***********************************************************************************



//***********************************************************************************
// defined files
//***********************************************************************************


//***********************************************************************************
// global variables
//***********************************************************************************


//***********************************************************************************
// function prototypes
//***********************************************************************************


//***********************************************************************************
// functions
//***********************************************************************************


//***********************************************************************************
// main
//***********************************************************************************

	void temperature_read_and_send_over_bluetooth(void)
	{
		uint8_t temp_buffer[5];
		uint8_t flags = 0;
		uint32_t temperature=0;
		temperature = get_temperature();
		uint8_t* temp_buffer_ptr = temp_buffer;
		Load_Power_Management(false);
		UINT8_TO_BITSTREAM(temp_buffer_ptr,flags);
		temperature = FLT_TO_UINT32(temperature,-3);
		UINT32_TO_BITSTREAM(temp_buffer_ptr,temperature);
		gecko_cmd_gatt_server_send_characteristic_notification(0xFF,gattdb_temp_measurement,5,temp_buffer);
	}

/**
 * @brief  Main function
 *
 */

int main(void)
{
	CHIP_Init();
    uint32_t i=0;
    uint8_t temp_mode=0;
    /* peripheral initialization routine();
  peripheral_call();*/
    // Initialize device
    initMcu();
    // Initialize board
    initBoard();

    /* Initialize GPIO */
    gpio_init();
    // Initialize clocks
    cmu_init();

    // Initialize stack
    gecko_init(&config);
    //block_sleep_mode(EM3);
    //block_sleep_mode(EM2);
    //block_sleep_mode(EM1);
    temp_i2c_init();
	cmu_letimer_init(cmuClkDiv_1);
 	letimer_sleep_init();

	while(1)
	{

	    /* Event pointer for handling events */
	    struct gecko_cmd_packet* evt;

	    /* Check for stack event. */
	    evt = gecko_wait_event();

	    /* Handle events */
	    switch (BGLIB_MSG_ID(evt->header))
	    {
				/* This boot event is generated when the system boots up after reset.
				* Do not call any stack commands before receiving the boot event.
				* Here the system is set to start advertising immediately after boot procedure. */
				case gecko_evt_system_boot_id:

				/* Set advertising parameters. 100ms advertisement interval. All channels used.
				 * The first two parameters are minimum and maximum advertising interval, both in
				 * units of (milliseconds * 1.6). The third parameter '7' sets advertising on all channels. */
				gecko_cmd_le_gap_set_adv_parameters( Advertise, Advertise, 7);

				/* Start general advertising and enable connections. */
				gecko_cmd_le_gap_set_mode(le_gap_general_discoverable, le_gap_undirected_connectable);
				break;

				case gecko_evt_le_connection_closed_id:

				/* Check if need to boot to dfu mode */
				if (boot_to_dfu) {
				  /* Enter to DFU OTA mode */
				  gecko_cmd_system_reset(2);
				} else {
				  /* Restart advertising after client has disconnected */
				  gecko_cmd_le_gap_set_mode(le_gap_general_discoverable, le_gap_undirected_connectable);
				}
				break;

				/* Events related to OTA upgrading
				 ----------------------------------------------------------------------------- */

				/* Check if the user-type OTA Control Characteristic was written.
				* If ota_control was written, boot the device into Device Firmware Upgrade (DFU) mode. */
				case gecko_evt_gatt_server_user_write_request_id:

				if (evt->data.evt_gatt_server_user_write_request.characteristic == gattdb_ota_control) {
				  /* Set flag to enter to OTA mode */
				  boot_to_dfu = 1;
				  /* Send response to Write Request */
				  gecko_cmd_gatt_server_send_user_write_response(
					evt->data.evt_gatt_server_user_write_request.connection,
					gattdb_ota_control,
					bg_err_success);
				  //GPIO_PinModeSet(LED0_port, LED1_pin, gpioModePushPull, LED_ON);
				  if(temperature_threshold==15)
					  {
						  temperature_threshold=40;
					  }
					  else
					  {
						  temperature_threshold=15;
					  }
					  /* Close connection to enter to DFU OTA mode */
					  gecko_cmd_endpoint_close(evt->data.evt_gatt_server_user_write_request.connection);
				}
				break;

				case gecko_evt_le_connection_opened_id:
				{
					BLE_CONNECT = evt -> data.evt_le_connection_opened.connection;
					gecko_cmd_le_connection_set_parameters(BLE_CONNECT,Connection_interval,Connection_interval,Latency,Timeout);
					break;
				}

				case gecko_evt_le_connection_rssi_id:
				{
					gecko_cmd_system_halt(1);
					if(evt->data.evt_le_connection_rssi.rssi > -35)
					{
						gecko_cmd_system_set_tx_power(Min_Transmit_Power);
					}
					else if((evt->data.evt_le_connection_rssi.rssi > -45)&&(evt->data.evt_le_connection_rssi.rssi < -35))
					{
						gecko_cmd_system_set_tx_power(-200);
					}
					else if((evt->data.evt_le_connection_rssi.rssi > -55)&&(evt->data.evt_le_connection_rssi.rssi < -45))
					{
						gecko_cmd_system_set_tx_power(-150);
					}
					else if((evt->data.evt_le_connection_rssi.rssi > -65)&&(evt->data.evt_le_connection_rssi.rssi < -55))
					{
						gecko_cmd_system_set_tx_power(-50);
					}
					else if((evt->data.evt_le_connection_rssi.rssi > -75)&&(evt->data.evt_le_connection_rssi.rssi < -65))
					{
						gecko_cmd_system_set_tx_power(0);
					}
					else if((evt->data.evt_le_connection_rssi.rssi > -85)&&(evt->data.evt_le_connection_rssi.rssi < -75))
					{
						gecko_cmd_system_set_tx_power(50);
					}
					else
					{
						gecko_cmd_system_set_tx_power(Max_Transmit_Power);
					}
					gecko_cmd_system_halt(0);
					break;
				}

				case gecko_evt_system_external_signal_id:
				{
				  if(temp_mode==0)
					{
					  	temperature_read_and_send_over_bluetooth();
						temp_mode=1;
						break;
					}
				  else
					{
						Load_Power_Management(true);
						/* Convert temperature to bitstream and place it in the HTM temperature data buffer (htmTempBuffer) */
						//UINT32_TO_BITSTREAM(temp_buffer_ptr, temp_buffer);
						//gecko_cmd_gatt_server_send_characteristic_notification(0xFF, 0xF, 5, temp_buffer);
						temp_mode=0;
						break;
					}
	    	  	}
	      default:
	        break;
	    }
	}
	return i;
}

/** @} (end addtogroup app) */
/** @} (end addtogroup Application) */
