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
 * Start the hash calculation of the currently selected file.
 * 
 * @param mainwin_ctx Context data of the target mainwin instance.
 */
extern
void
uhashtools_mainwin_hash_selected_file
(
    struct MainWindowCtx* mainwin_ctx
);
