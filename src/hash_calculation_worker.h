/*
 * µHashtools - A small graphical file hashing tool for Microsoft Windows
 * Copyright (C) 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * 
 * This file is part of µHashtools.
 * 
 * µHashtools is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 * 
 * µHashtools is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * µHashtools. If not, see <https://www.gnu.org/licenses/>.
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <Windows.h>

#include "buffer_sizes.h"

enum HashCalculationWorkerEventType
{
    HCWET_MESSAGE_RECEIVER_INITIALIZED,
    HCWET_CALCULATION_PROGRESS_CHANGED,
    HCWET_CALCULATION_CANCELED,
    HCWET_CALCULATION_COMPLETE,
    HCWET_CALCULATION_FAILED
};

struct HashCalculationWorkerProgressChangedEventData
{
    unsigned int current_progress_in_percent;
};

struct HashCalculationWorkerCompletedEventData
{
    wchar_t calculated_hash[HASH_RESULT_BUFFER_TSIZE];
};

struct HashCalculationWorkerFailedEventData
{
    wchar_t user_error_message[GENERIC_TXT_MESSAGES_BUFFER_TSIZE];
};

struct HashCalculationWorkerEventMessage
{
    enum HashCalculationWorkerEventType event_type;
    union HashCalculationWorkerEventData
    {
        struct HashCalculationWorkerProgressChangedEventData progress_changed_data;
        struct HashCalculationWorkerCompletedEventData opperation_finished_data;
        struct HashCalculationWorkerFailedEventData opperation_failed_data;
    } event_data;
    
};

struct HashCalculationWorkerParam
{
    struct HashCalculationWorkerEventMessage* event_message_buf;
    HANDLE event_message_buf_is_writeable_event;
    HWND event_message_receiver;
    const wchar_t* target_file;
};

struct HashCalculationWorkerInstanceData
{
    BOOL created_sucessfully;
    HANDLE thread_handle;
    DWORD thread_id;
};

extern
struct HashCalculationWorkerInstanceData
uhashtools_hash_calculation_worker_start
(
    struct HashCalculationWorkerParam* worker_param_buf,
    struct HashCalculationWorkerEventMessage* event_message_buf,
    HANDLE event_message_buf_is_writeable_event,
    HWND event_message_receiver,
    const wchar_t* target_file
);

extern
BOOL
uhashtools_hash_calculation_worker_request_cancelation
(
    DWORD worker_thread_id
);