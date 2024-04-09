/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
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