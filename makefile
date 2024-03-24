# µHashtools - A small graphical file hashing tool for Microsoft Windows
# Copyright (C) 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
# 
# This file is part of µHashtools.
# 
# µHashtools is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 2 of the License, or (at your option) any later
# version.
# 
# µHashtools is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE. See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along with
# µHashtools. If not, see <https://www.gnu.org/licenses/>.
#
# SPDX-License-Identifier: GPL-2.0-or-later


#
# Declaring the buildtools
#

# CC and RC are predefined.

AR      = lib
CP      = copy
RM      = del /F
RMDIR   = rmdir /s /q
LD      = link
MKDIR   = MD
MT      = mt

#
# Setting the product metadata
#

PRODUCT_NAME            = µHashtools
PRODUCT_FILE_NAMEBASE   = uhashtools
PRODUCT_VERSION         = 0.1.1

#
# Setting the buildmode.
#

!IF "$(BUILDMODE)" != "Release"
BUILDMODE = Debug
!Endif

#
# Setting artifacts output options.
#

# Setting the basenames
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
DIST_TARGET_NAME                            = $(PRODUCT_FILE_NAMEBASE)_v$(PRODUCT_VERSION)
DISTOUT_DIR                                 = $(DISTOUT_BASE_DIR)\$(DIST_TARGET_NAME)
DISTOUT_DOC_DIR                             = $(DISTOUT_DIR)\documentation
DISTOUT_SRC_PKG_DIR                         = $(DISTOUT_DIR)\source_code

# Setting the source distribution output options.
SRC_DIST_TARGET_NAME                        = $(DIST_TARGET_NAME)_src

#
# Setting compile options.
#

CFLAGS_COMMON               = /nologo /W4 /Zi /D_WIN32 /D_CRT_SECURE_NO_WARNINGS /D_CRT_NONSTDC_NO_WARNINGS /DUNICODE /D_UNICODE
CFLAGS_DEBUG                = /Od /MDd /D_CRTDBG_MAP_ALLOC
CFLAGS_RELEASE              = /O2 /MD

!IF "$(BUILDMODE)" == "Debug"
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

LFLAGS_COMMON               = /nologo /DEBUG
LFLAGS_DEBUG                = /INCREMENTAL
LFLAGS_RELEASE              = /INCREMENTAL:NO

!IF "$(BUILDMODE)" == "Debug"
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

UHASHTOOLS_SOURCES_COMMON       = src\main.c \
                                  src\errorutils.c \
                                  src\gui_common.c \
                                  src\gui_btn_common.c \
                                  src\gui_pb_common.c \
                                  src\gui_eb_common.c \
                                  src\gui_lbl_common.c \
                                  src\mainwin.c \
                                  src\mainwin_btn_action.c \
                                  src\mainwin_btn_select_file.c \
                                  src\mainwin_eb_calc_result.c \
                                  src\mainwin_lbl_result_hash.c \
                                  src\mainwin_pb_calc_result.c \
                                  src\mainwin_lbl_selected_file.c \
                                  src\mainwin_eb_current_selected_file.c \
                                  src\mainwin_lbl_filedrop.c \
                                  src\selectfiledialog.c \
                                  src\hash_calculation_worker.c \
                                  src\hash_calculation_impl.c \
                                  src\clipboard_utils.c

UHASHTOOLS_APP_ICON_COMMON      = res\application_icon\application_icon_64.ico
UHASHTOOLS_RC_SOURCES_COMMON    = src\uhashtools_common.rc

USHA256_SOURCES                 = src\product_usha256.c
USHA256_RC_SOURCES              = src\usha256.rc

USHA1_SOURCES                   = src\product_usha1.c
USHA1_RC_SOURCES                = src\usha1.rc

UMD5_SOURCES                    = src\product_umd5.c
UMD5_RC_SOURCES                 = src\umd5.rc

#
# Setting the header files.
# Updating a header file will cause a full recompilation.
#

