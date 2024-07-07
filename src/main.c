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

#include "errorutils.h"
#include "mainwin.h"
#include "mainwin_ctx.h"

#include <Windows.h>

static struct MainWindowCtx global_main_window_state;

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

    uhashtools_mainwin_ctx_init(&global_main_window_state);
    uhashtools_start_main_window(hInstance, nShowCmd, &global_main_window_state);

    return 0;
}
