/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "gui_btn_common.h"

#include "errorutils.h"

#include <CommCtrl.h>
#include <Windows.h>

HWND
uhashtools_btn_create
(
    HINSTANCE app_instance,
    HWND parent_window,
    DWORD style,
    DWORD style_ex,
    int x,
    int y,
    int width,
    int height,
    HICON icon
)
{
    HWND ret = NULL;

    ret = CreateWindowExW(style_ex,
                          L"BUTTON",       /* Window class */
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

    SendMessageW(ret, BM_SETIMAGE, (WPARAM) IMAGE_ICON, (LPARAM) icon);

    return ret;
}

void
uhashtools_btn_set_icon
(
    HWND self,
    HICON icon
)
{
    SendMessageW(self, BM_SETIMAGE, (WPARAM) IMAGE_ICON, (LPARAM) icon);
}