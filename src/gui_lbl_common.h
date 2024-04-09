/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <Windows.h>

extern
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
);

extern
void
uhashtools_lbl_change_text
(
    HWND lbl_handle,
    const wchar_t* txt
);
