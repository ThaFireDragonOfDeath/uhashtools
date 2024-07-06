/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwin_eb_calc_result.h"

#include <wchar.h>

#include <Windows.h>

#include "buffer_sizes.h"
#include "errorutils.h"
#include "gui_common.h"
#include "gui_eb_common.h"
#include "mainwin_state.h"

const DWORD EB_CALC_RESULT_STYLE = WS_CHILD | WS_VISIBLE | ES_LEFT | ES_READONLY;
const DWORD EB_CALC_RESULT_STYLE_EX = 0;
const int EB_CALC_RESULT_HIGHT = LBL_DEFAULT_HIGHT;
const int EB_CALC_RESULT_X = MW_FC_LBL_WIDTH + (DEFAULT_DISTANCE * 3);

static BOOL dyn_EB_CALC_RESULT_IS_VISIBLE(enum MainWindowState mainwin_state)
{
    switch(mainwin_state)
    {
        case MAINWINDOWSTATE_WORKING:
        case MAINWINDOWSTATE_WORKING_CANCELABLE:
        {
            return FALSE;
        }
        default:
        {
            return TRUE;
        }
    }
}

static int dyn_EB_CALC_RESULT_WIDTH(int right_anchor_element_x)
{
    return right_anchor_element_x - DEFAULT_DISTANCE - EB_CALC_RESULT_X;
}

static int dyn_EB_CALC_RESULT_Y(int main_win_hight)
{
    return main_win_hight - DEFAULT_DISTANCE - EB_CALC_RESULT_HIGHT - 2;
}

static wchar_t* dyn_EB_CALC_RESULT_TEXT(enum MainWindowState mainwin_state, const wchar_t* current_hash_result, wchar_t* eb_calc_result_txt_buf)
{
    errno_t strcpy_rc = 0;

    UHASHTOOLS_ASSERT(eb_calc_result_txt_buf, L"Internal parameter error: Entered with eb_calc_result_txt_buf == NULL!");

    switch(mainwin_state)
    {
        case MAINWINDOWSTATE_FINISHED_SUCCESS:
        {
            UHASHTOOLS_ASSERT(current_hash_result,
                              L"Internal parameter error: Entered with current_hash_result == NULL on 'MAINWINDOWSTATE_FINISHED_SUCCESS' state!");

            strcpy_rc = wcscpy_s(eb_calc_result_txt_buf, HASH_RESULT_BUFFER_TSIZE, current_hash_result);
            UHASHTOOLS_ASSERT(strcpy_rc == 0,
                              L"Internal error: Failed to copy the current hash result into the internal buffer!");
            
            return eb_calc_result_txt_buf;
        }
        default:
        {
            strcpy_rc = wcscpy_s(eb_calc_result_txt_buf, HASH_RESULT_BUFFER_TSIZE, L"Hash not calculated yet.");
            UHASHTOOLS_ASSERT(strcpy_rc == 0,
                              L"Internal error: Failed to copy the current hash result into the internal buffer!");
            
            return eb_calc_result_txt_buf;
        }
    }
}

HWND
uhashtools_eb_calc_result_create
(
    HINSTANCE app_instance,
    HWND parent_window,
    int right_anchor_win_x,
    enum MainWindowState mainwin_state,
    const wchar_t* current_hash_result,
    wchar_t* eb_calc_result_txt_buf
)
{
    HWND ret = NULL;
    int current_y = 0;
    int current_width = 0;
    wchar_t* current_txt = NULL;
    
    current_y = dyn_EB_CALC_RESULT_Y(uhashtools_gui_elm_get_height(parent_window));
    current_width = dyn_EB_CALC_RESULT_WIDTH(right_anchor_win_x);
    current_txt = dyn_EB_CALC_RESULT_TEXT(mainwin_state, current_hash_result, eb_calc_result_txt_buf);

    ret = uhashtools_eb_create(app_instance,
                               parent_window,
                               EB_CALC_RESULT_STYLE,
                               EB_CALC_RESULT_STYLE_EX,
                               EB_CALC_RESULT_X,
                               current_y,
                               current_width,
                               EB_CALC_RESULT_HIGHT,
                               current_txt);

    return ret;
}

void
uhashtools_eb_calc_result_on_parent_resize
(
    HWND self,
    UINT mainwin_new_width,
    int right_anchor_win_x
)
{
    int current_width = 0;
    int current_y = 0;

    current_width = dyn_EB_CALC_RESULT_WIDTH(right_anchor_win_x);
    current_y = dyn_EB_CALC_RESULT_Y(mainwin_new_width);

    uhashtools_gui_elm_resize(self, current_width, EB_CALC_RESULT_HIGHT);
    uhashtools_gui_elm_move(self, EB_CALC_RESULT_X, current_y);
}

void
uhashtools_eb_calc_result_on_state_changed
(
    HWND self,
    enum MainWindowState mainwin_state,
    const wchar_t* current_hash_result,
    wchar_t* eb_calc_result_txt_buf
)
{
    BOOL is_visible = FALSE;
    wchar_t* current_txt = NULL;
    
    is_visible = dyn_EB_CALC_RESULT_IS_VISIBLE(mainwin_state);
    current_txt = dyn_EB_CALC_RESULT_TEXT(mainwin_state, current_hash_result, eb_calc_result_txt_buf);
    
    uhashtools_gui_elm_set_visible(self, is_visible);
    uhashtools_eb_set_text(self, current_txt);
}