/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "hash_calculation_worker.h"

#include "error_utilities.h"
#include "hash_calculation_impl.h"
#include "hash_calculation_worker_com.h"
#include "hash_calculation_worker_ctx.h"
#include "print_utilities.h"

#include <process.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const unsigned int WORKER_THREAD_STACK_SIZE = 1024 * 512;

static
void
uhashtools_process_thread_messages
(
    struct ReceivedThreadMessages* received_thread_messages
)
{
    MSG peeked_msg;

    UHASHTOOLS_ASSERT(received_thread_messages,
                      L"Internal error: Entered with received_thread_messages == NULL!");

    while (PeekMessageW(&peeked_msg, (HWND) -1, WM_USER, WM_USER, PM_REMOVE))
    {
        if (peeked_msg.wParam == (WPARAM) HCWRC_CANCEL_HASH_CALCULATION)
        {
            received_thread_messages->cancel_requested = TRUE;
        }
    }
}

static
BOOL
uhashtools_check_is_cancel_requests_callback
(
    void* userdata
)
{
    BOOL ret = FALSE;
    struct ReceivedThreadMessages* received_thread_messages = NULL;

    if (!userdata)
    {
        return FALSE;
    }

    received_thread_messages = (struct ReceivedThreadMessages*) userdata;
    uhashtools_process_thread_messages(received_thread_messages);
    ret = received_thread_messages->cancel_requested;

    return ret;
}

static
void
uhashtools_on_progress_callback
(
    unsigned int current_calculation_progress,
    void* userdata
)
{
    struct OnProgressCallbackArguments* callback_arguments = NULL;
    struct HashCalculationWorkerEventMessage* sender_event_message_buf = NULL;
    struct OutgoingEventMessageTarget* event_message_target = NULL;

    if (!userdata)
    {
        return;
    }

    callback_arguments = (struct OnProgressCallbackArguments*) userdata;
    sender_event_message_buf = callback_arguments->sender_event_message_buf;
    event_message_target = callback_arguments->event_message_target;

    uhashtools_hash_calculation_worker_com_send_calculation_progress_message(sender_event_message_buf,
                                                                             event_message_target->event_message_receiver,
                                                                             event_message_target->receiver_event_message_buf,
                                                                             event_message_target->receiver_event_message_buf_is_writeable_event,
                                                                             current_calculation_progress);
}

static
void
uhashtools_thread_message_queue_init
(
    void
)
{
    MSG peeked_msg;

    /*
     * The first call of PeekMessageW() initialises the thread message queue.
     * For a detailed explanation please refer the following documentation:
     * https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-postthreadmessagew#remarks
     */
    PeekMessageW(&peeked_msg, (HWND) -1, WM_USER, WM_USER, PM_NOREMOVE);
}

