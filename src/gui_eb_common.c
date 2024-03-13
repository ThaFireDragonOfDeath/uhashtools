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

#include "gui_eb_common.h"

#include <CommCtrl.h>
#include <Windows.h>
#include <windowsx.h>

#include "errorutils.h"

HWND
uhashtools_eb_create
(
    HINSTANCE app_instance,
    HWND parant_window,
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
                          L"EDIT",         /* Window class */
                          txt,             /* Window title*/
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

    lbl_font = (HFONT) GetStockObject(DEFAULT_GUI_FONT);
    SendMessageW(ret, WM_SETFONT, (WPARAM) lbl_font, MAKELPARAM(TRUE, 0));
    
    return ret;
}

void
uhashtools_eb_set_text
(
    HWND eb_handle,
    const wchar_t* txt
)
{
    UHASHTOOLS_ASSERT(txt, L"Invalid param: Entered with txt == NULL!");

    Edit_SetText(eb_handle, txt);
}

