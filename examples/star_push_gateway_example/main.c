/*

 *  \copyright (C) Copyright 2015 University of Antwerp and others (http://oss-7.cosys.be)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Contributors:
 *     maarten.weyn@uantwerpen.be
 *
 * 	Example code for Star topology, push model
 * 	This is the Gateway example
 *
 * 	add the link to d7aoss library in de lnk_*.cmd file, e.g. -l "../../../d7aoss/Debug/d7aoss.lib"
 * 	Make sure to select the correct platform in d7aoss.h
 * 	If your platform is not present, you can add a header file in platforms and commit it to the repository.
 * 	Exclude the stub directories in d7aoss from the build when building for a device.
 *
 *  Create the apporpriate file system settings for the FLASH system:
 *
 * 	Add following sections to the SECTIONS in .cmd linker file to use the filesystem
 *		.fs_fileinfo_bitmap : 	{} > FLASH_FS1
 *  	.fs_fileinfo: 			{} > FLASH_FS1
 *		.fs_files	: 			{} > FLASH_FS2
 *
 *	Add FLASH_FS_FI and FLASH_FS_FILES to the MEMORY section
 *  eg.
 *  	FLASH_FS1               : origin = 0xC000, length = 0x0200 // The file headers
 *	    FLASH_FS2               : origin = 0xC200, length = 0x0400 // The file contents
 */


#include <d7aoss.h>
#include <framework/log.h>
#include <framework/timer.h>
#include <hal/leds.h>

#define TX_EIRP 10
#define USE_LEDS

static bool start_channel_scan = false;
uint8_t buffer[128];

static uint8_t receive_channel[2] = {0x04, 0x00};

void start_rx()
{
	start_channel_scan = false;
	trans_rx_query_start(0xFF, receive_channel);
}

void rx_callback(Trans_Rx_Alp_Result* rx_res)
{
	system_watchdog_timer_reset();

	led_blink(1);

	if (rx_res->nwl_rx_res->protocol_type == ProtocolTypeNetworkProtocol)
	{
		nwl_ff_D7ANP_t* np = (nwl_ff_D7ANP_t*) (rx_res->nwl_rx_res->data);
		uint8_t* address_ptr = NULL;
		uint8_t address_length = 0;

		switch (np->control & NWL_CONTRL_SRC_FULL)
		{
		case NWL_CONTRL_SRC_UID:
			address_ptr = &(np->d7anp_source_access_templ[0]);
			address_length = 8;
			break;
		case NWL_CONTRL_SRC_VID:
			address_ptr = &(np->d7anp_source_access_templ[0]);
			address_length = 2;
			break;
		case NWL_CONTRL_SRC_FULL:
			address_ptr = &(np->d7anp_source_access_templ[1]);

			if (np->d7anp_source_access_templ[0] & NWL_ACCESS_TEMPL_CTRL_VID)
			{
				address_length = 8;
			} else {
				address_length = 2;
			}
		}

		if (address_length == 2)
		{
			log_print_string("Received Query from: %x%x%x%x",
								address_ptr[1] >> 4, address_ptr[1] & 0x0F);
		} else if (address_length == 8) {
			log_print_string("Received Query from: %x%x%x%x%x%x%x%x%x%x%x%x%x%x%x",
					address_ptr[0] >> 4, address_ptr[0] & 0x0F,
					address_ptr[1] >> 4, address_ptr[1] & 0x0F,
					address_ptr[2] >> 4, address_ptr[2] & 0x0F,
					address_ptr[3] >> 4, address_ptr[3] & 0x0F,
					address_ptr[4] >> 4, address_ptr[4] & 0x0F,
					address_ptr[5] >> 4, address_ptr[5] & 0x0F,
					address_ptr[6] >> 4, address_ptr[6] & 0x0F,
					address_ptr[7] >> 4, address_ptr[7] & 0x0F);
		}
	log_print_string("RSS: %d dBm", rx_res->nwl_rx_res->dll_rx_res->rssi);
	//log_print_string("Netto Link: %d dBm", rx_res->nwl_rx_res->dll_rx_res->rssi  - ((frame->control & 0x3F) - 32));

	log_print_string("D7AQP received - ALP data:");

	log_print_data((uint8_t*) (rx_res->alp_record.alp_templates), rx_res->alp_record.record_lenght-3);
	}
	start_channel_scan = true;

}


int main(void) {
	// Initialize the OSS-7 Stack
	d7aoss_init(buffer, 128, buffer, 128);

	trans_set_alp_rx_callback(&rx_callback);
	// The initial Tca for the CSMA-CA in
	dll_set_initial_t_ca(200);

	start_channel_scan = true;


	log_print_string("gateway started");

	// Log the device id
	log_print_data(device_id, 8);


	system_watchdog_init(0x0020, 0x03);
	system_watchdog_timer_start();

	led_blink(1);

	while(1)
	{
		if (start_channel_scan)
		{
			start_rx();
		}

		// Don't know why but system reboots when LPM > 1 since ACLK is uses for UART
		system_lowpower_mode(0,1);
	}
}
