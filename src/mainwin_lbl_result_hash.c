/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwin_lbl_result_hash.h"

#include "gui_common.h"
#include "gui_lbl_common.h"
#include "mainwin_state.h"


/* Static GUI element properties */

const wchar_t LBL_RESULT_HASH_TXT[] = L"Result:   ";
const wchar_t LBL_RESULT_HASH_TXT_ON_WORKING[] = L"Progress:";
const DWORD LBL_RESULT_HASH_STYLE = WS_CHILD | WS_VISIBLE | SS_SIMPLE;
const DWORD LBL_RESULT_HASH_STYLE_EX = 0;
const int LBL_RESULT_HASH_WIDTH = MW_FC_LBL_WIDTH;
const int LBL_RESULT_HASH_HIGHT = LBL_DEFAULT_HIGHT;
const int LBL_RESULT_HASH_X = DEFAULT_DISTANCE;

/* Dynamic GUI element properties */

static const wchar_t* dyn_LBL_RESULT_HASH_TXT(enum MainWindowState mainwin_state)
{
    switch(mainwin_state)
    {
        case MAINWINDOWSTATE_WORKING:
        case MAINWINDOWSTATE_WORKING_CANCELABLE:
            return LBL_RESULT_HASH_TXT_ON_WORKING;
        default:
            return LBL_RESULT_HASH_TXT;
    }
}

static int dyn_LBL_RESULT_HASH_Y(int parent_height)
{
    return parent_height - DEFAULT_DISTANCE - LBL_RESULT_HASH_HIGHT - 2;
}

/* API functions */

HWND
uhashtools_lbl_result_hash_create
(
    HINSTANCE app_instance,
    HWND parent_window,
    enum MainWindowState mainwin_state
)
{
    HWND ret = NULL;
    int current_y = 0;
    const wchar_t* current_txt;

    current_y = dyn_LBL_RESULT_HASH_Y(uhashtools_gui_elm_get_height(parent_window));
    current_txt = dyn_LBL_RESULT_HASH_TXT(mainwin_state);

    ret = uhashtools_lbl_create(app_instance,
                             parent_window,
                             LBL_RESULT_HASH_STYLE,
                             LBL_RESULT_HASH_STYLE_EX,
                             LBL_RESULT_HASH_X,
                             current_y,
                             LBL_RESULT_HASH_WIDTH,
                             LBL_RESULT_HASH_HIGHT,
                             current_txt);
    
    return ret;
}

void
uhashtools_lbl_result_hash_on_parent_resize
(
    HWND self,
    int parent_height
)
{
    int current_y = dyn_LBL_RESULT_HASH_Y(parent_height);

    uhashtools_gui_elm_move(self, LBL_RESULT_HASH_X, current_y);
}

void
uhashtools_lbl_result_hash_on_state_changed
(
    HWND self,
    enum MainWindowState mainwin_state
)
{
    const wchar_t* current_txt;

    current_txt = dyn_LBL_RESULT_HASH_TXT(mainwin_state);

    uhashtools_lbl_change_text(self, current_txt);
}
