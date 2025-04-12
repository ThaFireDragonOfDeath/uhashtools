# This file is part of µHashtools.
# µHashtools is a small graphical file hashing tool for Microsoft Windows.
# 
# SPDX-FileCopyrightText: 2024-2025 Marcel Gosmann <thafiredragonofdeath@gmail.com>
# SPDX-License-Identifier: GPL-2.0-or-later


#
# Declaring the build tools
#

# CC and RC are predefined.

CP         = copy
POWERSHELL = powershell.exe
RM         = del /F
RMDIR      = rd /s /q
LD         = link
MKDIR      = MD
MT         = mt


#
# Setting the product metadata
#

PRODUCT_NAME            = µHashtools
PRODUCT_ASCII_NAME      = uhashtools
PRODUCT_VERSION         = 0.3.0-SNAPSHOT


#
# Set minimum Windows API version.
# Some features of this application are only enabled on certain values.
# 
# The value of "MINIMUM_WIN32_API_VERSION" must be one of the following
# values or higher:
# 0x0600 - Requires Windows Vista and Windows SDK v6.0a or newer.
#          This is the lowest supported value.
# 0x0601 - Requires Windows 7 and Windows SDK v7.0 or newer.
#          If "MINIMUM_WIN32_API_VERSION" is this value or higher, the
#          taskbar icon progress bar feature will be enabled.
#          This feature uses the "ITaskbarList3" COM interface which
#          requires Windows 7 or newer.
# 
# The minimum required Microsoft Visual C++ compiler is unaffected by this
# value and is at the moment always MSVC 9.0 (VS 2008).
#

MINIMUM_WIN32_API_VERSION = 0x0601


#
# Setting the build mode.
#

!IF "$(BUILD_MODE)" != "Release"
BUILD_MODE = Debug
!Endif


#
# Determine the target build architecture.
# This will be used in the file name of the release archive.
#

# The environment variable "VSCMD_ARG_TGT_ARCH" is set during the initialization
# of the Visual Studio shell and can be "x86", "x64", "arm" or "arm64".
# See "%VSINSTALLDIR%\Common7\Tools\vsdevcmd\ext\vcvars.bat" for details.
!IF "$(VSCMD_ARG_TGT_ARCH)" != ""
BUILD_TARGET_ARCH = $(VSCMD_ARG_TGT_ARCH)
!ELSE
# Old Visual Studio shell which doesn't set this environment variable.
# Assuming x86 target.
BUILD_TARGET_ARCH = x86
!Endif


#
# Setting artifacts output options.
#

# Setting the name bases
UHASHTOOLS_COMMON_NAME_BASE                 = uhashtools_common
USHA256_NAME_BASE                           = usha256
USHA1_NAME_BASE                             = usha1
UMD5_NAME_BASE                              = umd5

# Setting the build output settings
BUILDOUT_DIR                                = build_out
BUILDOUT_OBJ_DIR                            = $(BUILDOUT_DIR)\obj
BUILDOUT_BIN_DIR                            = $(BUILDOUT_DIR)\bin

UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR          = $(BUILDOUT_OBJ_DIR)\$(UHASHTOOLS_COMMON_NAME_BASE)
UHASHTOOLS_COMMON_BUILDOUT_OBJ_PDB_FILE     = $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\$(UHASHTOOLS_COMMON_NAME_BASE)_s.pdb

USHA256_BUILDOUT_OBJ_DIR                    = $(BUILDOUT_OBJ_DIR)\$(USHA256_NAME_BASE)
USHA256_BUILDOUT_OBJ_PDB_FILE               = $(USHA256_BUILDOUT_OBJ_DIR)\$(USHA256_NAME_BASE)_s.pdb
USHA256_BUILDOUT_EXE_WITHOUT_MANIFEST_FILE  = $(USHA256_BUILDOUT_OBJ_DIR)\$(USHA256_NAME_BASE)_without_manifest.exe
USHA256_BUILDOUT_MANIFEST_FILE              = $(USHA256_BUILDOUT_OBJ_DIR)\$(USHA256_NAME_BASE).manifest
USHA256_BUILDOUT_EXE_FILE                   = $(BUILDOUT_BIN_DIR)\$(USHA256_NAME_BASE).exe
USHA256_BUILDOUT_PDB_FILE                   = $(BUILDOUT_BIN_DIR)\$(USHA256_NAME_BASE).pdb

