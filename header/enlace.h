#ifndef __TCP_IP_STACK_ENLACE__
#define __TCP_IP_STACK_ENLACE__

#include "common.h"
#include "arp.h"

#define ETHER_TYPE_IPV4      0x0800
#define ETHER_TYPE_IPV6      0x86DD
#define ETHER_TYPE_ARP       0x0806


#define BUFFER_SIZE  (4 * 1024)
#define TAP_NAME     "tap0"


#define PRINT_MAC(mac, name) printf( \
        "MAC %s: %X%X%X%X%X%X\n",    \
        name,   \
        mac[0], \
        mac[1], \
        mac[2], \
        mac[3], \
        mac[4], \
        mac[5]) \


struct eth_frame {
    unsigned char dmac[6];
    unsigned char smac[6];
    unsigned short eth_type;
    unsigned char payload[1500];
} __attribute__((packed));


void eth_alloc_tap(char *dev);
void eth_handle_packet(struct eth_frame * ethframe);

struct eth_frame * eth_read();

#endif