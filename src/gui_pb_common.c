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
    HWND parant_window,
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
                          parant_window,
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
    SendMessage(pb_handle, PBM_SETPOS, (WPARAM) progress_in_percent, (LPARAM) 0);
}
