/*
 * µHashtools - A small graphical file hashing tool for Microsoft Windows
 * Copyright (C) 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * 
 * This file is part of µHashtools.
 * 
 * µHashtools is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 * 
 * µHashtools is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * µHashtools. If not, see <https://www.gnu.org/licenses/>.
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <Windows.h>

#define EB_EXTRA_Y_DISTANCE_TO_OTHER_EB 9
#define DEFAULT_DISTANCE 5
#define LBL_DEFAULT_HIGHT 18
#define LBL_EXTRA_Y_DISTANCE_TO_OTHER_EB 9
#define LBL_EXTRA_Y_DISTANCE_TO_OTHER_LBL 9
#define PB_EB_DEFAULT_HIGHT 26

/* 
 * In the main window nearly all labels are aranged in
 * one column. Those lables shares the same width.
 */
#define MW_FC_LBL_WIDTH 60

#ifndef WM_COPYGLOBALDATA
    #define WM_COPYGLOBALDATA 0x49
#endif

extern
int
uhashtools_gui_elm_get_x
(
    HWND elm_handle
);

extern
int
uhashtools_gui_elm_get_y
(
    HWND elm_handle
);

extern
int
uhashtools_gui_elm_get_width
(
    HWND elm_handle
);

extern
int
uhashtools_gui_elm_get_height
(
    HWND elm_handle
);

extern
void
uhashtools_gui_elm_resize
(
    HWND elm_handle,
    int new_width,
    int new_height
);

extern
void
uhashtools_gui_elm_move
(
    HWND elm_handle,
    int new_x,
    int new_y
);

extern
void
uhashtools_gui_elm_set_enabled
(
    HWND elm_handle,
    BOOL enabled
);

extern
void
uhashtools_gui_elm_set_visible
(
    HWND elm_handle,
    BOOL visible
);
