/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "mainwin_state.h"

#include <Windows.h>

extern
HWND
uhashtools_lbl_file_drop_create
(
    HINSTANCE app_instance,
    HWND parent_window,
    enum MainWindowState mainwin_state,
    int parent_width,
    int bottom_anchor_y
);

extern
void
uhashtools_lbl_file_drop_on_parent_resize
(
    HWND self,
    int parent_width,
    int bottom_anchor_y
);

void
uhashtools_lbl_file_drop_on_state_changed
(
    HWND self,
    enum MainWindowState mainwin_state
);
