/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <Windows.h>

#include "mainwin_state.h"

extern
HWND
uhashtools_eb_current_selected_file_create
(
    HINSTANCE app_instance,
    HWND parent_window,
    const enum MainWindowState mainwin_state,
    wchar_t* current_target_file,
    wchar_t* current_selected_file_txt_buf,
    int bottom_anchor_y,
    int right_anchor_x
);

extern
void
uhashtools_eb_current_selected_file_on_parent_resize
(
    HWND self,
    int bottom_anchor_y,
    int right_anchor_x
);

extern
void
uhashtools_eb_current_selected_file_on_state_changed
(
    HWND self,
    const enum MainWindowState new_mainwin_state,
    const wchar_t* current_target_file,
    wchar_t* current_selected_file_txt_buf
);
