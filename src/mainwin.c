/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwin.h"

#include <stdio.h>
#include <stdlib.h>

#include <CommCtrl.h>
#include <malloc.h>
#include <shellapi.h>
#include <Windows.h>
#include <windowsx.h>

#include "clipboard_utils.h"
#include "errorutils.h"
#include "gui_common.h"
#include "mainwin_btn_action.h"
#include "mainwin_btn_select_file.h"
#include "mainwin_eb_calc_result.h"
#include "mainwin_lbl_result_hash.h"
#include "mainwin_pb_calc_result.h"
#include "mainwin_lbl_selected_file.h"
#include "mainwin_eb_current_selected_file.h"
#include "mainwin_lbl_filedrop.h"
#include "product.h"
#include "selectfiledialog.h"

/* Internal enumerations */

/* Internal structure definitions */

/* Graphical element values */

const DWORD MAINWIN_STYLE = WS_OVERLAPPEDWINDOW;
const DWORD MAINWIN_STYLE_EX = WS_EX_OVERLAPPEDWINDOW;
const int MAINWIN_WIDTH_MIN = 300;
const int MAINWIN_HIGHT_MIN = 200;

/* Helper functions */

static
void
uhashtools_mainwin_init_ui_controls
(
    struct MainWindowCtx* mainwin_ctx
)
{
    HINSTANCE app_instance_handle = (HINSTANCE) INVALID_HANDLE_VALUE;
    HWND own_window_handle = (HWND) INVALID_HANDLE_VALUE;
    enum MainWindowState own_state = MAINWINDOWSTATE_INIT;
    int mainwin_width = 0;
    int mainwin_height = 0;
    int new_btn_action_x = 0;
    int new_btn_action_y = 0;
    int new_lbl_result_y = 0;
    int new_btn_select_file_x = 0;
    int new_eb_current_selected_file_y = 0;

    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");

    app_instance_handle = mainwin_ctx->app_instance_handle;
    own_window_handle = mainwin_ctx->own_window_handle;
    own_state = mainwin_ctx->own_state;

    mainwin_width = uhashtools_gui_elm_get_width(own_window_handle);
    mainwin_height = uhashtools_gui_elm_get_height(own_window_handle);

    mainwin_ctx->btn_action = uhashtools_btn_action_create(app_instance_handle,
                                                        own_window_handle,
                                                        own_state);

    new_btn_action_x = uhashtools_gui_elm_get_x(mainwin_ctx->btn_action);
    new_btn_action_y = uhashtools_gui_elm_get_y(mainwin_ctx->btn_action);
    
    mainwin_ctx->pb_calc_result = uhashtools_pb_calc_result_create(app_instance_handle,
                                                                own_window_handle,
                                                                new_btn_action_x);

    mainwin_ctx->eb_calc_result = uhashtools_eb_calc_result_create(app_instance_handle,
                                                                own_window_handle,
                                                                new_btn_action_x,
                                                                own_state,
                                                                mainwin_ctx->hash_result,
                                                                mainwin_ctx->eb_calc_result_txt_buf);

    mainwin_ctx->lbl_result_hash = uhashtools_lbl_result_hash_create(app_instance_handle,
                                                                  own_window_handle,
                                                                  own_state);
    
    new_lbl_result_y = uhashtools_gui_elm_get_y(mainwin_ctx->lbl_result_hash);

    mainwin_ctx->btn_select_file = uhashtools_btn_select_file_create(app_instance_handle,
                                                                  own_window_handle,
                                                                  new_btn_action_y);

    new_btn_select_file_x = uhashtools_gui_elm_get_x(mainwin_ctx->btn_select_file);
    
    mainwin_ctx->lbl_selected_file = uhashtools_lbl_selected_file_create(app_instance_handle,
                                                                      own_window_handle,
                                                                      new_lbl_result_y);

    mainwin_ctx->eb_current_selected_file = uhashtools_eb_current_selected_file_create(app_instance_handle,
                                                                                    own_window_handle,
                                                                                    mainwin_ctx->own_state,
                                                                                    mainwin_ctx->target_file,
                                                                                    mainwin_ctx->eb_current_selected_file_txt_buf,
                                                                                    new_lbl_result_y,
                                                                                    new_btn_select_file_x);
    
    new_eb_current_selected_file_y = uhashtools_gui_elm_get_y(mainwin_ctx->eb_current_selected_file);

    mainwin_ctx->lbl_filedrop = uhashtools_lbl_filedrop_create(app_instance_handle,
                                                            own_window_handle,
                                                            own_state,
                                                            mainwin_width,
                                                            new_eb_current_selected_file_y);
}

