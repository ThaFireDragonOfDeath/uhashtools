/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "gui_eb_common.h"

#include "errorutils.h"

#include <CommCtrl.h>
#include <Windows.h>
#include <windowsx.h>

HWND
uhashtools_eb_create
(
    HINSTANCE app_instance,
    HWND parent_window,
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
                          parent_window,
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