USHA1_BUILDOUT_OBJ_DIR                      = $(BUILDOUT_OBJ_DIR)\$(USHA1_NAME_BASE)
USHA1_BUILDOUT_OBJ_PDB_FILE                 = $(USHA1_BUILDOUT_OBJ_DIR)\$(USHA1_NAME_BASE)_s.pdb
USHA1_BUILDOUT_EXE_WITHOUT_MANIFEST_FILE    = $(USHA1_BUILDOUT_OBJ_DIR)\$(USHA1_NAME_BASE)_without_manifest.exe
USHA1_BUILDOUT_MANIFEST_FILE                = $(USHA1_BUILDOUT_OBJ_DIR)\$(USHA1_NAME_BASE).manifest
USHA1_BUILDOUT_EXE_FILE                     = $(BUILDOUT_BIN_DIR)\$(USHA1_NAME_BASE).exe
USHA1_BUILDOUT_PDB_FILE                     = $(BUILDOUT_BIN_DIR)\$(USHA1_NAME_BASE).pdb

UMD5_BUILDOUT_OBJ_DIR                       = $(BUILDOUT_OBJ_DIR)\$(UMD5_NAME_BASE)
UMD5_BUILDOUT_OBJ_PDB_FILE                  = $(UMD5_BUILDOUT_OBJ_DIR)\$(UMD5_NAME_BASE)_s.pdb
UMD5_BUILDOUT_EXE_WITHOUT_MANIFEST_FILE     = $(UMD5_BUILDOUT_OBJ_DIR)\$(UMD5_NAME_BASE)_without_manifest.exe
UMD5_BUILDOUT_MANIFEST_FILE                 = $(UMD5_BUILDOUT_OBJ_DIR)\$(UMD5_NAME_BASE).manifest
UMD5_BUILDOUT_EXE_FILE                      = $(BUILDOUT_BIN_DIR)\$(UMD5_NAME_BASE).exe
UMD5_BUILDOUT_PDB_FILE                      = $(BUILDOUT_BIN_DIR)\$(UMD5_NAME_BASE).pdb

# Setting the distribution output options.
DISTOUT_BASE_DIR                            = dist_out

!IF "$(BUILD_MODE)" == "Debug"
DIST_TARGET_NAME                            = $(PRODUCT_ASCII_NAME)_v$(PRODUCT_VERSION)_bin_$(BUILD_TARGET_ARCH)_debug
!ELSE
DIST_TARGET_NAME                            = $(PRODUCT_ASCII_NAME)_v$(PRODUCT_VERSION)_bin_$(BUILD_TARGET_ARCH)
!Endif

DISTOUT_DIR                                 = $(DISTOUT_BASE_DIR)\$(DIST_TARGET_NAME)
DISTOUT_DEBUG_SYMBOLS_DIR                   = $(DISTOUT_DIR)\debug_symbols
DISTOUT_DOC_DIR                             = $(DISTOUT_DIR)\documentation
DISTOUT_SRC_DIR                             = $(DISTOUT_DIR)\source_code

DIST_ARCHIVE_FILE                           = $(DISTOUT_BASE_DIR)\$(DIST_TARGET_NAME).zip


#
# Setting compile options.
#

CFLAGS_COMMON               = /nologo /W4 /we4013 /we4133 /Zi /D_WIN32 \
                              /DUNICODE /D_UNICODE /DWINVER=$(MINIMUM_WIN32_API_VERSION) \
                              /D_WIN32_WINNT=$(MINIMUM_WIN32_API_VERSION)