static
void
uhashtools_handle_calculation_progress_change
(
    struct MainWindowCtx* mainwin_ctx,
    unsigned int current_progress_in_percent
)
{
    uhashtools_pb_calc_result_on_work_progress(mainwin_ctx->pb_calc_result,
                                            current_progress_in_percent);
}

static
void
uhashtools_mainwin_change_state
(
    struct MainWindowCtx* mainwin_ctx,
    const enum MainWindowState new_mainwin_state
)
{
    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");
    
    mainwin_ctx->own_state = new_mainwin_state;
    
    uhashtools_btn_action_on_state_changed(mainwin_ctx->btn_action, new_mainwin_state);
    
    uhashtools_pb_calc_result_on_state_changed(mainwin_ctx->pb_calc_result, new_mainwin_state);
                                                      
    uhashtools_eb_calc_result_on_state_changed(mainwin_ctx->eb_calc_result,
                                            new_mainwin_state,
                                            mainwin_ctx->hash_result,
                                            mainwin_ctx->eb_calc_result_txt_buf);
    
    uhashtools_lbl_result_hash_on_state_changed(mainwin_ctx->lbl_result_hash,
                                             new_mainwin_state);
    
    uhashtools_btn_select_file_on_state_changed(mainwin_ctx->btn_select_file, new_mainwin_state);
    
    uhashtools_eb_current_selected_file_on_state_changed(mainwin_ctx->eb_current_selected_file,
                                                      new_mainwin_state,
                                                      mainwin_ctx->target_file,
                                                      mainwin_ctx->eb_current_selected_file_txt_buf);
    
    uhashtools_lbl_filedrop_on_state_changed(mainwin_ctx->lbl_filedrop,
                                          new_mainwin_state);
    
    if (new_mainwin_state == MAINWINDOWSTATE_FINISHED_ERROR)
    {
        if (mainwin_ctx->error_txt[0] == '\0')
        {
            (void) wcscpy_s(mainwin_ctx->error_txt, GENERIC_TXT_MESSAGES_BUFFER_TSIZE, L"I just don't know what went wrong (◑‿◐)!");
        }

        (void) MessageBoxW(mainwin_ctx->own_window_handle,
                           mainwin_ctx->error_txt,
                           L"Calculation failed",
                           MB_OK);
    }
    else if (new_mainwin_state == MAINWINDOWSTATE_WORKING)
    {
        uhashtools_handle_calculation_progress_change(mainwin_ctx, 0);
    }
}

static
void
uhashtools_mainwin_resize_child_elements
(
    struct MainWindowCtx* mainwin_ctx,
    UINT mainwin_new_width,
    UINT mainwin_new_height
)
{
    int new_btn_action_x = 0;
    int new_btn_action_y = 0;
    int new_lbl_result_y = 0;
    int new_btn_select_file_x = 0;
    int new_eb_current_selected_file_y = 0;

    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");

    uhashtools_btn_action_on_parent_resize(mainwin_ctx->btn_action, mainwin_new_width, mainwin_new_height);
    new_btn_action_x = uhashtools_gui_elm_get_x(mainwin_ctx->btn_action);
    new_btn_action_y = uhashtools_gui_elm_get_y(mainwin_ctx->btn_action);

    uhashtools_pb_calc_result_on_parent_resize(mainwin_ctx->pb_calc_result, mainwin_new_height, new_btn_action_x);
    uhashtools_eb_calc_result_on_parent_resize(mainwin_ctx->eb_calc_result, mainwin_new_height, new_btn_action_x);
    uhashtools_lbl_result_hash_on_parent_resize(mainwin_ctx->lbl_result_hash, mainwin_new_height);

    new_lbl_result_y = uhashtools_gui_elm_get_y(mainwin_ctx->lbl_result_hash);

    uhashtools_btn_select_file_on_parent_resize(mainwin_ctx->btn_select_file, mainwin_new_width, new_btn_action_y);

    new_btn_select_file_x = uhashtools_gui_elm_get_x(mainwin_ctx->btn_select_file);

    uhashtools_lbl_selected_file_on_parent_resize(mainwin_ctx->lbl_selected_file, new_lbl_result_y);
    uhashtools_eb_current_selected_file_on_parent_resize(mainwin_ctx->eb_current_selected_file, new_lbl_result_y, new_btn_select_file_x);

    new_eb_current_selected_file_y = uhashtools_gui_elm_get_y(mainwin_ctx->eb_current_selected_file);

    uhashtools_lbl_filedrop_on_parent_resize(mainwin_ctx->lbl_filedrop, mainwin_new_width, new_eb_current_selected_file_y);
}

