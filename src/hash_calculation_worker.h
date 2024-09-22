/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "buffer_sizes.h"
#include "hash_calculation_worker_com.h"

#include <Windows.h>

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

/**
 * Sends a cancellation request to the given worker thread.
 * 
 * @param worker_thread_id Thread id of the hash calculation worker.
 */
extern
void
uhashtools_hash_calculation_worker_request_cancellation
(
    DWORD worker_thread_id
);
