/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "error_utilities.h"

#include <Windows.h>

static HWND message_boxes_owner = NULL;

static
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
uhashtools_set_message_boxes_owner
(
    HWND new_message_boxes_owner
)
{
    message_boxes_owner = new_message_boxes_owner;
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
