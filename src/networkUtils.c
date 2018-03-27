#include "networkUtils.h"

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

char *getInterfaceAttachedIpv4Ip (char *ifName)
{
    int          fd;
    struct ifreq ifr;
    char         *ip;

    char         *ip_address;
    int          ip_address_len;

    if (ifName == NULL) {
        return NULL;
    }

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        return NULL;
    }

    /* Get an IPv4 IP */
    ifr.ifr_addr.sa_family = AF_INET;

    /* Get IP address attached to <ifName> */
    strncpy(ifr.ifr_name, ifName, IFNAMSIZ-1);
    if (ioctl(fd, SIOCGIFADDR, &ifr) != 0) {
        close(fd);
        return NULL;
    }
    close(fd);

    ip = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
    ip_address_len = strlen(ip);
    ip_address = malloc(sizeof(char) * (ip_address_len + 1));
    strncpy(ip_address, ip, ip_address_len + 1);

    return ip_address;
}

