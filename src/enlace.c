/**
 * ============================================================
 * 
 *      filename:  enlace.c
 * 
 *   Description:  This file use tun/tap devices to 
 *                 read and write ethernet frames and
 *                 decided if frame is passed to ARP
 *                 protocol or IP protocol
 * 
 *       Version:  0.1
 *       Created:  19/02/2023 22:30 PM
 *      Compiler:  Gcc
 *      Platform:  Linux
 * 
 *        Author:  Edmar Sousa
 * 
 * ============================================================
 */


#include "enlace.h"


void eth_handle_packet(struct net_device * device, struct eth_frame * ethframe)
{
    ethframe->eth_type = htons(ethframe->eth_type);

    switch (ethframe->eth_type)
    {
        case ETHER_TYPE_ARP:
            arp_handle_packet(device, ethframe->payload);
            eth_write(device, ethframe);
            break;
        
        case ETHER_TYPE_IPV4:
            printf("IPV4: %X\n", ethframe->eth_type);
            break;

        case ETHER_TYPE_IPV6:
            printf("IPV6: %X\n", ethframe->eth_type);
            break;

        default:
            printf("ANY: Package not found \"%X\"\n", ethframe->eth_type);
            break;
    }
}


struct eth_frame * eth_read(int fd, char * buf)
{
    ssize_t count = read(fd, buf, BUFFER_SIZE);

    if ( count < -1 ) 
    {
        printf("eth_read(): Error read frame\n");
        return NULL;
    }

    struct eth_frame * frame = (struct eth_frame *) buf;
    return frame;
}


void eth_write(struct net_device * device, struct eth_frame * ethframe)
{
    strncpy(ethframe->dmac, ethframe->smac, 6);
    strncpy(ethframe->smac, device->mac, 6);

    ethframe->eth_type = ntohs(ethframe->eth_type);

    if ( write(device->fd, (char *) ethframe, BUFFER_SIZE) < 0 )
        printf("eth_write(): Error write frame\n");
}
