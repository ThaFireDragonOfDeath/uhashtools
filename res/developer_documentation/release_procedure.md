<!--
SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
SPDX-License-Identifier: CC0-1.0
-->

# Automatic release procedure with the "dist" target (requires Windows PowerShell)
To building a release archive of this software please execute the
following steps:
1. Start the application "x64 Native Tools Command Prompt for VS
   2022" (name is different for other Visual Studio versions).
2. Navigate with the command `cd` to the directory which contains
   the file "makefile".
3. Run `nmake BUILD_MODE=Release dist` to start the build and
   packaging process.
   Warning! The "dist" target executes the "clean" target at the
   start to ensure that it operates within a clean source directory
   before doing anything else. So make sure that you don't have
   important files within the output directories before executing
   `nmake [...] dist`.
4. Collect the release archive from the directory ".\dist_out".