UHASHTOOLS_HEADERS_COMMON       = src\product.h \
                                  src\product_common.h \
                                  src\buffer_sizes.h \
                                  src\errorutils.h \
                                  src\gui_common.h \
                                  src\gui_btn_common.h \
                                  src\gui_pb_common.h \
                                  src\gui_eb_common.h \
                                  src\gui_lbl_common.h \
                                  src\mainwin.h \
                                  src\mainwin_btn_action.h \
                                  src\mainwin_btn_select_file.h \
                                  src\mainwin_eb_calc_result.h \
                                  src\mainwin_lbl_result_hash.h \
                                  src\mainwin_pb_calc_result.h \
                                  src\mainwin_lbl_selected_file.h \
                                  src\mainwin_eb_current_selected_file.h \
                                  src\mainwin_lbl_filedrop.h \
                                  src\selectfiledialog.h \
                                  src\hash_calculation_worker.h \
                                  src\hash_calculation_impl.h \
                                  src\clipboard_utils.h

USHA256_HEADERS                 = src\product_usha256.h
USHA1_HEADERS                   = src\product_usha1.h
UMD5_HEADERS                    = src\product_umd5.h

#
# Setting the out obj files.
#

UHASHTOOLS_OBJECTS_COMMON       = $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\main.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\errorutils.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\gui_common.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\gui_btn_common.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\gui_pb_common.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\gui_eb_common.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\gui_lbl_common.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_btn_action.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_btn_select_file.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_eb_calc_result.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_lbl_result_hash.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_pb_calc_result.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_lbl_selected_file.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_eb_current_selected_file.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\mainwin_lbl_filedrop.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\selectfiledialog.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\hash_calculation_worker.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\hash_calculation_impl.obj \
                                  $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR)\clipboard_utils.obj

USHA256_OBJECTS                 = $(USHA256_BUILDOUT_OBJ_DIR)\product_usha256.obj
USHA256_RES_OBJECTS             = $(USHA256_BUILDOUT_OBJ_DIR)\usha256.res

USHA1_OBJECTS                   = $(USHA1_BUILDOUT_OBJ_DIR)\product_usha1.obj
USHA1_RES_OBJECTS               = $(USHA1_BUILDOUT_OBJ_DIR)\usha1.res

UMD5_OBJECTS                    = $(UMD5_BUILDOUT_OBJ_DIR)\product_umd5.obj
UMD5_RES_OBJECTS                = $(UMD5_BUILDOUT_OBJ_DIR)\umd5.res

#
# Setting the distribution files.
#

UHASHTOOLS_DISTOUT_FILES        = $(DISTOUT_DIR)\$(USHA256_NAME_BASE).exe \
                                  $(DISTOUT_DIR)\$(USHA1_NAME_BASE).exe \
                                  $(DISTOUT_DIR)\$(UMD5_NAME_BASE).exe \
                                  $(DISTOUT_DIR)\README.txt \
                                  $(DISTOUT_DOC_DIR)\ATTRIBUTION.txt \
                                  $(DISTOUT_DOC_DIR)\LICENSE.CC0.txt \
                                  $(DISTOUT_DOC_DIR)\LICENSE.CC-BY-4.0.txt \
                                  $(DISTOUT_DOC_DIR)\LICENSE.GPL-2.txt \
                                  $(DISTOUT_DOC_DIR)\LICENSE.GPL-3.txt


#
# Definition of the main targets.
#

all: $(USHA256_BUILDOUT_EXE_FILE) $(USHA1_BUILDOUT_EXE_FILE) $(UMD5_BUILDOUT_EXE_FILE)

rebuild: clean all

run: $(USHA256_BUILDOUT_EXE_FILE)
    $(USHA256_BUILDOUT_EXE_FILE)

dist: $(UHASHTOOLS_DISTOUT_FILES) $(DISTOUT_SRC_PKG_DIR)
    @-echo.
    @-echo Distribution created at "$(DISTOUT_DIR)". Finally you have to copy the source archive into $(DISTOUT_SRC_PKG_DIR) and your distribution is ready to go. The source archive should have the name "$(SRC_DIST_TARGET_NAME).zip" and should be placed at "$(DISTOUT_SRC_PKG_DIR)".

