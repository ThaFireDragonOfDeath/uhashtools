/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

enum MainWindowState
{
    MAINWINDOWSTATE_INIT,
    MAINWINDOWSTATE_WORKING,
    MAINWINDOWSTATE_WORKING_CANCELABLE,
    MAINWINDOWSTATE_CANCELED,
    MAINWINDOWSTATE_FINISHED_SUCCESS,
    MAINWINDOWSTATE_FINISHED_ERROR,
    MAINWINDOWSTATE_FINISHED_ERROR_MSGBOX_CONFIRMED
};