CFLAGS_DEBUG                = /Od /MDd /D_CRTDBG_MAP_ALLOC
CFLAGS_RELEASE              = /O1 /MD

!IF "$(BUILD_MODE)" == "Debug"
CFLAGS                      = $(CFLAGS_COMMON) $(CFLAGS_DEBUG)
!ELSE
CFLAGS                      = $(CFLAGS_COMMON) $(CFLAGS_RELEASE)
!Endif

CFLAGS_UHASHTOOLS_COMMON    = $(CFLAGS) /Fo$(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\ /Fd$(UHASHTOOLS_COMMON_BUILDOUT_OBJ_PDB_FILE)
CFLAGS_USHA256              = $(CFLAGS) /Fo$(USHA256_BUILDOUT_OBJ_DIR)\ /Fd$(USHA256_BUILDOUT_OBJ_PDB_FILE)
CFLAGS_USHA1                = $(CFLAGS) /Fo$(USHA1_BUILDOUT_OBJ_DIR)\ /Fd$(USHA1_BUILDOUT_OBJ_PDB_FILE)
CFLAGS_UMD5                 = $(CFLAGS) /Fo$(UMD5_BUILDOUT_OBJ_DIR)\ /Fd$(UMD5_BUILDOUT_OBJ_PDB_FILE)


#
# Setting linker options.
#

UHASHTOOLS_LINK_LIBRARIES   = Gdi32.lib shell32.lib User32.lib UxTheme.lib Comdlg32.lib Bcrypt.lib

!IF $(MINIMUM_WIN32_API_VERSION) >= 0x0601
UHASHTOOLS_LINK_LIBRARIES   = $(UHASHTOOLS_LINK_LIBRARIES) Ole32.lib
!Endif

LFLAGS_COMMON               = /nologo /DEBUG
LFLAGS_DEBUG                = /INCREMENTAL
LFLAGS_RELEASE              = /INCREMENTAL:NO

!IF "$(BUILD_MODE)" == "Debug"
LFLAGS                      = $(LFLAGS_COMMON) $(LFLAGS_DEBUG)
!ELSE
LFLAGS                      = $(LFLAGS_COMMON) $(LFLAGS_RELEASE)
!Endif

LFLAGS_USHA256              = $(LFLAGS) /MANIFESTFILE:$(USHA256_BUILDOUT_MANIFEST_FILE) /PDB:$(USHA256_BUILDOUT_PDB_FILE) /OUT:$(USHA256_BUILDOUT_EXE_WITHOUT_MANIFEST_FILE)
LFLAGS_USHA1                = $(LFLAGS) /MANIFESTFILE:$(USHA1_BUILDOUT_MANIFEST_FILE) /PDB:$(USHA1_BUILDOUT_PDB_FILE) /OUT:$(USHA1_BUILDOUT_EXE_WITHOUT_MANIFEST_FILE)
LFLAGS_UMD5                 = $(LFLAGS) /MANIFESTFILE:$(UMD5_BUILDOUT_MANIFEST_FILE) /PDB:$(UMD5_BUILDOUT_PDB_FILE) /OUT:$(UMD5_BUILDOUT_EXE_WITHOUT_MANIFEST_FILE)


#
# Setting the source files.
# Updating a source file will cause an incremental compilation.
#

UHASHTOOLS_SOURCES_COMMON        = src\cli_arguments.c \
                                   src\clipboard_utils.c \
                                   src\error_utilities.c \
                                   src\gui_btn_common.c \
                                   src\gui_common.c \
                                   src\gui_eb_common.c \
                                   src\gui_lbl_common.c \
                                   src\gui_pb_common.c \
                                   src\hash_calculation_impl.c \
                                   src\hash_calculation_worker_com.c \
                                   src\hash_calculation_worker_ctx.c \
                                   src\hash_calculation_worker.c \
                                   src\main.c \
                                   src\mainwin.c \
                                   src\mainwin_actions.c \
                                   src\mainwin_btn_action.c \
                                   src\mainwin_btn_select_file.c \
                                   src\mainwin_ctx.c \
                                   src\mainwin_eb_calc_result.c \
                                   src\mainwin_eb_current_selected_file.c \
                                   src\mainwin_event_handler.c \
                                   src\mainwin_lbl_file_drop.c \
                                   src\mainwin_lbl_result_hash.c \
                                   src\mainwin_lbl_selected_file.c \
                                   src\mainwin_message_handler.c \
                                   src\mainwin_pb_calc_result.c \
                                   src\selectfiledialog.c

!IF $(MINIMUM_WIN32_API_VERSION) >= 0x0601
UHASHTOOLS_SOURCES_COMMON_0x0601 = src\com_lib.c \
                                   src\taskbar_icon_pb.c \
                                   src\taskbarlist_com_api.c

UHASHTOOLS_SOURCES_COMMON        = $(UHASHTOOLS_SOURCES_COMMON) \
                                   $(UHASHTOOLS_SOURCES_COMMON_0x0601)
!Endif

UHASHTOOLS_APP_ICON_COMMON       = res\application_icon\application_icon_64.ico
UHASHTOOLS_RC_SOURCES_COMMON     = src\uhashtools_common.rc

USHA256_SOURCES                  = src\product_usha256.c
USHA256_RC_SOURCES               = src\usha256.rc

USHA1_SOURCES                    = src\product_usha1.c
USHA1_RC_SOURCES                 = src\usha1.rc

UMD5_SOURCES                     = src\product_umd5.c
UMD5_RC_SOURCES                  = src\umd5.rc


#
# Setting the header files.
# Updating a header file will cause a full recompilation.
#

UHASHTOOLS_HEADERS_COMMON        = src\buffer_sizes.h \
                                   src\cli_arguments.h \
                                   src\clipboard_utils.h \
                                   src\error_utilities.h \
                                   src\gui_btn_common.h \
                                   src\gui_common.h \
                                   src\gui_eb_common.h \
                                   src\gui_lbl_common.h \
                                   src\gui_pb_common.h \
                                   src\hash_calculation_impl.h \
                                   src\hash_calculation_worker_com.h \
                                   src\hash_calculation_worker_ctx.h \
                                   src\hash_calculation_worker.h \
                                   src\mainwin.h \
                                   src\mainwin_actions.h \
                                   src\mainwin_btn_action.h \
                                   src\mainwin_btn_select_file.h \
                                   src\mainwin_ctx.h \
                                   src\mainwin_eb_calc_result.h \
                                   src\mainwin_eb_current_selected_file.h \
                                   src\mainwin_event_handler.h \
                                   src\mainwin_lbl_file_drop.h \
                                   src\mainwin_lbl_result_hash.h \
                                   src\mainwin_lbl_selected_file.h \
                                   src\mainwin_message_handler.h \
                                   src\mainwin_pb_calc_result.h \
                                   src\mainwin_state.h \
                                   src\print_utilities.h \
                                   src\product.h \
                                   src\product_common.h \
                                   src\selectfiledialog.h \
                                   src\taskbar_icon_pb_ctx.h

!IF $(MINIMUM_WIN32_API_VERSION) >= 0x0601
UHASHTOOLS_HEADERS_COMMON_0x0601 = src\com_lib.h \
                                   src\taskbar_icon_pb.h \
                                   src\taskbarlist_com_api.h

UHASHTOOLS_HEADERS_COMMON        = $(UHASHTOOLS_HEADERS_COMMON) \
                                   $(UHASHTOOLS_HEADERS_COMMON_0x0601)
!Endif

USHA256_HEADERS                  = src\product_usha256.h
USHA1_HEADERS                    = src\product_usha1.h
UMD5_HEADERS                     = src\product_umd5.h


#
# Setting the out obj files.
#

UHASHTOOLS_OBJECTS_COMMON        = $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\cli_arguments.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\clipboard_utils.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\error_utilities.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\gui_btn_common.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\gui_common.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\gui_eb_common.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\gui_lbl_common.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\gui_pb_common.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\hash_calculation_impl.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\\hash_calculation_worker_com.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\\hash_calculation_worker_ctx.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\hash_calculation_worker.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\main.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_actions.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_btn_action.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_btn_select_file.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_ctx.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_eb_calc_result.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_eb_current_selected_file.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_event_handler.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_lbl_file_drop.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_lbl_result_hash.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_lbl_selected_file.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_message_handler.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_pb_calc_result.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\selectfiledialog.obj

!IF $(MINIMUM_WIN32_API_VERSION) >= 0x0601
UHASHTOOLS_OBJECTS_COMMON_0x0601 = $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\com_lib.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\taskbar_icon_pb.obj \
                                   $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\taskbarlist_com_api.obj

UHASHTOOLS_OBJECTS_COMMON        = $(UHASHTOOLS_OBJECTS_COMMON) \
                                   $(UHASHTOOLS_OBJECTS_COMMON_0x0601)
!Endif

USHA256_OBJECTS                  = $(USHA256_BUILDOUT_OBJ_DIR)\product_usha256.obj
USHA256_RES_OBJECTS              = $(USHA256_BUILDOUT_OBJ_DIR)\usha256.res

USHA1_OBJECTS                    = $(USHA1_BUILDOUT_OBJ_DIR)\product_usha1.obj
USHA1_RES_OBJECTS                = $(USHA1_BUILDOUT_OBJ_DIR)\usha1.res

UMD5_OBJECTS                     = $(UMD5_BUILDOUT_OBJ_DIR)\product_umd5.obj
UMD5_RES_OBJECTS                 = $(UMD5_BUILDOUT_OBJ_DIR)\umd5.res


#
# Setting the distribution files.
#

UHASHTOOLS_DISTOUT_FILES        = $(DISTOUT_DIR)\$(USHA256_NAME_BASE).exe \
                                  $(DISTOUT_DIR)\$(USHA1_NAME_BASE).exe \
                                  $(DISTOUT_DIR)\$(UMD5_NAME_BASE).exe \
                                  $(DISTOUT_DIR)\README.txt \
                                  $(DISTOUT_DEBUG_SYMBOLS_DIR)\$(USHA256_NAME_BASE).pdb \
                                  $(DISTOUT_DEBUG_SYMBOLS_DIR)\$(USHA1_NAME_BASE).pdb \
                                  $(DISTOUT_DEBUG_SYMBOLS_DIR)\$(UMD5_NAME_BASE).pdb \
                                  $(DISTOUT_DOC_DIR)\ATTRIBUTION.txt \
                                  $(DISTOUT_DOC_DIR)\CHANGELOG.txt \
                                  $(DISTOUT_DOC_DIR)\LICENSE.CC0-1.0.txt \
                                  $(DISTOUT_DOC_DIR)\LICENSE.CC-BY-4.0.txt \
                                  $(DISTOUT_DOC_DIR)\LICENSE.GPL-2.0-or-later.txt


#
# Definition of the main targets.
#

all: $(USHA256_BUILDOUT_EXE_FILE) $(USHA1_BUILDOUT_EXE_FILE) $(UMD5_BUILDOUT_EXE_FILE)

rebuild: clean all

run: $(USHA256_BUILDOUT_EXE_FILE)
    $(USHA256_BUILDOUT_EXE_FILE)

dist: clean $(DIST_ARCHIVE_FILE)
    @-echo.
    @-echo Distribution archive file "$(DIST_ARCHIVE_FILE)" has been created.

clean:
    -$(RMDIR) $(BUILDOUT_DIR)
    -$(RMDIR) $(DISTOUT_BASE_DIR)
    -$(RM) src\rc_application_icon.ico


#
# Definition of the preparation targets.
#

$(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR):
    $(MKDIR) $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)

