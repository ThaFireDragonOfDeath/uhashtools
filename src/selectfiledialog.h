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
BOOL
uhashtools_select_file_dialog_open
(
    HWND dialog_owner_win,
    wchar_t* target_file_buf,
    size_t target_file_buf_tsize
);
