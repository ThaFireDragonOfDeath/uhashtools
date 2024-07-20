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
"UHASHTOOLS_ASSERT()" from the header file "error_utilities.h".
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
"UHASHTOOLS_FATAL_ERROR()" from the header file "error_utilities.h".
This macro function accepts only one argument which is a wide
string error message. This error message along with other
information like filename and line number will be shown within an
error message box. After the error message box is closed by the user
the application terminates.

# Non critical errors in the hash background worker thread
Errors during the hash calculation are handled gracefully by sending
an hash calculation failed user event window message to the main
window. The event handler will then show the error message within a
message box. In practice the blocking hash calculation function
"uhashtools_hash_calculator_impl_hash_file()" gets the wide string
buffer "result_string_buf" in which the implementation can write
either the calculated hash of the selected file or an error message.
What information is stored in this buffer is determined by the
return value of this function. If the function returns the success
indicator then the buffer will contain the hash result. But if the
function returns the failed indicator the buffer will contain an
error message. In other words if we encounter a non critical error
within the blocking hash calculation function we simply write the
error message for the user into the result buffer and returning
the failed indicator. The thread function of the hash background
worker thread within the source file "hash_calculation_worker.c"
will check the return code of the blocking hash calculation function
and will send a calculation failed message to the main window.

# Printing warning messages
To print warning messages we're including the standard C header file
"stdio.h" and using the following code:
```C
(void) wprintf_s(L"[WARNING]: Warning message\n");
(void) fflush(stdout);
```

# Printing information messages
To print information messages we're including the standard C header
file "stdio.h" and using the following code:
```C
(void) wprintf_s(L"[INFO]: Information message\n");
(void) fflush(stdout);
```

# Printing debug messages
To print debug messages we're including the standard C header file
"stdio.h" and using the following code:
```C
(void) wprintf_s(L"[DEBUG]: Debug message\n");
(void) fflush(stdout);
```