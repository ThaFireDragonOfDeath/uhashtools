/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#if WINVER >= 0x0601

#include "taskbarlist_com_api.h"

#include "errorutils.h"

#include <combaseapi.h>
#include <Objbase.h>
#include <Shobjidl.h>
#include <Windows.h>

static
TBPFLAG
uhashtools_taskbar_progress_flags_from_pvm
(
    enum ProgressViewMode progress_view_mode
)
{
    switch (progress_view_mode)
    {
        case PROGRESS_VIEW_MODE_NONE: return TBPF_NOPROGRESS;
        case PROGRESS_VIEW_MODE_NORMAL_PROGRESS: return TBPF_NORMAL;
        case PROGRESS_VIEW_MODE_ERROR_PROGRESS: return TBPF_ERROR;
        default: return TBPF_NOPROGRESS;
    }
}

BOOL
uhashtools_taskbar_list_com_api_init
(
    struct TaskbarListComApi* taskbar_list_com_api,
    struct ComLibState* com_lib_state,
    HWND main_window_handle
)
{
    ITaskbarList3* new_taskbar_list_v3_instance = NULL;
    HRESULT create_instance_result = 0;

    UHASHTOOLS_ASSERT(com_lib_state, L"Given ComLibState pointer is NULL!");
    UHASHTOOLS_ASSERT(com_lib_state->com_lib_is_initialized, L"The COM library isn't initialized yet!");
    UHASHTOOLS_ASSERT(main_window_handle, L"Given main window handle is NULL!");
    UHASHTOOLS_ASSERT(main_window_handle != INVALID_HANDLE_VALUE, L"Given main window handle is INVALID_HANDLE_VALUE!");

    create_instance_result = CoCreateInstance(&CLSID_TaskbarList,
                                              NULL,
                                              CLSCTX_INPROC_SERVER,
                                              &IID_ITaskbarList3,
                                              &new_taskbar_list_v3_instance);

    if (create_instance_result != S_OK || !new_taskbar_list_v3_instance)
    {
        return FALSE;
    }

    SecureZeroMemory(taskbar_list_com_api, sizeof *taskbar_list_com_api);
    taskbar_list_com_api->main_window_handle = main_window_handle;
    taskbar_list_com_api->taskbar_list_v3_instance = new_taskbar_list_v3_instance;
    
    return TRUE;
}

void
uhashtools_taskbar_list_com_api_set_progress_value
(
    struct TaskbarListComApi* initialized_taskbar_list_com_api,
    unsigned int progress_in_percent
)
{
    ITaskbarList3* taskbar_list_v3 = NULL;
    HWND main_window_handle = NULL;

    if (!initialized_taskbar_list_com_api)
    {
        return;
    }

    taskbar_list_v3 = initialized_taskbar_list_com_api->taskbar_list_v3_instance;
    main_window_handle = initialized_taskbar_list_com_api->main_window_handle;

    if (!taskbar_list_v3 || !main_window_handle || main_window_handle == INVALID_HANDLE_VALUE)
    {
        return;
    }

    if (progress_in_percent > 100)
    {
        progress_in_percent = 100;
    }

    (void) taskbar_list_v3->lpVtbl->SetProgressValue(taskbar_list_v3,
                                                     main_window_handle,
                                                     progress_in_percent,
                                                     100);
}

void
uhashtools_taskbar_list_com_api_set_progress_view_mode
(
    struct TaskbarListComApi* initialized_taskbar_list_com_api,
    enum ProgressViewMode progress_view_mode
)
{
    ITaskbarList3* taskbar_list_v3 = NULL;
    HWND main_window_handle = NULL;
    TBPFLAG taskbar_progress_flags = 0;

    if (!initialized_taskbar_list_com_api)
    {
        return;
    }

    taskbar_list_v3 = initialized_taskbar_list_com_api->taskbar_list_v3_instance;
    main_window_handle = initialized_taskbar_list_com_api->main_window_handle;

    if (!taskbar_list_v3 || !main_window_handle || main_window_handle == INVALID_HANDLE_VALUE)
    {
        return;
    }

    taskbar_progress_flags = uhashtools_taskbar_progress_flags_from_pvm(progress_view_mode);

    (void) taskbar_list_v3->lpVtbl->SetProgressState(taskbar_list_v3,
                                                     main_window_handle,
                                                     taskbar_progress_flags);
}

#endif