$(USHA256_BUILDOUT_OBJ_DIR):
    $(MKDIR) $(USHA256_BUILDOUT_OBJ_DIR)

$(USHA1_BUILDOUT_OBJ_DIR):
    $(MKDIR) $(USHA1_BUILDOUT_OBJ_DIR)

$(UMD5_BUILDOUT_OBJ_DIR):
    $(MKDIR) $(UMD5_BUILDOUT_OBJ_DIR)

$(BUILDOUT_BIN_DIR):
    $(MKDIR) $(BUILDOUT_BIN_DIR)

src\rc_application_icon.ico: $(UHASHTOOLS_APP_ICON_COMMON)
    $(CP) $(UHASHTOOLS_APP_ICON_COMMON) src\rc_application_icon.ico


#
# Definition of the compilation targets.
#

$(UHASHTOOLS_OBJECTS_COMMON): $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR) $(UHASHTOOLS_HEADERS_COMMON)

$(USHA256_OBJECTS): $(USHA256_BUILDOUT_OBJ_DIR) $(USHA256_HEADERS)
$(USHA256_RES_OBJECTS): $(UHASHTOOLS_RC_SOURCES_COMMON) $(USHA256_RC_SOURCES) $(USHA256_HEADERS) src\product_common.h src\rc_application_icon.ico