static
void
uhashtools_handle_file_selection
(
    struct MainWindowCtx* mainwin_ctx
)
{
    (void) wprintf_s(L"[INFO] Handling file selection of file: %s\n", mainwin_ctx->target_file);
    (void) fflush(stdout);

    uhashtools_mainwin_change_state(mainwin_ctx, MAINWINDOWSTATE_WORKING);
    mainwin_ctx->worker_instance_data = uhashtools_hash_calculation_worker_start(&mainwin_ctx->worker_thread_param_buf,
                                                                              &mainwin_ctx->event_message_buf,
                                                                              mainwin_ctx->event_message_buf_is_writeable_event,
                                                                              mainwin_ctx->own_window_handle,
                                                                              mainwin_ctx->target_file);
    
    if (!mainwin_ctx->worker_instance_data.created_sucessfully)
    {
        (void) wprintf_s(L"[ERROR] Failed to create hash calculation worker thread!\n");
        (void) fflush(stdout);

        (void) wcscpy_s(mainwin_ctx->error_txt, GENERIC_TXT_MESSAGES_BUFFER_TSIZE, L"Internal error: Failed to create hash calculation worker thread!");
        uhashtools_mainwin_change_state(mainwin_ctx, MAINWINDOWSTATE_FINISHED_ERROR);
        
        return;
    }
    
    (void) wprintf_s(L"[DEBUG] Sucessfully created hash calculation worker thread with the thread id \"%lu\"\n", mainwin_ctx->worker_instance_data.thread_id);
    (void) fflush(stdout);
}

static
void
uhashtools_on_cancel_requested
(
    struct MainWindowCtx* mainwin_ctx
)
{
    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");
    
    uhashtools_hash_calculation_worker_request_cancelation(mainwin_ctx->worker_instance_data.thread_id);
}

static
void
uhashtools_on_copy_to_clipboard_requested
(
    struct MainWindowCtx* mainwin_ctx
)
{
    size_t hash_result_strlen = 0;
    
    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");
    
    hash_result_strlen = wcsnlen_s(mainwin_ctx->hash_result, HASH_RESULT_BUFFER_TSIZE);
    
    if (hash_result_strlen == HASH_RESULT_BUFFER_TSIZE)
    {
        return;
    }
    
    uhashtools_clipboard_utils_set_clipboard_text(mainwin_ctx->hash_result, hash_result_strlen);
}

static
void
uhashtools_on_retry_requested
(
    struct MainWindowCtx* mainwin_ctx
)
{
    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error: Entered with mainwin_ctx == NULL!");
    
    uhashtools_handle_file_selection(mainwin_ctx);
}

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
    if(uMsg == WM_CREATE)
    {
        struct MainWindowCtx* mainwin_ctx = NULL;
        CREATESTRUCTW* create_params = (CREATESTRUCTW*) lParam;

        uhashtools_set_message_boxes_owner(hwnd);

        if(create_params == NULL || create_params->lpCreateParams == NULL)
        {
            (void) wprintf_s(L"Main window: WM_CREATE failed! 'create_params' or 'create_params->lpCreateParams' were NULL!\n");
            (void) fflush(stdout);

            return -1;
        }

        mainwin_ctx = (struct MainWindowCtx*) create_params->lpCreateParams;
        mainwin_ctx->own_window_handle = hwnd;

        SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR) mainwin_ctx);

#if _WIN32_WINNT >= 0x0601
        ChangeWindowMessageFilterEx(hwnd, WM_DROPFILES, MSGFLT_ALLOW, NULL);
        ChangeWindowMessageFilterEx(hwnd, WM_COPYDATA, MSGFLT_ALLOW, NULL);
        ChangeWindowMessageFilterEx(hwnd, WM_COPYGLOBALDATA, MSGFLT_ALLOW, NULL);
