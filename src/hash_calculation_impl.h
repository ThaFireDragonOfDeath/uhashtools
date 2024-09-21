/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "buffer_sizes.h"

#include <Windows.h>

typedef BOOL CheckIsCancelRequestedCallbackFunction(void* userdata);
typedef void OnProgressCallbackFunction(unsigned int current_calculation_progress, void* userdata);

enum HashCalculatorResultCode
{
	HashCalculatorResultCode_SUCCESS,
	HashCalculatorResultCode_CANCELED,
	HashCalculatorResultCode_FAILED
};

extern
enum HashCalculatorResultCode
uhashtools_hash_calculator_impl_hash_file
(
	unsigned char* file_read_buf,
	size_t file_read_buf_tsize,
	wchar_t* result_string_buf,
	size_t result_string_buf_tsize,
	const wchar_t* target_file,
	CheckIsCancelRequestedCallbackFunction* check_is_cancel_requested_callback,
	void* check_is_cancel_requested_callback_userdata,
	OnProgressCallbackFunction* progress_callback,
	void* progress_callback_userdata
);
