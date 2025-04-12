/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024-2025 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <Windows.h>

/**
 * Opens a file selection dialog, blocks until the user has selected a target
 * file and writes the selected file into the "target_file_buf" buffer.
 * If the user cancels the file selection dialog the "target_file_buf" buffer
 * won't be modified and this method will return 'FALSE'.
 * 
 * @param dialog_owner_win Handle of the owner of the file selection dialog. If
 *                         this argument is 'NULL' the dialog will open without
 *                         owner. The value must not be 'INVALID_HANDLE_VALUE'.
 *                         Usually the handle of the main window is passed here.
 * @param target_file_buf Output buffer for the selected file path.
 * @param target_file_buf_tsize How many wide characters (including the
 *                              terminating null byte) can fit into the
 *                              "target_file_buf" buffer.
 * @return This method returns 'TRUE' if the user selected a file. If 'TRUE' is
 *         returned the "target_file_buf" buffer will contain the selected file
 *         path.
 *         This method returns 'FALSE' if the user canceled or closed the file
 *         selection dialog. The content of the "target_file_buf" buffer will
 *         remain unchanged.
 */
extern
BOOL
uhashtools_select_file_dialog_open
(
    HWND dialog_owner_win,
    wchar_t* target_file_buf,
    size_t target_file_buf_tsize
);
