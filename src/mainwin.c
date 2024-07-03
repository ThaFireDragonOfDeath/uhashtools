/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwin.h"

#include "errorutils.h"
#include "gui_common.h"
#include "mainwin_actions.h"
#include "mainwin_ctx.h"
#include "mainwin_event_handler.h"
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
uhashtools_eb_lbl_handle_WM_CTLCOLOR_msg
(
    WPARAM wParam
)
{
    HDC hdc = (HDC) wParam;
    SetTextColor(hdc, GetSysColor(COLOR_WINDOWTEXT));
    SetBkColor(hdc, GetSysColor(COLOR_WINDOW));

    return (LRESULT) (COLOR_WINDOW + 1);
}

#if _WIN32_WINNT >= 0x0601
static
BOOL
uhashtools_register_wm_taskbar_button_created
(
    HWND main_window_handle,
    struct MainWindowCtx* main_window_ctx
)
{
    UINT register_window_message_result = 0;
    BOOL change_message_window_filter_result = FALSE;

    UHASHTOOLS_ASSERT(main_window_ctx, L"Internal error: Entered with main_window_ctx == NULL in uhashtools_register_taskbar_button_created_wm()!");

    register_window_message_result = RegisterWindowMessageW(L"TaskbarButtonCreated");

    if (register_window_message_result == 0)
    {
        return FALSE;
    }

    change_message_window_filter_result = ChangeWindowMessageFilterEx(main_window_handle, register_window_message_result, MSGFLT_ALLOW, NULL);

    if (!change_message_window_filter_result)
    {
        wprintf_s(L"[WARNING]: Failed to allow 'TaskbarButtonCreated' window message flow! Taskbar icon may not work!");
        fflush(stdout);
    }

    main_window_ctx->wm_taskbar_button_created = register_window_message_result;

    return TRUE;
}
#endif

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
    struct MainWindowCtx* main_window_ctx = NULL;

    /* Handle window creation event */

    if(uMsg == WM_CREATE)
    {
        CREATESTRUCTW* create_params = (CREATESTRUCTW*) lParam;

        uhashtools_set_message_boxes_owner(hwnd);

        if(create_params == NULL || create_params->lpCreateParams == NULL)
        {
            (void) wprintf_s(L"Main window: WM_CREATE failed! 'create_params' or 'create_params->lpCreateParams' were NULL!\n");
            (void) fflush(stdout);

            return -1;
        }

        main_window_ctx = (struct MainWindowCtx*) create_params->lpCreateParams;
        main_window_ctx->own_window_handle = hwnd;

        SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR) main_window_ctx);

#if _WIN32_WINNT >= 0x0601
        /* Allow receiving messages for drag and drop files. */
        (void) ChangeWindowMessageFilterEx(hwnd, WM_DROPFILES, MSGFLT_ALLOW, NULL);
        (void) ChangeWindowMessageFilterEx(hwnd, WM_COPYDATA, MSGFLT_ALLOW, NULL);
        (void) ChangeWindowMessageFilterEx(hwnd, WM_COPYGLOBALDATA, MSGFLT_ALLOW, NULL);

        (void) uhashtools_com_lib_init(&main_window_ctx->com_lib_state);
        (void) uhashtools_register_wm_taskbar_button_created(hwnd, main_window_ctx);
#endif

        uhashtools_mainwin_init_ui_controls(main_window_ctx);

        return 0;
    }

    /* Handle events that aren't depending on the main window context */

    if(uMsg == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }
    else if(uMsg == WM_GETMINMAXINFO)
    {
        MINMAXINFO* minMaxPtr = (MINMAXINFO*) lParam;
        POINT minRes;

        /* Restrict minimum size to start size */
        minRes.x = MAINWIN_WIDTH_MIN;
        minRes.y = MAINWIN_HIGHT_MIN;

        minMaxPtr->ptMinTrackSize = minRes;

        return 0;
    }
    else if(uMsg == WM_CTLCOLORSTATIC || uMsg == WM_CTLCOLOREDIT)
    {
        return uhashtools_eb_lbl_handle_WM_CTLCOLOR_msg(wParam);
    }

    main_window_ctx = (struct MainWindowCtx*) GetWindowLongPtrW(hwnd, GWLP_USERDATA);

    if (!main_window_ctx)
    {
        return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }

    /* Handle events that are depending on the main window context */

#if _WIN32_WINNT >= 0x0601
    if(uMsg == main_window_ctx->wm_taskbar_button_created)
    {
        uhashtools_mainwin_on_taskbar_button_created(main_window_ctx);

        return 0;
    }
