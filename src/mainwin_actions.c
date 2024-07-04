/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwin_actions.h"

#include "clipboard_utils.h"
#include "errorutils.h"
#include "gui_common.h"
#include "mainwin_btn_action.h"
#include "mainwin_btn_select_file.h"
#include "mainwin_ctx.h"
#include "mainwin_eb_calc_result.h"
#include "mainwin_lbl_result_hash.h"
#include "mainwin_pb_calc_result.h"
#include "mainwin_lbl_selected_file.h"
#include "mainwin_eb_current_selected_file.h"
#include "mainwin_lbl_file_drop.h"
#include "selectfiledialog.h"

#if _WIN32_WINNT >= 0x0601
    #include "taskbar_icon_pb.h"
#endif

#include <stdio.h>

void
uhashtools_mainwin_init_ui_controls
(
    struct MainWindowCtx* mainwin_ctx
)
{
    HINSTANCE app_instance_handle = (HINSTANCE) INVALID_HANDLE_VALUE;
    HWND own_window_handle = (HWND) INVALID_HANDLE_VALUE;
    enum MainWindowState own_state = MAINWINDOWSTATE_INIT;
    int mainwin_width = 0;
    int mainwin_height = 0;
    int new_btn_action_x = 0;
    int new_btn_action_y = 0;
    int new_lbl_result_y = 0;
    int new_btn_select_file_x = 0;
    int new_eb_current_selected_file_y = 0;

    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");

    app_instance_handle = mainwin_ctx->app_instance_handle;
    own_window_handle = mainwin_ctx->own_window_handle;
    own_state = mainwin_ctx->own_state;

    mainwin_width = uhashtools_gui_elm_get_width(own_window_handle);
    mainwin_height = uhashtools_gui_elm_get_height(own_window_handle);

    mainwin_ctx->btn_action = uhashtools_btn_action_create(app_instance_handle,
                                                           own_window_handle,
                                                           own_state);

    new_btn_action_x = uhashtools_gui_elm_get_x(mainwin_ctx->btn_action);
    new_btn_action_y = uhashtools_gui_elm_get_y(mainwin_ctx->btn_action);
    
    mainwin_ctx->pb_calc_result = uhashtools_pb_calc_result_create(app_instance_handle,
                                                                   own_window_handle,
                                                                   new_btn_action_x);

    mainwin_ctx->eb_calc_result = uhashtools_eb_calc_result_create(app_instance_handle,
                                                                own_window_handle,
                                                                new_btn_action_x,
                                                                own_state,
                                                                mainwin_ctx->hash_result,
                                                                mainwin_ctx->eb_calc_result_txt_buf);

    mainwin_ctx->lbl_result_hash = uhashtools_lbl_result_hash_create(app_instance_handle,
                                                                     own_window_handle,
                                                                     own_state);
    
    new_lbl_result_y = uhashtools_gui_elm_get_y(mainwin_ctx->lbl_result_hash);

    mainwin_ctx->btn_select_file = uhashtools_btn_select_file_create(app_instance_handle,
                                                                     own_window_handle,
                                                                     new_btn_action_y);

    new_btn_select_file_x = uhashtools_gui_elm_get_x(mainwin_ctx->btn_select_file);
    
    mainwin_ctx->lbl_selected_file = uhashtools_lbl_selected_file_create(app_instance_handle,
                                                                         own_window_handle,
                                                                         new_lbl_result_y);

    mainwin_ctx->eb_current_selected_file = uhashtools_eb_current_selected_file_create(app_instance_handle,
                                                                                       own_window_handle,
                                                                                       mainwin_ctx->own_state,
                                                                                       mainwin_ctx->target_file,
                                                                                       mainwin_ctx->eb_current_selected_file_txt_buf,
                                                                                       new_lbl_result_y,
                                                                                       new_btn_select_file_x);
    
    new_eb_current_selected_file_y = uhashtools_gui_elm_get_y(mainwin_ctx->eb_current_selected_file);

    mainwin_ctx->lbl_file_drop = uhashtools_lbl_file_drop_create(app_instance_handle,
                                                                 own_window_handle,
                                                                 own_state,
                                                                 mainwin_width,
                                                                 new_eb_current_selected_file_y);
}

