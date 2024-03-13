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

#include "gui_lbl_common.h"

#include <Windows.h>

#include "errorutils.h"

HWND
uhashtools_lbl_create
(
    HINSTANCE hInstance,
    HWND parentWinHandle,
    DWORD style,
    DWORD style_ex,
    int x,
    int y,
    int width,
    int height,
    const wchar_t* txt
)
{
    HWND ret = NULL;
    HFONT lbl_font = NULL;

    ret = CreateWindowExW(style_ex,
                          L"STATIC",
                          txt,
                          style,
                          x,
                          y,
                          width,
                          height,
                          parentWinHandle,
                          NULL,
                          hInstance,
                          NULL);

    UHASHTOOLS_ASSERT(ret != NULL, L"Internal error: CreateWindowExW failed!");

    lbl_font = (HFONT) GetStockObject(DEFAULT_GUI_FONT);
    SendMessageW(ret, WM_SETFONT, (WPARAM) lbl_font, MAKELPARAM(TRUE, 0));
    
    return ret;
}

void
uhashtools_lbl_change_text
(
    HWND lbl_handle,
    const wchar_t* txt
)
{
    SetWindowTextW(lbl_handle, txt);
}