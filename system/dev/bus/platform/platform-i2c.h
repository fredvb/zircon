// Copyright 2018 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <ddk/protocol/i2c.h>
#include <lib/sync/completion.h>
#include <zircon/listnode.h>
#include <threads.h>

typedef struct pdev_req pdev_req_t;

typedef struct platform_i2c_bus {
    i2c_impl_protocol_t i2c;
    uint32_t bus_id;
    size_t max_transfer;

    list_node_t queued_txns;
    list_node_t free_txns;
    sync_completion_t txn_signal;

    thrd_t thread;
    mtx_t lock;
} platform_i2c_bus_t;

zx_status_t platform_i2c_init(platform_bus_t* bus, i2c_impl_protocol_t* i2c);
zx_status_t platform_i2c_transact(platform_bus_t* bus, pdev_req_t* req, pbus_i2c_channel_t* channel,
                                  const void* write_buf, zx_handle_t channel_handle);
