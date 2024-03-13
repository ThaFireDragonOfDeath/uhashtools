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

#include "product.h"

#include <Windows.h>

#include "product_usha1.h"

const wchar_t MAINWIN_CLASSNAME[] = UHASHTOOLS_MAINWIN_CLASSNAME;
const wchar_t MAINWIN_TITLE[] = UHASHTOOLS_MAINWIN_TITLE;
const int MAINWIN_RECOMMENDED_WIDTH = UHASHTOOLS_MAINWIN_RECOMMENDED_WIDTH;
const wchar_t BCRYPT_HASH_ALGORITHM_NAME[] = UHASHTOOLS_BCRYPT_HASH_ALGORITHM_NAME;

const wchar_t*
uhashes_product_get_mainwin_classname
(
    void
)
{
    return MAINWIN_CLASSNAME;
}

const wchar_t*
uhashes_product_get_mainwin_title
(
    void
)
{
    return MAINWIN_TITLE;
}

int
uhashes_product_get_recommended_mainwin_width
(
    void
)
{
    return MAINWIN_RECOMMENDED_WIDTH;
}

const wchar_t*
uhashes_product_get_bcrypt_algorithm_str
(
    void
)
{
    return BCRYPT_HASH_ALGORITHM_NAME;
}