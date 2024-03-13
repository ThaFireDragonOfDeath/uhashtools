/*
 * µHashtools - A small graphical file hashing tool for Microsoft Windows
 * Copyright (C) 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * 
 * This file is part of µHashtools.
 * 
 * µHashtools is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 * 
 * µHashtools is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * µHashtools. If not, see <https://www.gnu.org/licenses/>.
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwin_lbl_selected_file.h"

#include <Windows.h>

#include "errorutils.h"
#include "gui_lbl_common.h"
#include "gui_common.h"

const wchar_t* LBL_SELECTED_FILE_TXT = L"Selected file:";
const DWORD LBL_SELECTED_FILE_STYLE = WS_CHILD | WS_VISIBLE | SS_SIMPLE;
const DWORD LBL_SELECTED_FILE_STYLE_EX = 0;
const int LBL_SELECTED_FILE_X = DEFAULT_DISTANCE;
const int LBL_SELECTED_FILE_WIDTH = MW_FC_LBL_WIDTH;
const int LBL_SELECTED_FILE_HIGHT = LBL_DEFAULT_HIGHT;

static int dyn_LBL_SELECTED_FILE_Y(int bottom_anker_element_y)
{
    return bottom_anker_element_y - LBL_SELECTED_FILE_HIGHT - DEFAULT_DISTANCE - LBL_EXTRA_Y_DISTANCE_TO_OTHER_LBL;
}

HWND
uhashtools_lbl_selected_file_create
(
    HINSTANCE app_instance,
    HWND parent_window,
    int bottom_anker_y
)
{
    HWND ret = NULL;
    int current_y = 0;

    current_y = dyn_LBL_SELECTED_FILE_Y(bottom_anker_y);

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
    int bottom_anker_y
)
{
    int current_y = dyn_LBL_SELECTED_FILE_Y(bottom_anker_y);

    uhashtools_gui_elm_move(self, LBL_SELECTED_FILE_X, current_y);
}
