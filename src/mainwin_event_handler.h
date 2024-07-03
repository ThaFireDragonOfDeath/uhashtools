/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <Windows.h>

struct HashCalculationWorkerEventMessage;
struct MainWindowCtx;

extern
void
uhashtools_mainwin_on_cancel_button_pressed
(
    struct MainWindowCtx* mainwin_ctx
);

extern
void
uhashtools_mainwin_on_retry_button_pressed
(
    struct MainWindowCtx* mainwin_ctx
);

extern
void
uhashtools_mainwin_on_copy_to_clipboard_button_pressed
(
    struct MainWindowCtx* mainwin_ctx
);

extern
void
uhashtools_mainwin_on_select_file_button_pressed
(
    struct MainWindowCtx* mainwin_ctx
);

extern
void
uhashtools_mainwin_on_taskbar_button_created
(
    struct MainWindowCtx* mainwin_ctx
);

extern
void
uhashtools_mainwin_on_file_dropped
(
    struct MainWindowCtx* mainwin_ctx,
    HDROP dropped_files_event_handle
);

extern
void
uhashtools_mainwin_on_hash_calculation_worker_event_message_received
(
    struct MainWindowCtx* mainwin_ctx,
    const struct HashCalculationWorkerEventMessage* event_message
);
