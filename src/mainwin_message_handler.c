/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwin_message_handler.h"

#include "errorutils.h"
#include "gui_common.h"
#include "mainwin_actions.h"
#include "mainwin_ctx.h"
#include "mainwin_event_handler.h"

#if _WIN32_WINNT >= 0x0601
    #include "com_lib.h"
#endif

#include <stdio.h>

static
LRESULT
uhashtools_mainwin_handle_message_WM_CREATE
(
    HWND hwnd,
    LPARAM lParam
)
{
    struct MainWindowCtx* mainwin_ctx = NULL;
    CREATESTRUCTW* create_params = (CREATESTRUCTW*) lParam;
    LONG_PTR set_window_long_ptr_rc = 0;

    uhashtools_set_message_boxes_owner(hwnd);

    if (create_params == NULL || create_params->lpCreateParams == NULL)
    {
        (void) wprintf_s(L"[ERROR] Main window: WM_CREATE failed! 'create_params' or 'create_params->lpCreateParams' were NULL!\n");
        (void) fflush(stdout);

        return -1;
    }

    mainwin_ctx = (struct MainWindowCtx*) create_params->lpCreateParams;
    mainwin_ctx->own_window_handle = hwnd;

    SetLastError(0);
    set_window_long_ptr_rc = SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR) mainwin_ctx);

    if (!set_window_long_ptr_rc && GetLastError() != 0)
    {
        (void) wprintf_s(L"[ERROR] Main window: WM_CREATE failed! Function 'SetWindowLongPtrW()' failed!\n");
        (void) fflush(stdout);

        return -1;
    }

#if _WIN32_WINNT >= 0x0601
    /* Allow receiving messages for drag and drop files. */
    (void) ChangeWindowMessageFilterEx(hwnd, WM_DROPFILES, MSGFLT_ALLOW, NULL);
    (void) ChangeWindowMessageFilterEx(hwnd, WM_COPYDATA, MSGFLT_ALLOW, NULL);
    (void) ChangeWindowMessageFilterEx(hwnd, WM_COPYGLOBALDATA, MSGFLT_ALLOW, NULL);

    (void) uhashtools_com_lib_init(&mainwin_ctx->com_lib_state);
    (void) uhashtools_register_message_type_taskbar_button_created(hwnd, mainwin_ctx);
#endif

    uhashtools_mainwin_init_ui_controls(mainwin_ctx);

    return 0;
}

static
LRESULT
uhashtools_mainwin_handle_message_WM_DESTROY
(
    void
)
{
    PostQuitMessage(0);
    
    return 0;
}

static
LRESULT
uhashtools_mainwin_handle_message_WM_GETMINMAXINFO
(
    LPARAM lParam,
    int mainwin_min_width,
    int mainwin_min_height
)
{
    MINMAXINFO* minMaxPtr = (MINMAXINFO*) lParam;
    POINT minRes;

    /* Restrict minimum size to start size */
    minRes.x = mainwin_min_width;
    minRes.y = mainwin_min_height;

    minMaxPtr->ptMinTrackSize = minRes;

    return 0;
}

static
LRESULT
uhashtools_mainwin_handle_message_WM_CTLCOLOR
(
    WPARAM wParam
)
{
    HDC hdc = (HDC) wParam;
    SetTextColor(hdc, GetSysColor(COLOR_WINDOWTEXT));
    SetBkColor(hdc, GetSysColor(COLOR_WINDOW));

    return (LRESULT) (COLOR_WINDOW + 1);
}

static
LRESULT
uhashtools_mainwin_handle_message_WM_CLOSE
(
    HWND hwnd,
    struct MainWindowCtx* mainwin_ctx
)
{
    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");

#if _WIN32_WINNT >= 0x0601
    (void) uhashtools_com_lib_deinit(&mainwin_ctx->com_lib_state);
#endif

    uhashtools_set_message_boxes_owner(NULL);

    DestroyWindow(hwnd);
    mainwin_ctx->own_window_handle = NULL;

    return 0;
}

static
LRESULT
uhashtools_mainwin_handle_message_WM_SIZE
(
    LPARAM lParam,
    struct MainWindowCtx* mainwin_ctx
)
{
    const UINT new_width = LOWORD(lParam);
    const UINT new_height = HIWORD(lParam);

    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");

    uhashtools_mainwin_resize_child_elements(mainwin_ctx, new_width, new_height);

    return 0;
}

static
LRESULT
uhashtools_mainwin_handle_message_WM_DROPFILES
(
    WPARAM wParam,
    struct MainWindowCtx* mainwin_ctx
)
{
    HDROP dropped_files_event_handle = (HDROP) wParam;

    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");
        
    uhashtools_mainwin_on_file_dropped(mainwin_ctx, dropped_files_event_handle);

    return 0;
}

