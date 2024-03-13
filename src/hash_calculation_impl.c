/*
 * µHashtools - A small graphical file hashing tool for Microsoft Windows
 * Copyright (C) 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * 
 * This file is part of µHashtools.
 * 
 * µHashtools is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 * 
 * µHashtools is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * µHashtools. If not, see <https://www.gnu.org/licenses/>.
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "hash_calculation_impl.h"

#include <limits.h>
#include <stdio.h>

#include <bcrypt.h>
#include <io.h>

#include "errorutils.h"
#include "product.h"

#define FILE_READ_BUF_SIZE 1024 * 512

#ifndef STATUS_SUCCESS
    #define STATUS_SUCCESS ((NTSTATUS) 0x00000000L)
#endif

struct OpenedTargetFile
{
    BOOL is_ok;
    FILE* target_file_handle;
    unsigned __int64 target_file_size;
};

struct PreparedWinCngHasherImpl
{
    BOOL is_ok;
    BCRYPT_ALG_HANDLE cng_algorithm_provider_handle;
    PUCHAR cng_algorithm_object_memory;
    PUCHAR hash_out_buf;
    size_t hash_out_buf_size;
    BCRYPT_HASH_HANDLE cng_algorithm_object_handle;
};

static
void
vscha256_encode_single_byte_to_hex
(
    const unsigned char target_byte,
    wchar_t* upper_hex_char,
    wchar_t* lower_hex_char
)
{
    wchar_t print_buf[3];

    (void) _snwprintf_s(print_buf, 3, _TRUNCATE, L"%.2hhx", target_byte);

    *upper_hex_char = print_buf[0];
    *lower_hex_char = print_buf[1];
}

static
BOOL
uhashtools_encode_bytes_to_hex
(
    const PUCHAR bytes_buf,
    const size_t bytes_buf_bytes,
    wchar_t* out_buf,
    size_t out_buf_tsize
)
{
    const size_t result_hex_characters = bytes_buf_bytes * 2;
    const size_t out_buf_required_tsize = result_hex_characters + 1;
    size_t current_hash_buf_pos = 0;
    size_t current_out_buf_pos = 0;

    if (bytes_buf_bytes >= 2000 || out_buf_required_tsize > out_buf_tsize)
    {
        return FALSE;
    }

    for (current_hash_buf_pos = 0; current_hash_buf_pos < bytes_buf_bytes; ++current_hash_buf_pos)
    {
        const unsigned char current_hash_byte = bytes_buf[current_hash_buf_pos];
        wchar_t current_upper_hex_char = 0;
        wchar_t current_lower_hex_char = 0;

        vscha256_encode_single_byte_to_hex(current_hash_byte, &current_upper_hex_char, &current_lower_hex_char);

        out_buf[current_out_buf_pos] = current_upper_hex_char;
        ++current_out_buf_pos;
        out_buf[current_out_buf_pos] = current_lower_hex_char;
        ++current_out_buf_pos;
    }

    return TRUE;
}

static
unsigned int
uhashtools_calculate_current_progress
(
    unsigned __int64 file_size,
    unsigned __int64 processed_bytes
)
{
    UHASHTOOLS_ASSERT(file_size <= _UI64_MAX / 100, L"Limit reached: The size of the given file is to big. It would cause an integer overflow.");

    if (file_size == 0)
    {
        /* Preventing division by zero */

        return 100u;
    }

    if (processed_bytes == 0)
    {
        return 0;
    }

    if (processed_bytes >= file_size)
    {
        return 100u;
    }

    /* Basic formular G / 100% = W/p -> W * 100 / G */
    return (unsigned int) ((processed_bytes * 100u) / file_size);
}

