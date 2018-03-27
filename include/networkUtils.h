#ifndef _NETWORKUTILS_H
#define _NETWORKUTILS_H

#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
 * Function: getInterfaceAttachedIpv4Ip
 * ----------------------------
 *   Returns the Ipv4 Ip of particular interface
 *   The called must call free() to free the C string later on.
 *
 *   ifn: interface name
 *
 *   returns: zero terminated C string with ipv4 address attatched on interface or NULL if ipv4 Ip not attached
 */

char *getInterfaceAttachedIpv4Ip (char *ifName);

#endif
