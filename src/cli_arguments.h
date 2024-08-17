/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "buffer_sizes.h"

#include <wchar.h>
#include <Windows.h>

/**
 * Structure holding the command line interface arguments.
 * All arguments are optional. The default initialisation for an
 * instance of this structure is to do a memset zero.
 */
struct CliArguments
{
    /**
     * File for which the hash code shall be calculated. This argument
     * is an optional positional argument and if set always located
     * at argv[1]. If argc is smaller then 2 then this application is
     * started without a target file and this wide string buffer will
     * be an empty C wide string. 
     */
    wchar_t target_file[FILEPATH_BUFFER_TSIZE];
};

/* 
 * We don't need an uhashtools_cli_arguments_init_empty() function
 * because the only place where an instance of this structure can
 * be found is within the MainWindowCtx structure. This structure
 * is initialized by the function uhashtools_mainwin_ctx_init() which
 * does a memset zero and therefore also initializes the CliArguments
 * with the valid empty state.
 */


/**
 * Fills the members of the passed CliArguments structure with the arguments
 * from the command line argument vector.
 * 
 * @param cli_arguments Zero initialized instance of the CliArguments structure.
 * @param argc Number of elements in argv.
 * @param argv Command line argument vector.
 */
extern
void
uhashtools_cli_arguments_fill_from_argc_argv
(
    struct CliArguments* cli_arguments,
    int argc,
    LPWSTR argv[]
);

/**
 * Checks if a target file has been set.
 * 
 * @param cli_arguments Initialized instance of the CliArguments structure.
 * 
 * @return TRUE if a target file is set else FALSE.
 */
extern
BOOL
uhashtools_cli_arguments_has_target_file
(
    const struct CliArguments* cli_arguments
);
