/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "com_lib.h"

#if WINVER >= 0x0601

#include <Objbase.h>
#include <Windows.h>

#include "errorutils.h"

BOOL
uhashtools_com_lib_init
(
    struct ComLibState* com_lib_state
)
{
    HRESULT com_init_result = 0;

    UHASHTOOLS_ASSERT(com_lib_state, L"Internal error: Entered with null pointer as com_lib_state in uhashtools_com_lib_init()!");

    com_init_result = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    if (com_init_result != S_OK)
    {
        return FALSE;
    }

    SecureZeroMemory(com_lib_state, sizeof *com_lib_state);
    com_lib_state->com_lib_is_initialized = TRUE;
    com_lib_state->initialized_for_thread_id = GetCurrentThreadId();

    return TRUE;
}

void
uhashtools_com_lib_deinit
(
    struct ComLibState* com_lib_state
)
{
    const DWORD current_thread_id = GetCurrentThreadId();

    UHASHTOOLS_ASSERT(com_lib_state, L"Internal error: Entered with null pointer as com_lib_state in uhashtools_com_lib_deinit()!");

    if (com_lib_state->initialized_for_thread_id != current_thread_id)
    {
        UHASHTOOLS_FATAL_ERROR(L"Internal error: Tried to deinitialize the com library from the wrong thread!");
    }

    CoUninitialize();

    com_lib_state->com_lib_is_initialized = FALSE;
    com_lib_state->initialized_for_thread_id = 0;
}

#endif
