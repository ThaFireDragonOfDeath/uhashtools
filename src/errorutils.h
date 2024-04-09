/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <Windows.h>

#define UHASHTOOLS_STRINGIFY_LITERAL(literal) L###literal
#define UHASHTOOLS_STRINGIFY_MACRO(macro) UHASHTOOLS_STRINGIFY_LITERAL(macro)

#define UHASHTOOLS_WIDEIFY_TXT_LITERAL(literal) L##literal
#define UHASHTOOLS_WIDEIFY_TXT_MACRO(macro) UHASHTOOLS_WIDEIFY_TXT_LITERAL(macro)

#define UHASHTOOLS_ASSERT(cond_expr, static_err_msg) { if(!(cond_expr)) { uhashtools_handle_fatal_error(UHASHTOOLS_WIDEIFY_TXT_MACRO(__FILE__) L": Line " UHASHTOOLS_STRINGIFY_MACRO(__LINE__), static_err_msg); } }
#define UHASHTOOLS_FATAL_ERROR(static_err_msg) { uhashtools_handle_fatal_error(UHASHTOOLS_WIDEIFY_TXT_MACRO(__FILE__) L": Line " UHASHTOOLS_STRINGIFY_MACRO(__LINE__), static_err_msg); }
extern
void
uhashtools_set_message_boxes_owner
(
    HWND new_message_boxes_owner
);

extern
void
uhashtools_show_error_msg
(
    const wchar_t* error_title,
    const wchar_t* error_txt
);

__declspec(noreturn)
extern
void
uhashtools_handle_fatal_error
(
    const wchar_t* error_title,
    const wchar_t* error_txt
);