/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "mainwin_state.h"

#include <Windows.h>

struct MainWindowCtx;

/**
 * Registers the main window class.
 * This function must be called before the main window can
 * be created.
 * 
 * @param hInstance Handle of the application.
 * @param window_message_procedure Function that handles incoming window messages.
 * 
 * @return Zero on failure and a value other than zero on success.
 *         This return value will be needed when calling the
 *         function 'CreateWindowExW()'.
 */
extern
ATOM
uhashtools_mainwin_register_mainwin_class
(
    HINSTANCE hInstance,
    WNDPROC window_message_procedure
);

#if _WIN32_WINNT >= 0x0601
/**
 * By default there is no message type to signalize that the icon button
 * in the taskbar has been created.
 * This function adds this message type to the list of receivable message
 * types.
 * This function should be called during the handling of the 'WM_CREATE'
 * window message.
 * 
 * @param mainwin_handle Handle of the main window.
 * @param mainwin_handle Context data of the main window.
 * 
 * @return TRUE on success and FALSE on error.
 */
extern
BOOL
uhashtools_register_message_type_taskbar_button_created
(
    HWND mainwin_handle,
    struct MainWindowCtx* mainwin_ctx
);
#endif

/**
 * Initializes the ui elements of the main window.
 * 
 * @param mainwin_ctx Context data of the target mainwin instance.
 */
extern
void
uhashtools_mainwin_init_ui_controls
(
    struct MainWindowCtx* mainwin_ctx
);

/**
 * Resizes the child elements of the main window to fit within the
 * new size of said window.
 * 
 * @param mainwin_ctx Context data of the target mainwin instance.
 * @param mainwin_new_width New width of the main window.
 * @param mainwin_new_height New height of the main window.
 */
extern
void
uhashtools_mainwin_resize_child_elements
(
    struct MainWindowCtx* mainwin_ctx,
    UINT mainwin_new_width,
    UINT mainwin_new_height
);

/**
 * Changes the general state of the main window. See the file
 * "mainwin_state.h" for an overview of the possible general window
 * states.
 * 
 * @param mainwin_ctx Context data of the target mainwin instance.
 * @param new_mainwin_state New general state of the main window.
 */
extern
void
uhashtools_mainwin_change_state
(
    struct MainWindowCtx* mainwin_ctx,
    enum MainWindowState new_mainwin_state
);

/**
 * Changes the displayed calculation progress.
 * 
 * @param mainwin_ctx Context data of the target mainwin instance.
 * @param current_progress_in_percent Current calculation progress in
 *                                    range from 0 to 100.
 */
extern
void
uhashtools_mainwin_change_displayed_calculation_progress
(
    struct MainWindowCtx* mainwin_ctx,
    unsigned int current_progress_in_percent
);

/**
 * Copies the currently displayed hash result into the clipboard.
 * 
 * @param mainwin_ctx Context data of the target mainwin instance.
 */
extern
void
uhashtools_mainwin_copy_hash_result_to_clipboard
(
    struct MainWindowCtx* mainwin_ctx
);

/**
 * Start the hash calculation of the currently provided file.
 * 
 * @param mainwin_ctx Context data of the target mainwin instance.
 * @param target_file Filepath of the target file.
 */
extern
void
uhashtools_mainwin_hash_file
(
    struct MainWindowCtx* mainwin_ctx,
    const wchar_t* target_file
);

/**
 * Start the hash calculation of the currently selected file.
 * The selected file is the file stored in the "mainwin_ctx->target_file"
 * filepath variable.
 * 
 * @param mainwin_ctx Context data of the target mainwin instance.
 */
extern
void
uhashtools_mainwin_hash_selected_file
(
    struct MainWindowCtx* mainwin_ctx
);
