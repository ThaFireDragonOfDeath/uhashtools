/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "buffer_sizes.h"
#include "hash_calculation_worker.h"
#include "mainwin_state.h"

#if WINVER >= 0x0601
    #include "com_lib.h"
    #include "taskbar_icon_pb_ctx.h"
    #include "taskbarlist_com_api.h"
#endif

#include <Windows.h>

struct MainWindowCtx
{
    /* General handles */
    HINSTANCE app_instance_handle;
    HWND own_window_handle;

    #if WINVER >= 0x0601
        /* COM API */
        struct ComLibState com_lib_state;

        /* Taskbar progress view */
        struct TaskbarListComApi taskbar_list_com_api;
        struct TaskbarIconProgressBarCtx pb_taskbar_icon_ctx;
        UINT wm_taskbar_button_created;
    #endif

    /* Window state data */
    enum MainWindowState own_state;
    wchar_t target_file[FILEPATH_BUFFER_TSIZE];
    wchar_t hash_result[HASH_RESULT_BUFFER_TSIZE];
    wchar_t error_txt[GENERIC_TXT_MESSAGES_BUFFER_TSIZE];

    /* Hash calculation worker state */
    struct HashCalculationWorkerEventMessage event_message_buf;
    HANDLE event_message_buf_is_writeable_event;
    struct HashCalculationWorkerParam worker_thread_param_buf;
    struct HashCalculationWorkerInstanceData worker_instance_data;

    /* GUI memory buffers */
    wchar_t select_file_dlg_buf[FILEPATH_BUFFER_TSIZE];

    /* GUI elements */
    HWND lbl_file_drop;
    HWND lbl_selected_file;
    HWND eb_current_selected_file;
    wchar_t eb_current_selected_file_txt_buf[FILEPATH_BUFFER_TSIZE];
    HWND btn_select_file;
    HWND lbl_result_hash;
    HWND eb_calc_result;
    wchar_t eb_calc_result_txt_buf[HASH_RESULT_BUFFER_TSIZE];
    HWND pb_calc_result;
    HWND btn_action; /* Button for: Cancel operation, Copy result */
};

/**
 * Initializes the context data with the initial default state.
 * Since on every member of the MainWindowCtx structure the default
 * state is zero this function will do effectively memset zero on
 * the whole memory block. 
 * 
 * @param mainwin_ctx Allocated but uninitialized context data of
 *                    the target mainwin instance.
 */
extern
void
uhashtools_mainwin_ctx_init
(
    struct MainWindowCtx* mainwin_ctx
);
