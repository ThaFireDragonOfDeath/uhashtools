/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwin_btn_action.h"

#include <Windows.h>

#include "errorutils.h"
#include "gui_btn_common.h"
#include "gui_common.h"
#include "mainwin_state_enum.h"

const DWORD BTN_ACTION_STYLE = WS_CHILD | WS_VISIBLE | WS_DISABLED | BS_PUSHBUTTON | BS_ICON;
const DWORD BTN_ACTION_STYLE_EX = 0;
static int BTN_ACTION_WIDTH = PB_EB_DEFAULT_HIGHT;
static int BTN_ACTION_HIGHT = PB_EB_DEFAULT_HIGHT;
static int dyn_BTN_ACTION_X(int main_win_width) {return main_win_width - DEFAULT_DISTANCE - BTN_ACTION_WIDTH;}
static int dyn_BTN_ACTION_Y(int main_win_hight) {return main_win_hight - DEFAULT_DISTANCE - BTN_ACTION_HIGHT;}
static HICON dyn_BTN_ACTION_ICON(enum MainWindowState state)
{
    HICON ret = NULL;

    switch(state)
    {
        case MAINWINDOWSTATE_WORKING:
        case MAINWINDOWSTATE_WORKING_CANCELABLE:
            ExtractIconExW(L"%SystemRoot%\\System32\\shell32.dll", 131, NULL, &ret, 1); /* Cancel icon */
            break;
        case MAINWINDOWSTATE_CANCELED:
        case MAINWINDOWSTATE_FINISHED_ERROR:
        case MAINWINDOWSTATE_FINISHED_ERROR_MSGBOX_CONFIRMED:
            ExtractIconExW(L"%SystemRoot%\\System32\\shell32.dll", 238, NULL, &ret, 1); /* Retry icon */
            break;
        default:
            ExtractIconExW(L"%SystemRoot%\\System32\\shell32.dll", 134, NULL, &ret, 1); /* Copy icon */
            break;
    }

    UHASHTOOLS_ASSERT(ret, L"Extracted Shel32 icon is NULL!");

    return ret;
}
static BOOL dyn_BTN_ACTION_ENABLED(enum MainWindowState state)
{
    switch (state)
    {
        case MAINWINDOWSTATE_WORKING_CANCELABLE:
        case MAINWINDOWSTATE_CANCELED:
        case MAINWINDOWSTATE_FINISHED_SUCCESS:
        case MAINWINDOWSTATE_FINISHED_ERROR:
        case MAINWINDOWSTATE_FINISHED_ERROR_MSGBOX_CONFIRMED:
            return TRUE;

        default:
            return FALSE;
    }
}

HWND
uhashtools_btn_action_create
(
    HINSTANCE app_instance,
    HWND parent_window,
    enum MainWindowState mainwin_state
)
{
    HWND ret = NULL;
    int current_x = dyn_BTN_ACTION_X(uhashtools_gui_elm_get_width(parent_window));
    int current_y = dyn_BTN_ACTION_Y(uhashtools_gui_elm_get_height(parent_window));
    HICON current_icon = dyn_BTN_ACTION_ICON(mainwin_state);

    ret = uhashtools_btn_create(app_instance,
                                parent_window,
                                BTN_ACTION_STYLE,
                                BTN_ACTION_STYLE_EX,
                                current_x,
                                current_y,
                                BTN_ACTION_WIDTH,
                                BTN_ACTION_HIGHT,
                                current_icon);

    return ret;
}

void
uhashtools_btn_action_on_parent_resize
(
    HWND self,
    int parent_width,
    int parent_height
)
{
    int current_x = 0;
    int current_y = 0;

    UHASHTOOLS_ASSERT(self != NULL, L"Internal error: Entered with NULL!");

    current_x = dyn_BTN_ACTION_X(parent_width);
    current_y = dyn_BTN_ACTION_Y(parent_height);

    uhashtools_gui_elm_move(self, current_x, current_y);
}

void
uhashtools_btn_action_on_state_changed
(
    HWND self,
    enum MainWindowState mainwin_state
)
{
    BOOL is_enabled = TRUE;
    HICON icon = NULL;

    UHASHTOOLS_ASSERT(self != NULL, L"Internal error: Entered with NULL!");

    is_enabled = dyn_BTN_ACTION_ENABLED(mainwin_state);
    icon = dyn_BTN_ACTION_ICON(mainwin_state);

    uhashtools_gui_elm_set_enabled(self, is_enabled);
    uhashtools_btn_set_icon(self, icon);
}