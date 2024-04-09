/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <stddef.h>

extern
void
uhashtools_clipboard_utils_set_clipboard_text
(
    const wchar_t* clipboard_text,
    size_t clipboard_text_strlen
);
