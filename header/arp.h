#ifndef __TCP_IP_STACK_ARP__
#define __TCP_IP_STACK_ARP__

#include "common.h"


#define ARP_REQUEST     0x0001
#define ARP_RESPONSE    0x0002


struct arp_packet {
    unsigned short hrd;         // hardware address space
    unsigned short pro;         // protocol address space
    unsigned char hln;          // byte length of each hardware address
    unsigned char pln;          // byte length of each protocol address
    unsigned short op;          // opcode $REQUEST or $REPLY
    unsigned char payload[];
} __attribute__((packed));


void handle_arp_packet(unsigned char * payload);

#endif