static
LRESULT
uhashtools_mainwin_handle_message_WM_COMMAND
(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam,
    struct MainWindowCtx* mainwin_ctx
)
{
    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");

    if ((HWND) lParam == mainwin_ctx->btn_select_file)
    {
        const WORD control_notification = HIWORD(wParam);

        if (control_notification == BN_CLICKED)
        {
            uhashtools_mainwin_on_select_file_button_pressed(mainwin_ctx);

            return 0;
        }
    }
    else if ((HWND) lParam == mainwin_ctx->btn_action)
    {
        const WORD control_notification = HIWORD(wParam);

        if (control_notification == BN_CLICKED)
        {
            if (mainwin_ctx->own_state == MAINWINDOWSTATE_WORKING_CANCELABLE)
            {
                uhashtools_mainwin_on_cancel_button_pressed(mainwin_ctx);
                
                return 0;
            }
            else if (mainwin_ctx->own_state == MAINWINDOWSTATE_CANCELED ||
                     mainwin_ctx->own_state == MAINWINDOWSTATE_FINISHED_ERROR ||
                     mainwin_ctx->own_state == MAINWINDOWSTATE_FINISHED_ERROR_MSGBOX_CONFIRMED)
            {
                uhashtools_mainwin_on_retry_button_pressed(mainwin_ctx);

                return 0;
            }
            else if (mainwin_ctx->own_state == MAINWINDOWSTATE_FINISHED_SUCCESS)
            {
                uhashtools_mainwin_on_copy_to_clipboard_button_pressed(mainwin_ctx);

                return 0;
            }
        }
    }
    
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

static
LRESULT
uhashtools_mainwin_handle_message_WM_USER
(
    struct MainWindowCtx* mainwin_ctx
)
{
    struct HashCalculationWorkerEventMessage event_message_buf_clone;
    BOOL signal_event_success = FALSE;

    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");
    
    event_message_buf_clone = mainwin_ctx->event_message_buf;
    
    signal_event_success = SetEvent(mainwin_ctx->event_message_buf_is_writeable_event);
    UHASHTOOLS_ASSERT(signal_event_success,
                      L"Failed reset the event synchronization object back into the signaled state!");

    uhashtools_mainwin_on_hash_calculation_worker_event_message_received(mainwin_ctx,
                                                                         &event_message_buf_clone);
    
    return 0;
}

LRESULT
uhashtools_mainwin_handle_message
(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam,
    int mainwin_min_width,
    int mainwin_min_height
)
{
    struct MainWindowCtx* mainwin_ctx = NULL;
    
    mainwin_ctx = (struct MainWindowCtx*) GetWindowLongPtrW(hwnd, GWLP_USERDATA);

    if (uMsg == WM_CREATE)
    {
        return uhashtools_mainwin_handle_message_WM_CREATE(hwnd, lParam);
    }
    else if (uMsg == WM_DESTROY)
    {
        return uhashtools_mainwin_handle_message_WM_DESTROY();
    }
    else if (uMsg == WM_GETMINMAXINFO)
    {
        return uhashtools_mainwin_handle_message_WM_GETMINMAXINFO(lParam,
                                                                  mainwin_min_width,
                                                                  mainwin_min_height);
    }
    else if (uMsg == WM_CTLCOLORSTATIC || uMsg == WM_CTLCOLOREDIT)
    {
        return uhashtools_mainwin_handle_message_WM_CTLCOLOR(wParam);
    }
    else if (uMsg == WM_CLOSE)
    {
        UHASHTOOLS_ASSERT(mainwin_ctx,
                          L"Internal error: No mainwin_ctx while handling the WM_CLOSE message!");

        return uhashtools_mainwin_handle_message_WM_CLOSE(hwnd, mainwin_ctx);
    }
#if _WIN32_WINNT >= 0x0601
    else if (mainwin_ctx && uMsg == mainwin_ctx->wm_taskbar_button_created)
    {
        uhashtools_mainwin_on_taskbar_button_created(mainwin_ctx);

        return 0;
    }
#endif
    else if (mainwin_ctx && uMsg == WM_SIZE)
    {
        return uhashtools_mainwin_handle_message_WM_SIZE(lParam, mainwin_ctx);
    }
    else if (mainwin_ctx && uMsg == WM_DROPFILES)
    {
        return uhashtools_mainwin_handle_message_WM_DROPFILES(wParam, mainwin_ctx);
    }
    else if (mainwin_ctx && uMsg == WM_COMMAND)
    {
        return uhashtools_mainwin_handle_message_WM_COMMAND(hwnd, uMsg, wParam, lParam, mainwin_ctx);
    }
    else if (mainwin_ctx && uMsg == WM_USER)
    {
        return uhashtools_mainwin_handle_message_WM_USER(mainwin_ctx);
    }
    else
    {
        return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }
}
