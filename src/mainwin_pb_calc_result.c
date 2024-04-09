/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwin_pb_calc_result.h"

#include "gui_common.h"
#include "gui_pb_common.h"
#include "mainwin.h"

static BOOL dyn_PB_CALC_RESULT_VISIBLE(enum MainWindowState state)
{
    switch(state)
    {
        case MAINWINDOWSTATE_WORKING:
        case MAINWINDOWSTATE_WORKING_CANCELABLE: return TRUE;
        default: return FALSE;
    }
}
const DWORD PB_CALC_RESULT_STYLE = WS_CHILD;
const DWORD PB_CALC_RESULT_STYLE_EX = 0;
const int PB_CALC_RESULT_HIGHT = PB_EB_DEFAULT_HIGHT;
const int PB_CALC_RESULT_X = MW_FC_LBL_WIDTH + DEFAULT_DISTANCE * 2;
static int dyn_PB_CALC_RESULT_WIDTH(int right_anker_element_x)
{
    return right_anker_element_x - DEFAULT_DISTANCE - PB_CALC_RESULT_X;
}
static int dyn_PB_CALC_RESULT_Y(int main_win_hight)
{
    return main_win_hight - DEFAULT_DISTANCE - PB_CALC_RESULT_HIGHT;
}

HWND
uhashtools_pb_calc_result_create
(
    HINSTANCE app_instance,
    HWND parant_window,
    int right_anker_win_x
)
{
    HWND ret = NULL;
    int current_y = dyn_PB_CALC_RESULT_Y(uhashtools_gui_elm_get_height(parant_window));
    int current_width = dyn_PB_CALC_RESULT_WIDTH(right_anker_win_x);

    ret = uhashtools_pb_create(app_instance,
                            parant_window,
                            PB_CALC_RESULT_STYLE,
                            PB_CALC_RESULT_STYLE_EX,
                            PB_CALC_RESULT_X,
                            current_y,
                            current_width,
                            PB_CALC_RESULT_HIGHT);

    return ret;
}

void
uhashtools_pb_calc_result_on_parent_resize
(
    HWND self,
    UINT mainwin_new_width,
    int right_anker_win_x
)
{
    int current_width = 0;
    int current_y = 0;

    current_width = dyn_PB_CALC_RESULT_WIDTH(right_anker_win_x);
    current_y = dyn_PB_CALC_RESULT_Y(mainwin_new_width);

    uhashtools_gui_elm_resize(self, current_width, PB_CALC_RESULT_HIGHT);
    uhashtools_gui_elm_move(self, PB_CALC_RESULT_X, current_y);
}

void
uhashtools_pb_calc_result_on_state_changed
(
    HWND self,
    enum MainWindowState mainwin_state
)
{
    BOOL progressBarShouldBeVisible = dyn_PB_CALC_RESULT_VISIBLE(mainwin_state);

    uhashtools_gui_elm_set_visible(self, progressBarShouldBeVisible);
}

void
uhashtools_pb_calc_result_on_work_progress
(
    HWND self,
    unsigned int progress_in_percent
)
{
    uhashtools_pb_set_progress(self, progress_in_percent);
}