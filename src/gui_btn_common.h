/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024-2025 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <Windows.h>

/**
 * Creates a button control. This application uses only icon buttons
 * so the buttons created by this function don't have text.
 * 
 * If the functions fails because of invalid arguments or an internal error
 * the application will crash with a fatal error message.
 * 
 * @param app_instance Handle to the current executable. This is the handle which
 *                     we will receive from the CRT in the "wWinMain()" function.
 *                     This parameter must not be 'NULL' or 'INVALID_HANDLE_VALUE'.
 * @param parent_window Handle to the parent element of this UI element. This is
 *                      usually the main window.
 *                      This parameter must not be 'NULL' or 'INVALID_HANDLE_VALUE'.
 * @param style Style flags bitset of this element.
 *              See "https://learn.microsoft.com/en-us/windows/win32/winmsg/window-styles"
 *              and "https://learn.microsoft.com/en-us/windows/win32/controls/button-styles"
 *              for an overview of possible values.
 * @param style_ex Extended window styles bitset. This is usually '0'.
 *                 See "https://learn.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles"
 *                 for an overview of possible values.
 * @param x Position of this element on the x axis relative to the parent element.
 * @param y Position of this element on the y axis relative to the parent element.
 * @param width Width of this element.
 * @param height Height of this element.
 * @param icon Handle to the icon which shall be displayed within the button.
 *             A handle to an icon can be obtained using the Win32 functions
 *             "ExtractIconExW()" or "LoadImageW()".
 *             This parameter must not be 'NULL' or 'INVALID_HANDLE_VALUE'.
 * 
 * @return Returns the Window handle of the created button control element.
 */
extern
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
);

/**
 * Changes the icon of the button control after it has been created.
 * 
 * @param self Handle to the target button control.
 *             This parameter must not be 'NULL' or 'INVALID_HANDLE_VALUE'.
 * @param icon Handle to the icon which shall be displayed within the button.
 *             A handle to an icon can be obtained using the Win32 functions
 *             "ExtractIconExW()" or "LoadImageW()".
 *             This parameter must not be 'NULL' or 'INVALID_HANDLE_VALUE'.
 */
extern
void
uhashtools_btn_set_icon
(
    HWND self,
    HICON icon
);
