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

static int fd = -1;


static void print_eth_frame(struct eth_frame * frame)
{
    printf("\nFRAME ETHERNET\nTYPE: %X\n", frame->eth_type);
    PRINT_MAC(frame->dmac, "DEST");
    PRINT_MAC(frame->smac, "SRC");
    print("\n");
}



/**
 *    https://www.kernel.org/doc/Documentation/networking/tuntap.txt
 */
void eth_alloc_tap(char *dev)
{
    struct ifreq ifr;
    int err;

    if ( (fd = open("/dev/net/tap", O_RDWR)) < 0 )
    {
        printf("alloc_tap(): Error init tap device.\n");
        exit(EXIT_FAILURE);
    }

    memset(&ifr, 0, sizeof(ifr));

    /**
     *        IFF_TAP:   Packet with ethernet headers
     *        IFF_TUN:   Packet without ethernet headers
     *      IFF_NO_PI:   Do not provide packet information
     */
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;

    if ( *dev )
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    if ( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 )
    {
        printf("alloc_tap(): ioctl error.\n");
        exit(EXIT_FAILURE);
    }

    #ifdef DEBUG
    printf("TAP (%s): started\n", dev);
    #endif
}


void eth_handle_packet(struct eth_frame * ethframe)
{
    uint16_t frame_type = htons(ethframe->eth_type);

    switch (frame_type)
    {
        case ETHER_TYPE_ARP:
            #ifdef DEBUG
            print_eth_frame(ethframe);
            #endif

            handle_arp_packet(ethframe->payload);
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


struct eth_frame * eth_read()
{
    char buffer[BUFFER_SIZE];
    struct eth_frame * frame = (struct eth_frame *) malloc(sizeof(struct eth_frame));

    if ( frame == NULL )
    {
        free(frame);
        printf("eth_read(): Error create frame\n");
        exit(EXIT_FAILURE);
    }

    ssize_t count = read(fd, buffer, BUFFER_SIZE);

    if ( count < -1 ) 
    {
        printf("eth_read(): Error read frame\n");
        exit(EXIT_FAILURE);
    }

    memcpy(frame, buffer, sizeof(struct eth_frame));
    return frame;
}


void eth_write(unsigned char * payload)
{
    
}