/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwin_event_handler.h"

#include "buffer_sizes.h"
#include "cli_arguments.h"
#include "error_utilities.h"
#include "hash_calculation_worker.h"
#include "mainwin_actions.h"
#include "mainwin_ctx.h"
#include "print_utilities.h"
#include "selectfiledialog.h"

#if _WIN32_WINNT >= 0x0601
    #include "taskbarlist_com_api.h"
#endif

#include <stdio.h>

void
uhashtools_mainwin_on_window_created
(
    struct MainWindowCtx* mainwin_ctx
)
{
    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");

    uhashtools_mainwin_init_ui_controls(mainwin_ctx);

    if (uhashtools_cli_arguments_has_target_file(&mainwin_ctx->cli_arguments))
    {
        uhashtools_mainwin_hash_file(mainwin_ctx, mainwin_ctx->cli_arguments.target_file);
    }
}

void
uhashtools_mainwin_on_cancel_button_pressed
(
    struct MainWindowCtx* mainwin_ctx
)
{
    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");
    
    uhashtools_hash_calculation_worker_request_cancellation(mainwin_ctx->worker_instance_data.thread_id);
}

void
uhashtools_mainwin_on_retry_button_pressed
(
    struct MainWindowCtx* mainwin_ctx
)
{
    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");
    
    uhashtools_mainwin_hash_selected_file(mainwin_ctx);
}

void
uhashtools_mainwin_on_copy_to_clipboard_button_pressed
(
    struct MainWindowCtx* mainwin_ctx
)
{
    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");

    uhashtools_mainwin_copy_hash_result_to_clipboard(mainwin_ctx);
}

void
uhashtools_mainwin_on_select_file_button_pressed
(
    struct MainWindowCtx* mainwin_ctx
)
{
    BOOL user_selected_a_file = uhashtools_select_file_dialog_open(mainwin_ctx->own_window_handle,
                                                                   mainwin_ctx->select_file_dlg_buf,
                                                                   FILEPATH_BUFFER_TSIZE);
    
    if (user_selected_a_file)
    {
        uhashtools_mainwin_hash_file(mainwin_ctx, mainwin_ctx->select_file_dlg_buf);
    }
}

#if _WIN32_WINNT >= 0x0601
void
uhashtools_mainwin_on_taskbar_button_created
(
    struct MainWindowCtx* mainwin_ctx
)
{
    BOOL init_taskbar_api_rc = FALSE;

    init_taskbar_api_rc = uhashtools_taskbar_list_com_api_init(&mainwin_ctx->taskbar_list_com_api,
                                                               &mainwin_ctx->com_lib_state,
                                                               mainwin_ctx->own_window_handle);
    
    UHASHTOOLS_ASSERT(init_taskbar_api_rc, L"Failed to initialize the taskbar list API!");

    mainwin_ctx->pb_taskbar_icon_ctx.current_progress_in_percent = 0;
    mainwin_ctx->pb_taskbar_icon_ctx.current_progress_view_mode = PROGRESS_VIEW_MODE_NONE;
}
#endif

void
uhashtools_mainwin_on_file_dropped
(
    struct MainWindowCtx* mainwin_ctx,
    HDROP dropped_files_event_handle
)
{
    UINT dropped_files_count = 0;
    
    dropped_files_count = DragQueryFileW(dropped_files_event_handle, 0xFFFFFFFF, NULL, 0);

    if (dropped_files_count >= 1)
    {
        wchar_t* ctx_target_file = mainwin_ctx->target_file;
        UINT get_drag_file_succeeded = 0;

        if (dropped_files_count > 1)
        {
            UHASHTOOLS_PRINTF_LINE_WARN(L"The received \"WM_DROPFILES\" event contains multiple files! We're taking the first and ignoring the rest...");
        }

        get_drag_file_succeeded = DragQueryFileW(dropped_files_event_handle,
                                                 0,
                                                 ctx_target_file,
                                                 FILEPATH_BUFFER_TSIZE);

        if (get_drag_file_succeeded)
        {
            uhashtools_mainwin_hash_selected_file(mainwin_ctx);
        }
        else
        {
            UHASHTOOLS_PRINTF_LINE_WARN(L"Failed to get the files from the \"WM_DROPFILES\" event! Ignoring the event...");
        }
    }
}

void
uhashtools_mainwin_on_hash_calculation_worker_event_message_received
(
    struct MainWindowCtx* mainwin_ctx,
    const struct HashCalculationWorkerEventMessage* event_message
)
{
    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");
    UHASHTOOLS_ASSERT(event_message, L"Internal error: Entered with event_message == NULL!");

    if (event_message->event_type == HCWET_MESSAGE_RECEIVER_INITIALIZED)
    {
        uhashtools_mainwin_change_state(mainwin_ctx,
                                        MAINWINDOWSTATE_WORKING_CANCELABLE);
    }
    else if (event_message->event_type == HCWET_CALCULATION_PROGRESS_CHANGED)
    {
        const unsigned int current_progress = event_message->event_data.progress_changed_data.current_progress_in_percent;
        
        uhashtools_mainwin_change_displayed_calculation_progress(mainwin_ctx,
                                                                 current_progress);
    }
    else if (event_message->event_type == HCWET_CALCULATION_COMPLETE)
    {
        (void) wcscpy_s(mainwin_ctx->hash_result,
                        HASH_RESULT_BUFFER_TSIZE,
                        event_message->event_data.operation_finished_data.calculated_hash);

        uhashtools_mainwin_change_state(mainwin_ctx,
                                        MAINWINDOWSTATE_FINISHED_SUCCESS);
    }
    else if (event_message->event_type == HCWET_CALCULATION_FAILED)
    {
        (void) wcscpy_s(mainwin_ctx->error_txt,
                        GENERIC_TXT_MESSAGES_BUFFER_TSIZE,
                        event_message->event_data.operation_failed_data.user_error_message);
        
        uhashtools_mainwin_change_state(mainwin_ctx,
                                        MAINWINDOWSTATE_FINISHED_ERROR);
    }
    else if (event_message->event_type == HCWET_CALCULATION_CANCELED)
    {
        uhashtools_mainwin_change_state(mainwin_ctx,
                                        MAINWINDOWSTATE_CANCELED);
    }
    else
    {
        UHASHTOOLS_FATAL_ERROR(L"Received event message with unexpected type!");
    }
}
