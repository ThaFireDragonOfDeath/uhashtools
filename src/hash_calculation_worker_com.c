/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "hash_calculation_worker_com.h"

#include "error_utilities.h"
#include "print_utilities.h"

#include <string.h>

static
void
uhashtools_send_event_message
(
    HWND event_message_receiver,
    const struct HashCalculationWorkerEventMessage* event_message_to_send,
    struct HashCalculationWorkerEventMessage* receiver_event_message_buf,
    HANDLE receiver_event_message_buf_is_writeable_event
)
{
    DWORD wait_for_write_result = 0;
    BOOL event_msg_send_success = FALSE;
    
    wait_for_write_result = WaitForSingleObject(receiver_event_message_buf_is_writeable_event, INFINITE);
    UHASHTOOLS_ASSERT(wait_for_write_result == WAIT_OBJECT_0,
                      L"WaitForSingleObject() on event_message_buf_is_writeable_event failed!");

    *receiver_event_message_buf = *event_message_to_send;

    event_msg_send_success = PostMessageW(event_message_receiver,
                                          WM_USER,
                                          (WPARAM) receiver_event_message_buf,
                                          0);
    UHASHTOOLS_ASSERT(event_msg_send_success, L"Failed to send the event message with PostMessageW()!");
}

void
uhashtools_hash_calculation_worker_com_send_worker_initialized_message
(
    struct HashCalculationWorkerEventMessage* sender_event_message_buf,
    HWND event_message_receiver,
    struct HashCalculationWorkerEventMessage* receiver_event_message_buf,
    HANDLE receiver_event_message_buf_is_writeable_event
)
{
    UHASHTOOLS_ASSERT(sender_event_message_buf,
                      L"Internal error: Entered with sender_event_message_buf == NULL!");
    UHASHTOOLS_ASSERT(event_message_receiver && event_message_receiver != INVALID_HANDLE_VALUE,
                      L"Internal error: Entered with empty or invalid 'event_message_receiver' window handle!");
    UHASHTOOLS_ASSERT(receiver_event_message_buf,
                      L"Internal error: Entered with receiver_event_message_buf == NULL!");
    UHASHTOOLS_ASSERT(receiver_event_message_buf_is_writeable_event &&
                      receiver_event_message_buf_is_writeable_event != INVALID_HANDLE_VALUE,
                      L"Internal error: Entered with empty or invalid 'receiver_event_message_buf_is_writeable_event' handle!");

    (void) memset((void*) sender_event_message_buf, 0, sizeof *sender_event_message_buf);

    UHASHTOOLS_PRINTF_LINE_DEBUG(L"Sending worker initialized message.");

    sender_event_message_buf->event_type = HCWET_MESSAGE_RECEIVER_INITIALIZED;

    uhashtools_send_event_message(event_message_receiver,
                                  sender_event_message_buf,
                                  receiver_event_message_buf,
                                  receiver_event_message_buf_is_writeable_event);
}

void
uhashtools_hash_calculation_worker_com_send_worker_canceled_message
(
    struct HashCalculationWorkerEventMessage* sender_event_message_buf,
    HWND event_message_receiver,
    struct HashCalculationWorkerEventMessage* receiver_event_message_buf,
    HANDLE receiver_event_message_buf_is_writeable_event
)
{
    UHASHTOOLS_ASSERT(sender_event_message_buf,
                      L"Internal error: Entered with sender_event_message_buf == NULL!");
    UHASHTOOLS_ASSERT(event_message_receiver && event_message_receiver != INVALID_HANDLE_VALUE,
                      L"Internal error: Entered with empty or invalid 'event_message_receiver' window handle!");
    UHASHTOOLS_ASSERT(receiver_event_message_buf,
                      L"Internal error: Entered with receiver_event_message_buf == NULL!");
    UHASHTOOLS_ASSERT(receiver_event_message_buf_is_writeable_event &&
                      receiver_event_message_buf_is_writeable_event != INVALID_HANDLE_VALUE,
                      L"Internal error: Entered with empty or invalid 'receiver_event_message_buf_is_writeable_event' handle!");

    (void) memset((void*) sender_event_message_buf, 0, sizeof *sender_event_message_buf);

    UHASHTOOLS_PRINTF_LINE_DEBUG(L"Sending calculation canceled message.");

    sender_event_message_buf->event_type = HCWET_CALCULATION_CANCELED;

    uhashtools_send_event_message(event_message_receiver,
                                  sender_event_message_buf,
                                  receiver_event_message_buf,
                                  receiver_event_message_buf_is_writeable_event);
}

