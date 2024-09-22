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
#include "hash_calculation_worker.h"

#include <Windows.h>

struct ReceivedThreadMessages
{
    BOOL cancel_requested;
};

struct OutgoingEventMessageTarget
{
    HWND event_message_receiver;
    struct HashCalculationWorkerEventMessage* receiver_event_message_buf;
    HANDLE receiver_event_message_buf_is_writeable_event;
};

struct OnProgressCallbackArguments
{
    struct HashCalculationWorkerEventMessage* sender_event_message_buf;
    struct OutgoingEventMessageTarget* event_message_target;
};

struct HashCalculationWorkerCtx
{
    struct HashCalculationWorkerParam hash_calc_worker_param;
    struct OutgoingEventMessageTarget event_message_target;
    struct HashCalculationWorkerEventMessage event_message_buf;
    struct ReceivedThreadMessages received_thread_messages;
    wchar_t calculation_result_string[GENERIC_TXT_MESSAGES_BUFFER_TSIZE];
    size_t calculation_result_string_tsize;
    unsigned char file_read_buf[FILE_READ_BUF_TSIZE];
    size_t file_read_buf_tsize;

    struct OnProgressCallbackArguments on_progress_cb_args;
};

/**
 * Initializes the context data with the information from the
 * provided hash calculation worker parameters.
 * 
 * @param worker_ctx Allocated but uninitialized context data of
 *                   the target hash calculation worker instance.
 * @param worker_param Start parameters of the hash calculation worker
 *                     thread.
 */
extern
void
uhashtools_hash_calculation_worker_ctx_init
(
    struct HashCalculationWorkerCtx* worker_ctx,
    const struct HashCalculationWorkerParam* worker_param
);
