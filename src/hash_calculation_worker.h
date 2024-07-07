/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "buffer_sizes.h"

#include <Windows.h>

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
        struct HashCalculationWorkerCompletedEventData operation_finished_data;
        struct HashCalculationWorkerFailedEventData operation_failed_data;
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
    BOOL created_successfully;
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
uhashtools_hash_calculation_worker_request_cancellation
(
    DWORD worker_thread_id
);
