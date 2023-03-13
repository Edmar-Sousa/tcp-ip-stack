#ifndef __TCP_IP_STACK_ENLACE__
#define __TCP_IP_STACK_ENLACE__

#include "common.h"
#include "device.h"
#include "arp.h"

#define ETHER_TYPE_IPV4      0x0800
#define ETHER_TYPE_IPV6      0x86DD
#define ETHER_TYPE_ARP       0x0806


#define BUFFER_SIZE  (4 * 1024)


struct eth_frame {
    unsigned char dmac[6];
    unsigned char smac[6];
    unsigned short eth_type;
    unsigned char payload[];
} __attribute__((packed));



struct eth_frame * eth_read(int fd);

void eth_write(int fd, struct eth_frame * eth_frame);
void eth_handle_packet(struct net_device * device, struct eth_frame * ethframe);

#endif