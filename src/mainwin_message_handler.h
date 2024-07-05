#pragma once

#include <Windows.h>

extern
LRESULT
uhashtools_mainwin_handle_message
(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam,
    int mainwin_min_width,
    int mainwin_min_height
);
