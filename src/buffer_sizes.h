/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

/* 
 * Attention!
 * Those buffer sizes are not in bytes! To get the size in
 * bytes use the formula: XYZ_TSIZE * sizeof(wchar_t)
 * 
 * Since we don't allocate the memory of those buffers with malloc
 * and we're using the wide string C functions that shouldn't be
 * a problem. 
 */
#define FILEPATH_BUFFER_TSIZE 512
#define HASH_RESULT_BUFFER_TSIZE 256
#define GENERIC_TXT_MESSAGES_BUFFER_TSIZE 512