void
uhashtools_mainwin_resize_child_elements
(
    struct MainWindowCtx* mainwin_ctx,
    UINT mainwin_new_width,
    UINT mainwin_new_height
)
{
    int new_btn_action_x = 0;
    int new_btn_action_y = 0;
    int new_lbl_result_y = 0;
    int new_btn_select_file_x = 0;
    int new_eb_current_selected_file_y = 0;

    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");

    uhashtools_btn_action_on_parent_resize(mainwin_ctx->btn_action,
                                           mainwin_new_width,
                                           mainwin_new_height);

    new_btn_action_x = uhashtools_gui_elm_get_x(mainwin_ctx->btn_action);
    new_btn_action_y = uhashtools_gui_elm_get_y(mainwin_ctx->btn_action);

    uhashtools_pb_calc_result_on_parent_resize(mainwin_ctx->pb_calc_result,
                                               mainwin_new_height,
                                               new_btn_action_x);

    uhashtools_eb_calc_result_on_parent_resize(mainwin_ctx->eb_calc_result,
                                               mainwin_new_height,
                                               new_btn_action_x);

    uhashtools_lbl_result_hash_on_parent_resize(mainwin_ctx->lbl_result_hash,
                                                mainwin_new_height);

    new_lbl_result_y = uhashtools_gui_elm_get_y(mainwin_ctx->lbl_result_hash);

    uhashtools_btn_select_file_on_parent_resize(mainwin_ctx->btn_select_file,
                                                mainwin_new_width,
                                                new_btn_action_y);

    new_btn_select_file_x = uhashtools_gui_elm_get_x(mainwin_ctx->btn_select_file);

    uhashtools_lbl_selected_file_on_parent_resize(mainwin_ctx->lbl_selected_file,
                                                  new_lbl_result_y);

    uhashtools_eb_current_selected_file_on_parent_resize(mainwin_ctx->eb_current_selected_file,
                                                         new_lbl_result_y,
                                                         new_btn_select_file_x);

    new_eb_current_selected_file_y = uhashtools_gui_elm_get_y(mainwin_ctx->eb_current_selected_file);

    uhashtools_lbl_file_drop_on_parent_resize(mainwin_ctx->lbl_file_drop,
                                              mainwin_new_width,
                                              new_eb_current_selected_file_y);
}

void
uhashtools_mainwin_change_state
(
    struct MainWindowCtx* mainwin_ctx,
    const enum MainWindowState new_mainwin_state
)
{
    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");
    
    mainwin_ctx->own_state = new_mainwin_state;
    
    uhashtools_btn_action_on_state_changed(mainwin_ctx->btn_action,
                                           new_mainwin_state);
    
    uhashtools_pb_calc_result_on_state_changed(mainwin_ctx->pb_calc_result,
                                               new_mainwin_state);
                                                      
    uhashtools_eb_calc_result_on_state_changed(mainwin_ctx->eb_calc_result,
                                               new_mainwin_state,
                                               mainwin_ctx->hash_result,
                                               mainwin_ctx->eb_calc_result_txt_buf);
    
    uhashtools_lbl_result_hash_on_state_changed(mainwin_ctx->lbl_result_hash,
                                                new_mainwin_state);
    
    uhashtools_btn_select_file_on_state_changed(mainwin_ctx->btn_select_file,
                                                new_mainwin_state);
    
    uhashtools_eb_current_selected_file_on_state_changed(mainwin_ctx->eb_current_selected_file,
                                                         new_mainwin_state,
                                                         mainwin_ctx->target_file,
                                                         mainwin_ctx->eb_current_selected_file_txt_buf);
    
    uhashtools_lbl_file_drop_on_state_changed(mainwin_ctx->lbl_file_drop,
                                              new_mainwin_state);

#if _WIN32_WINNT >= 0x0601
    uhashtools_taskbar_icon_progress_bar_on_state_changed(&mainwin_ctx->pb_taskbar_icon_ctx,
                                                          &mainwin_ctx->taskbar_list_com_api,
                                                          new_mainwin_state);
#endif
    
    if (new_mainwin_state == MAINWINDOWSTATE_FINISHED_ERROR)
    {
        if (mainwin_ctx->error_txt[0] == '\0')
        {
            (void) wcscpy_s(mainwin_ctx->error_txt, GENERIC_TXT_MESSAGES_BUFFER_TSIZE, L"I just don't know what went wrong (◑‿◐)!");
        }

        (void) MessageBeep(MB_OK);

        (void) MessageBoxW(mainwin_ctx->own_window_handle,
                           mainwin_ctx->error_txt,
                           L"Calculation failed",
                           MB_OK);
        
        uhashtools_mainwin_change_state(mainwin_ctx,
                                        MAINWINDOWSTATE_FINISHED_ERROR_MSGBOX_CONFIRMED);
    }
    else if (new_mainwin_state == MAINWINDOWSTATE_WORKING)
    {
        uhashtools_mainwin_change_displayed_calculation_progress(mainwin_ctx, 0);
    }
}

