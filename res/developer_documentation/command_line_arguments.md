<!--
This file is part of µHashtools.
µHashtools is a small graphical file hashing tool for Microsoft Windows.

SPDX-FileCopyrightText: 2024-2025 Marcel Gosmann <thafiredragonofdeath@gmail.com>
SPDX-License-Identifier: CC0-1.0
-->

This application can be started with optional command line arguments.
This document describes the possible arguments and its effects.

# application.exe
If no arguments are passed then this application will start normally
without preselected file.
This happens if you double click on the executable file.

# application.exe <filepath>
If one command line argument is passed then this argument will be
interpreted as a file selection and this application will start
with the file hashing as soon the main window is visible.
But if the string in this argument is to long the this argument will
be ignored and the application starts as if no arguments were
passed.
This happens, if you open a file with this application.