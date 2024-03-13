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

#include "gui_common.h"

#include <Windows.h>

#include "errorutils.h"

static
RECT
uhashtools_gui_elm_get_win_rect
(
    HWND elm_handle
)
{
    RECT win_rect;

    UHASHTOOLS_ASSERT(elm_handle, L"Internal error: Given element handle is NULL!");
    UHASHTOOLS_ASSERT(GetWindowRect(elm_handle, &win_rect), L"Internal error: Failed to get window rectangle!");

    return win_rect;
}

static
RECT
uhashtools_gui_elm_get_win_rect_relative_to_parent
(
    HWND elm_handle
)
{
    HWND parant_win = NULL;
    RECT abs_win_rect;
    RECT rel_win_rect;
    int mapping_return_code = 0;

    parant_win = GetParent(elm_handle);
    abs_win_rect = uhashtools_gui_elm_get_win_rect(elm_handle);
    rel_win_rect = abs_win_rect;

    mapping_return_code = MapWindowPoints(HWND_DESKTOP, parant_win, (LPPOINT) &rel_win_rect, 2);

    UHASHTOOLS_ASSERT(mapping_return_code != 0, L"Internal error: MapWindowPoints() failed!");

    return rel_win_rect;
}

static
RECT
uhashtools_gui_elm_get_client_rect
(
    HWND elm_handle
)
{
    RECT client_rect;

    UHASHTOOLS_ASSERT(elm_handle, L"Internal error: Given element handle is NULL!");
    UHASHTOOLS_ASSERT(GetClientRect(elm_handle, &client_rect), L"Internal error: Failed to get client rectangle!");

    return client_rect;
}

int
uhashtools_gui_elm_get_x
(
    HWND elm_handle
)
{
    RECT win_rect = uhashtools_gui_elm_get_win_rect_relative_to_parent(elm_handle);

    return win_rect.left;
}

int
uhashtools_gui_elm_get_y
(
    HWND elm_handle
)
{
    RECT win_rect = uhashtools_gui_elm_get_win_rect_relative_to_parent(elm_handle);

    return win_rect.top;
}

int
uhashtools_gui_elm_get_width
(
    HWND elm_handle
)
{
    RECT client_rect = uhashtools_gui_elm_get_client_rect(elm_handle);

    return client_rect.right;
}

int
uhashtools_gui_elm_get_height
(
    HWND elm_handle
)
{
    RECT client_rect = uhashtools_gui_elm_get_client_rect(elm_handle);

    return client_rect.bottom;
}

void
uhashtools_gui_elm_resize
(
    HWND elm_handle,
    int new_width,
    int new_height
)
{
    SetWindowPos(elm_handle, NULL, 0, 0, new_width, new_height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOCOPYBITS);
}

void
uhashtools_gui_elm_move
(
    HWND elm_handle,
    int new_x,
    int new_y
)
{
    SetWindowPos(elm_handle, NULL, new_x, new_y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOCOPYBITS);
}

void
uhashtools_gui_elm_set_enabled
(
    HWND elm_handle,
    BOOL enabled
)
{
    (void) EnableWindow(elm_handle, enabled);
}

void
uhashtools_gui_elm_set_visible
(
    HWND elm_handle,
    BOOL visible
)
{
    if(visible == TRUE)
    {
        (void) ShowWindow(elm_handle, SW_SHOW);
    }
    else
    {
        (void) ShowWindow(elm_handle, SW_HIDE);
    }
}