void
uhashtools_mainwin_change_displayed_calculation_progress
(
    struct MainWindowCtx* mainwin_ctx,
    unsigned int current_progress_in_percent
)
{
    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");

    uhashtools_pb_calc_result_on_work_progress(mainwin_ctx->pb_calc_result,
                                               current_progress_in_percent);

#if _WIN32_WINNT >= 0x0601
    uhashtools_taskbar_icon_progress_bar_on_work_progress(&mainwin_ctx->pb_taskbar_icon_ctx,
                                                          &mainwin_ctx->taskbar_list_com_api,
                                                          current_progress_in_percent);
#endif
}

void
uhashtools_mainwin_copy_hash_result_to_clipboard
(
    struct MainWindowCtx* mainwin_ctx
)
{
    size_t hash_result_strlen = 0;
    
    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");
    
    hash_result_strlen = wcsnlen_s(mainwin_ctx->hash_result, HASH_RESULT_BUFFER_TSIZE);
    
    if (hash_result_strlen == HASH_RESULT_BUFFER_TSIZE)
    {
        return;
    }
    
    uhashtools_clipboard_utils_set_clipboard_text(mainwin_ctx->hash_result, hash_result_strlen);
}

void
uhashtools_mainwin_hash_selected_file
(
    struct MainWindowCtx* mainwin_ctx
)
{
    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");

    (void) wprintf_s(L"[INFO] Handling file selection of file: %s\n", mainwin_ctx->target_file);
    (void) fflush(stdout);

    uhashtools_mainwin_change_state(mainwin_ctx, MAINWINDOWSTATE_WORKING);
    mainwin_ctx->worker_instance_data = uhashtools_hash_calculation_worker_start(&mainwin_ctx->worker_thread_param_buf,
                                                                              &mainwin_ctx->event_message_buf,
                                                                              mainwin_ctx->event_message_buf_is_writeable_event,
                                                                              mainwin_ctx->own_window_handle,
                                                                              mainwin_ctx->target_file);
    
    if (!mainwin_ctx->worker_instance_data.created_successfully)
    {
        (void) wprintf_s(L"[ERROR] Failed to create hash calculation worker thread!\n");
        (void) fflush(stdout);

        (void) wcscpy_s(mainwin_ctx->error_txt, GENERIC_TXT_MESSAGES_BUFFER_TSIZE, L"Internal error: Failed to create hash calculation worker thread!");
        uhashtools_mainwin_change_state(mainwin_ctx, MAINWINDOWSTATE_FINISHED_ERROR);
        
        return;
    }
    
    (void) wprintf_s(L"[DEBUG] Successfully created hash calculation worker thread with the thread id \"%lu\"\n", mainwin_ctx->worker_instance_data.thread_id);
    (void) fflush(stdout);
}