clean:
    -$(RMDIR) $(BUILDOUT_DIR)
    -$(RMDIR) $(DISTOUT_BASE_DIR)
    -$(RM) src\application_icon.ico

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

src\application_icon.ico: $(UHASHTOOLS_APP_ICON_COMMON)
    $(CP) $(UHASHTOOLS_APP_ICON_COMMON) src\application_icon.ico

#
# Definition of the compilation targets.
#

$(UHASHTOOLS_OBJECTS_COMMON): $(UHASHTOOLS_COMMON_BUILDOUT_OBJ_DIR) $(UHASHTOOLS_HEADERS_COMMON)

$(USHA256_OBJECTS): $(USHA256_BUILDOUT_OBJ_DIR) $(USHA256_HEADERS)
$(USHA256_RES_OBJECTS): $(UHASHTOOLS_RC_SOURCES_COMMON) $(USHA256_RC_SOURCES) $(USHA256_HEADERS) src\product_common.h src\application_icon.ico

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

$(DISTOUT_DIR):
    $(MKDIR) $(DISTOUT_DIR)

$(DISTOUT_DOC_DIR):
    $(MKDIR) $(DISTOUT_DOC_DIR)

$(DISTOUT_SRC_PKG_DIR):
    $(MKDIR) $(DISTOUT_SRC_PKG_DIR)

$(DISTOUT_DIR)\$(USHA256_NAME_BASE).exe: $(DISTOUT_DIR) $(USHA256_BUILDOUT_EXE_FILE)
    $(CP) $(USHA256_BUILDOUT_EXE_FILE) $(DISTOUT_DIR)\$(USHA256_NAME_BASE).exe

$(DISTOUT_DIR)\$(USHA1_NAME_BASE).exe: $(DISTOUT_DIR) $(USHA1_BUILDOUT_EXE_FILE)
    $(CP) $(USHA1_BUILDOUT_EXE_FILE) $(DISTOUT_DIR)\$(USHA1_NAME_BASE).exe

$(DISTOUT_DIR)\$(UMD5_NAME_BASE).exe: $(DISTOUT_DIR) $(UMD5_BUILDOUT_EXE_FILE)
    $(CP) $(UMD5_BUILDOUT_EXE_FILE) $(DISTOUT_DIR)\$(UMD5_NAME_BASE).exe

$(DISTOUT_DIR)\README.txt: $(DISTOUT_DIR) res\user_documentation\README.txt
    $(CP) res\user_documentation\README.txt $(DISTOUT_DIR)\README.txt

$(DISTOUT_DOC_DIR)\ATTRIBUTION.txt: $(DISTOUT_DOC_DIR) ATTRIBUTION
    $(CP) ATTRIBUTION $(DISTOUT_DOC_DIR)\ATTRIBUTION.txt

$(DISTOUT_DOC_DIR)\LICENSE.CC0.txt: $(DISTOUT_DOC_DIR) LICENSE.CC0
    $(CP) LICENSE.CC0 $(DISTOUT_DOC_DIR)\LICENSE.CC0.txt

$(DISTOUT_DOC_DIR)\LICENSE.CC-BY-4.0.txt: $(DISTOUT_DOC_DIR) LICENSE.CC-BY-4.0
    $(CP) LICENSE.CC-BY-4.0 $(DISTOUT_DOC_DIR)\LICENSE.CC-BY-4.0.txt

$(DISTOUT_DOC_DIR)\LICENSE.GPL-2.txt: $(DISTOUT_DOC_DIR) LICENSE.GPL-2
    $(CP) LICENSE.GPL-2 $(DISTOUT_DOC_DIR)\LICENSE.GPL-2.txt

$(DISTOUT_DOC_DIR)\LICENSE.GPL-3.txt: $(DISTOUT_DOC_DIR) LICENSE.GPL-3
    $(CP) LICENSE.GPL-3 $(DISTOUT_DOC_DIR)\LICENSE.GPL-3.txt
