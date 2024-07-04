/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwin_lbl_selected_file.h"

#include "errorutils.h"
#include "gui_lbl_common.h"
#include "gui_common.h"

#include <Windows.h>

const wchar_t* LBL_SELECTED_FILE_TXT = L"Selected file:";
const DWORD LBL_SELECTED_FILE_STYLE = WS_CHILD | WS_VISIBLE | SS_SIMPLE;
const DWORD LBL_SELECTED_FILE_STYLE_EX = 0;
const int LBL_SELECTED_FILE_X = DEFAULT_DISTANCE;
const int LBL_SELECTED_FILE_WIDTH = MW_FC_LBL_WIDTH;
const int LBL_SELECTED_FILE_HIGHT = LBL_DEFAULT_HIGHT;

static int dyn_LBL_SELECTED_FILE_Y(int bottom_anchor_element_y)
{
    return bottom_anchor_element_y - LBL_SELECTED_FILE_HIGHT - DEFAULT_DISTANCE - LBL_EXTRA_Y_DISTANCE_TO_OTHER_LBL;
}

HWND
uhashtools_lbl_selected_file_create
(
    HINSTANCE app_instance,
    HWND parent_window,
    int bottom_anchor_y
)
{
    HWND ret = NULL;
    int current_y = 0;

    current_y = dyn_LBL_SELECTED_FILE_Y(bottom_anchor_y);

    ret = uhashtools_lbl_create(app_instance,
                                parent_window,
                                LBL_SELECTED_FILE_STYLE,
                                LBL_SELECTED_FILE_STYLE_EX,
                                LBL_SELECTED_FILE_X,
                                current_y,
                                LBL_SELECTED_FILE_WIDTH,
                                LBL_SELECTED_FILE_HIGHT,
                                LBL_SELECTED_FILE_TXT);
    
    return ret;
}

void
uhashtools_lbl_selected_file_on_parent_resize
(
    HWND self,
    int bottom_anchor_y
)
{
    int current_y = dyn_LBL_SELECTED_FILE_Y(bottom_anchor_y);

    uhashtools_gui_elm_move(self, LBL_SELECTED_FILE_X, current_y);
}