static
struct OpenedTargetFile
uhashtools_target_file_open
(
    wchar_t* error_message_buf,
    size_t error_message_buf_tsize,
    const wchar_t* target_file
)
{
    struct OpenedTargetFile ret;
    errno_t target_file_open_error = 0;
    FILE* target_file_handle = NULL;
    int target_file_fd = 0;
    __int64 filelengthi64_rc = 0;
    unsigned __int64 target_file_size = 0;

    UHASHTOOLS_ASSERT(error_message_buf, L"Internal error: error_message_buf is NULL!");
    UHASHTOOLS_ASSERT(target_file, L"Internal error: target_file is NULL!");

    (void) SecureZeroMemory(&ret, sizeof ret);
    ret.is_ok = FALSE;

    target_file_open_error = _wfopen_s(&target_file_handle,
                                       target_file,
                                       L"rb");

    if (target_file_open_error || !target_file_handle)
    {
        (void) wcscpy_s(error_message_buf, error_message_buf_tsize, L"Failed to open the selected file!");

        goto cleanup_and_out;
    }

    target_file_fd = _fileno(target_file_handle);

    UHASHTOOLS_ASSERT(target_file_fd != -1, L"Failed to get file descriptor of the opened file!");

    filelengthi64_rc = _filelengthi64(target_file_fd);

    if (filelengthi64_rc == -1)
    {
        (void) wcscpy_s(error_message_buf, error_message_buf_tsize, L"Failed to get the size of the selected file!");

        goto cleanup_and_out;
    }

    target_file_size = (unsigned __int64) filelengthi64_rc;

    (void) wprintf_s(L"[DEBUG] The opened file has a size of \"%I64u\" bytes.\n", target_file_size);
    (void) fflush(stdout);

    (void) clearerr_s(target_file_handle);

    ret.is_ok = TRUE;
    ret.target_file_handle = target_file_handle; target_file_handle = NULL;
    ret.target_file_size = target_file_size;

cleanup_and_out:
    if (target_file_handle)
    {
        (void) fclose(target_file_handle);
    }

    return ret;
}

static
void
uhashtools_target_file_close
(
    struct OpenedTargetFile* opened_target_file
)
{
    if (!opened_target_file || !opened_target_file->is_ok)
    {
        return;
    }

    (void) fclose(opened_target_file->target_file_handle);

    (void) SecureZeroMemory(opened_target_file, sizeof *opened_target_file);
    opened_target_file->is_ok = FALSE;
}

