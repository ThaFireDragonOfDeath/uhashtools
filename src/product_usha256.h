/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <bcrypt.h>

/* Product specific resource compiler definitions */
#define UHASHTOOLS_RC_INTERNALNAME_STR L"usha256\0"
#define UHASHTOOLS_RC_ORIGINALFILENAME_STR L"usha256.exe\0"
#define UHASHTOOLS_RC_FILEDESCRIPTION_STR L"\x00b5SHA-256\0"
#define UHASHTOOLS_RC_PRODUCTNAME_STR L"\x00b5SHA-256\0"

/* Product specific C code definitions */
#define UHASHTOOLS_MAINWIN_CLASSNAME L"CLASS_USHA256_MAINWIN"
#define UHASHTOOLS_MAINWIN_TITLE L"\x00b5SHA-256"
#define UHASHTOOLS_MAINWIN_RECOMMENDED_WIDTH 550
#define UHASHTOOLS_BCRYPT_HASH_ALGORITHM_NAME BCRYPT_SHA256_ALGORITHM

/*
 * Because this file is included by a resource file, this file must
 * always end with an empty line!
 */
