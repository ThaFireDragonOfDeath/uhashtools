/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "hash_calculation_worker.h"

#include <Windows.h>

#define WORKER_CANCEL_REQUEST_MSG 1


/* Methods for sending information from the worker thread to the GUI thread. */

/**
 * Signals the GUI thread that the preparations in the hash calculation
 * worker are completed and the worker is now calculating the hash sum
 * of the target file.
 * After this signal message has been sent the hash calculation worker
 * listens for cancel request messages which means the operation can
 * be cancelled after this point.
 * 
 * When the GUI thread receives this event message it will enable the
 * cancel button and the progress bar.
 * 
 * @param sender_event_message_buf Buffer in which this function can prepare the event
 *                                 message.
 * @param event_message_receiver Handle of the event message receiver. This is usually
 *                               the handle of the main window.
 * @param receiver_event_message_buf Event message buffer which was provided in the
 *                                   worker parameters during the hash calculation worker
 *                                   start. After the event message has been prepared
 *                                   with in the "sender_event_message_buf" buffer, the
 *                                   data of said buffer will be copied into this one as
 *                                   soon the "is_writeable_event" for this buffer is in
 *                                   the signalled state.
 * @param receiver_event_message_buf_is_writeable_event Signals if we can write into this buffer.
 *                                                      After the main window has been setup, this event is
 *                                                      in the signalled state. When we want to send an event
 *                                                      message, we first wait until this event is in the
 *                                                      signalled state since the buffer which this event
 *                                                      protects is also used by the main window in the GUI
 *                                                      thread. After that point the event goes into the
 *                                                      un-signalled state. Then we're copying the prepared
 *                                                      event message buffer into the one which is shared
 *                                                      with the GUI thread and sending a signal to the message
 *                                                      loop in the GUI thread. The GUI thread then copies
 *                                                      the event message data and after that resets this
 *                                                      event back into the signalled state.
 */
extern
void
uhashtools_hash_calculation_worker_com_send_worker_initialized_message
(
    struct HashCalculationWorkerEventMessage* sender_event_message_buf,
    HWND event_message_receiver,
    struct HashCalculationWorkerEventMessage* receiver_event_message_buf,
    HANDLE receiver_event_message_buf_is_writeable_event
);

/**
 * Signals the GUI thread that the hash calculation operation has
 * been cancelled after receiving a cancellation request from the
 * user.
 * 
 * @param sender_event_message_buf Buffer in which this function can prepare the event
 *                                 message.
 * @param event_message_receiver Handle of the event message receiver. This is usually
 *                               the handle of the main window.
 * @param receiver_event_message_buf Event message buffer which was provided in the
 *                                   worker parameters during the hash calculation worker
 *                                   start. After the event message has been prepared
 *                                   with in the "sender_event_message_buf" buffer, the
 *                                   data of said buffer will be copied into this one as
 *                                   soon the "is_writeable_event" for this buffer is in
 *                                   the signalled state.
 * @param receiver_event_message_buf_is_writeable_event Signals if we can write into this buffer.
 *                                                      After the main window has been setup, this event is
 *                                                      in the signalled state. When we want to send an event
 *                                                      message, we first wait until this event is in the
 *                                                      signalled state since the buffer which this event
 *                                                      protects is also used by the main window in the GUI
 *                                                      thread. After that point the event goes into the
 *                                                      un-signalled state. Then we're copying the prepared
 *                                                      event message buffer into the one which is shared
 *                                                      with the GUI thread and sending a signal to the message
 *                                                      loop in the GUI thread. The GUI thread then copies
 *                                                      the event message data and after that resets this
 *                                                      event back into the signalled state.
 */
extern
void
uhashtools_hash_calculation_worker_com_send_worker_canceled_message
(
    struct HashCalculationWorkerEventMessage* sender_event_message_buf,
    HWND event_message_receiver,
    struct HashCalculationWorkerEventMessage* receiver_event_message_buf,
    HANDLE receiver_event_message_buf_is_writeable_event
);

/**
 * Signals operation success and sends the calculated hash to the GUI thread which
 * will display the result in the main window.
 * 
 * @param sender_event_message_buf Buffer in which this function can prepare the event
 *                                 message.
 * @param event_message_receiver Handle of the event message receiver. This is usually
 *                               the handle of the main window.
 * @param receiver_event_message_buf Event message buffer which was provided in the
 *                                   worker parameters during the hash calculation worker
 *                                   start. After the event message has been prepared
 *                                   with in the "sender_event_message_buf" buffer, the
 *                                   data of said buffer will be copied into this one as
 *                                   soon the "is_writeable_event" for this buffer is in
 *                                   the signalled state.
 * @param receiver_event_message_buf_is_writeable_event Signals if we can write into this buffer.
 *                                                      After the main window has been setup, this event is
 *                                                      in the signalled state. When we want to send an event
 *                                                      message, we first wait until this event is in the
 *                                                      signalled state since the buffer which this event
 *                                                      protects is also used by the main window in the GUI
 *                                                      thread. After that point the event goes into the
 *                                                      un-signalled state. Then we're copying the prepared
 *                                                      event message buffer into the one which is shared
 *                                                      with the GUI thread and sending a signal to the message
 *                                                      loop in the GUI thread. The GUI thread then copies
 *                                                      the event message data and after that resets this
 *                                                      event back into the signalled state.
 * @param calculated_hash Calculated hash sum of the selected file.
 */