$(USHA1_OBJECTS): $(USHA1_BUILDOUT_OBJ_DIR) $(USHA1_HEADERS)
$(USHA1_RES_OBJECTS): $(UHASHTOOLS_RC_SOURCES_COMMON) $(USHA1_RC_SOURCES) $(USHA1_HEADERS) src\product_common.h

$(UMD5_OBJECTS): $(UMD5_BUILDOUT_OBJ_DIR) $(UMD5_HEADERS)
$(UMD5_RES_OBJECTS): $(UHASHTOOLS_RC_SOURCES_COMMON) $(UMD5_RC_SOURCES) $(UMD5_HEADERS) src\product_common.h

{src}.c{$(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)}.obj:
    $(CC) $(CFLAGS_UHASHTOOLS_COMMON) /c $<

{src}.c{$(USHA256_BUILDOUT_OBJ_DIR)}.obj:
    $(CC) $(CFLAGS_USHA256) /c $<

{src}.rc{$(USHA256_BUILDOUT_OBJ_DIR)}.res:
    $(RC) $(RCFLAGS) /fo $@ $<

{src}.c{$(USHA1_BUILDOUT_OBJ_DIR)}.obj:
    $(CC) $(CFLAGS_USHA1) /c $<

{src}.rc{$(USHA1_BUILDOUT_OBJ_DIR)}.res:
    $(RC) $(RCFLAGS) /fo $@ $<

