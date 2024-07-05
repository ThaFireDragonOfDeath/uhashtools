<!--
SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
SPDX-License-Identifier: CC0-1.0
-->

# µHashtools
µHashtools is a small graphical file hashing tool for Microsoft Windows.
It focuses on small executable file size, low memory footprint and easy usage.

# Features
* Supports currently the algorithms MD5, SHA-1 and SHA-256.
* Selecting the target file by the file selection dialog or by drag and drop.
* Simplicity. For each supported algorithm exists one separate application. Instead of one application that does everything, this tool set has multiple applications that do one thing and do it well.
* Portability. Each application of this tool set is a single, self contained .exe file without dependencies on external libraries.

# License
Summery for documentation purposes:
This software is licensed under the terms of GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.
The image files (for example the application icon) are licensed under the terms of the "Creative Commons Attribution 4.0 International" as published by the Creative Commons Corporation.
The documentation files, Visual Studio Code files and Git configuration files are licensed under the terms of the "Creative Commons CC0 1.0 Universal" as published by the Creative Commons Corporation.

Please refer the file "[COPYING](COPYING)" for the effective copyright and permission notice.

# Building
## Build dependencies
* Visual Studio (supported are the versions 2008 up to 2022)

## Build process
1. Start the application "x64 Native Tools Command Prompt for VS 2022" (name is different for other Visual Studio versions).
2. Navigate with the command `cd` to the directory which contains the file "makefile".
3. Run `nmake all` to build this software in debug mode or run `nmake BUILDMODE=Release all` to build in release mode.
4. Collect the artifacts from `build_out\bin`.

# Known issues / ToDo
* The developer documentation is nearly non existent.
* The code documentation (Doxygen code comments) is missing.