static
unsigned int
__stdcall
uhashtools_hash_calculation_worker_thread_function
(
    void* thread_param
)
{
    /*
     * We only need the buffers as long the current calculation is running. So
     * we're binding the lifetime of the buffers to the lifetime of the current
     * worker thread. Since we're using a thread local variable here we don't
     * have to worry about freeing the memory. 
     */
    static __declspec(thread) struct HashCalculationWorkerCtx worker_ctx;

    const struct HashCalculationWorkerParam* hash_calc_worker_param = NULL;
    enum HashCalculatorResultCode calculation_result_code = HashCalculatorResultCode_FAILED;

    UHASHTOOLS_ASSERT(thread_param, L"Internal error: Entered with thread_param == NULL!");

    hash_calc_worker_param = (const struct HashCalculationWorkerParam*) thread_param;

    uhashtools_hash_calculation_worker_ctx_init(&worker_ctx, hash_calc_worker_param);
    uhashtools_thread_message_queue_init();
    uhashtools_hash_calculation_worker_com_send_worker_initialized_message(&worker_ctx.event_message_buf,
                                                                           hash_calc_worker_param->event_message_receiver,
                                                                           hash_calc_worker_param->event_message_buf,
                                                                           hash_calc_worker_param->event_message_buf_is_writeable_event);

    calculation_result_code = uhashtools_hash_calculator_impl_hash_file(worker_ctx.file_read_buf,
                                                                        worker_ctx.file_read_buf_tsize,
                                                                        worker_ctx.calculation_result_string,
                                                                        worker_ctx.calculation_result_string_tsize,
                                                                        hash_calc_worker_param->target_file,
                                                                        &uhashtools_check_is_cancel_requests_callback,
                                                                        &worker_ctx.received_thread_messages,
                                                                        &uhashtools_on_progress_callback,
                                                                        &worker_ctx.on_progress_cb_args);

    switch (calculation_result_code)
    {
        case HashCalculatorResultCode_SUCCESS:
        {
            uhashtools_hash_calculation_worker_com_send_calculation_complete_message(&worker_ctx.event_message_buf,
                                                                                     hash_calc_worker_param->event_message_receiver,
                                                                                     hash_calc_worker_param->event_message_buf,
                                                                                     hash_calc_worker_param->event_message_buf_is_writeable_event,
                                                                                     worker_ctx.calculation_result_string);
        } break;
        case HashCalculatorResultCode_CANCELED:
        {
            uhashtools_hash_calculation_worker_com_send_worker_canceled_message(&worker_ctx.event_message_buf,
                                                                                hash_calc_worker_param->event_message_receiver,
                                                                                hash_calc_worker_param->event_message_buf,
                                                                                hash_calc_worker_param->event_message_buf_is_writeable_event);
        } break;
        case HashCalculatorResultCode_FAILED:
        {
            uhashtools_hash_calculation_worker_com_send_calculation_failed_message(&worker_ctx.event_message_buf,
                                                                                   hash_calc_worker_param->event_message_receiver,
                                                                                   hash_calc_worker_param->event_message_buf,
                                                                                   hash_calc_worker_param->event_message_buf_is_writeable_event,
                                                                                   worker_ctx.calculation_result_string);
        } break;
        default:
        {
            UHASHTOOLS_FATAL_ERROR(L"Internal error: calculation_result_code has an unexpected value!");
        }
    }

    return 0;
}

struct HashCalculationWorkerInstanceData
uhashtools_hash_calculation_worker_start
(
    struct HashCalculationWorkerParam* worker_param_buf,
    struct HashCalculationWorkerEventMessage* event_message_buf,
    HANDLE event_message_buf_is_writeable_event,
    HWND event_message_receiver,
    const wchar_t* target_file
)
{
    struct HashCalculationWorkerInstanceData return_value;
    BOOL created_successfully = FALSE;
    uintptr_t thread_handle = 0;
    unsigned int thread_id = 0;

    return_value.created_successfully = created_successfully;
    return_value.thread_handle = (HANDLE) thread_handle;
    return_value.thread_id = (DWORD) thread_id;

    worker_param_buf->event_message_buf = event_message_buf;
    worker_param_buf->event_message_buf_is_writeable_event = event_message_buf_is_writeable_event;
    worker_param_buf->event_message_receiver = event_message_receiver;
    worker_param_buf->target_file = target_file;

    thread_handle = _beginthreadex(NULL,
                                   WORKER_THREAD_STACK_SIZE,
                                   uhashtools_hash_calculation_worker_thread_function,
                                   worker_param_buf,
                                   0,
                                   &thread_id);

    if (thread_handle == 0)
    {
        return return_value;
    }

    created_successfully = TRUE;

    return_value.created_successfully = created_successfully;
    return_value.thread_handle = (HANDLE) thread_handle;
    return_value.thread_id = (DWORD) thread_id;

    return return_value;
}

void
uhashtools_hash_calculation_worker_request_cancellation
(
    DWORD worker_thread_id
)
{
    uhashtools_hash_calculation_worker_com_send_cancel_request(worker_thread_id);
}
