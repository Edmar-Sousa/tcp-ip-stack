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

struct arp_table_entry table[ARP_TABLE_LENGHT];


static int arp_table_insert(struct arp_ipv4 * ipv4_packet)
{
    for ( struct arp_table_entry * entry = table; entry < &table[ARP_TABLE_LENGHT]; entry++ )
        if ( !entry->ip )
        {
            entry->ip = ipv4_packet->sip;
            strncpy(entry->mac, ipv4_packet->smac, 6);

            return 0;
        }
    

    return 1;
}


static int arp_table_check(struct arp_ipv4 * ipv4_packet) 
{
    for ( struct arp_table_entry * entry = table; entry < &table[ARP_TABLE_LENGHT]; entry++ )
        if ( entry->ip == ipv4_packet->sip )
        {
            strncpy(entry->mac, ipv4_packet->smac, 6);
            return 1;
        }
    
    return 0;
}


static unsigned char * arp_reply(struct net_device * device, struct arp_packet * arppacket, struct arp_ipv4 * ipv4_packet)
{
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
    struct arp_ipv4 * ipv4_packet = (struct arp_ipv4 *) arppacket->payload;

    arppacket->op = htons(arppacket->op);
    arppacket->hrd = htons(arppacket->hrd);
    arppacket->pro = htons(arppacket->pro);

    if ( arppacket->hrd != ETHERNET_HR )
    {
        printf("process_arp_packet(): The hardware type is not suported\n");
        return;
    }

    if ( arppacket->pro != ARP_PRO_IPV4 )
    {
        printf("process_arp_packet(): The protocol type is not suported\n");
        return;
    }

    if ( ipv4_packet->dip != device->ip )
    {
        printf("process_arp_packet(): Operation not suported\n");
        return;
    }

    int merge_flag = arp_table_check(ipv4_packet);

    if ( !merge_flag && arp_table_insert(ipv4_packet) )
    {
        printf("process_arp_packet(): Error add entry on arp table\n");
        return;
    }

    switch ( arppacket->op )
    {
        case ARP_REQUEST: {
            arp_reply(device, arppacket, ipv4_packet);
            break;
        }

        default:
            printf("ARP opcode invalid\n");
            break;
    }
}
