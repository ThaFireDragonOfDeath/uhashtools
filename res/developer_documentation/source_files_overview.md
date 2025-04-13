<!--
This file is part of µHashtools.
µHashtools is a small graphical file hashing tool for Microsoft Windows.

SPDX-FileCopyrightText: 2024-2025 Marcel Gosmann <thafiredragonofdeath@gmail.com>
SPDX-License-Identifier: CC0-1.0
-->

# buffer_sizes.h
This application uses fixed sizes for the buffers containing
filepaths, hash results and textual result messages. This file
sets the sizes of those buffers.

# cli_arguments.[ch]
Contains the functionality to get the passed options from the command line
and putting them into a structure. Also provides helper functions to get
information about the options contained in the structure.

# clipboard_utils.[ch]
Contains the functionality to set the clipboard content
to a provided string.

# com_lib.[ch]
Helper utilities for initializing and uninitializing the COM
(Component Object Model) library.

# error_utilities.[ch]
Contains utilities for verifying expected conditions and signaling
critical errors.

# gui_common.[ch]
Contains utility functions and constants that are valid for multiple
or all graphical element types. For example the functions for
getting the position or size of an element or resizing or moving
an element are within this unit.

# gui_*_common.[ch]
Contains utility functions and constants that are valid for one
specific graphical element type. Here is a list with the element
types:
* btn = push button
* eb = edit box
* lbl = label
* pb = progress bar

# hash_calculation_impl.[ch]
This unit does the actual work and contains the code for hashing
the file in the provided filepath. The functions of this unit should
never be called from the UI thread since file hashing is a time
expensive operation that could block the UI thread and leading to
an unresponsive application.

# hash_calculation_worker_com.[ch]
Provides the functions for communication between the main window thread
and the hash calculation worker thread. The main window thread uses this
unit to send a cancellation request to the hash calculation worker and the
hash calculation worker uses this unit to send result and progress messages
to the main window.

# hash_calculation_worker_ctx.[ch]
Provides the definition and initialization function of the hash calculation
worker thread memory. The thread memory will be allocated and initialized
at the beginning of the worker thread and will be freed at the end of the
worker thread.

# hash_calculation_worker.[ch]
This unit is the layer between the UI thread and the hashing
implementation. The UI thread uses this unit to start a background
worker thread. This background worker then uses the hashing
implementation from the unit "hash_calculation_impl.[ch]" to do the
actual file hash calculation.

# main.c
The entry point of the application. It initializes the main window
context data and then calls the main window startup function within
the unit "mainwin.[ch]".

# mainwin_actions.[ch]
This is the unit where the functionality like initializing the UI
elements or changing the current state of the main window is placed.
The functions of this unit should only be called during the startup
phase or within the UI thread and not from within a background
worker thread.

# mainwin_btn_*.[ch] mainwin_eb_*.[ch] mainwin_lbl_*.[ch] mainwin_pb_*.[ch]
Those units are the UI elements in the main window. Each UI element
is contained within a single .c/.h unit which provides
functionality like creating the element, reacting on size changes of
the parent UI element or reacting on a state change of the main
window. The functionality of each UI unit is called in the file
"mainwin_actions.c". That file wires all functionality together.

# mainwin_ctx.[ch]
This unit contains the definition and initialization functionality
of the main window context data. This data structure contains all
data the main window needs to operate. The context data must live
at minimum as long the main window exists. In this application
we're going a step further and tying the lifecycle of the main
window context data to the lifecycle of the application (see file
"main.c").

# mainwin_event_handler.[ch]
Here we are reacting on events for the main window. For example
if a button is clicked, a file is dropped or we received an event
from the background worker thread this unit will by called from
the code within the file "mainwin_message_handler.c".

# mainwin_message_handler.[ch]
In this unit we're processing the received window messages. The
functionality of this unit is called by the window procedure in the
file "mainwin.c". In the majority of the cases we're checking if we
process the received event and if thats the case getting the
relevant information from the received message and call upon the
functionality in the unit "mainwin_event_handler.[ch]". In some
exceptional cases we handle the message directly in this unit.

# mainwin_state.h
This unit defines the states in which the main window can be.
Like for example if the main window has currently just started up or
if the main window is currently doing a calculation of a file hash.
The current main window state is always stored within the main
window context data. The state of the main window is the main
deciding factor on which UI elements are visible, enabled and in
case of the action button even which icon the button has and what
code will be executed when the button is clicked.

# mainwin.[ch]
This unit contains the startup code for the main window and the
window message procedure for the main window. This message procedure
receives all messages for the main window and forwards them to the
"mainwin_message_handler.[ch]" unit.

# print_utilities.h
This header contains helper macros for printing debug, information, warning
and error messages to stdout. Usually this messages are not visible in
graphical applications (even if the application is started from a CMD
window) but if the application is started from Visual Studio Code using the
"Start Debugging" or "Run without debugging" commands the content of stdout
will be printed within the "DEBUG CONSOLE" tab.

# product_common.h
This unit contains the application information which is the same
across all generated executable files. For example this unit defines
the version, author and copyright statement. This unit is included
by the resource files which means the information from this unit
are integrated in the final executable files.

# product_umd5.[ch] product_usha1.[ch] product_usha256.[ch]
Those units declare application specific information like the
application name, executable filename, file description, title of
the main window, the initial width of the main window and the hash
algorithm of the specific application. Some of those information
are included by the resource files and are therefore embedded in
the executable file. The C source files are also implementing the
interface functions of the file "product.h".

# product.h
This unit declares interface functions for getting application
specific information like title of the main window or the hash
algorithm at runtime. Those interface functions are implemented by
the source files of the
"product_umd5.[ch] product_usha1.[ch] product_usha256.[ch]" units.
Each application can only have one implementation of this interface
functions and which implementation is the effective one for the
specific application is resolved during the linking of the
executable file. For example the file "usha256.exe" links all common
.obj files (which are the same for every application) and the .obj
file "product_usha256.obj" which is specific for usha256. This
object file contains the complied implementation of the interface
functions from the file "product.h".

# selectfiledialog.[ch]
This unit allows to open a file selection dialog and is used if the
select file button is clicked.

# taskbar_icon_pb_ctx.h
This unit defines which information is contained within the context
data of the taskbar icon progress bar UI element. The taskbar icon
progress bar is currently the only UI element with separate context
data. All other UI elements get their context data from their window
handle. But the taskbar icon progress bar isn't based upon a regular
window handle but a COM object. Getting context information out of
that object is way more expensive than getting information from a
window handle. So we're storing the context data of the taskbar icon
progress bar within a context data structure.

# taskbar_icon_pb.[ch]
Representation of the taskbar icon progress bar as UI element. This
unit follows the same scheme as the other main window UI elements.

# taskbarlist_com_api.[ch]
This unit is an abstraction over the COM API of the taskbar list
and the glue between the taskbar icon progress bar UI element and
the COM interface "ITaskbarList3".

# uhashtools_common.rc
This unit defines all resources embedded in the executable file.
But this unit can't be used directly since it expects that the
application specific information constants defined by the units
"product_umd5.h product_usha1.h product_usha256.h" are already set
when this file is compiled. So this file is include by the application
specific resource files after the application specific information is
set.

# umd5.rc usha1.rc usha256.rc
Those units are the application specific resource files whose are
compiled and linked into the resulting executable file of the
specific application. The application specific resource files just
include the product header file for the specific application and
then including the file "uhashtools_common.rc".