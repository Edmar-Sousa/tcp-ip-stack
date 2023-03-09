#ifndef __TCP_IP_STACK_ENLACE__
#define __TCP_IP_STACK_ENLACE__

#include "common.h"
#include "arp.h"

#define ETHER_TYPE_IPV4      0x0800
#define ETHER_TYPE_IPV6      0x86DD
#define ETHER_TYPE_ARP       0x0806


struct eth_frame {
    unsigned char dmac[6];
    unsigned char smac[6];
    unsigned short eth_type;
    unsigned char payload[1500];
} __attribute__((packed));


int eth_alloc_tap(char *dev);
void eth_handle_packet(struct eth_frame * ethframe);

#endif