/**
 * ============================================================
 * 
 *      filename:  main.c
 * 
 *   Description:  This file is entry point of tcp/ip stack
 * 
 *       Version:  0.1
 *       Created:  19/02/2023 22:30 PM
 *      Compiler:  gcc
 *      Platform:  Linux
 * 
 *        Author:  Edmar Sousa
 * 
 * ============================================================
 */

#include "device.h"
#include "enlace.h"


int main()
{
    struct net_device * device = init_device("tap0", "10.0.0.6", "1C:44:F5:AA:12:DD");

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    while ( 1 )
    {
        struct eth_frame * frame = eth_read(device->fd, buffer);

        if ( frame != NULL )
            eth_handle_packet(device, frame);
    }

    return 0;
}
