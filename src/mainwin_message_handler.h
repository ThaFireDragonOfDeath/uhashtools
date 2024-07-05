/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <Windows.h>

/**
 * Handles received messages for the main window.
 * This function is called by the window message procedure in
 * the file 'mainwin.c'.
 */
extern
LRESULT
uhashtools_mainwin_handle_message
(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam,
    int mainwin_min_width,
    int mainwin_min_height
);
