/*
 * Copyright (c) 2023 Silicon Laboratories Inc. (www.silabs.com)
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of the Silicon Labs Master Software License
 * Agreement (MSLA) available at [1].  This software is distributed to you in
 * Object Code format and/or Source Code format and is governed by the sections
 * of the MSLA applicable to Object Code, Source Code and Modified Open Source
 * Code. By using this software, you agree to the terms of the MSLA.
 *
 * [1]: https://www.silabs.com/about-us/legal/master-software-license-agreement
 */
#include "stack/mac/fhss_ws_extension.h"
#include "common/iobuf.h"
#include "common/spinel_defs.h"
#include "common/spinel_buffer.h"

#include "wsbr_mac.h"
#include "wsbr.h"
#include "rcp_api.h"

static void rcp_set_bool(unsigned int prop, bool val)
{
    struct wsbr_ctxt *ctxt = &g_ctxt;
    struct iobuf_write buf = { };

    spinel_push_hdr_set_prop(ctxt, &buf, prop);
    spinel_push_bool(&buf, val);
    rcp_tx(ctxt, &buf);
    iobuf_free(&buf);
}

static void rcp_set_u8(unsigned int prop, uint8_t val)
{
    struct wsbr_ctxt *ctxt = &g_ctxt;
    struct iobuf_write buf = { };

    spinel_push_hdr_set_prop(ctxt, &buf, prop);
    spinel_push_u8(&buf, val);
    rcp_tx(ctxt, &buf);
    iobuf_free(&buf);
}

static void rcp_set_u16(unsigned int prop, uint16_t val)
{
    struct wsbr_ctxt *ctxt = &g_ctxt;
    struct iobuf_write buf = { };

    spinel_push_hdr_set_prop(ctxt, &buf, prop);
    spinel_push_u16(&buf, val);
    rcp_tx(ctxt, &buf);
    iobuf_free(&buf);
}

static void rcp_set_u32(unsigned int prop, uint32_t val)
{
    struct wsbr_ctxt *ctxt = &g_ctxt;
    struct iobuf_write buf = { };

    spinel_push_hdr_set_prop(ctxt, &buf, prop);
    spinel_push_u32(&buf, val);
    rcp_tx(ctxt, &buf);
    iobuf_free(&buf);
}

static void rcp_set_eui64(unsigned int prop, const uint8_t val[8])
{
    struct wsbr_ctxt *ctxt = &g_ctxt;
    struct iobuf_write buf = { };

    spinel_push_hdr_set_prop(ctxt, &buf, prop);
    spinel_push_fixed_u8_array(&buf, val, 8);
    rcp_tx(ctxt, &buf);
    iobuf_free(&buf);
}


void rcp_set_fhss_neighbor(const uint8_t neigh[8],
                           const struct fhss_ws_neighbor_timing_info *timing_info)
{
    struct wsbr_ctxt *ctxt = &g_ctxt;
    struct iobuf_write buf = { };

    spinel_push_hdr_set_prop(ctxt, &buf, SPINEL_PROP_WS_FHSS_UPDATE_NEIGHBOR);
    spinel_push_fixed_u8_array(&buf, neigh, 8);
    spinel_push_u8(&buf, timing_info->clock_drift);
    spinel_push_u8(&buf, timing_info->timing_accuracy);
    spinel_push_u16(&buf, timing_info->uc_channel_list.channel_count);
    spinel_push_fixed_u8_array(&buf, timing_info->uc_channel_list.channel_mask, 32);
    spinel_push_u8(&buf, timing_info->uc_timing_info.unicast_channel_function);
    spinel_push_u8(&buf, timing_info->uc_timing_info.unicast_dwell_interval);
    spinel_push_u16(&buf, timing_info->uc_timing_info.unicast_number_of_channels);
    spinel_push_u16(&buf, timing_info->uc_timing_info.fixed_channel);
    spinel_push_u32(&buf, timing_info->uc_timing_info.ufsi);
    spinel_push_u32(&buf, timing_info->uc_timing_info.utt_rx_timestamp);
    rcp_tx(ctxt, &buf);
    iobuf_free(&buf);
}
void rcp_drop_fhss_neighbor(const uint8_t eui64[8])
{
    struct wsbr_ctxt *ctxt = &g_ctxt;
    struct iobuf_write buf = { };

    spinel_push_hdr_set_prop(ctxt, &buf, SPINEL_PROP_WS_FHSS_DROP_NEIGHBOR);
    spinel_push_fixed_u8_array(&buf, eui64, 8);
    rcp_tx(ctxt, &buf);
    iobuf_free(&buf);
}

void rcp_set_fhss_hop_count(int hop_count)
{
    rcp_set_u8(SPINEL_PROP_WS_FHSS_SET_HOP_COUNT, hop_count);
}
