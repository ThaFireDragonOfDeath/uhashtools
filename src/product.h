/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <Windows.h>

extern
const wchar_t*
uhashes_product_get_mainwin_classname
(
    void
);

extern
const wchar_t*
uhashes_product_get_mainwin_title
(
    void
);

extern
int
uhashes_product_get_recommended_mainwin_width
(
    void
);

extern
const wchar_t*
uhashes_product_get_bcrypt_algorithm_str
(
    void
);
