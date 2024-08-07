/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwin_lbl_file_drop.h"

#include "buffer_sizes.h"
#include "error_utilities.h"
#include "gui_lbl_common.h"
#include "gui_common.h"
#include "mainwin_state.h"

#include <wchar.h>
#include <Windows.h>

const wchar_t LBL_FILE_DROP_TXT[] = L"File drop zone";
const DWORD LBL_FILE_DROP_STYLE = WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE;
const DWORD LBL_FILE_DROP_STYLE_EX = WS_EX_ACCEPTFILES;
const int LBL_FILE_DROP_X = DEFAULT_DISTANCE;
const int LBL_FILE_DROP_Y = DEFAULT_DISTANCE;

static int dyn_LBL_FILE_DROP_WIDTH(int parent_width)
{
    return parent_width - LBL_FILE_DROP_X - DEFAULT_DISTANCE;
}

static int dyn_LBL_FILE_DROP_HIGHT(int bottom_anchor_element_y)
{
    return bottom_anchor_element_y - LBL_FILE_DROP_Y - DEFAULT_DISTANCE - LBL_EXTRA_Y_DISTANCE_TO_OTHER_EB;
}

static BOOL dyn_LBL_FILE_DROP_IS_ENABLED(enum MainWindowState mainwin_state)
{
    UHASHTOOLS_ASSERT(mainwin_state >= MAINWINDOWSTATE_INIT && mainwin_state <= MAINWINDOWSTATE_FINISHED_ERROR_MSGBOX_CONFIRMED,
                      L"Internal error: MainWindow state is invalid!");
    
    switch(mainwin_state)
    {
        case MAINWINDOWSTATE_INIT:
        case MAINWINDOWSTATE_CANCELED:
        case MAINWINDOWSTATE_FINISHED_SUCCESS:
        case MAINWINDOWSTATE_FINISHED_ERROR:
        case MAINWINDOWSTATE_FINISHED_ERROR_MSGBOX_CONFIRMED:
        {
            return TRUE;
        }
        default:
        {
            return FALSE;
        }
    }
}

static
LRESULT
CALLBACK uhashtools_lbl_file_drop_winproc
(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    if (uMsg == WM_DROPFILES)
    {
        HWND main_win_handle = GetParent(hwnd);

        PostMessageW(main_win_handle, uMsg, wParam, lParam);
        return 0;
    }
    else
    {
        WNDPROC default_win_proc = (WNDPROC) GetWindowLongPtr(hwnd, GWLP_USERDATA);
        return CallWindowProcW(default_win_proc, hwnd, uMsg, wParam, lParam);
    }
}

HWND
uhashtools_lbl_file_drop_create
(
    HINSTANCE app_instance,
    HWND parent_window,
    enum MainWindowState mainwin_state,
    int parent_width,
    int bottom_anchor_y
)
{
    HWND ret = NULL;
    int current_width = 0;
    int current_hight = 0;
    LONG_PTR default_win_proc = 0;

    UHASHTOOLS_ASSERT(mainwin_state >= MAINWINDOWSTATE_INIT && mainwin_state <= MAINWINDOWSTATE_FINISHED_SUCCESS,
                      L"Internal error: Entered with unexpected main window state in uhashtools_lbl_file_drop_create()!");

    current_width = dyn_LBL_FILE_DROP_WIDTH(parent_width);
    current_hight = dyn_LBL_FILE_DROP_HIGHT(bottom_anchor_y);

    ret = uhashtools_lbl_create(app_instance,
                                parent_window,
                                LBL_FILE_DROP_STYLE,
                                LBL_FILE_DROP_STYLE_EX,
                                LBL_FILE_DROP_X,
                                LBL_FILE_DROP_Y,
                                current_width,
                                current_hight,
                                LBL_FILE_DROP_TXT);

    default_win_proc = GetWindowLongPtr(ret, GWLP_WNDPROC);
    SetWindowLongPtr(ret, GWLP_USERDATA, default_win_proc);

#if _WIN32_WINNT >= 0x0601
    ChangeWindowMessageFilterEx(ret, WM_DROPFILES, MSGFLT_ALLOW, NULL);
    ChangeWindowMessageFilterEx(ret, WM_COPYDATA, MSGFLT_ALLOW, NULL);
    ChangeWindowMessageFilterEx(ret, WM_COPYGLOBALDATA, MSGFLT_ALLOW, NULL);
#endif

    SetWindowLongPtr(ret, GWLP_WNDPROC, (LONG_PTR) uhashtools_lbl_file_drop_winproc);
    
    return ret;
}

void
uhashtools_lbl_file_drop_on_parent_resize
(
    HWND self,
    int parent_width,
    int bottom_anchor_y
)
{
    int current_width = 0;
    int current_hight = 0;

    current_width = dyn_LBL_FILE_DROP_WIDTH(parent_width);
    current_hight = dyn_LBL_FILE_DROP_HIGHT(bottom_anchor_y);

    uhashtools_gui_elm_resize(self, current_width, current_hight);
}

void
uhashtools_lbl_file_drop_on_state_changed
(
    HWND self,
    enum MainWindowState mainwin_state
)
{
    BOOL current_is_enabled = FALSE;
    
    current_is_enabled = dyn_LBL_FILE_DROP_IS_ENABLED(mainwin_state);
    
    uhashtools_gui_elm_set_enabled(self, current_is_enabled);
}
