/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <Windows.h>


/* Helper macros */

#define UHASHTOOLS_STRINGIFY_LITERAL(literal) L###literal
#define UHASHTOOLS_STRINGIFY_MACRO(macro) UHASHTOOLS_STRINGIFY_LITERAL(macro)

#define UHASHTOOLS_WIDEIFY_TXT_LITERAL(literal) L##literal
#define UHASHTOOLS_WIDEIFY_TXT_MACRO(macro) UHASHTOOLS_WIDEIFY_TXT_LITERAL(macro)


/* API macros */

/**
 * If the expression passes in the argument "cond_expr" resolves to 0 (aka. false)
 * the fatal error handler (see: uhashtools_handle_fatal_error()) will be executed.
 * The argument "error_title" of said fatal error handler will be set to the file
 * and the line from where this macro was called.
 * 
 * The text passed by the argument "static_err_msg" has to be a NULL terminated
 * wide character array.
 */
#define UHASHTOOLS_ASSERT(cond_expr, static_err_msg) { if(!(cond_expr)) { uhashtools_handle_fatal_error(UHASHTOOLS_WIDEIFY_TXT_MACRO(__FILE__) L": Line " UHASHTOOLS_STRINGIFY_MACRO(__LINE__), static_err_msg); } }

/**
 * Executes the fatal error handler (see: uhashtools_handle_fatal_error()).
 * The argument "error_title" of said fatal error handler will be set to the file
 * and the line from where this macro was called.
 * 
 * The text passed by the argument "static_err_msg" has to be a NULL terminated
 * wide character array.
 */
#define UHASHTOOLS_FATAL_ERROR(static_err_msg) { uhashtools_handle_fatal_error(UHASHTOOLS_WIDEIFY_TXT_MACRO(__FILE__) L": Line " UHASHTOOLS_STRINGIFY_MACRO(__LINE__), static_err_msg); }

/**
 * Sets the owner window of the fatal error message box.
 * After the main window has been created it's recommended to set the
 * fatal error message box owner to the main window.
 * 
 * @param new_message_boxes_owner New owner of fatal error message boxes.
 */
extern
void
uhashtools_set_message_boxes_owner
(
    HWND new_message_boxes_owner
);

/**
 * This fatal error handler prints the error message passed by the argument
 * "static_err_msg" within a message box and aborts the application, after the
 * message box has been closed.
 * The title of the message box is set by the argument "error_title".
 * 
 * @param error_title Title of the fatal error message box.
 * @param error_txt Content of the fatal error message box.
 */
__declspec(noreturn)
extern
void
uhashtools_handle_fatal_error
(
    const wchar_t* error_title,
    const wchar_t* error_txt
);
