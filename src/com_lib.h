/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024-2025 Marcel Gosmann <thafiredragonofdeath@gmail.com>
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

/**
 * Initializes the Windows COM library for the current thread.
 * This function must be called before anything from the taskbar
 * icon progress bar can be used.
 * 
 * This operation allocates dynamic ressources which must be freed
 * after usage to avoid resource leaks. To free the resources
 * allocated by this function call the function "uhashtools_com_lib_deinit()"
 * when you don't need the COM library anymore.
 * 
 * @param com_lib_state Structure holding the current COM library
 *                      initialization state. If the initialization
 *                      state changes the new state will be written
 *                      into this structure.
 * 
 * @return Returns 'TRUE' if the operation was successful.
 *         Otherwise this function returns 'FALSE'.
 */
extern
BOOL
uhashtools_com_lib_init
(
    struct ComLibState* com_lib_state
);

/**
 * DeInitializes the Windows COM library for the current thread and frees the
 * resources allocated by the "uhashtools_com_lib_init()" function. This
 * function must be called in the same thread as the previous call of the
 * "uhashtools_com_lib_init()" function.
 * 
 * @param com_lib_state Structure holding the current COM library
 *                      initialization state. If the initialization
 *                      state changes the new state will be written
 *                      into this structure.
 */
extern
void
uhashtools_com_lib_deinit
(
    struct ComLibState* com_lib_state
);

#endif
