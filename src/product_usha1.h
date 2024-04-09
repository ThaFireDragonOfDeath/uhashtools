/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <bcrypt.h>

/* Product specific ressource compiler definitions */
#define UHASHTOOLS_RC_INTERNALNAME_STR L"usha1\0"
#define UHASHTOOLS_RC_ORIGINALFILENAME_STR L"usha1.exe\0"
#define UHASHTOOLS_RC_FILEDESCRIPTION_STR L"\x00b5SHA-1\0"
#define UHASHTOOLS_RC_PRODUCTNAME_STR L"\x00b5SHA-1\0"

/* Product specific C code definitions */
#define UHASHTOOLS_MAINWIN_CLASSNAME L"CLASS_USHA1_MAINWIN"
#define UHASHTOOLS_MAINWIN_TITLE L"\x00b5SHA-1"
#define UHASHTOOLS_MAINWIN_RECOMMENDED_WIDTH 410
#define UHASHTOOLS_BCRYPT_HASH_ALGORITHM_NAME BCRYPT_SHA1_ALGORITHM
