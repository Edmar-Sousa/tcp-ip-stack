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

#include "enlace.h"


int main()
{
    int fd = eth_alloc_tap(TAP_NAME);

    char buffer[BUFFER_SIZE];
    struct eth_frame ethframe;

    while (1) {
        ssize_t count = read(fd, buffer, BUFFER_SIZE);

        if ( count < 0 )
        {
            printf("main(): Error read ethernet frame.\n");
            return 1;
        }

        memcpy(&ethframe, buffer, sizeof(struct eth_frame));

        eth_handle_packet(&ethframe);
    }

    return 0;
}
