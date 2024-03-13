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

#pragma once

#include <bcrypt.h>

/* Product specific ressource compiler definitions */
#define UHASHTOOLS_RC_INTERNALNAME_STR L"umd5\0"
#define UHASHTOOLS_RC_ORIGINALFILENAME_STR L"umd5.exe\0"
#define UHASHTOOLS_RC_FILEDESCRIPTION_STR L"\x00b5MD5\0"
#define UHASHTOOLS_RC_PRODUCTNAME_STR L"\x00b5MD5\0"

/* Product specific C code definitions */
#define UHASHTOOLS_MAINWIN_CLASSNAME L"CLASS_UMD5_MAINWIN"
#define UHASHTOOLS_MAINWIN_TITLE L"\x00b5MD5"
#define UHASHTOOLS_MAINWIN_RECOMMENDED_WIDTH 380
#define UHASHTOOLS_BCRYPT_HASH_ALGORITHM_NAME BCRYPT_MD5_ALGORITHM
