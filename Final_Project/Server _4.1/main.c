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
sleep.h, em_letimer.h, em_emu.h, em_core.h, em_cmu.h, em_assert.h, graphics.h, native_gecko.h, bg_types.h,
I have referred the code for accelerometer, mitm, encryption-decryption from silicon labs
I have referred the server and client sample examples from silicon labs website to develop my project.
I have used the event scheduler developed by silicon labs.
*****/


/* Board headers */

//***********************************************************************************
// defined files
//***********************************************************************************
#define reset_counter_address (0x4004)
#define gattdb_temp_measurement (15)
#ifndef MAX_CONNECTIONSinlcude
#define MAX_CONNECTIONS 4
#endif
#define Max_Transmit_Power	(80)
#define Min_Transmit_Power	(-260)
#define Slave_interval	(450)
#define Latency	((Slave_interval/(1.25*Connection_interval))-1)
#define Connection_interval	(75/1.25)
#define Advertise (7)
#define Timeout (20)
#include "init_mcu.h"
#include "init_board.h"
#include "ble-configuration.h"
#include "board_features.h"
#include "gpio.h"
#include "cmu.h"
#include "em_letimer.h"
#include "persistent_memory.h"
#include "bg_types.h"
#include "native_gecko.h"
#include "gatt_db.h"
#include "em_chip.h"
/* Libraries containing default Gecko configuration values */
#include "em_emu.h"
#include "em_cmu.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "gatt_db.h"
#include "graphics.h"
//#include  "si7013.h"
/* Device initialization header */
#include "hal-config.h"
#include "sleep.h"
#include "infrastructure.h"
#include "letimer.h"
#include "main.h"
#include "black_box.h"
#include "chassis.h"
#include "lux.h"
#ifdef HAL_CONFIG
#include "bsphalconfig.h"
#else
#include "bspconfig.h"
#endif
uint8_t BLE_CON;
#include "sleep.h"

uint8_t activeConnectionId=0;
bool read_pk;
bool read_y_n;



//***********************************************************************************
// global variables
//***********************************************************************************
#define SPP_TX_TIMER  2

#define STATE_ADVERTISING 1
#define STATE_CONNECTED   2
#define STATE_SPP_MODE    3

static uint8 _conn_handle = 0xFF;
static int _main_state;

static void reset_variables()
{
	_conn_handle = 0xFF;
	_main_state = STATE_ADVERTISING;
}


uint8_t bluetooth_stack_heap[DEFAULT_BLUETOOTH_HEAP(MAX_CONNECTIONS)];

// Gecko configuration parameters (see gecko_configuration.h)
//uint8_t boot_to_dfu = 0;

#include "main.h"

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

void reset_board(void)
{
	reset_variables();
	/* Start general advertising and enable connections. */
	gecko_cmd_sm_delete_bondings();
	gecko_cmd_sm_configure(0x0F, sm_io_capability_displayyesno); /* Numeric comparison */
	gecko_cmd_sm_set_bondable_mode(1);
	gecko_cmd_le_gap_set_adv_parameters(Advertise,Advertise,7);
	gecko_cmd_le_gap_set_mode(le_gap_general_discoverable, le_gap_undirected_connectable);
	GRAPHICS_AppendString("Monish & Sanika");
	GRAPHICS_AppendString("Server");
	GRAPHICS_AppendString("Advertising");
	GRAPHICS_Update();
}

