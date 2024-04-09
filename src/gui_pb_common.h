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
);

extern
void
uhashtools_pb_set_progress
(
    HWND pb_handle,
    unsigned int progress_in_percent
);
