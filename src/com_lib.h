/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#if WINVER >= 0x0601

#include <Windows.h>

struct ComLibState
{
    BOOL com_lib_is_initialized;
    DWORD initialized_for_thread_id;
};

extern
BOOL
uhashtools_com_lib_init
(
    struct ComLibState* com_lib_state
);

extern
void
uhashtools_com_lib_deinit
(
    struct ComLibState* com_lib_state
);

#endif