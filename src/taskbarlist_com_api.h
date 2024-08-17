/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#if WINVER >= 0x0601

#include "com_lib.h"

#include <Shobjidl.h>
#include <Windows.h>

enum ProgressViewMode
{
    PROGRESS_VIEW_MODE_NONE,
    PROGRESS_VIEW_MODE_NORMAL_PROGRESS,
    PROGRESS_VIEW_MODE_ERROR_PROGRESS
};

struct TaskbarListComApi
{
    HWND main_window_handle;
    ITaskbarList3* taskbar_list_v3_instance;
};

extern
BOOL
uhashtools_taskbar_list_com_api_init
(
    struct TaskbarListComApi* taskbar_list_com_api,
    struct ComLibState* com_lib_state,
    HWND main_window_handle
);

extern
BOOL
uhashtools_taskbar_list_com_api_set_progress_value
(
    struct TaskbarListComApi* initialized_taskbar_list_com_api,
    unsigned int progress_in_percent
);

extern
BOOL
uhashtools_taskbar_list_com_api_set_progress_view_mode
(
    struct TaskbarListComApi* initialized_taskbar_list_com_api,
    enum ProgressViewMode progress_view_mode
);

#endif
