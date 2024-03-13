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

#pragma once

#include <Windows.h>

#include "buffer_sizes.h"

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
	wchar_t* result_string_buf,
	size_t result_string_buf_tsize,
	const wchar_t* target_file,
	CheckIsCancelRequestedCallbackFunction* check_is_cancel_requested_callback,
	void* check_is_cancel_requested_callback_userdata,
	OnProgressCallbackFunction* progress_callback,
	void* progress_callback_userdata
);