static
struct PreparedWinCngHasherImpl
uhashtools_win_cng_hash_impl_prepare
(
    wchar_t* error_message_buf,
    size_t error_message_buf_tsize
)
{
    struct PreparedWinCngHasherImpl ret;
    NTSTATUS open_algorithm_provider_rc = 0;
    BCRYPT_ALG_HANDLE cng_algorithm_provider_handle = NULL;
    NTSTATUS get_required_alg_obj_memory_rc = 0;
    DWORD algorithm_object_required_memory = 0;
    ULONG get_property_bytes_copied = 0;
    PUCHAR cng_algorithm_object_memory = NULL;
    NTSTATUS get_out_buf_required_size_rc = 0;
    DWORD hash_out_buf_required_size = 0;
    PUCHAR hash_out_buf = NULL;
    BCRYPT_HASH_HANDLE cng_algorithm_object_handle = NULL;
    NTSTATUS create_hash_object_rc = 0;

    UHASHTOOLS_ASSERT(error_message_buf, L"Internal error: error_message_buf is NULL!");

    (void) SecureZeroMemory(&ret, sizeof ret);
    ret.is_ok = FALSE;

    open_algorithm_provider_rc = BCryptOpenAlgorithmProvider(&cng_algorithm_provider_handle,
                                                             uhashes_product_get_bcrypt_algorithm_str(),
                                                             NULL,
                                                             0);

    if (open_algorithm_provider_rc != STATUS_SUCCESS)
    {
        (void) wcscpy_s(error_message_buf, error_message_buf_tsize, L"Failed to open the Windows BCrypt hashing algorithm provider!\nThis is either a bug in this software or your Windows doesn't have the required CNG algorithm provider.");

        goto cleanup_and_out;
    }

    get_required_alg_obj_memory_rc = BCryptGetProperty(cng_algorithm_provider_handle,
                                                       BCRYPT_OBJECT_LENGTH,
                                                       (PUCHAR) &algorithm_object_required_memory,
                                                       sizeof algorithm_object_required_memory,
                                                       &get_property_bytes_copied,
                                                       0);

    if (get_required_alg_obj_memory_rc != STATUS_SUCCESS || algorithm_object_required_memory < 1)
    {
        (void) wcscpy_s(error_message_buf, error_message_buf_tsize, L"Internal error: Failed to get the required memory size for the Win32 CNG object!");

        goto cleanup_and_out;
    }

    get_out_buf_required_size_rc = BCryptGetProperty(cng_algorithm_provider_handle,
                                                     BCRYPT_HASH_LENGTH,
                                                     (PUCHAR) &hash_out_buf_required_size,
                                                     sizeof hash_out_buf_required_size,
                                                     &get_property_bytes_copied,
                                                     0);

    if (get_out_buf_required_size_rc != STATUS_SUCCESS || hash_out_buf_required_size < 1)
    {
        (void)wcscpy_s(error_message_buf, error_message_buf_tsize, L"Internal error: Failed to get the required memory size for the result hash buffer!");

        goto cleanup_and_out;
    }

    cng_algorithm_object_memory = (PUCHAR) malloc(algorithm_object_required_memory);

    if (!cng_algorithm_object_memory)
    {
        (void) wcscpy_s(error_message_buf, error_message_buf_tsize, L"Failed to allocate the required memory. Please download more RAM!");

        goto cleanup_and_out;
    }

    hash_out_buf = (PUCHAR)malloc((size_t) hash_out_buf_required_size);

    if (!hash_out_buf)
    {
        (void) wcscpy_s(error_message_buf, error_message_buf_tsize, L"Failed to allocate the required memory for the hash result. Please download more RAM!");

        goto cleanup_and_out;
    }

    create_hash_object_rc = BCryptCreateHash(cng_algorithm_provider_handle,
                                             &cng_algorithm_object_handle,
                                             cng_algorithm_object_memory,
                                             (ULONG)algorithm_object_required_memory,
                                             NULL,
                                             0,
                                             0);

    if (create_hash_object_rc != STATUS_SUCCESS)
    {
        (void) wcscpy_s(error_message_buf, error_message_buf_tsize, L"Internal error: Failed to create the Win32 CNG hash object!");

        goto cleanup_and_out;
    }

    ret.is_ok = TRUE;
    ret.cng_algorithm_provider_handle = cng_algorithm_provider_handle; cng_algorithm_provider_handle = NULL;
    ret.cng_algorithm_object_memory = cng_algorithm_object_memory; cng_algorithm_object_memory = NULL;
    ret.hash_out_buf = hash_out_buf; hash_out_buf = NULL;
    ret.hash_out_buf_size = (size_t) hash_out_buf_required_size;
    ret.cng_algorithm_object_handle = cng_algorithm_object_handle; cng_algorithm_object_handle = NULL;

cleanup_and_out:
    if (cng_algorithm_object_handle)
    {
        (void) BCryptDestroyHash(cng_algorithm_object_handle);
    }

    if (hash_out_buf)
    {
        free((void*) hash_out_buf);
    }

    if (cng_algorithm_object_memory)
    {
        free((void*) cng_algorithm_object_memory);
    }

    if (cng_algorithm_provider_handle)
    {
        (void) BCryptCloseAlgorithmProvider(cng_algorithm_provider_handle, 0);
    }

    return ret;
}

