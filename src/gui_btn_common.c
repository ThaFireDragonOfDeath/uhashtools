/*
 * µHashtools - A small graphical file hashing tool for Microsoft Windows
 * Copyright (C) 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * 
 * This file is part of µHashtools.
 * 
 * µHashtools is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 * 
 * µHashtools is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * µHashtools. If not, see <https://www.gnu.org/licenses/>.
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "gui_btn_common.h"

#include <CommCtrl.h>
#include <Windows.h>

#include "errorutils.h"

HWND
uhashtools_btn_create
(
    HINSTANCE app_instance,
    HWND parant_window,
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
                          parant_window,
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