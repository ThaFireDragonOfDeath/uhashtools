/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <Windows.h>

#include "mainwin_state_enum.h"

extern
HWND
uhashtools_pb_calc_result_create
(
    HINSTANCE app_instance,
    HWND parent_window,
    int right_anchor_win_x
);

extern
void
uhashtools_pb_calc_result_on_parent_resize
(
    HWND self,
    UINT mainwin_new_width,
    int right_anchor_win_x
);

extern
void
uhashtools_pb_calc_result_on_state_changed
(
    HWND self,
    enum MainWindowState mainwin_state
);

extern
void
uhashtools_pb_calc_result_on_work_progress
(
    HWND self,
    unsigned int progress_in_percent
);