static
void
uhashtools_win_cng_hash_impl_destroy
(
    struct PreparedWinCngHasherImpl* prepared_hasher_impl
)
{
    if (!prepared_hasher_impl || !prepared_hasher_impl->is_ok)
    {
        return;
    }

    (void) BCryptDestroyHash(prepared_hasher_impl->cng_algorithm_object_handle);
    free((void*) prepared_hasher_impl->hash_out_buf);
    free((void*) prepared_hasher_impl->cng_algorithm_object_memory);
    (void) BCryptCloseAlgorithmProvider(prepared_hasher_impl->cng_algorithm_provider_handle, 0);

    (void) SecureZeroMemory(prepared_hasher_impl, sizeof *prepared_hasher_impl);
    prepared_hasher_impl->is_ok = FALSE;
}

static
void
uhashtools_report_current_calculation_progress
(
    unsigned int current_calculation_progress,
    OnProgressCallbackFunction* progress_callback,
    void* progress_callback_userdata
)
{
    if (progress_callback)
    {
        progress_callback(current_calculation_progress, progress_callback_userdata);
    }
}

static
BOOL
uhashtools_check_is_cancelled
(
    CheckIsCancelRequestedCallbackFunction* check_is_cancel_requested_callback,
    void* check_is_cancel_requested_callback_userdata
)
{
    if (!check_is_cancel_requested_callback)
    {
        return FALSE;
    }

    return check_is_cancel_requested_callback(check_is_cancel_requested_callback_userdata);
}

