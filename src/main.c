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
    eth_alloc_tap(TAP_NAME);

    while (1) {
        struct eth_frame * ethframe = eth_read();
        eth_handle_packet(ethframe);
    }

    return 0;
}
