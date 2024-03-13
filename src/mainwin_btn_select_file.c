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

#include "mainwin_btn_select_file.h"

#include <Windows.h>

#include "errorutils.h"
#include "gui_btn_common.h"
#include "gui_common.h"


/* Static GUI element properties */

const DWORD BTN_SELECT_FILE_STYLE = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON;
const DWORD BTN_SELECT_FILE_STYLE_EX = 0;
const int BTN_SELECT_FILE_WIDTH = PB_EB_DEFAULT_HIGHT;
const int BTN_SELECT_FILE_HIGHT = PB_EB_DEFAULT_HIGHT;

/* Dynamic GUI element properties */

static
BOOL
dyn_BTN_SELECT_FILE_IS_ENABLED
(
    enum MainWindowState mainwin_state
)
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

static
int
dyn_BTN_SELECT_FILE_X
(
    int main_win_width
)
{
    return main_win_width - DEFAULT_DISTANCE - BTN_SELECT_FILE_WIDTH;
}

static
int
dyn_BTN_SELECT_FILE_Y
(
    int bottom_anker_y
)
{
    return bottom_anker_y - DEFAULT_DISTANCE - BTN_SELECT_FILE_HIGHT;
}

static
HICON
dyn_BTN_SELECT_FILE_ICON(void)
{
    HICON ret = NULL;

    ExtractIconExW(L"%SystemRoot%\\System32\\shell32.dll", 55, NULL, &ret, 1);
    UHASHTOOLS_ASSERT(ret, L"Extracted Shell32 icon is NULL!");

    return ret;
}

/* API functions */

HWND
uhashtools_btn_select_file_create
(
    HINSTANCE app_instance,
    HWND parant_window,
    int bottom_anker_y
)
{
    HWND ret = NULL;
    int current_x = 0;
    int current_y = 0;
    HICON current_icon = NULL;

    current_x = dyn_BTN_SELECT_FILE_X(uhashtools_gui_elm_get_width(parant_window));
    current_y = dyn_BTN_SELECT_FILE_Y(bottom_anker_y);
    current_icon = dyn_BTN_SELECT_FILE_ICON();

    ret = uhashtools_btn_create(app_instance,
                             parant_window,
                             BTN_SELECT_FILE_STYLE,
                             BTN_SELECT_FILE_STYLE_EX,
                             current_x,
                             current_y,
                             BTN_SELECT_FILE_WIDTH,
                             BTN_SELECT_FILE_HIGHT,
                             current_icon);

    return ret;
}

void
uhashtools_btn_select_file_on_parent_resize
(
    HWND self,
    int parent_width,
    int bottom_anker_y
)
{
    int current_x = 0;
    int current_y = 0;

    current_x = dyn_BTN_SELECT_FILE_X(parent_width);
    current_y = dyn_BTN_SELECT_FILE_Y(bottom_anker_y);

    uhashtools_gui_elm_move(self, current_x, current_y);
}

void
uhashtools_btn_select_file_on_state_changed
(
    HWND self,
    enum MainWindowState mainwin_state
)
{
    BOOL is_enabled = FALSE;
    
    is_enabled = dyn_BTN_SELECT_FILE_IS_ENABLED(mainwin_state);
    
    uhashtools_gui_elm_set_enabled(self, is_enabled);
}
