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


static unsigned char * arp_reply(struct net_device * device, struct arp_packet * arppacket)
{
    struct arp_ipv4 * ipv4_packet = (struct arp_ipv4 *) arppacket->payload;

    strncpy(ipv4_packet->dmac, ipv4_packet->smac, 6);
    ipv4_packet->dip = ipv4_packet->sip;

    arppacket->op = ntohs(ARP_RESPONSE);

    strncpy(ipv4_packet->smac, device->mac, 6);
    ipv4_packet->sip = device->ip;

    arppacket->hrd = ntohs(arppacket->hrd);
    arppacket->pro = ntohs(arppacket->pro);
}


void arp_handle_packet(struct net_device * device, unsigned char * payload)
{
    struct arp_packet * arppacket = (struct arp_packet *) payload;

    arppacket->op = htons(arppacket->op);
    arppacket->hrd = htons(arppacket->hrd);
    arppacket->pro = htons(arppacket->pro);

    if (arppacket->hrd != ETHERNET_HR)
    {
        printf("process_arp_packet(): The hardware type is not suported\n");
        return;
    }

    if (arppacket->pro != ARP_PRO_IPV4)
    {
        printf("process_arp_packet(): The protocol type is not suported\n");
        return;
    }

    switch (arppacket->op)
    {
        case ARP_REQUEST:
            arp_reply(device, arppacket);
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