#endif

        uhashtools_mainwin_init_ui_controls(mainwin_ctx);

        return 0;
    }
    else if(uMsg == WM_CLOSE)
    {
        struct MainWindowCtx* main_window_state = (struct MainWindowCtx*) GetWindowLongPtrW(hwnd, GWLP_USERDATA);

        if(main_window_state != NULL)
        {
            uhashtools_set_message_boxes_owner(NULL);

            DestroyWindow(hwnd);
            main_window_state->own_window_handle = NULL;
        }

        return 0;
    }
    else if(uMsg == WM_DESTROY)
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
    else if(uMsg == WM_SIZE)
    {
        struct MainWindowCtx* mainwin_ctx = (struct MainWindowCtx*) GetWindowLongPtrW(hwnd, GWLP_USERDATA);

        if(mainwin_ctx != NULL)
        {
            UINT new_width = LOWORD(lParam);
            UINT new_height = HIWORD(lParam);

            uhashtools_mainwin_resize_child_elements(mainwin_ctx, new_width, new_height);
        }

        return 0;
    }
    else if(uMsg == WM_CTLCOLORSTATIC || uMsg == WM_CTLCOLOREDIT)
    {
        return uhashtools_eb_lbl_handle_WM_CTLCOLOR_msg(wParam);
    }
    else if(uMsg == WM_DROPFILES)
    {
        struct MainWindowCtx* mainwin_ctx = (struct MainWindowCtx*) GetWindowLongPtrW(hwnd, GWLP_USERDATA);

        if(mainwin_ctx != NULL)
        {
            HDROP dropped_files_event_handle = (HDROP) wParam;
            UINT dropped_files_count = 0;
            
            dropped_files_count = DragQueryFileW(dropped_files_event_handle, 0xFFFFFFFF, NULL, 0);

            if (dropped_files_count >= 1)
            {
                wchar_t* ctx_target_file = mainwin_ctx->target_file;
                UINT get_drag_file_succeded = 0;

                if (dropped_files_count > 1)
                {
                    (void) wprintf_s(L"[WARNING] The received \"WM_DROPFILES\" event contains multiple files! We're taking the first and ignoring the rest...\n");
                    (void) fflush(stdout);
                }

                get_drag_file_succeded = DragQueryFileW(dropped_files_event_handle, 0, ctx_target_file, FILEPATH_BUFFER_TSIZE);

                if(get_drag_file_succeded)
                {
                    uhashtools_handle_file_selection(mainwin_ctx);
                }
                else
                {
                    (void) wprintf_s(L"[WARNING] Failed to get the files from the \"WM_DROPFILES\" event! Ignoring the event...\n");
                    (void) fflush(stdout);
                }
            }
        }
        else
        {
            (void) wprintf_s(L"[WARNING] Received \"WM_DROPFILES\" event but getting our window state failed! Ignoring event...\n");
            (void) fflush(stdout);
        }

        return 0;
    }
    else if(uMsg == WM_COMMAND)
    {
        struct MainWindowCtx* mainwin_ctx = (struct MainWindowCtx*) GetWindowLongPtrW(hwnd, GWLP_USERDATA);

        if((HWND) lParam == mainwin_ctx->btn_select_file)
        {
            WORD control_notification = HIWORD(wParam);

            if(control_notification == BN_CLICKED)
            {
                BOOL user_selected_a_file = uhashtools_select_file_dialog_open(mainwin_ctx->own_window_handle,
                                                                            mainwin_ctx->select_file_dlg_buf,
                                                                            FILEPATH_BUFFER_TSIZE);
                
                if (user_selected_a_file)
                {
                    (void) wcscpy_s(mainwin_ctx->target_file, FILEPATH_BUFFER_TSIZE, mainwin_ctx->select_file_dlg_buf);
                    
                    uhashtools_handle_file_selection(mainwin_ctx);
                }

                return 0;
            }
        }
        else if ((HWND) lParam == mainwin_ctx->btn_action)
        {
            WORD control_notification = HIWORD(wParam);

            if(control_notification == BN_CLICKED)
            {
                if (mainwin_ctx->own_state == MAINWINDOWSTATE_WORKING_CANCELABLE)
                {
                    uhashtools_on_cancel_requested(mainwin_ctx);
                }
                else if (mainwin_ctx->own_state == MAINWINDOWSTATE_CANCELED || mainwin_ctx->own_state == MAINWINDOWSTATE_FINISHED_ERROR)
                {
                    uhashtools_on_retry_requested(mainwin_ctx);
                }
                else if (mainwin_ctx->own_state == MAINWINDOWSTATE_FINISHED_SUCCESS)
                {
                    uhashtools_on_copy_to_clipboard_requested(mainwin_ctx);
                }
                
                return 0;
            }
        }
    }
    else if(uMsg == WM_USER)
    {
        struct MainWindowCtx* mainwin_ctx = NULL;
        struct HashCalculationWorkerEventMessage event_message_buf_clone;
        BOOL signal_event_success = FALSE;
        
        mainwin_ctx = (struct MainWindowCtx*) GetWindowLongPtrW(hwnd, GWLP_USERDATA);
        event_message_buf_clone = mainwin_ctx->event_message_buf;
        
        signal_event_success = SetEvent(mainwin_ctx->event_message_buf_is_writeable_event);
        UHASHTOOLS_ASSERT(signal_event_success, L"Failed reset the event synchronization object back into the signaled state!");

        if (event_message_buf_clone.event_type == HCWET_MESSAGE_RECEIVER_INITIALIZED)
        {
            uhashtools_mainwin_change_state(mainwin_ctx, MAINWINDOWSTATE_WORKING_CANCELABLE);
        }
        else if (event_message_buf_clone.event_type == HCWET_CALCULATION_PROGRESS_CHANGED)
        {
            uhashtools_handle_calculation_progress_change(mainwin_ctx,
                                                       event_message_buf_clone.event_data.progress_changed_data.current_progress_in_percent);
        }
        else if (event_message_buf_clone.event_type == HCWET_CALCULATION_COMPLETE)
        {
            (void) wcscpy_s(mainwin_ctx->hash_result,
                            HASH_RESULT_BUFFER_TSIZE,
                            event_message_buf_clone.event_data.opperation_finished_data.calculated_hash);

            uhashtools_mainwin_change_state(mainwin_ctx, MAINWINDOWSTATE_FINISHED_SUCCESS);
        }
        else if (event_message_buf_clone.event_type == HCWET_CALCULATION_FAILED)
        {
            (void) wcscpy_s(mainwin_ctx->error_txt,
                            GENERIC_TXT_MESSAGES_BUFFER_TSIZE,
                            event_message_buf_clone.event_data.opperation_failed_data.user_error_message);
            
            uhashtools_mainwin_change_state(mainwin_ctx, MAINWINDOWSTATE_FINISHED_ERROR);
        }
        else if (event_message_buf_clone.event_type == HCWET_CALCULATION_CANCELED)
        {
            uhashtools_mainwin_change_state(mainwin_ctx, MAINWINDOWSTATE_CANCELED);
        }
        else
        {
            UHASHTOOLS_FATAL_ERROR(L"Received event message with unexpected type!");
        }
        
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
    wc.lpszClassName = uhashes_product_get_mainwin_classname();
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
    struct MainWindowCtx* main_window_state
)
{
    HWND main_window_handle = NULL;

    main_window_state->app_instance_handle = hInstance;

    main_window_handle = CreateWindowExW(MAINWIN_STYLE_EX,
                                         uhashes_product_get_mainwin_classname(),
                                         uhashes_product_get_mainwin_title(),
                                         MAINWIN_STYLE,
                                         CW_USEDEFAULT,
                                         CW_USEDEFAULT,
                                         uhashes_product_get_recommended_mainwin_width(),
                                         MAINWIN_HIGHT_MIN,
                                         NULL,
                                         NULL,
                                         hInstance,
                                         (LPVOID) main_window_state);

    main_window_state->own_window_handle = main_window_handle;

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

            (void) wprintf_s(L"[DEBUG] Exiting main loop normaly with return code '%i'...\n", gui_rc);
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

    (void) wprintf_s(L"[DEBUG] Registering main window class...\n");
    (void) fflush(stdout);
    mainWinClassAtom = uhashtools_register_main_window_class(hInstance);
    UHASHTOOLS_ASSERT(mainWinClassAtom, L"Failed to register the main window class!");

    (void) wprintf_s(L"[DEBUG] Creating the event message synchronization object...\n");
    (void) fflush(stdout);
    mainwin_ctx->event_message_buf_is_writeable_event = CreateEventExW(NULL,
                                                                       NULL,
                                                                       CREATE_EVENT_INITIAL_SET,
                                                                       DELETE | SYNCHRONIZE | EVENT_MODIFY_STATE);
    UHASHTOOLS_ASSERT(mainwin_ctx->event_message_buf_is_writeable_event, L"Failed to create the event message synchronization object!");

    (void) wprintf_s(L"[DEBUG] Creating main window...\n");
    (void) fflush(stdout);
    UHASHTOOLS_ASSERT(uhashtools_create_main_window(hInstance, mainwin_ctx), L"Failed to create the main window!");

    (void) wprintf_s(L"[DEBUG] Making the main window visible...\n");
    (void) fflush(stdout);
    uhashtools_show_main_window(mainwin_ctx->own_window_handle, nCmdShow);

    (void) wprintf_s(L"[DEBUG] Entering main message loop...\n");
    (void) fflush(stdout);
    uhashtools_enter_main_message_loop();

    if(mainwin_ctx->own_window_handle != NULL)
    {
        DestroyWindow(mainwin_ctx->own_window_handle);
        mainwin_ctx->own_window_handle = NULL;
    }

    if(mainWinClassAtom != 0)
    {
        UnregisterClassW(uhashes_product_get_mainwin_classname(),
                         hInstance);
    }

    return !isErr;
}