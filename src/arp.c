/**
 * ============================================================
 * 
 *      filename:  arp.c
 * 
 *   Description:  This file provide functions to ARP
 *                 protocol
 * 
 *       Version:  0.1
 *       Created:  08/03/2023 20:30 PM
 *      Compiler:  Gcc
 *      Platform:  Linux
 * 
 *        Author:  Edmar Sousa
 * 
 * ============================================================
 */


#include "arp.h"



void handle_arp_packet(unsigned char * payload)
{
    struct arp_packet arppacket;
    memcpy(&arppacket, payload, sizeof(struct arp_packet));

    uint16_t op = htons(arppacket.op);
}
