/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "gui_lbl_common.h"

#include "error_utilities.h"

#include <Windows.h>

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
