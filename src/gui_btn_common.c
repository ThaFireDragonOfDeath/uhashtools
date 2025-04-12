/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024-2025 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "gui_btn_common.h"

#include "error_utilities.h"

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

    UHASHTOOLS_ASSERT(app_instance != NULL && app_instance != INVALID_HANDLE_VALUE,
                      L"Internal error: Entered with invalid application instance handle!");

    UHASHTOOLS_ASSERT(parent_window != NULL && parent_window != INVALID_HANDLE_VALUE,
                      L"Internal error: Entered with invalid parent window handle!");

    UHASHTOOLS_ASSERT(icon != NULL && icon != INVALID_HANDLE_VALUE,
                      L"Internal error: Entered with invalid icon handle!");

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

    UHASHTOOLS_ASSERT(ret != NULL, L"Internal error: CreateWindowExW() failed!");

    (void) SendMessageW(ret, BM_SETIMAGE, (WPARAM) IMAGE_ICON, (LPARAM) icon);

    return ret;
}

void
uhashtools_btn_set_icon
(
    HWND self,
    HICON icon
)
{
    UHASHTOOLS_ASSERT(self != NULL && self != INVALID_HANDLE_VALUE,
                      L"Internal error: Entered with invalid own window handle!");

    UHASHTOOLS_ASSERT(icon != NULL && icon != INVALID_HANDLE_VALUE,
                      L"Internal error: Entered with invalid icon handle!");

    (void) SendMessageW(self, BM_SETIMAGE, (WPARAM) IMAGE_ICON, (LPARAM) icon);
}
