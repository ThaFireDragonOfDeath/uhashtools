<!--
SPDX-FileCopyrightText: 2024-2025 Marcel Gosmann <thafiredragonofdeath@gmail.com>
SPDX-License-Identifier: CC0-1.0
-->

This document describes how a release archive can be build locally and which steps
must be taken to release a new version of this software.

# Build a release archive locally
## Introduction
A release archive of this software can be built locally using the "dist" NMake
target. This target will do a full rebuild, using various CMD and Windows
PowerShell commands to copy the sources and built artifacts into the correct
structure within a subdirectory within the "dist_out" directory and then uses
the PowerShell command "Compress-Archive" to compress that subdirectory into
a .zip archive.

## Prerequisites
* The [build dependencies](/README.md#build-dependencies)
  are satisfied.
* Windows PowerShell installed and the path to the directory containing the
  "powershell.exe" file exists within the "PATH" environment variable.
## Build steps
To building a release archive of this software please execute the following steps:
1. Start the application "x64 Native Tools Command Prompt for VS 2022" (name is
   different for other Visual Studio versions and profiles).
2. Navigate with the command `cd` to the directory which contains the file "makefile".
3. Run `nmake BUILD_MODE=Release dist` to start the build and packaging process.
   Warning! The "dist" target executes the "clean" target at the
   start to ensure that it operates within a clean source directory
   before doing anything else. So make sure that you don't have
   important files within the output directories before executing
   `nmake [...] dist`.
4. Collect the release .zip archive from the directory ".\dist_out".

# Procedure for releasing a new version of this software
## Introduction
Since version 0.3.0 we're using the artifacts created during the Github CI
build pipeline as base for the release.

## Prerequisites
* The run of the "Github CI" workflow for last pushed commit was successful.
* The executables from the last release archive produced by the "Github CI" workflow
  are starting and after following the chapter "Basic Usage" from the
  [README.txt of the user documentation](../user_documentation/README.txt) produces expected
  results.
* All files within the "src" directory are covered by the
  [source files overview documentation](./source_files_overview.md).

## Release steps
1.  Change the release date in the [CHANGELOG.txt](/CHANGELOG.txt) from "not released yet"
    to the current date.
2.  Remove the "-SNAPSHOT" from the version numbers in the files [makefile](/makefile) and
    [src/product_common.h](/src/product_common.h).
3.  Commit and push the changes.
4.  Go to the actions tab and wait until the workflow has completed successfully.
    If the workflow has completed with an error which shouldn't happen (see
    [prerequisites](#prerequisites-1)) you must fix the errors and commit the fixes until
    the workflow completes successfully.
5.  Download the "release-archive.zip" artifact from the workflow and extract the
    "uhashtools_vX.Y.Z_bin_x64.zip" file.
6.  Extract the "uhashtools_vX.Y.Z_bin_x64.zip" file and check the content.
    The "uhashtools_vX.Y.Z_bin_x64.zip" file must contain the executables,
    the user specific "README.txt", the licenses related documentation (should be in the
    "documentation" directory), the change log (should be in the "documentation" directory),
    the source code and the debug symbols.
7.  Test that the executables from the "uhashtools_vX.Y.Z_bin_x64.zip" file are starting
    and after following the chapter "Basic Usage" from the README.txt produces expected
    results.
8.  Add and push the Git tag "vX.Y.Z" to the commit which produced the previously tested
    "release-archive.zip" file.
9.  Upload the "uhashtools_vX.Y.Z_bin_x64.zip" file previously extracted from the
    "release-archive.zip" file as asset.
10. Add a short description containing the link to the workflow run and a notice
    of the required MSVC runtime.
11. Increase the version number in the files [makefile](/makefile) and
    [src/product_common.h](/src/product_common.h) and add "-SNAPSHOT" to the places where
    you removed them during step 2.
12. Add a new block for the next version to the [CHANGELOG.txt](/CHANGELOG.txt) with the
    content:
    ```
    µHashtools X.Y.Z (not released yet):
    # No changes implemented yet
    ```
13. Commit and push the changes.