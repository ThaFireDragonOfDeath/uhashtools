/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "cli_arguments.h"

#include "error_utilities.h"

#include <string.h>

void
uhashtools_cli_arguments_fill_from_argc_argv
(
    struct CliArguments* cli_arguments,
    int argc,
    LPWSTR argv[]
)
{
    wchar_t* cli_target_file = NULL;
    size_t cli_target_file_strlen = 0;

    UHASHTOOLS_ASSERT(cli_arguments, L"Internal error: Entered with cli_arguments == NULL!");

    if (!argv || argc != 2)
    {
        return;
    }

    cli_target_file = argv[1];

    if (!cli_target_file)
    {
        return;
    }

    cli_target_file_strlen = wcslen(cli_target_file);

    if (cli_target_file_strlen == 0 || cli_target_file_strlen >= FILEPATH_BUFFER_TSIZE)
    {
        return;
    }

    (void) wcscpy_s(cli_arguments->target_file, FILEPATH_BUFFER_TSIZE, cli_target_file);
}

BOOL
uhashtools_cli_arguments_has_target_file
(
    const struct CliArguments* cli_arguments
)
{
    UHASHTOOLS_ASSERT(cli_arguments, L"Internal error: Entered with cli_arguments == NULL!");

    return cli_arguments->target_file[0] != L'\0';
}
