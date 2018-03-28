#ifndef _IGMPTOOL_H__
#define _IGMPTOOL_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef void* fa_igmp_handler_t;

/*
 * Function: fa_igmp_hdl_create
 * ----------------------------
 *   Create fa igmp handler.
 *
 *   returns: fa igmp handler
 */
fa_igmp_handler_t fa_igmp_hdl_create ();

/*
 * Function: fa_igmp_hdl_destroy
 * ----------------------------
 *   Destroy fa igmp handler, this funcion will set p_hdl to NULL.
 *
 *   p_hdl: poiner to fa igmp handler
 */
void fa_igmp_hdl_destroy (fa_igmp_handler_t *p_hdl);

/*
 * Function: fa_igmptool_join
 * ----------------------------
 *   Join igmp group.
 *
 *   i_hdl: igmp handler
 *   ip   : joint group ip
 *   port : binded port
 *
 *   returns: On success, 0 is returned. If the input is invalid, -1 is returned.
 */
int fa_igmp_join(fa_igmp_handler_t i_hdl, char *ip, uint16_t port);

/*
 * Function: fa_igmptool_leave
 * ----------------------------
 *   Leave IGMP group.
 *
 *   i_hdl: igmp handler
 *
 *   returns: On success, 0 is returned. If the input is invalid, -1 is returned.
 */
int fa_igmp_leave(fa_igmp_handler_t i_hdl);

#endif

