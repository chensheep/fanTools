#include <stdlib.h>
#include <stdio.h>

#include "networkUtils.h"

static char *ifnList[] = {
    "eth0",
    "wlan",
    "abcde",
    ""
};

void main (void)
{
    int i;
    char *ip;

    for (i=0; i < sizeof(ifnList)/sizeof(char*); i++) {
        if ((ip = getInterfaceAttachedIpv4Ip(ifnList[i])) != NULL) {
            printf("[INFO] Interface '%s' ip '%s'.\n", ifnList[i], ip);
            free(ip);
        } else {
            printf("[ERRO] Interface '%s' not attached ip.\n", ifnList[i]);
        }
    }
}
