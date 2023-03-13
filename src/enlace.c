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
    uint16_t frame_type = htons(ethframe->eth_type);

    switch (frame_type)
    {
        case ETHER_TYPE_ARP:
            eth_write(device->fd, ethframe);
            arp_handle_packet(device, ethframe->payload);
            eth_write(device->fd, ethframe);
            break;
        
        case ETHER_TYPE_IPV4:
            printf("IPV4: %X\n", ethframe->eth_type);
            break;

        case ETHER_TYPE_IPV6:
            printf("IPV6: %X\n", ethframe->eth_type);
            break;

        default:
            printf("ANY: Package not found \"%X\"\n", frame_type);
            break;
    }
}


struct eth_frame * eth_read(int fd)
{
    char buffer[BUFFER_SIZE];
    ssize_t count = read(fd, buffer, BUFFER_SIZE);

    if ( count < -1 ) 
    {
        printf("eth_read(): Error read frame\n");
        return NULL;
    }

    struct eth_frame * frame = (struct eth_frame *) buffer;
    return frame;
}


void eth_write(int fd, struct eth_frame * eth_frame)
{
    struct arp_packet * arp = (struct arp_packet *) eth_frame->payload;
    printf("ARP OP: %d\n", htons(arp->op));
}
