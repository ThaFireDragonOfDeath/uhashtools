/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#ifndef UNICODE
    #error This application must be compiled with the compiler option "/DUNICODE" and "/D_UNICODE"!
#endif 

#ifndef _UNICODE
    #error This application must be compiled with the compiler option "/DUNICODE" and "/D_UNICODE"!
#endif 

#include "cli_arguments.h"
#include "error_utilities.h"
#include "mainwin.h"
#include "mainwin_ctx.h"

#include <Windows.h>

#include <stdlib.h>

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
    /*
     * Since there can only exist one main window per process, the
     * main window context instance will exist as long the process
     * is running.
     */
    static struct MainWindowCtx main_window_state;

    /* Silencing the unused parameter warnings */
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    uhashtools_mainwin_ctx_init(&main_window_state);
    uhashtools_cli_arguments_fill_from_argc_argv(&main_window_state.cli_arguments, __argc, __wargv);
    uhashtools_start_main_window(hInstance, nShowCmd, &main_window_state);

    return 0;
}