extern
void
uhashtools_hash_calculation_worker_com_send_calculation_complete_message
(
    struct HashCalculationWorkerEventMessage* sender_event_message_buf,
    HWND event_message_receiver,
    struct HashCalculationWorkerEventMessage* receiver_event_message_buf,
    HANDLE receiver_event_message_buf_is_writeable_event,
    const wchar_t* calculated_hash
);

/**
 * Signals operation failure and sends the error message to the GUI thread which will
 * display said error message within a message box.
 * 
 * @param sender_event_message_buf Buffer in which this function can prepare the event
 *                                 message.
 * @param event_message_receiver Handle of the event message receiver. This is usually
 *                               the handle of the main window.
 * @param receiver_event_message_buf Event message buffer which was provided in the
 *                                   worker parameters during the hash calculation worker
 *                                   start. After the event message has been prepared
 *                                   with in the "sender_event_message_buf" buffer, the
 *                                   data of said buffer will be copied into this one as
 *                                   soon the "is_writeable_event" for this buffer is in
 *                                   the signalled state.
 * @param receiver_event_message_buf_is_writeable_event Signals if we can write into this buffer.
 *                                                      After the main window has been setup, this event is
 *                                                      in the signalled state. When we want to send an event
 *                                                      message, we first wait until this event is in the
 *                                                      signalled state since the buffer which this event
 *                                                      protects is also used by the main window in the GUI
 *                                                      thread. After that point the event goes into the
 *                                                      un-signalled state. Then we're copying the prepared
 *                                                      event message buffer into the one which is shared
 *                                                      with the GUI thread and sending a signal to the message
 *                                                      loop in the GUI thread. The GUI thread then copies
 *                                                      the event message data and after that resets this
 *                                                      event back into the signalled state.
 * @param user_error_message Error message which shall be shown to the user of this application.
 */
extern
void
uhashtools_hash_calculation_worker_com_send_calculation_failed_message
(
    struct HashCalculationWorkerEventMessage* sender_event_message_buf,
    HWND event_message_receiver,
    struct HashCalculationWorkerEventMessage* receiver_event_message_buf,
    HANDLE receiver_event_message_buf_is_writeable_event,
    const wchar_t* user_error_message
);

/**
 * Signals operation failure and sends the error message to the GUI thread which will
 * display said error message within a message box.
 * 
 * @param sender_event_message_buf Buffer in which this function can prepare the event
 *                                 message.
 * @param event_message_receiver Handle of the event message receiver. This is usually
 *                               the handle of the main window.
 * @param receiver_event_message_buf Event message buffer which was provided in the
 *                                   worker parameters during the hash calculation worker
 *                                   start. After the event message has been prepared
 *                                   with in the "sender_event_message_buf" buffer, the
 *                                   data of said buffer will be copied into this one as
 *                                   soon the "is_writeable_event" for this buffer is in
 *                                   the signalled state.
 * @param receiver_event_message_buf_is_writeable_event Signals if we can write into this buffer.
 *                                                      After the main window has been setup, this event is
 *                                                      in the signalled state. When we want to send an event
 *                                                      message, we first wait until this event is in the
 *                                                      signalled state since the buffer which this event
 *                                                      protects is also used by the main window in the GUI
 *                                                      thread. After that point the event goes into the
 *                                                      un-signalled state. Then we're copying the prepared
 *                                                      event message buffer into the one which is shared
 *                                                      with the GUI thread and sending a signal to the message
 *                                                      loop in the GUI thread. The GUI thread then copies
 *                                                      the event message data and after that resets this
 *                                                      event back into the signalled state.
 * @param current_calculation_progress Current calculation progress in range from 0 to 100.
 */
extern
void
uhashtools_hash_calculation_worker_com_send_calculation_progress_message
(
    struct HashCalculationWorkerEventMessage* sender_event_message_buf,
    HWND event_message_receiver,
    struct HashCalculationWorkerEventMessage* receiver_event_message_buf,
    HANDLE receiver_event_message_buf_is_writeable_event,
    unsigned int current_calculation_progress
);


/* Methods for sending information from the GUI thread to the worker thread. */

/**
 * Sends a cancellation request to the given worker thread.
 * 
 * @param worker_thread_id Thread id of the hash calculation worker.
 * 
 * @return If the function succeeds, the return value is TRUE. Otherwise the return
 *         value is FALSE.
 */
extern
BOOL
uhashtools_hash_calculation_worker_com_send_cancel_request
(
    DWORD worker_thread_id
);
