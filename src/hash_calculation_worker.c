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

#include "hash_calculation_worker.h"

#include <stdlib.h>
#include <stdio.h>

#include <process.h>

#include "errorutils.h"
#include "hash_calculation_impl.h"

#define FILE_READ_BUF_SIZE 1024 * 512
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#define WORKER_CANCEL_REQUEST_MSG 1
#define WORKER_THREAD_STACK_SIZE 1024 * 1024 * 2

struct ReceivedThreadMessages
{
    BOOL cancel_requested;
};

struct OutgoingEventMessageTarget
{
    HWND event_message_receiver;
    struct HashCalculationWorkerEventMessage* event_message_buf;
    HANDLE event_message_buf_is_writeable_event;
};

static
void
uhashtools_send_event_message
(
    HWND event_message_receiver,
    const struct HashCalculationWorkerEventMessage* event_message_to_send,
    struct HashCalculationWorkerEventMessage* event_message_buf,
    HANDLE event_message_buf_is_writeable_event
)
{
    DWORD wait_for_write_result = 0;
    errno_t event_msg_copy_error = 0;
    BOOL event_msg_send_success = FALSE;
    
    wait_for_write_result = WaitForSingleObject(event_message_buf_is_writeable_event, INFINITE);
    UHASHTOOLS_ASSERT(wait_for_write_result == WAIT_OBJECT_0, L"WaitForSingleObject() on event_message_buf_is_writeable_event failed!");

    event_msg_copy_error = memcpy_s(event_message_buf, sizeof *event_message_buf, event_message_to_send, sizeof *event_message_to_send);
    UHASHTOOLS_ASSERT(!event_msg_copy_error, L"Failed to copy the generated event message into the shared buffer!");

    event_msg_send_success = PostMessageW(event_message_receiver, WM_USER, (WPARAM) event_message_buf, 0);
    UHASHTOOLS_ASSERT(event_msg_send_success, L"Failed to send the event message with PostMessageW()!");
}

static
void
uhashtools_send_worker_initialized_message
(
    HWND event_message_receiver,
    struct HashCalculationWorkerEventMessage* event_message_buf,
    HANDLE event_message_buf_is_writeable_event
)
{
    struct HashCalculationWorkerEventMessage event_message;

    SecureZeroMemory(&event_message, sizeof event_message);

    (void) wprintf_s(L"[DEBUG] Sending worker initialized message.\n");
    (void) fflush(stdout);

    event_message.event_type = HCWET_MESSAGE_RECEIVER_INITIALIZED;

    uhashtools_send_event_message(event_message_receiver,
                               &event_message,
                               event_message_buf,
                               event_message_buf_is_writeable_event);
}

static
void
uhashtools_send_worker_canceled_message
(
    HWND event_message_receiver,
    struct HashCalculationWorkerEventMessage* event_message_buf,
    HANDLE event_message_buf_is_writeable_event
)
{
    struct HashCalculationWorkerEventMessage event_message;

    SecureZeroMemory(&event_message, sizeof event_message);

    (void) wprintf_s(L"[DEBUG] Sending calculation canceled message.\n");
    (void) fflush(stdout);

    event_message.event_type = HCWET_CALCULATION_CANCELED;

    uhashtools_send_event_message(event_message_receiver,
                               &event_message,
                               event_message_buf,
                               event_message_buf_is_writeable_event);
}

static
void
uhashtools_send_calculation_complete_message
(
    HWND event_message_receiver,
    struct HashCalculationWorkerEventMessage* event_message_buf,
    HANDLE event_message_buf_is_writeable_event,
    const wchar_t* calculated_hash
)
{
    struct HashCalculationWorkerEventMessage event_message;

    SecureZeroMemory(&event_message, sizeof event_message);

    (void) wprintf_s(L"[DEBUG] Sending calculated complete message with content \"%s\".\n", calculated_hash);
    (void) fflush(stdout);

    event_message.event_type = HCWET_CALCULATION_COMPLETE;
    (void) wcscpy_s(event_message.event_data.opperation_finished_data.calculated_hash,
                    HASH_RESULT_BUFFER_TSIZE,
                    calculated_hash);

    uhashtools_send_event_message(event_message_receiver,
                               &event_message,
                               event_message_buf,
                               event_message_buf_is_writeable_event);
}

static
void
uhashtools_send_calculation_failed_message
(
    HWND event_message_receiver,
    struct HashCalculationWorkerEventMessage* event_message_buf,
    HANDLE event_message_buf_is_writeable_event,
    const wchar_t* user_error_message
)
{
    struct HashCalculationWorkerEventMessage event_message;

    SecureZeroMemory(&event_message, sizeof event_message);

    (void) wprintf_s(L"[DEBUG] Sending calculated failed message with content \"%s\".\n", user_error_message);
    (void) fflush(stdout);

    event_message.event_type = HCWET_CALCULATION_FAILED;
    (void) wcscpy_s(event_message.event_data.opperation_failed_data.user_error_message,
                    GENERIC_TXT_MESSAGES_BUFFER_TSIZE,
                    user_error_message);

    uhashtools_send_event_message(event_message_receiver,
                               &event_message,
                               event_message_buf,
                               event_message_buf_is_writeable_event);
}

