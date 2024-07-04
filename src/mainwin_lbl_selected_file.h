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
uhashtools_lbl_selected_file_create
(
    HINSTANCE app_instance,
    HWND parent_window,
    int bottom_anchor_y
);

extern
void
uhashtools_lbl_selected_file_on_parent_resize
(
    HWND self,
    int bottom_anchor_y
);
