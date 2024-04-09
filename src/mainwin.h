/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <Windows.h>

#include "buffer_sizes.h"
#include "hash_calculation_worker.h"

/* Shared constants */

/* Shared enumerations */

/* Shared structures */

enum MainWindowState
{
    MAINWINDOWSTATE_INIT,
    MAINWINDOWSTATE_WORKING,
    MAINWINDOWSTATE_WORKING_CANCELABLE,
    MAINWINDOWSTATE_CANCELED,
    MAINWINDOWSTATE_FINISHED_SUCCESS,
    MAINWINDOWSTATE_FINISHED_ERROR
};

struct MainWindowCtx
{
    HINSTANCE app_instance_handle;
    HWND own_window_handle;

    /* Window state data */
    enum MainWindowState own_state;
    wchar_t target_file[FILEPATH_BUFFER_TSIZE];
    wchar_t hash_result[HASH_RESULT_BUFFER_TSIZE];
    wchar_t error_txt[GENERIC_TXT_MESSAGES_BUFFER_TSIZE];

    /* Hash calculatoion worker state */
    struct HashCalculationWorkerEventMessage event_message_buf;
    HANDLE event_message_buf_is_writeable_event;
    struct HashCalculationWorkerParam worker_thread_param_buf;
    struct HashCalculationWorkerInstanceData worker_instance_data;

    /* GUI memory buffers */
    wchar_t select_file_dlg_buf[FILEPATH_BUFFER_TSIZE];

    /* GUI elements */
    HWND lbl_filedrop;
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

/* API functions */

extern
BOOL
uhashtools_start_main_window
(
    HINSTANCE hInstance,
    int nCmdShow,
    struct MainWindowCtx* mainwin_ctx
);
