/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <stdio.h>

#define UHASHTOOLS_PRINTF_LINE_DEBUG(...) \
{ \
    (void) wprintf_s(L"[DEBUG]: "); \
    (void) wprintf_s(__VA_ARGS__); \
    (void) wprintf_s(L"\n"); \
    (void) fflush(stdout); \
}

#define UHASHTOOLS_PRINTF_LINE_INFO(...) \
{ \
    (void) wprintf_s(L"[INFO]: "); \
    (void) wprintf_s(__VA_ARGS__); \
    (void) wprintf_s(L"\n"); \
    (void) fflush(stdout); \
}

#define UHASHTOOLS_PRINTF_LINE_WARN(...) \
{ \
    (void) wprintf_s(L"[WARNING]: "); \
    (void) wprintf_s(__VA_ARGS__); \
    (void) wprintf_s(L"\n"); \
    (void) fflush(stdout); \
}

#define UHASHTOOLS_PRINTF_LINE_ERROR(...) \
{ \
    (void) wprintf_s(L"[ERROR]: "); \
    (void) wprintf_s(__VA_ARGS__); \
    (void) wprintf_s(L"\n"); \
    (void) fflush(stdout); \
}
