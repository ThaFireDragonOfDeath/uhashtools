/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "taskbarlist_com_api.h"

/**
 * Current state of the taskbar icon progress bar UI element.
 * It saves, what is currently shown to avoid unnecessary calls
 * of COM object functions.
 */
struct TaskbarIconProgressBarCtx
{
    enum ProgressViewMode current_progress_view_mode;
    unsigned int current_progress_in_percent;
};