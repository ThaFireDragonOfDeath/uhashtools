/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#if WINVER >= 0x0601

#include <Windows.h>

#include "mainwin_state.h"
#include "taskbar_icon_pb_ctx.h"
#include "taskbarlist_com_api.h"

/**
 * Event reactor function to react on a change of the general
 * main window state.
 * 
 * @param own_state State of this object instance. Must not be NULL.
 * @param taskbar_list_com_api Initialized taskbar COM api instance. See taskbarlist_com_api.h for details. Must not be NULL.
 * @param mainwin_state New general main window state.
 */
extern
void
uhashtools_taskbar_icon_progress_bar_on_state_changed
(
    struct TaskbarIconProgressBarCtx* own_state,
    struct TaskbarListComApi* taskbar_list_com_api,
    enum MainWindowState mainwin_state
);

/**
 * Event reactor function to react on a change of the current progress
 * of the current operation.
 * 
 * @param own_state State of this object instance. Must not be NULL.
 * @param taskbar_list_com_api Initialized taskbar COM api instance. See taskbarlist_com_api.h for details. Must not be NULL.
 * @param progress_in_percent New progress value. Value must be in range of 0 to 100.
 */
extern
void
uhashtools_taskbar_icon_progress_bar_on_work_progress
(
    struct TaskbarIconProgressBarCtx* own_state,
    struct TaskbarListComApi* taskbar_list_com_api,
    unsigned int progress_in_percent
);

#endif
