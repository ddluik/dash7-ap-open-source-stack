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
 *
 */

#include "../system.h"
#include "../framework/queue.h"
#include "../dae/fs.h"

void PMM_SetVCore (uint8_t level)
{

}

void system_init(uint8_t* tx_buffer, uint16_t tx_buffer_size, uint8_t* rx_buffer, uint16_t rx_buffer_size)
{
    // TODO not hardware specific
    queue_init_with_header(&tx_queue, tx_buffer, tx_buffer_size, 1, 30);
    queue_init(&rx_queue, rx_buffer, rx_buffer_size, 1);

    file_handler fh;
    fs_open(&fh, DA_FILE_ID_UID, file_system_user_root, file_system_access_type_read);
    device_id = fs_get_data_pointer(&fh, 0);
}

void system_watchdog_timer_stop()
{

}

void system_watchdog_timer_start()
{

}

void system_watchdog_timer_reset()
{

}

void system_watchdog_timer_enable_interrupt()
{

}

void system_watchdog_timer_init(unsigned char clockSelect, unsigned char clockDivider)
{

}

void system_watchdog_init(unsigned char clockSelect, unsigned char clockDivider)
{

}

void system_lowpower_mode(unsigned char mode, unsigned char enableInterrupts)
{

}

void system_get_unique_id(unsigned char *tagId)
{

}
