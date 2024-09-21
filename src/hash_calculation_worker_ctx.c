/*
 * This file is part of µHashtools.
 * µHashtools is a small graphical file hashing tool for Microsoft Windows.
 * 
 * SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "hash_calculation_worker_ctx.h"

#include "error_utilities.h"

#include <string.h>

void
uhashtools_hash_calculation_worker_ctx_init
(
    struct HashCalculationWorkerCtx* worker_ctx,
    const struct HashCalculationWorkerParam* worker_param
)
{
    UHASHTOOLS_ASSERT(worker_ctx,
                      L"Internal error (invalid argument): Argument 'worker_ctx' is a null pointer!");
    
    (void) memset((void*) worker_ctx, 0, sizeof *worker_ctx);

    worker_ctx->calculation_result_string_tsize = GENERIC_TXT_MESSAGES_BUFFER_TSIZE;
    worker_ctx->file_read_buf_tsize = FILE_READ_BUF_TSIZE;

    worker_ctx->event_message_target.event_message_receiver = worker_param->event_message_receiver;
    worker_ctx->event_message_target.receiver_event_message_buf = worker_param->event_message_buf;
    worker_ctx->event_message_target.receiver_event_message_buf_is_writeable_event = worker_param->event_message_buf_is_writeable_event;

    worker_ctx->on_progress_cb_args.event_message_target = &worker_ctx->event_message_target;
    worker_ctx->on_progress_cb_args.sender_event_message_buf = &worker_ctx->event_message_buf;
}
