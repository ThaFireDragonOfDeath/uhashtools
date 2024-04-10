/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "gui_pb_common.h"

#include <CommCtrl.h>
#include <Windows.h>

#include "errorutils.h"

HWND
uhashtools_pb_create
(
    HINSTANCE app_instance,
    HWND parent_window,
    DWORD style,
    DWORD style_ex,
    int x,
    int y,
    int width,
    int height
)
{
    HWND ret = NULL;

    ret = CreateWindowExW(style_ex,
                          PROGRESS_CLASSW, /* Window class */
                          NULL,            /* Window title*/
                          style,
                          x,
                          y,
                          width,
                          height,
                          parent_window,
                          NULL,            /* Menu handle */
                          app_instance,
                          NULL);           /* LP param */

    UHASHTOOLS_ASSERT(ret != NULL, L"Internal error: CreateWindowExW failed!");

    return ret;
}

void
uhashtools_pb_set_progress
(
    HWND pb_handle,
    unsigned int progress_in_percent
)
{
    /* 
     * We have to implement a workaround here since the Win32 progress bar
     * control forces a smoothness animation on increasing the current
     * displayed progress.
     * This doesn't happen on decreasing the current displayed progress so
     * we first set the current progress to a slightly bigger value and
     * then immediately decrease it again to stop the animation and show
     * the accurate progress.
     * 
     * This is the C equivalent to the code from this reference:
     * https://stackoverflow.com/a/10452817
     */
    if (progress_in_percent < 100)
    {
        SendMessage(pb_handle, PBM_SETPOS, (WPARAM) progress_in_percent + 1, (LPARAM) 0);
        SendMessage(pb_handle, PBM_SETPOS, (WPARAM) progress_in_percent, (LPARAM) 0);
    }
    else
    {
        SendMessage(pb_handle, PBM_SETRANGE, (WPARAM) NULL, MAKELPARAM(0, 101));
        SendMessage(pb_handle, PBM_SETPOS, (WPARAM) progress_in_percent + 1, (LPARAM) 0);
        SendMessage(pb_handle, PBM_SETRANGE, (WPARAM) NULL, MAKELPARAM(0, 100));
    }
}
