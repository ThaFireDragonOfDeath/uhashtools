<!--
SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
SPDX-License-Identifier: CC0-1.0
-->

# Invalid arguments
This application runs with the assumption that all arguments of a
function are as expected and valid. As a result invalid arguments
are treated as critical errors. That means the application will 
crash with a detailed and user visible error message.
To test arguments for validity we're using the macro function
"UHASHTOOLS_ASSERT()" from the header file "errorutils.h".
This macro accepts two arguments. The first argument is for a
conditional expression and the second argument is for a wide string
error message. If the conditional expression doesn't resolve to
a value other then zero (or in other words: if the value is not
true), then the error message along with other information like
filename and line number will be shown within an error message box.
After the error message box is closed by the user the application
terminates.

# Critical errors
To deal with other critical errors we're using the macro function
"UHASHTOOLS_FATAL_ERROR()" from the header file "errorutils.h".
This macro function accepts only one argument which is a wide
string error message. This error message along with other
information like filename and line number will be shown within an
error message box. After the error message box is closed by the user
the application terminates.

# Printing warning messages
To print warning messages we're including the standard C header file
"stdio.h" and using the following code:
```C
(void) wprintf_s(L"[WARNING]: Warning message");
(void) fflush(stdout);
```

# Printing debug messages
To print debug messages we're including the standard C header file
"stdio.h" and using the following code:
```C
(void) wprintf_s(L"[DEBUG]: Debug message");
(void) fflush(stdout);
```