#endif
    
    if(uMsg == WM_CLOSE)
    {
#if _WIN32_WINNT >= 0x0601
        (void) uhashtools_com_lib_deinit(&main_window_ctx->com_lib_state);
#endif

        uhashtools_set_message_boxes_owner(NULL);

        DestroyWindow(hwnd);
        main_window_ctx->own_window_handle = NULL;

        return 0;
    }
    else if(uMsg == WM_SIZE)
    {
        UINT new_width = LOWORD(lParam);
        UINT new_height = HIWORD(lParam);

        uhashtools_mainwin_resize_child_elements(main_window_ctx, new_width, new_height);

        return 0;
    }
    else if(uMsg == WM_DROPFILES)
    {
        HDROP dropped_files_event_handle = (HDROP) wParam;
        
        uhashtools_mainwin_on_file_dropped(main_window_ctx, dropped_files_event_handle);

        return 0;
    }
    else if(uMsg == WM_COMMAND)
    {
        if((HWND) lParam == main_window_ctx->btn_select_file)
        {
            WORD control_notification = HIWORD(wParam);

            if(control_notification == BN_CLICKED)
            {
                uhashtools_mainwin_on_select_file_button_pressed(main_window_ctx);

                return 0;
            }
        }
        else if ((HWND) lParam == main_window_ctx->btn_action)
        {
            WORD control_notification = HIWORD(wParam);

            if(control_notification == BN_CLICKED)
            {
                if (main_window_ctx->own_state == MAINWINDOWSTATE_WORKING_CANCELABLE)
                {
                    uhashtools_mainwin_on_cancel_button_pressed(main_window_ctx);
                }
                else if (main_window_ctx->own_state == MAINWINDOWSTATE_CANCELED ||
                         main_window_ctx->own_state == MAINWINDOWSTATE_FINISHED_ERROR ||
                         main_window_ctx->own_state == MAINWINDOWSTATE_FINISHED_ERROR_MSGBOX_CONFIRMED)
                {
                    uhashtools_mainwin_on_retry_button_pressed(main_window_ctx);
                }
                else if (main_window_ctx->own_state == MAINWINDOWSTATE_FINISHED_SUCCESS)
                {
                    uhashtools_mainwin_on_copy_to_clipboard_button_pressed(main_window_ctx);
                }
                
                return 0;
            }
        }
    }
    else if(uMsg == WM_USER)
    {
        struct HashCalculationWorkerEventMessage event_message_buf_clone;
        BOOL signal_event_success = FALSE;
        
        event_message_buf_clone = main_window_ctx->event_message_buf;
        
        signal_event_success = SetEvent(main_window_ctx->event_message_buf_is_writeable_event);
        UHASHTOOLS_ASSERT(signal_event_success, L"Failed reset the event synchronization object back into the signaled state!");

        uhashtools_mainwin_on_hash_calculation_worker_event_message_received(main_window_ctx, &event_message_buf_clone);
        
        return 0;
    }

    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

static
ATOM
uhashtools_register_main_window_class
(
    HINSTANCE hInstance
)
{
    WNDCLASSEXW wc;

    SecureZeroMemory(&wc, sizeof wc);

    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc = uhashtools_main_win_proc;
    wc.hInstance = hInstance;
    wc.lpszClassName = uhashtools_product_get_mainwin_classname();
    wc.hIcon = LoadIconW(hInstance, L"UHASHTOOLS_APPLICATION_ICON");
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);

    return RegisterClassExW(&wc);
}

static 
BOOL
uhashtools_create_main_window
(
    HINSTANCE hInstance,
    struct MainWindowCtx* main_window_ctx
)
{
    HWND main_window_handle = NULL;

    main_window_ctx->app_instance_handle = hInstance;

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
                                         (LPVOID) main_window_ctx);

    main_window_ctx->own_window_handle = main_window_handle;

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

    SecureZeroMemory(&msg, sizeof msg);

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

    mainWinClassAtom = uhashtools_register_main_window_class(hInstance);
    UHASHTOOLS_ASSERT(mainWinClassAtom, L"Failed to register the main window class!");

    mainwin_ctx->event_message_buf_is_writeable_event = CreateEventExW(NULL,
                                                                       NULL,
                                                                       CREATE_EVENT_INITIAL_SET,
                                                                       DELETE | SYNCHRONIZE | EVENT_MODIFY_STATE);
    UHASHTOOLS_ASSERT(mainwin_ctx->event_message_buf_is_writeable_event, L"Failed to create the event message synchronization object!");

    UHASHTOOLS_ASSERT(uhashtools_create_main_window(hInstance, mainwin_ctx), L"Failed to create the main window!");

    uhashtools_show_main_window(mainwin_ctx->own_window_handle, nCmdShow);
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