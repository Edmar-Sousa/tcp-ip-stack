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

static void process_arp_packet(struct arp_packet * arppacket)
{
    if (htons(arppacket->hrd) != ETHERNET_HR)
    {
        printf("process_arp_packet(): The hardware type is not suported\n");
        exit(EXIT_FAILURE);
    }

    printf("arp hdr: %x\n", htons(arppacket->hrd));
}



void handle_arp_packet(unsigned char * payload)
{
    struct arp_packet arppacket;
    memcpy(&arppacket, payload, sizeof(struct arp_packet));

    uint16_t op = htons(arppacket.op);
    
    switch (op)
    {
        case ARP_REQUEST:
            process_arp_packet(&arppacket);
            break;

        default:
            printf("ARP opcode invalid\n");
            break;
    }
}

/*
  ?Do I speak the protocol in ar$pro?
  Yes:
    [optionally check the protocol length ar$pln]
    Merge_flag := false
    If the pair <protocol type, sender protocol address> is
        already in my translation table, update the sender
        hardware address field of the entry with the new
        information in the packet and set Merge_flag to true.
    ?Am I the target protocol address?
    Yes:
      If Merge_flag is false, add the triplet <protocol type,
          sender protocol address, sender hardware address> to
          the translation table.
      ?Is the opcode ares_op$REQUEST?  (NOW look at the opcode!!)
      Yes:
        Swap hardware and protocol fields, putting the local
            hardware and protocol addresses in the sender fields.
        Set the ar$op field to ares_op$REPLY
        Send the packet to the (new) target hardware address on
            the same hardware on which the request was received. */


