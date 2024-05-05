/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#if WINVER >= 0x0601

#include "taskbar_icon_pb.h"

#include "errorutils.h"
#include "mainwin_state_enum.h"

#include <Shobjidl.h>

static enum ProgressViewMode dyn_PB_TASKBAR_ICON_STATE(enum MainWindowState mainwin_state)
{
    switch(mainwin_state)
    {
        case MAINWINDOWSTATE_INIT:
        case MAINWINDOWSTATE_CANCELED:
        case MAINWINDOWSTATE_FINISHED_SUCCESS:
        case MAINWINDOWSTATE_FINISHED_ERROR_MSGBOX_CONFIRMED:
            return PROGRESS_VIEW_MODE_NONE;

        case MAINWINDOWSTATE_WORKING:
        case MAINWINDOWSTATE_WORKING_CANCELABLE:
            return PROGRESS_VIEW_MODE_NORMAL_PROGRESS;

        case MAINWINDOWSTATE_FINISHED_ERROR:
            return PROGRESS_VIEW_MODE_ERROR_PROGRESS;

        default:
            return PROGRESS_VIEW_MODE_NONE;
    }
}

void
uhashtools_taskbar_icon_progress_bar_on_state_changed
(
    struct TaskbarIconProgressBarCtx* own_state,
    struct TaskbarListComApi* taskbar_list_com_api,
    enum MainWindowState mainwin_state
)
{
    enum ProgressViewMode new_progress_view_mode = PROGRESS_VIEW_MODE_NONE;

    UHASHTOOLS_ASSERT(own_state, L"Internal error: Entered with own_state == NULL!");
    UHASHTOOLS_ASSERT(taskbar_list_com_api, L"Internal error: Entered with taskbar_list_com_api == NULL!");

    new_progress_view_mode = dyn_PB_TASKBAR_ICON_STATE(mainwin_state);

    if (own_state->current_progress_view_mode == new_progress_view_mode)
    {
        return;
    }

    if (new_progress_view_mode == PROGRESS_VIEW_MODE_ERROR_PROGRESS)
    {
        uhashtools_taskbar_list_com_api_set_progress_value(taskbar_list_com_api,
                                                           100);
    }

    uhashtools_taskbar_list_com_api_set_progress_view_mode(taskbar_list_com_api,
                                                           new_progress_view_mode);
    
    own_state->current_progress_view_mode = new_progress_view_mode;
}

void
uhashtools_taskbar_icon_progress_bar_on_work_progress
(
    struct TaskbarIconProgressBarCtx* own_state,
    struct TaskbarListComApi* taskbar_list_com_api,
    unsigned int progress_in_percent
)
{
    UHASHTOOLS_ASSERT(own_state, L"Internal error: Entered with own_state == NULL!");
    UHASHTOOLS_ASSERT(taskbar_list_com_api, L"Internal error: Entered with taskbar_list_com_api == NULL!");
    UHASHTOOLS_ASSERT(progress_in_percent <= 100, L"Internal error: Entered with invalid value for progress_in_percent!");

    if (own_state->current_progress_in_percent == progress_in_percent)
    {
        return;
    }

    uhashtools_taskbar_list_com_api_set_progress_value(taskbar_list_com_api,
                                                       progress_in_percent);

    own_state->current_progress_in_percent = progress_in_percent;
}

#endif