void main(void)
{
	uint8_t printbuf[128];
	uint8_t next_move = behind, prev_move = stop, led_status = both_on, led_0_status = 0, led_1_status = 0, brightness = 5, test_value='M';
	uint32_t passkey=0;
	CHIP_Init();
    // Initialize device
    initMcu();
    // Initialize board
    initBoard();
    /* Initialize GPIO */
    gpio_init();
    // Initialize clocks
    cmu_init();
    GRAPHICS_Init();
    // Initialize stack
    gecko_init(&config);
    //lux_init();
    GRAPHICS_Clear();
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
			{
				reset_board();
				break;
			}

			case gecko_evt_le_connection_closed_id:
			{
				reset_board();
				SLEEP_SleepBlockEnd(sleepEM2); // enable sleeping
				break;
			}

			/* Connection opened event */

			case gecko_evt_le_connection_opened_id:
			{
				_conn_handle = evt->data.evt_le_connection_opened.connection;
				_main_state = STATE_CONNECTED;
				activeConnectionId = evt->data.evt_le_connection_opened.connection;
				gecko_cmd_sm_increase_security(activeConnectionId);
				gecko_cmd_le_connection_set_parameters(BLE_CONNECT,Connection_interval,Connection_interval,Latency,Timeout);
				break;
			}

			/*
			case gecko_evt_le_connection_parameters_id:
			{
				evt->data.evt_le_connection_parameters.interval;
				evt->data.evt_le_connection_parameters.txsize;
				break;
			}
			*/
			case gecko_evt_sm_confirm_passkey_id:
			{
				passkey = evt->data.evt_sm_confirm_passkey.passkey;
				GRAPHICS_Clear();
				GRAPHICS_AppendString("Passkey");
				print_number(passkey);
				GRAPHICS_Update();
			    letimer_init();
				while(GPIO_PinInGet(PB0_port,PB0_pin)&&GPIO_PinInGet(PB1_port,PB1_pin));
				black_box_init();
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
				//lux_test();
			    //brightness=lux_read();
				brightness++;
				gecko_cmd_gatt_server_send_characteristic_notification(0xFF,gattdb_Brightness_value_ID,1,&brightness);
				break;
			}

			case gecko_evt_gatt_server_user_write_request_id:
			{
				/* Automation IO digital control */
				if (evt->data.evt_gatt_server_user_write_request.characteristic == gattdb_PB0_ID)
				{
					led_status = evt->data.evt_gatt_server_attribute_value.value.data[0];
					GRAPHICS_Clear();
					print_number(led_status);
					GRAPHICS_Update();
					switch (led_status)
					{
						case led_0_on:
						{
							led_0_status = 1;
							led_1_status = 0;
							break;
						}

						case led_1_on:
						{
							led_0_status = 0;
							led_1_status = 1;
							break;
						}

						case both_on:
						{
							led_1_status = 1;
							led_0_status = 1;
							break;
						}

						case none_on:
						{
							led_1_status = 0;
							led_0_status = 0;
							break;
						}

						default:
						{
							break;
						}
					}
					GPIO_PinModeSet(LED1_port, LED1_pin, gpioModePushPull,led_1_status);
					GPIO_PinModeSet(LED0_port, LED0_pin, gpioModePushPull,led_0_status);
					gecko_cmd_gatt_server_send_user_write_response(evt->data.evt_gatt_server_user_write_request.connection,gattdb_PB0_ID,bg_err_success);
				}
				if (evt->data.evt_gatt_server_user_write_request.characteristic == gattdb_Next_Move_ID)
				{
					next_move = evt->data.evt_gatt_server_attribute_value.value.data[0];
					switch(next_move)
					{
						case right_ahead:
						{
							next_move = right;
							break;
						}

						case left_ahead:
						{
							next_move = left;
							break;
						}

						case right_back:
						{
							next_move = right;
							break;
						}

						case left_back:
						{
							next_move = left;
							break;
						}

						default:
						{
							break;
						}
					}
					if(prev_move!=next_move)
					{
						move_motors(next_move);
						prev_move = next_move;
					}
					gecko_cmd_gatt_server_send_user_write_response(evt->data.evt_gatt_server_user_write_request.connection,gattdb_Next_Move_ID,bg_err_success);
				}
				break;
			}

			case gecko_evt_gatt_server_attribute_value_id:
			{
				memcpy(printbuf, evt->data.evt_gatt_server_attribute_value.value.data, evt->data.evt_gatt_server_attribute_value.value.len);
				printbuf[evt->data.evt_gatt_server_attribute_value.value.len] = 0;
				break;
			}

			default:
			{
				break;
			}
		}
	}
}
