/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024-2025 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <Windows.h>

/* Common resource compiler definitions */
#define UHASHTOOLS_RC_FILEVERSION          0,3,0,1
#define UHASHTOOLS_RC_FILEVERSION_STR      L"0.3.0.1-SNAPSHOT\0"
#define UHASHTOOLS_RC_FILEFLAGS            (VS_FF_PRERELEASE | VS_FF_DEBUG)
#define UHASHTOOLS_RC_PRODUCTVERSION       0,3,0,0
#define UHASHTOOLS_RC_PRODUCTVERSION_STR   L"0.3.0-SNAPSHOT\0"
#define UHASHTOOLS_RC_COMPANY_STR          L"techdragonblog.de\0"
#define UHASHTOOLS_RC_LEGALCOPYRIGHT_STR   L"\x00a9 2024-2025 Marcel Gosmann\0"

/*
 * Because this file is included by a resource file, this file must
 * always end with an empty line!
 */
