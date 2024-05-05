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
uhashtools_btn_action_create
(
    HINSTANCE app_instance,
    HWND parent_window,
    enum MainWindowState mainwin_state
);

extern
void
uhashtools_btn_action_on_parent_resize
(
    HWND self,
    int parent_width,
    int parent_height
);

extern
void
uhashtools_btn_action_on_state_changed
(
    HWND self,
    enum MainWindowState mainwin_state
);