static
void
uhashtools_send_calculation_progress_message
(
    HWND event_message_receiver,
    struct HashCalculationWorkerEventMessage* event_message_buf,
    HANDLE event_message_buf_is_writeable_event,
    unsigned int current_calculation_progress
)
{
    struct HashCalculationWorkerEventMessage event_message;

    SecureZeroMemory(&event_message, sizeof event_message);

    (void) wprintf_s(L"[DEBUG] Sending calculated progress message with content \"%u\".\n", current_calculation_progress);
    (void) fflush(stdout);

    event_message.event_type = HCWET_CALCULATION_PROGRESS_CHANGED;
    event_message.event_data.progress_changed_data.current_progress_in_percent = current_calculation_progress;

    uhashtools_send_event_message(event_message_receiver,
                               &event_message,
                               event_message_buf,
                               event_message_buf_is_writeable_event);
}

static
void
uhashtools_process_thread_messages
(
    struct ReceivedThreadMessages* received_thread_messages
)
{
    MSG peeked_msg;

    UHASHTOOLS_ASSERT(received_thread_messages, L"Internal error: Entered with received_thread_messages == NULL!");

    while (PeekMessageW(&peeked_msg, (HWND) -1, WM_USER, WM_USER, PM_REMOVE))
    {
        if (peeked_msg.wParam == WORKER_CANCEL_REQUEST_MSG)
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
    struct OutgoingEventMessageTarget* event_message_target = NULL;

    if (!userdata)
    {
        return;
    }

    event_message_target = (struct OutgoingEventMessageTarget*) userdata;

    uhashtools_send_calculation_progress_message(event_message_target->event_message_receiver,
                                              event_message_target->event_message_buf,
                                              event_message_target->event_message_buf_is_writeable_event,
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
     * For a detailed explenation please refer the following documentation:
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
    struct HashCalculationWorkerParam* hash_calc_worker_param = NULL;
    struct ReceivedThreadMessages received_thread_messages;
    struct OutgoingEventMessageTarget event_message_target;
    wchar_t calculation_result_string[GENERIC_TXT_MESSAGES_BUFFER_TSIZE];
    const size_t calculation_result_string_tsize = GENERIC_TXT_MESSAGES_BUFFER_TSIZE;
    enum HashCalculatorResultCode calculation_result_code = HashCalculatorResultCode_FAILED;
    
    UHASHTOOLS_ASSERT(thread_param, L"Internal error: Entered with thread_param == NULL!");

    hash_calc_worker_param = (struct HashCalculationWorkerParam*) thread_param;
    SecureZeroMemory(&received_thread_messages, sizeof received_thread_messages);
    SecureZeroMemory(&event_message_target, sizeof event_message_target);
    SecureZeroMemory(calculation_result_string, sizeof calculation_result_string);

    received_thread_messages.cancel_requested = FALSE;
    event_message_target.event_message_receiver = hash_calc_worker_param->event_message_receiver;
    event_message_target.event_message_buf = hash_calc_worker_param->event_message_buf;
    event_message_target.event_message_buf_is_writeable_event = hash_calc_worker_param->event_message_buf_is_writeable_event;

    uhashtools_thread_message_queue_init();
    uhashtools_send_worker_initialized_message(hash_calc_worker_param->event_message_receiver,
                                            hash_calc_worker_param->event_message_buf,
                                            hash_calc_worker_param->event_message_buf_is_writeable_event);

    calculation_result_code = uhashtools_hash_calculator_impl_hash_file(calculation_result_string,
                                                                     calculation_result_string_tsize,
                                                                     hash_calc_worker_param->target_file,
                                                                     &uhashtools_check_is_cancel_requests_callback,
                                                                     &received_thread_messages,
                                                                     &uhashtools_on_progress_callback,
                                                                     &event_message_target);

    switch (calculation_result_code)
    {
        case HashCalculatorResultCode_SUCCESS:
        {
            uhashtools_send_calculation_complete_message(hash_calc_worker_param->event_message_receiver,
                                                      hash_calc_worker_param->event_message_buf,
                                                      hash_calc_worker_param->event_message_buf_is_writeable_event,
                                                      calculation_result_string);
        } break;
        case HashCalculatorResultCode_CANCELED:
        {
            uhashtools_send_worker_canceled_message(hash_calc_worker_param->event_message_receiver,
                                                 hash_calc_worker_param->event_message_buf,
                                                 hash_calc_worker_param->event_message_buf_is_writeable_event);
        } break;
        case HashCalculatorResultCode_FAILED:
        {
            uhashtools_send_calculation_failed_message(hash_calc_worker_param->event_message_receiver,
                                                    hash_calc_worker_param->event_message_buf,
                                                    hash_calc_worker_param->event_message_buf_is_writeable_event,
                                                    calculation_result_string);
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
    BOOL created_sucessfully = FALSE;
    uintptr_t thread_handle = 0;
    unsigned int thread_id = 0;

    return_value.created_sucessfully = created_sucessfully;
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

    created_sucessfully = TRUE;

    return_value.created_sucessfully = created_sucessfully;
    return_value.thread_handle = (HANDLE) thread_handle;
    return_value.thread_id = (DWORD) thread_id;

    return return_value;
}

BOOL
uhashtools_hash_calculation_worker_request_cancelation
(
    DWORD worker_thread_id
)
{
    return PostThreadMessageW(worker_thread_id, WM_USER, WORKER_CANCEL_REQUEST_MSG, 0);
}