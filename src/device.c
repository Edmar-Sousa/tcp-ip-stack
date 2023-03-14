/**
 * ============================================================
 * 
 *      filename:  device.c
 * 
 *   Description:  This file contain functions and constants
 *                 to create a device
 * 
 *       Version:  0.1
 *       Created:  12/03/2023 23:24 PM
 *      Compiler:  Gcc
 *      Platform:  Linux
 * 
 *        Author:  Edmar Sousa
 * 
 * ============================================================
 */


#include "device.h"


/**
 *    https://www.kernel.org/doc/Documentation/networking/tuntap.txt
 */
static void alloc_tap_device(char * dev, int * fd)
{
    struct ifreq ifr;
    int err;

    if ( (*fd = open("/dev/net/tap", O_RDWR)) < 0 )
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

    if ( (err = ioctl(*fd, TUNSETIFF, (void *) &ifr)) < 0 )
    {
        printf("alloc_tap(): ioctl error.\n");
        exit(EXIT_FAILURE);
    }

    #ifdef DEBUG
    printf("TAP (%s): started\n", dev);
    #endif
}


struct net_device * init_device(char * name, unsigned char * ip, unsigned char * mac)
{
    struct net_device * device = (struct net_device *) malloc( sizeof(struct net_device) );
    strncpy(device->name, name, IFNAMSIZ);
    
    sscanf(
        mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
        &device->mac[0],
        &device->mac[1],
        &device->mac[2],
        &device->mac[3],
        &device->mac[4],
        &device->mac[5]
    );

    alloc_tap_device( device->name, &device->fd );

    if ( inet_pton(AF_INET, ip, &device->ip) )
        printf("eth_init(): Error convert ip to binary ip\n");

    if ( system("ip link set dev tap0 up") != 0 )
        printf("eth_init(): Error set up\n");


    if ( system("ip route add dev tap0 10.0.0.0/25") != 0 )
        printf("eth_init(): Error set routing\n");
    
    return device;
}