{src}.c{$(UMD5_BUILDOUT_OBJ_DIR)}.obj:
    $(CC) $(CFLAGS_UMD5) /c $<

{src}.rc{$(UMD5_BUILDOUT_OBJ_DIR)}.res:
    $(RC) $(RCFLAGS) /fo $@ $<


#
# Definition of the linking targets.
#

$(USHA256_BUILDOUT_EXE_WITHOUT_MANIFEST_FILE) $(USHA256_BUILDOUT_PDB_FILE): $(BUILDOUT_BIN_DIR) $(UHASHTOOLS_OBJECTS_COMMON) $(USHA256_OBJECTS) $(USHA256_RES_OBJECTS)
    $(LD) $(LFLAGS_USHA256) $(UHASHTOOLS_OBJECTS_COMMON) $(USHA256_OBJECTS) $(USHA256_RES_OBJECTS) $(UHASHTOOLS_LINK_LIBRARIES)

$(USHA256_BUILDOUT_EXE_FILE): $(USHA256_BUILDOUT_EXE_WITHOUT_MANIFEST_FILE)
    $(CP) $(USHA256_BUILDOUT_EXE_WITHOUT_MANIFEST_FILE) $(USHA256_BUILDOUT_EXE_FILE)
    $(MT) -nologo -manifest $(USHA256_BUILDOUT_MANIFEST_FILE) -outputresource:$(USHA256_BUILDOUT_EXE_FILE);1

