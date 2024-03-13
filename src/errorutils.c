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

#include "errorutils.h"

#include <Windows.h>

static HWND message_boxes_owner = NULL;

void
uhashtools_set_message_boxes_owner
(
    HWND new_message_boxes_owner
)
{
    message_boxes_owner = new_message_boxes_owner;
}

void
uhashtools_show_error_msg
(
    const wchar_t* error_title,
    const wchar_t* error_txt
)
{
    MessageBoxW(message_boxes_owner, error_txt, error_title, MB_ICONERROR);
}

void
uhashtools_handle_fatal_error
(
    const wchar_t* error_title,
    const wchar_t* error_txt
)
{
  uhashtools_show_error_msg(error_title, error_txt);
  FatalExit(1);
}