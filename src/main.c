/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#ifndef UNICODE
#error This application must be compiled with the compiler option "/DUNICODE"!
#endif 

#include "errorutils.h"
#include "mainwin.h"
#include "mainwin_ctx_struct.h"

#include <Windows.h>


/* Application global variables */

static struct MainWindowCtx global_main_window_state;


/* Internal helper functions */

static
void
uhashtools_main_window_ctx_init
(
    struct MainWindowCtx* main_window_state
)
{
    UHASHTOOLS_ASSERT(main_window_state, L"Internal error: Entered with NULL in uhashtools_main_window_ctx_init()!");

    SecureZeroMemory(&main_window_state, sizeof main_window_state);
}


/* Public functions */

int
WINAPI
wWinMain
(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    /* Silencing the unused parameter warnings */
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    uhashtools_main_window_ctx_init(&global_main_window_state);
    uhashtools_start_main_window(hInstance, nShowCmd, &global_main_window_state);

    return 0;
}