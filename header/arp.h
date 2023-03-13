#ifndef __TCP_IP_STACK_ARP__
#define __TCP_IP_STACK_ARP__

#include "common.h"
#include "device.h"

#define ARP_REQUEST     0x0001
#define ARP_RESPONSE    0x0002

#define ETHERNET_HR     0x0001

#define ARP_PRO_IPV4    0x0800  // Protocol address space


struct arp_packet {
    unsigned short hrd;         // hardware address space
    unsigned short pro;         // protocol address space
    unsigned char hln;          // byte length of each hardware address
    unsigned char pln;          // byte length of each protocol address
    unsigned short op;          // opcode $REQUEST or $REPLY
    unsigned char payload[];
} __attribute__((packed));


struct arp_ipv4 {
    unsigned char smac[6];
    unsigned int sip;

    unsigned char dmac[6];
    unsigned int dip;
} __attribute__((packed));

void arp_handle_packet(struct net_device * device, unsigned char * payload);

#endif