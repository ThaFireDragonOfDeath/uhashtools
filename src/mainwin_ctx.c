/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "mainwin_ctx.h"

#include "errorutils.h"

#include <memory.h>

void
uhashtools_mainwin_ctx_init
(
    struct MainWindowCtx* mainwin_ctx
)
{
    UHASHTOOLS_ASSERT(mainwin_ctx, L"Internal error (invalid argument): Argument 'mainwin_ctx' is a null pointer!");

    memset((void*) mainwin_ctx, 0, sizeof *mainwin_ctx);
}
