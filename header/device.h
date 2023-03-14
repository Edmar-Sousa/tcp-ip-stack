#ifndef  __TCP_IP_STACK_DEVICE__
#define  __TCP_IP_STACK_DEVICE__

#include "common.h"

struct net_device {
    int fd;
    unsigned char name[IFNAMSIZ];
    unsigned char mac[6];
    unsigned int ip;
};


struct net_device * init_device(char * name, unsigned char * ip, unsigned char * mac);

#endif