void
uhashtools_hash_calculation_worker_com_send_calculation_complete_message
(
    struct HashCalculationWorkerEventMessage* sender_event_message_buf,
    HWND event_message_receiver,
    struct HashCalculationWorkerEventMessage* receiver_event_message_buf,
    HANDLE receiver_event_message_buf_is_writeable_event,
    const wchar_t* calculated_hash
)
{
    UHASHTOOLS_ASSERT(sender_event_message_buf,
                      L"Internal error: Entered with sender_event_message_buf == NULL!");
    UHASHTOOLS_ASSERT(event_message_receiver && event_message_receiver != INVALID_HANDLE_VALUE,
                      L"Internal error: Entered with empty or invalid 'event_message_receiver' window handle!");
    UHASHTOOLS_ASSERT(receiver_event_message_buf,
                      L"Internal error: Entered with receiver_event_message_buf == NULL!");
    UHASHTOOLS_ASSERT(receiver_event_message_buf_is_writeable_event &&
                      receiver_event_message_buf_is_writeable_event != INVALID_HANDLE_VALUE,
                      L"Internal error: Entered with empty or invalid 'receiver_event_message_buf_is_writeable_event' handle!");
    UHASHTOOLS_ASSERT(calculated_hash, L"Internal error: Entered with calculated_hash == NULL!")

    (void) memset((void*) sender_event_message_buf, 0, sizeof *sender_event_message_buf);

    UHASHTOOLS_PRINTF_LINE_DEBUG(L"Sending calculated complete message with content \"%s\".",
                                 calculated_hash);

    sender_event_message_buf->event_type = HCWET_CALCULATION_COMPLETE;

    (void) wcscpy_s(sender_event_message_buf->event_data.operation_finished_data.calculated_hash,
                    HASH_RESULT_BUFFER_TSIZE,
                    calculated_hash);

    uhashtools_send_event_message(event_message_receiver,
                                  sender_event_message_buf,
                                  receiver_event_message_buf,
                                  receiver_event_message_buf_is_writeable_event);
}

void
uhashtools_hash_calculation_worker_com_send_calculation_failed_message
(
    struct HashCalculationWorkerEventMessage* sender_event_message_buf,
    HWND event_message_receiver,
    struct HashCalculationWorkerEventMessage* receiver_event_message_buf,
    HANDLE receiver_event_message_buf_is_writeable_event,
    const wchar_t* user_error_message
)
{
    UHASHTOOLS_ASSERT(sender_event_message_buf,
                      L"Internal error: Entered with sender_event_message_buf == NULL!");
    UHASHTOOLS_ASSERT(event_message_receiver && event_message_receiver != INVALID_HANDLE_VALUE,
                      L"Internal error: Entered with empty or invalid 'event_message_receiver' window handle!");
    UHASHTOOLS_ASSERT(receiver_event_message_buf,
                      L"Internal error: Entered with receiver_event_message_buf == NULL!");
    UHASHTOOLS_ASSERT(receiver_event_message_buf_is_writeable_event &&
                      receiver_event_message_buf_is_writeable_event != INVALID_HANDLE_VALUE,
                      L"Internal error: Entered with empty or invalid 'receiver_event_message_buf_is_writeable_event' handle!");

    (void) memset((void*) sender_event_message_buf, 0, sizeof *sender_event_message_buf);

    UHASHTOOLS_PRINTF_LINE_DEBUG(L"Sending calculated failed message with content \"%s\".",
                                 user_error_message);

    sender_event_message_buf->event_type = HCWET_CALCULATION_FAILED;
    (void) wcscpy_s(sender_event_message_buf->event_data.operation_failed_data.user_error_message,
                    GENERIC_TXT_MESSAGES_BUFFER_TSIZE,
                    user_error_message);

    uhashtools_send_event_message(event_message_receiver,
                                  sender_event_message_buf,
                                  receiver_event_message_buf,
                                  receiver_event_message_buf_is_writeable_event);
}

void
uhashtools_hash_calculation_worker_com_send_calculation_progress_message
(
    struct HashCalculationWorkerEventMessage* sender_event_message_buf,
    HWND event_message_receiver,
    struct HashCalculationWorkerEventMessage* receiver_event_message_buf,
    HANDLE receiver_event_message_buf_is_writeable_event,
    unsigned int current_calculation_progress
)
{
    UHASHTOOLS_ASSERT(sender_event_message_buf,
                      L"Internal error: Entered with sender_event_message_buf == NULL!");
    UHASHTOOLS_ASSERT(event_message_receiver && event_message_receiver != INVALID_HANDLE_VALUE,
                      L"Internal error: Entered with empty or invalid 'event_message_receiver' window handle!");
    UHASHTOOLS_ASSERT(receiver_event_message_buf,
                      L"Internal error: Entered with receiver_event_message_buf == NULL!");
    UHASHTOOLS_ASSERT(receiver_event_message_buf_is_writeable_event &&
                      receiver_event_message_buf_is_writeable_event != INVALID_HANDLE_VALUE,
                      L"Internal error: Entered with empty or invalid 'receiver_event_message_buf_is_writeable_event' handle!");

    (void) memset((void*) sender_event_message_buf, 0, sizeof *sender_event_message_buf);

    UHASHTOOLS_PRINTF_LINE_DEBUG(L"Sending calculated progress message with content \"%u\".",
                                 current_calculation_progress);

    sender_event_message_buf->event_type = HCWET_CALCULATION_PROGRESS_CHANGED;
    sender_event_message_buf->event_data.progress_changed_data.current_progress_in_percent = current_calculation_progress;

    uhashtools_send_event_message(event_message_receiver,
                                  sender_event_message_buf,
                                  receiver_event_message_buf,
                                  receiver_event_message_buf_is_writeable_event);
}

BOOL
uhashtools_hash_calculation_worker_com_send_cancel_request
(
    DWORD worker_thread_id
)
{
    return PostThreadMessageW(worker_thread_id, WM_USER, WORKER_CANCEL_REQUEST_MSG, 0);
}
