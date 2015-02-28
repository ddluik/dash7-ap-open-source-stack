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
 *     	glenn.ergeerts@uantwerpen.be
 *     	maarten.weyn@uantwerpen.be
 *		alexanderhoet@gmail.com
 *
 */

#include "cc430_phy.h"

// Interrupt branch table
InterruptHandler interrupt_table[34] = {
	//Rising Edges
	no_interrupt_isr,        	// 00 No RF core interrupt pending
	rx_timeout_isr,			    // 01 RFIFG0 - Timeout
	no_interrupt_isr,           // 02 RFIFG1 - RSSI_VALID
	no_interrupt_isr,           // 03 RFIFG2
	rx_data_isr,				// 04 RFIFG3 - RX FIFO filled or above the RX FIFO threshold
	no_interrupt_isr,           // 05 RFIFG4 - RX FIFO filled or above the RX FIFO threshold or end of packet is reached (Do not use for eop! Will not reset until rxfifo emptied)
	no_interrupt_isr,		    // 06 RFIFG5 - TX FIFO filled or above the TX FIFO threshold
	no_interrupt_isr,			// 07 RFIFG6 - TX FIFO full
	rx_fifo_overflow_isr, 	    // 08 RFIFG7 - RX FIFO overflowed
	rxtx_finish_isr,			// 09 RFIFG8 - TX FIFO underflowed
	no_interrupt_isr,			// 10 RFIFG9 - Sync word sent or received
	no_interrupt_isr,           // 11 RFIFG10 - Packet received with CRC OK
	no_interrupt_isr,           // 12 RFIFG11 - Preamble quality reached (PQI) is above programmed PQT value
	no_interrupt_isr,           // 13 RFIFG12 - Clear channel assessment when RSSI level is below threshold
	no_interrupt_isr,           // 14 RFIFG13 - Carrier sense. RSSI level is above threshold
	no_interrupt_isr,           // 15 RFIFG14 - WOR event 0
	no_interrupt_isr,       	// 16 RFIFG15 - WOR event 1

	//Falling Edges
	no_interrupt_isr,        	// No RF core interrupt pending
	no_interrupt_isr,			// 17 RFIFG0 TODO: timeout not implemented yet
	no_interrupt_isr,           // 18 RFIFG1 - RSSI_VALID
	no_interrupt_isr,           // 19 RFIFG2 -
	no_interrupt_isr,			// 20 RFIFG3 - RX FIFO drained below RX FIFO threshold
	no_interrupt_isr,           // 21 RFIFG4 - RX FIFO empty
	tx_data_isr,				// 22 RFIFG5 - TX FIFO below TX FIFO threshold
	no_interrupt_isr,			// 23 RFIFG6 - TX FIFO below TX FIFO threshold
	no_interrupt_isr,           // 24 RFIFG7 - RX FIFO flushed
	no_interrupt_isr,			// 25 RFIFG8 - TX FIFO flushed
	end_of_packet_isr,			// 26 RFIFG9 - End of packet or in RX when optional address check fails or RX FIFO overflows or in TX when TX FIFO underflows
	no_interrupt_isr,           // 27 RFIFG10 - First byte read from RX FIFO
	no_interrupt_isr,           // 28 RFIFG11 - (LPW)
	no_interrupt_isr,           // 29 RFIFG12 - RSSI level is above threshold
	no_interrupt_isr,           // 30 RFIFG13 - RSSI level is below threshold
	no_interrupt_isr,           // 31 RFIFG14 - WOR event 0 + 1 ACLK
	no_interrupt_isr,       	// 32 RFIFG15 - RF oscillator stable or next WOR event0 triggered
};