$(USHA1_BUILDOUT_EXE_WITHOUT_MANIFEST_FILE) $(USHA1_BUILDOUT_PDB_FILE): $(BUILDOUT_BIN_DIR) $(UHASHTOOLS_OBJECTS_COMMON) $(USHA1_OBJECTS) $(USHA1_RES_OBJECTS)
    $(LD) $(LFLAGS_USHA1) $(UHASHTOOLS_OBJECTS_COMMON) $(USHA1_OBJECTS) $(USHA1_RES_OBJECTS) $(UHASHTOOLS_LINK_LIBRARIES)

$(USHA1_BUILDOUT_EXE_FILE): $(USHA1_BUILDOUT_EXE_WITHOUT_MANIFEST_FILE)
    $(CP) $(USHA1_BUILDOUT_EXE_WITHOUT_MANIFEST_FILE) $(USHA1_BUILDOUT_EXE_FILE)
    $(MT) -nologo -manifest $(USHA1_BUILDOUT_MANIFEST_FILE) -outputresource:$(USHA1_BUILDOUT_EXE_FILE);1

$(UMD5_BUILDOUT_EXE_WITHOUT_MANIFEST_FILE) $(UMD5_BUILDOUT_PDB_FILE): $(BUILDOUT_BIN_DIR) $(UHASHTOOLS_OBJECTS_COMMON) $(UMD5_OBJECTS) $(UMD5_RES_OBJECTS)
    $(LD) $(LFLAGS_UMD5) $(UHASHTOOLS_OBJECTS_COMMON) $(UMD5_OBJECTS) $(UMD5_RES_OBJECTS) $(UHASHTOOLS_LINK_LIBRARIES)

$(UMD5_BUILDOUT_EXE_FILE): $(UMD5_BUILDOUT_EXE_WITHOUT_MANIFEST_FILE)
    $(CP) $(UMD5_BUILDOUT_EXE_WITHOUT_MANIFEST_FILE) $(UMD5_BUILDOUT_EXE_FILE)
    $(MT) -nologo -manifest $(UMD5_BUILDOUT_MANIFEST_FILE) -outputresource:$(UMD5_BUILDOUT_EXE_FILE);1


#
# Definition of the distribution targets
#

$(DIST_ARCHIVE_FILE): $(UHASHTOOLS_DISTOUT_FILES) copy-sources
    $(POWERSHELL) -Command "& {Compress-Archive -Path '$(DISTOUT_DIR)' -DestinationPath '$(DIST_ARCHIVE_FILE)'}"

$(DISTOUT_DIR):
    $(MKDIR) $(DISTOUT_DIR)

$(DISTOUT_DEBUG_SYMBOLS_DIR):
    $(MKDIR) $(DISTOUT_DEBUG_SYMBOLS_DIR)

$(DISTOUT_DOC_DIR):
    $(MKDIR) $(DISTOUT_DOC_DIR)

$(DISTOUT_SRC_DIR):
    $(MKDIR) $(DISTOUT_SRC_DIR)

$(DISTOUT_DIR)\$(USHA256_NAME_BASE).exe: $(DISTOUT_DIR) $(USHA256_BUILDOUT_EXE_FILE)
    $(CP) $(USHA256_BUILDOUT_EXE_FILE) $(DISTOUT_DIR)\$(USHA256_NAME_BASE).exe

