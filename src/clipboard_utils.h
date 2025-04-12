/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024-2025 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <stddef.h>

/**
 * Sets the clipboard content to the given text.
 * 
 * @param clipboard_text Text encoded as null byte terminated wide C string which shall
 *                       be written into the clipboard. This argument must not be a
 *                       null pointer.
 * @param clipboard_text_strlen Length of the wide C string (amount of wide characters
 *                              without counting the terminating null byte) given in the
 *                              argument "clipboard_text".
 */
extern
void
uhashtools_clipboard_utils_set_clipboard_text
(
    const wchar_t* clipboard_text,
    size_t clipboard_text_strlen
);
