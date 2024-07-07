/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwin_eb_current_selected_file.h"

#include "buffer_sizes.h"
#include "errorutils.h"
#include "gui_eb_common.h"
#include "gui_common.h"
#include "mainwin_state.h"

#include <Windows.h>

/* Static GUI element properties */

const DWORD EB_CURRENT_SELECTED_FILE_STYLE = WS_CHILD | WS_VISIBLE | ES_LEFT | ES_READONLY;
const DWORD EB_CURRENT_SELECTED_FILE_STYLE_EX = 0;
const int EB_CURRENT_SELECTED_FILE_X = MW_FC_LBL_WIDTH + (DEFAULT_DISTANCE * 3);
const int EB_CURRENT_SELECTED_FILE_HIGHT = LBL_DEFAULT_HIGHT;

/* Dynamic GUI element properties */

static int dyn_EB_CURRENT_SELECTED_FILE_WIDTH(int right_anchor_element_x)
{
    return right_anchor_element_x - DEFAULT_DISTANCE - EB_CURRENT_SELECTED_FILE_X;
}

static int dyn_CURRENT_SELECTED_FILE_Y(int bottom_anchor_y)
{
    return bottom_anchor_y - DEFAULT_DISTANCE - EB_CURRENT_SELECTED_FILE_HIGHT - EB_EXTRA_Y_DISTANCE_TO_OTHER_EB;
}

static
wchar_t*
dyn_EB_CURRENT_SELECTED_FILE_TXT
(
    const enum MainWindowState mainwin_state,
    const wchar_t* current_target_file,
    wchar_t* txt_buf
)
{
    UHASHTOOLS_ASSERT(txt_buf, L"Entered with txt_buf == NULL!");
    
    switch (mainwin_state)
    {
        case MAINWINDOWSTATE_WORKING:
        case MAINWINDOWSTATE_WORKING_CANCELABLE:
        case MAINWINDOWSTATE_CANCELED:
        case MAINWINDOWSTATE_FINISHED_SUCCESS:
        case MAINWINDOWSTATE_FINISHED_ERROR:
        case MAINWINDOWSTATE_FINISHED_ERROR_MSGBOX_CONFIRMED:
        {
            UHASHTOOLS_ASSERT(current_target_file, L"Entered with current_target_file == NULL!");
            wcscpy_s(txt_buf, FILEPATH_BUFFER_TSIZE, current_target_file);
            return txt_buf;
        }
        case MAINWINDOWSTATE_INIT:
        default:
        {
            wcscpy_s(txt_buf, FILEPATH_BUFFER_TSIZE, L"No file selected yet.");
            return txt_buf;
        }
    }
}

/* API functions */

HWND
uhashtools_eb_current_selected_file_create
(
    HINSTANCE app_instance,
    HWND parent_window,
    const enum MainWindowState mainwin_state,
    wchar_t* current_target_file,
    wchar_t* current_selected_file_txt_buf,
    int bottom_anchor_y,
    int right_anchor_x
)
{
    HWND ret = NULL;
    int current_y = 0;
    int current_width = 0;
    wchar_t* current_txt = NULL;

    current_y = dyn_CURRENT_SELECTED_FILE_Y(bottom_anchor_y);
    current_width = dyn_EB_CURRENT_SELECTED_FILE_WIDTH(right_anchor_x);
    current_txt = dyn_EB_CURRENT_SELECTED_FILE_TXT(mainwin_state,
                                                   current_target_file,
                                                   current_selected_file_txt_buf);

    ret = uhashtools_eb_create(app_instance,
                            parent_window,
                            EB_CURRENT_SELECTED_FILE_STYLE,
                            EB_CURRENT_SELECTED_FILE_STYLE_EX,
                            EB_CURRENT_SELECTED_FILE_X,
                            current_y,
                            current_width,
                            EB_CURRENT_SELECTED_FILE_HIGHT,
                            current_txt);

    return ret;
}

void
uhashtools_eb_current_selected_file_on_parent_resize
(
    HWND self,
    int bottom_anchor_y,
    int right_anchor_x
)
{
    int current_y = 0;
    int current_width = 0;

    current_y = dyn_CURRENT_SELECTED_FILE_Y(bottom_anchor_y);
    current_width = dyn_EB_CURRENT_SELECTED_FILE_WIDTH(right_anchor_x);

    uhashtools_gui_elm_resize(self, current_width, EB_CURRENT_SELECTED_FILE_HIGHT);
    uhashtools_gui_elm_move(self, EB_CURRENT_SELECTED_FILE_X, current_y);
}

void
uhashtools_eb_current_selected_file_on_state_changed
(
    HWND self,
    const enum MainWindowState new_mainwin_state,
    const wchar_t* current_target_file,
    wchar_t* current_selected_file_txt_buf
)
{
    wchar_t* current_txt = NULL;

    UHASHTOOLS_ASSERT(self != NULL, L"Invalid param: Entered with self == NULL!");
    UHASHTOOLS_ASSERT(self != INVALID_HANDLE_VALUE,
                      L"Invalid param: Entered with self == INVALID_HANDLE_VALUE!");
    UHASHTOOLS_ASSERT(current_target_file,
                      L"Invalid param: Entered with current_target_file == NULL!");

    current_txt = dyn_EB_CURRENT_SELECTED_FILE_TXT(new_mainwin_state,
                                                   current_target_file,
                                                   current_selected_file_txt_buf);

    uhashtools_eb_set_text(self, current_txt);
}
