/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <Windows.h>

#include "mainwin.h"

extern
HWND
uhashtools_eb_calc_result_create
(
    HINSTANCE app_instance,
    HWND parant_window,
    int right_anker_win_x,
    enum MainWindowState mainwin_state,
    const wchar_t* current_hash_result,
    wchar_t* eb_calc_result_txt_buf
);

extern
void
uhashtools_eb_calc_result_on_parent_resize
(
    HWND self,
    UINT mainwin_new_width,
    int right_anker_win_x
);

extern
void
uhashtools_eb_calc_result_on_state_changed
(
    HWND self,
    enum MainWindowState mainwin_state,
    const wchar_t* current_hash_result,
    wchar_t* eb_calc_result_txt_buf
);
