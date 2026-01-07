#ifndef __RWNX_TX_H__
#define __RWNX_TX_H__
#include <lwip/opt.h>
#include <lwip/mem.h>
#include <utils_list.h>

#include "lmac_types.h"
#include "ipc_shared.h"
#include "bl_utils.h"

/**
 ****************************************************************************************
 *
 * @file bl_tx.h
 * Copyright (C) Bouffalo Lab 2016-2018
 *
 ****************************************************************************************
 */

typedef void (*bl_custom_tx_callback_t)(void *cb_arg, bool tx_ok);

struct bl_custom_tx_cfm {
    bl_custom_tx_callback_t cb;
    void *cb_arg;
};

/**
 * struct bl_txhdr - Stucture to control transimission of packet
 * (Added in skb headroom)
 *
 * @sw_hdr: Information from driver
 * @hw_hdr: Information for/from hardware
 */
union bl_hw_txstatus {
    struct {
        u32 tx_done            : 1;
        u32 retry_required     : 1;
        u32 sw_retry_required  : 1;
        u32 reserved           :29;
    };
    u32 value;
};
struct bl_txhdr {
    struct utils_list_hdr item;
    union bl_hw_txstatus status;
    uint32_t *p;
    struct hostdesc host;
    struct bl_custom_tx_cfm custom_cfm;
};

err_t bl_output(struct bl_hw *bl_hw, struct netif *netif, struct pbuf *p, int is_sta, struct bl_custom_tx_cfm *custom_cfm);
int bl_wifi_eth_tx(struct pbuf *p, bool is_sta, struct bl_custom_tx_cfm *custom_cfm);
int bl_txdatacfm(void *pthis, void *host_id);
void bl_tx_try_flush();
void bl_irq_handler();
int bl_tx_find_sta_by_mac(uint8_t vif_idx, struct mac_addr *mac);
err_t bl_tx_intra_bss_forward(struct pbuf *p, int dst_sta_idx);
err_t bl_tx_intra_bss_broadcast(struct pbuf *p, int src_sta_idx);
#endif
