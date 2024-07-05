/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwin.h"

#include "errorutils.h"
#include "mainwin_actions.h"
#include "mainwin_ctx.h"
#include "mainwin_message_handler.h"
#include "product.h"

#if _WIN32_WINNT >= 0x0601
    #include "com_lib.h"
#endif

#include <malloc.h>
#include <shellapi.h>
#include <Windows.h>
#include <windowsx.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Internal enumerations */

/* Internal structure definitions */

/* Graphical element values */

const DWORD MAINWIN_STYLE = WS_OVERLAPPEDWINDOW;
const DWORD MAINWIN_STYLE_EX = WS_EX_OVERLAPPEDWINDOW;
const int MAINWIN_WIDTH_MIN = 300;
const int MAINWIN_HIGHT_MIN = 200;

/* Helper functions */

static
LRESULT
CALLBACK uhashtools_main_win_proc
(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    return uhashtools_mainwin_handle_message(hwnd,
                                             uMsg,
                                             wParam,
                                             lParam,
                                             MAINWIN_WIDTH_MIN,
                                             MAINWIN_HIGHT_MIN);
}

static 
BOOL
uhashtools_create_main_window
(
    HINSTANCE hInstance,
    struct MainWindowCtx* mainwin_ctx
)
{
    HWND main_window_handle = NULL;

    mainwin_ctx->app_instance_handle = hInstance;

    main_window_handle = CreateWindowExW(MAINWIN_STYLE_EX,
                                         uhashtools_product_get_mainwin_classname(),
                                         uhashtools_product_get_mainwin_title(),
                                         MAINWIN_STYLE,
                                         CW_USEDEFAULT,
                                         CW_USEDEFAULT,
                                         uhashtools_product_get_recommended_mainwin_width(),
                                         MAINWIN_HIGHT_MIN,
                                         NULL,
                                         NULL,
                                         hInstance,
                                         (LPVOID) mainwin_ctx);

    mainwin_ctx->own_window_handle = main_window_handle;

    return main_window_handle != NULL;
}

static
void
uhashtools_show_main_window
(
    HWND winHandle,
    int nCmdShow
)
{
    ShowWindow(winHandle, nCmdShow);
    UpdateWindow(winHandle);
}

static
void
uhashtools_enter_main_message_loop
(
    void
)
{
    MSG msg;
    BOOL contLoop = TRUE;
    BOOL getMsgResult = FALSE;

    (void) memset((void*) &msg, 0, sizeof msg);

    while(contLoop == TRUE)
    {
        getMsgResult = GetMessageW(&msg, NULL, 0, 0);

        if(getMsgResult > 0)
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        else if(getMsgResult == 0)
        {
            int gui_rc = (int) msg.wParam;
            contLoop = FALSE;

            (void) wprintf_s(L"[DEBUG] Exiting main loop normally with return code '%i'...\n", gui_rc);
            (void) fflush(stdout);
        }
        else
        {
            DWORD lastError = GetLastError();
            contLoop = FALSE;

            (void) wprintf_s(L"[ERROR] Internal error: GetMessage() failed with errno '%lu'...\n", lastError);
            (void) fflush(stdout);
        }
    }
}

/* API functions */

BOOL
uhashtools_start_main_window
(
    HINSTANCE hInstance,
    int nCmdShow,
    struct MainWindowCtx* mainwin_ctx
)
{
    BOOL isErr = FALSE;
    ATOM mainWinClassAtom = 0;

    mainWinClassAtom = uhashtools_mainwin_register_mainwin_class(hInstance,
                                                                 uhashtools_main_win_proc);

    UHASHTOOLS_ASSERT(mainWinClassAtom, L"Failed to register the main window class!");

    mainwin_ctx->event_message_buf_is_writeable_event = CreateEventExW(NULL,
                                                                       NULL,
                                                                       CREATE_EVENT_INITIAL_SET,
                                                                       DELETE | SYNCHRONIZE | EVENT_MODIFY_STATE);
    UHASHTOOLS_ASSERT(mainwin_ctx->event_message_buf_is_writeable_event,
                      L"Failed to create the event message synchronization object!");

    UHASHTOOLS_ASSERT(uhashtools_create_main_window(hInstance, mainwin_ctx),
                      L"Failed to create the main window!");

    uhashtools_show_main_window(mainwin_ctx->own_window_handle,
                                nCmdShow);
    uhashtools_enter_main_message_loop();

    if(mainwin_ctx->own_window_handle != NULL)
    {
        DestroyWindow(mainwin_ctx->own_window_handle);
        
        mainwin_ctx->own_window_handle = NULL;
    }

    if(mainWinClassAtom != 0)
    {
        UnregisterClassW(uhashtools_product_get_mainwin_classname(),
                         hInstance);
    }

    return !isErr;
}
