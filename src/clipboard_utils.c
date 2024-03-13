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

#include "clipboard_utils.h"

#include <stdio.h>

#include <Windows.h>

#include "errorutils.h"

void
uhashtools_clipboard_utils_set_clipboard_text
(
    const wchar_t* clipboard_text,
    size_t clipboard_text_strlen
)
{
    BOOL open_clipboard_rc = FALSE;
    const size_t clipboard_text_copy_required_mem_tsize = clipboard_text_strlen + 1;
    const size_t clipboard_text_copy_required_mem_bsize = clipboard_text_copy_required_mem_tsize * sizeof *clipboard_text;
    HGLOBAL clipboard_text_copy_glba_handle = NULL;
    wchar_t* clipboard_text_copy = NULL;
    
    UHASHTOOLS_ASSERT(clipboard_text, L"Internal error: Entered with clipboard_text == NULL!");
    
    open_clipboard_rc = OpenClipboard(NULL);
    
    if (!open_clipboard_rc)
    {
        (void) wprintf_s(L"[ERROR] OpenClipboard() failed!\n");
        (void) fflush(stdout);
        
        return;
    }
    
    clipboard_text_copy_glba_handle = GlobalAlloc(GMEM_ZEROINIT | GMEM_MOVEABLE, clipboard_text_copy_required_mem_bsize);
    
    if (!clipboard_text_copy_glba_handle)
    {
        (void) wprintf_s(L"[ERROR] GlobalAlloc() failed!\n");
        (void) fflush(stdout);
        
        goto cleanup_and_out;
    }
    
    clipboard_text_copy = GlobalLock(clipboard_text_copy_glba_handle);
    
    if (!clipboard_text_copy)
    {
        (void) wprintf_s(L"[ERROR] GlobalLock() failed!\n");
        (void) fflush(stdout);
        
        goto cleanup_and_out;
    }
    
    (void) wcscpy_s(clipboard_text_copy, clipboard_text_copy_required_mem_tsize, clipboard_text);
    
    (void) SetClipboardData(CF_UNICODETEXT, (HANDLE) clipboard_text_copy_glba_handle);
    
    (void) GlobalUnlock(clipboard_text_copy_glba_handle);
    clipboard_text_copy = NULL;
    clipboard_text_copy_glba_handle = NULL;
    
cleanup_and_out:
    if (clipboard_text_copy)
    {
        (void) GlobalUnlock(clipboard_text_copy_glba_handle);
        clipboard_text_copy = NULL;
    }
    
    if (clipboard_text_copy_glba_handle)
    {
        (void) GlobalFree(clipboard_text_copy_glba_handle);
    }
    
    (void) CloseClipboard();
}