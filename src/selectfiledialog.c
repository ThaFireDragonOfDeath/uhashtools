/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "selectfiledialog.h"

#include "errorutils.h"

#include <Windows.h>

#include <string.h>

const wchar_t SELECT_FILE_DIALOG_TITLE[] = L"Select file";
const DWORD SELECT_FILE_DIALOG_FLAGS = OFN_ENABLESIZING | OFN_DONTADDTORECENT | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_LONGNAMES | OFN_PATHMUSTEXIST;

BOOL
uhashtools_select_file_dialog_open
(
    HWND dialog_owner_win,
    wchar_t* target_file_buf,
    size_t target_file_buf_tsize
)
{
    OPENFILENAMEW open_file_dlg_settings;
    BOOL open_file_dialog_result = FALSE;
    
    /*
     * The input parameter 'target_file_buf_tsize' comes from a
     * predefined value (see define of 'MW_TARGET_FILE_TBUFSIZE' in
     * mainwin.h and the call of this function in mainwin.c).
     * So no overflow check is necessary here. 
     */
    DWORD nMaxFile = (DWORD) target_file_buf_tsize;

    UHASHTOOLS_ASSERT(dialog_owner_win != INVALID_HANDLE_VALUE, L"Entered with an invalid dialog owner handle!");
    UHASHTOOLS_ASSERT(target_file_buf, L"Entered with target_file_buf == NULL!");

    (void) memset((void*) &open_file_dlg_settings, 0, sizeof open_file_dlg_settings);

    open_file_dlg_settings.lStructSize = sizeof open_file_dlg_settings;
    open_file_dlg_settings.hwndOwner = dialog_owner_win;
    open_file_dlg_settings.hInstance = NULL;
    open_file_dlg_settings.lpstrFilter = NULL;
    open_file_dlg_settings.lpstrCustomFilter = NULL;
    open_file_dlg_settings.nMaxCustFilter = 0;
    open_file_dlg_settings.nFilterIndex = 0;
    open_file_dlg_settings.lpstrFile = target_file_buf;
    open_file_dlg_settings.nMaxFile = nMaxFile;
    open_file_dlg_settings.lpstrFileTitle = NULL;
    open_file_dlg_settings.nMaxFileTitle = 0;
    open_file_dlg_settings.lpstrInitialDir = NULL;
    open_file_dlg_settings.lpstrTitle = SELECT_FILE_DIALOG_TITLE;
    open_file_dlg_settings.Flags = SELECT_FILE_DIALOG_FLAGS;
    open_file_dlg_settings.nFileOffset = 0;
    open_file_dlg_settings.nFileExtension = 0;
    open_file_dlg_settings.lpstrDefExt = NULL;
    open_file_dlg_settings.lCustData = 0;
    open_file_dlg_settings.lpfnHook = NULL;
    open_file_dlg_settings.lpTemplateName = NULL;

    open_file_dialog_result = GetOpenFileNameW(&open_file_dlg_settings);

    return open_file_dialog_result;
}