enum HashCalculatorResultCode
uhashtools_hash_calculator_impl_hash_file
(
    wchar_t* result_string_buf,
    size_t result_string_buf_tsize,
    const wchar_t* target_file,
    CheckIsCancelRequestedCallbackFunction* check_is_cancel_requested_callback,
    void* check_is_cancel_requested_callback_userdata,
    OnProgressCallbackFunction* progress_callback,
    void* progress_callback_userdata
)
{
    enum HashCalculatorResultCode ret = HashCalculatorResultCode_FAILED;
    struct OpenedTargetFile opened_target_file;
    struct PreparedWinCngHasherImpl prepared_hasher_impl;
    BOOL hash_calculation_finished = FALSE;
    BOOL hash_calculation_failed = FALSE;
    BOOL cancel_requested = FALSE;
    unsigned char file_read_buf[FILE_READ_BUF_SIZE];
    unsigned __int64 processed_bytes = 0;
    unsigned int last_reported_calculation_progress = 0;

    UHASHTOOLS_ASSERT(result_string_buf, L"Internal error: result_string_buf is NULL");
    UHASHTOOLS_ASSERT(result_string_buf_tsize >= 256, L"Internal error: result_string_buf_tsize is to small. The buffer must fit at minimum 256 elements!");
    UHASHTOOLS_ASSERT(target_file, L"Internal error: target_file is NULL");

    (void) SecureZeroMemory(result_string_buf, result_string_buf_tsize * (sizeof *result_string_buf));
    (void) SecureZeroMemory(&opened_target_file, sizeof opened_target_file);
    (void) SecureZeroMemory(&prepared_hasher_impl, sizeof prepared_hasher_impl);

    opened_target_file = uhashtools_target_file_open(result_string_buf, result_string_buf_tsize, target_file);

    if (!opened_target_file.is_ok)
    {
        goto cleanup_and_out;
    }

    prepared_hasher_impl = uhashtools_win_cng_hash_impl_prepare(result_string_buf, result_string_buf_tsize);

    if (!prepared_hasher_impl.is_ok)
    {
        goto cleanup_and_out;
    }

    cancel_requested = uhashtools_check_is_cancelled(check_is_cancel_requested_callback,
                                                  check_is_cancel_requested_callback_userdata);

    while (!hash_calculation_finished && !hash_calculation_failed && !cancel_requested)
    {
        BOOL reached_eof = FALSE;
        size_t read_characters = 0;
        NTSTATUS hash_data_rc = 0;
        unsigned int current_calculation_progress = 0;

        read_characters = fread_s((void*) file_read_buf,
                                  FILE_READ_BUF_SIZE,
                                  sizeof(unsigned char),
                                  FILE_READ_BUF_SIZE,
                                  opened_target_file.target_file_handle);

        if (read_characters != FILE_READ_BUF_SIZE)
        {
            if (ferror(opened_target_file.target_file_handle))
            {
                (void) wcscpy_s(result_string_buf, result_string_buf_tsize, L"Failed to read the selected file!");
                hash_calculation_failed = TRUE;

                break;
            }
            else if (feof(opened_target_file.target_file_handle))
            {
                reached_eof = TRUE;
            }
        }

        hash_data_rc = BCryptHashData(prepared_hasher_impl.cng_algorithm_object_handle,
                                      file_read_buf,
                                      (ULONG) read_characters,
                                      0);

        if (hash_data_rc != STATUS_SUCCESS)
        {
            (void) wcscpy_s(result_string_buf, result_string_buf_tsize, L"Internal error: Failed to hash the selected file. BCryptHashData() failed!");
            hash_calculation_failed = TRUE;

            break;
        }

        processed_bytes += read_characters;
        current_calculation_progress = uhashtools_calculate_current_progress(opened_target_file.target_file_size, processed_bytes);

        if (current_calculation_progress > last_reported_calculation_progress)
        {
            uhashtools_report_current_calculation_progress(current_calculation_progress, progress_callback, progress_callback_userdata);

            last_reported_calculation_progress = current_calculation_progress;
        }

        if (reached_eof)
        {
            NTSTATUS finish_hash_rc = 0;
            BOOL encode_hash_to_hex_rc = FALSE;

            finish_hash_rc = BCryptFinishHash(prepared_hasher_impl.cng_algorithm_object_handle,
                                              prepared_hasher_impl.hash_out_buf,
                                              (ULONG) prepared_hasher_impl.hash_out_buf_size,
                                              0);

            if (finish_hash_rc != STATUS_SUCCESS)
            {
                (void) wcscpy_s(result_string_buf, result_string_buf_tsize, L"Internal error: Failed to hash the selected file. BCryptFinishHash() failed!");
                hash_calculation_failed = TRUE;

                break;
            }

            encode_hash_to_hex_rc = uhashtools_encode_bytes_to_hex(prepared_hasher_impl.hash_out_buf,
                                                                prepared_hasher_impl.hash_out_buf_size,
                                                                result_string_buf,
                                                                result_string_buf_tsize);

            if (!encode_hash_to_hex_rc)
            {
                (void) wcscpy_s(result_string_buf, result_string_buf_tsize, L"Internal error: Failed to hash the selected file. Encoding the hash result to hex failed!");
                hash_calculation_failed = TRUE;

                break;
            }

            hash_calculation_finished = TRUE;
            break;
        }

        cancel_requested = uhashtools_check_is_cancelled(check_is_cancel_requested_callback,
                                                      check_is_cancel_requested_callback_userdata);
    }

    UHASHTOOLS_ASSERT(hash_calculation_finished || hash_calculation_failed || cancel_requested, L"Internal error: Exited hashing loop with unexpected state!");

    if (hash_calculation_finished)
    {
        ret = HashCalculatorResultCode_SUCCESS;
    }
    else if (cancel_requested)
    {
        (void) wcscpy_s(result_string_buf, result_string_buf_tsize, L"Received cancel request!");

        ret = HashCalculatorResultCode_CANCELED;
    }
    else if (hash_calculation_failed)
    {
        ret = HashCalculatorResultCode_FAILED;
    }

cleanup_and_out:
    if (prepared_hasher_impl.is_ok)
    {
        uhashtools_win_cng_hash_impl_destroy(&prepared_hasher_impl);
    }

    if (opened_target_file.is_ok)
    {
        uhashtools_target_file_close(&opened_target_file);
    }

    return ret;
}