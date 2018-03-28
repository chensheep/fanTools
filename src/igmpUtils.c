#include "igmpUtils.h"

struct fa_igmp_handler_t
{
    int      sockFd;
    char     ipv4Ip[16];
    uint16_t port;
};

fa_igmp_handler_t fa_igmp_hdl_create ()
{
    struct fa_igmp_handler_t *hdl = malloc (1 * sizeof(*hdl));

    hdl->sockFd = -1;
    memset(hdl->ipv4Ip, '\0', sizeof(hdl->ipv4Ip)/sizeof(char));
    hdl->port = -1;

    return (void*) hdl;
}

void fa_igmp_hdl_destroy (fa_igmp_handler_t *p_hdl)
{
    struct fa_igmp_handler_t *hdl;

    if (p_hdl == NULL) {
        return;
    }

    if (*p_hdl == NULL) {
        return;
    }

    hdl = (struct fa_igmp_handler_t *) *p_hdl;

    if (hdl->sockFd != -1) {
        close(hdl->sockFd);
    }
    free(hdl);

    hdl = NULL;
    *p_hdl = NULL;
}

int fa_igmp_join (fa_igmp_handler_t i_hdl, char *jointIp, uint16_t port)
{
    struct fa_igmp_handler_t *hdl;
    int                    ret;
    struct sockaddr_in     serverAddr;
    struct ip_mreq         mreq;
    int                    sockReuseOption = 1;

    if (i_hdl == NULL || jointIp == NULL || port <= 0) {
        perror("[INFO] igmp_join:: input parameter is illegal.");
        return -1;
    }

    hdl = (struct fa_igmp_handler_t *) i_hdl;

    printf("[INFO] igmp_join:: TO join IGMP channel %s on port %"PRIu16"\n", jointIp, port);

    strncpy(hdl->ipv4Ip, jointIp, strlen(jointIp) + 1);
    hdl->port = port;;

    hdl->sockFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (hdl->sockFd < 0) {
        perror("[ERRO] igmp_join:: created socket unsucessfully.");
        return -1;
    }

    ret = setsockopt(hdl->sockFd, SOL_SOCKET, SO_REUSEADDR, (void*)&sockReuseOption, sizeof(sockReuseOption));
    if (ret < 0) {
        perror("[ERRO] igmp_join:: set socket option SO_REUSEADDR unsucessfully.");
        close(hdl->sockFd);
        return -1;
    }


    memset(&mreq, 0, sizeof(mreq));
    memset(&serverAddr, 0, sizeof(serverAddr));


    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, hdl->ipv4Ip, &(serverAddr.sin_addr)) != 1) {
        perror("[ERRO] igmp_join:: Server address not identifided.");
        close(hdl->sockFd);
        return -1;
    }
    ret = bind(hdl->sockFd, (struct sockaddr *)(&serverAddr), sizeof(serverAddr));
    if (ret < 0) {
        perror("[ERRO] igmp_join:: binded socket unsucessfully.");
        close(hdl->sockFd);
        return -1;
    }


    if (inet_pton(AF_INET, hdl->ipv4Ip, &(mreq.imr_multiaddr)) != 1) {
        perror("[ERRO] igmp_join:: Server address not identifided.");
        close(hdl->sockFd);
        return -1;
    }
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    ret = setsockopt(hdl->sockFd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    if (0 != ret) {
        perror("[ERRO] igmp_join:: set socket option IP_ADD_MEMBERSHIP unsucessfully.");
        close(hdl->sockFd);
        return -1;
    }

    return 0;
}

int fa_igmp_leave (fa_igmp_handler_t i_hdl)
{
    int                    ret;
    struct fa_igmp_handler_t *hdl;
    struct ip_mreq         mreq;

    if (i_hdl == NULL) {
        return -1;
    }

    hdl = (struct fa_igmp_handler_t *) i_hdl;

    memset(&mreq, 0, sizeof(mreq));
    if (inet_pton(AF_INET, hdl->ipv4Ip, &(mreq.imr_multiaddr)) != 1) {
        return -1;
    }

    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    ret = setsockopt(hdl->sockFd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
    if (0 != ret) {
        perror("[ERRO] fa_igmp_leave:: set socket option IP_DROP_MEMBERSHIP unsucessfully.");
        return -1;
    }

    return 0;
}