$(DISTOUT_DIR)\$(USHA1_NAME_BASE).exe: $(DISTOUT_DIR) $(USHA1_BUILDOUT_EXE_FILE)
    $(CP) $(USHA1_BUILDOUT_EXE_FILE) $(DISTOUT_DIR)\$(USHA1_NAME_BASE).exe

$(DISTOUT_DIR)\$(UMD5_NAME_BASE).exe: $(DISTOUT_DIR) $(UMD5_BUILDOUT_EXE_FILE)
    $(CP) $(UMD5_BUILDOUT_EXE_FILE) $(DISTOUT_DIR)\$(UMD5_NAME_BASE).exe

$(DISTOUT_DIR)\README.txt: $(DISTOUT_DIR) res\user_documentation\README.txt
    $(CP) res\user_documentation\README.txt $(DISTOUT_DIR)\README.txt

$(DISTOUT_DEBUG_SYMBOLS_DIR)\$(USHA256_NAME_BASE).pdb: $(DISTOUT_DEBUG_SYMBOLS_DIR) $(USHA256_BUILDOUT_PDB_FILE)
    $(CP) $(USHA256_BUILDOUT_PDB_FILE) $(DISTOUT_DEBUG_SYMBOLS_DIR)\$(USHA256_NAME_BASE).pdb

$(DISTOUT_DEBUG_SYMBOLS_DIR)\$(USHA1_NAME_BASE).pdb: $(DISTOUT_DEBUG_SYMBOLS_DIR) $(USHA1_BUILDOUT_PDB_FILE)
    $(CP) $(USHA1_BUILDOUT_PDB_FILE) $(DISTOUT_DEBUG_SYMBOLS_DIR)\$(USHA1_NAME_BASE).pdb

$(DISTOUT_DEBUG_SYMBOLS_DIR)\$(UMD5_NAME_BASE).pdb: $(DISTOUT_DEBUG_SYMBOLS_DIR) $(UMD5_BUILDOUT_PDB_FILE)
    $(CP) $(UMD5_BUILDOUT_PDB_FILE) $(DISTOUT_DEBUG_SYMBOLS_DIR)\$(UMD5_NAME_BASE).pdb

$(DISTOUT_DOC_DIR)\ATTRIBUTION.txt: $(DISTOUT_DOC_DIR) ATTRIBUTION
    $(CP) ATTRIBUTION $(DISTOUT_DOC_DIR)\ATTRIBUTION.txt

$(DISTOUT_DOC_DIR)\CHANGELOG.txt: $(DISTOUT_DOC_DIR) CHANGELOG.txt
    $(CP) CHANGELOG.txt $(DISTOUT_DOC_DIR)\CHANGELOG.txt

$(DISTOUT_DOC_DIR)\LICENSE.CC0-1.0.txt: $(DISTOUT_DOC_DIR) LICENSES\CC0-1.0.txt
    $(CP) LICENSES\CC0-1.0.txt $(DISTOUT_DOC_DIR)\LICENSE.CC0-1.0.txt

$(DISTOUT_DOC_DIR)\LICENSE.CC-BY-4.0.txt: $(DISTOUT_DOC_DIR) LICENSES\CC-BY-4.0.txt
    $(CP) LICENSES\CC-BY-4.0.txt $(DISTOUT_DOC_DIR)\LICENSE.CC-BY-4.0.txt

$(DISTOUT_DOC_DIR)\LICENSE.GPL-2.0-or-later.txt: $(DISTOUT_DOC_DIR) LICENSES\GPL-2.0-or-later.txt
    $(CP) LICENSES\GPL-2.0-or-later.txt $(DISTOUT_DOC_DIR)\LICENSE.GPL-2.0-or-later.txt

copy-sources: $(DISTOUT_SRC_DIR)
    $(POWERSHELL) -Command "& {Copy-Item -Path '.\*' -Destination '$(DISTOUT_SRC_DIR)' -Recurse -Exclude @('rc_application_icon.ico', '.git', '$(BUILDOUT_DIR)', '$(DISTOUT_BASE_DIR)')}"
