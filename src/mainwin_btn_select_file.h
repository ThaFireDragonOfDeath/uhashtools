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

#include "mainwin.h"

extern
HWND
uhashtools_btn_select_file_create
(
    HINSTANCE app_instance,
    HWND parant_window,
    int bottom_anker_y
);

extern
void
uhashtools_btn_select_file_on_parent_resize
(
    HWND self,
    int parent_width,
    int bottom_anker_y
);

extern
void
uhashtools_btn_select_file_on_state_changed
(
    HWND self,
    enum MainWindowState mainwin_state
);
