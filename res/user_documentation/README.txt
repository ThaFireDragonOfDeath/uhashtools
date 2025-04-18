This file is part of µHashtools.
µHashtools is a small graphical file hashing tool for Microsoft Windows.

SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
SPDX-License-Identifier: CC0-1.0


-Copyright and license notices---------------------------------------

µHashtools is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or (at
your option) any later version.

µHashtools is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
(see "documentation/LICENSE.GPL-2.0-or-later.txt") along with this
µHashtools distribution.
If not can get the license text of the GNU General Public License
version 2 and newer versions at "https://www.gnu.org/licenses/".

The application logo is licensed under the terms of the "Creative
Commons Attribution 4.0 International" as published by the Creative
Commons Corporation.
You should have received a copy of the "Creative Commons Attribution
4.0 International" (see the file "documentation/LICENSE.CC-BY-4.0")
along with this µHashtools distribution.
If not you can get the license text at
"https://creativecommons.org/licenses/by/4.0/legalcode".

This copyright information is for documentation and attribution
purposes and is required to be in conformity with the information
from the "COPYING" document in the source code.
Please refer that document for the full copyright and permission
information.


-Source code---------------------------------------------------------

You can find a copy of the source code from which this release is
built in the directory "source_code".

The upstream of this µHashtools distribution is located at:
https://github.com/ThaFireDragonOfDeath/uhashtools


-Basic usage---------------------------------------------------------

1.  Double click on the .exe file for the target hash algorithm
    ("usha256.exe" for SHA-256, "usha1.exe" for SHA-1 and "umd5.exe"
    for MD5).
2.  To select the target file you can either Drag and drop your
    target file into the "File drop zone" or click on the select
    file button to open a file selection dialog for selecting the
    target file.
3.  Wait until the calculation is finished.
4.  You can find the calculated hash right next to the "Result:"
    label.
5.  You can use the copy button right next to the calculated hash
    result to copy the calculated hash into the clipboard.


-Advanced usage: Preselected target file-----------------------------

It's also possible to start the application with the target file as
parameter. In that case the file given as parameter will be taken as
target file and the calculation of the hash code of that file starts
after the application has been started.

1.  Drag and drop the target file on the .exe file for the target
    hash algorithm ("usha256.exe" for SHA-256, "usha1.exe" for SHA-1
    and "umd5.exe" for MD5). As alternative you can also open the
    target file with the .exe file for the target hash algorithm
    using the "Open With" Windows feature.
2.  Wait until the calculation is finished.
3.  You can find the calculated hash right next to the "Result:"
    label.
4.  You can use the copy button right next to the calculated hash
    result to copy the calculated hash into the clipboard.