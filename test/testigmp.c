#include <stdlib.h>
#include <stdio.h>

#include "igmpUtils.h"

int main (void)
{
    fa_igmp_handler_t igmphdl;

    igmphdl = fa_igmp_hdl_create();

    if (fa_igmp_join(igmphdl, "224.1.4.120", 11111) != 0) {
        perror("fa_igmp_join failed.");
        fa_igmp_hdl_destroy(&igmphdl);
        return 0;
    }

    sleep(10);

    if (fa_igmp_leave(igmphdl) != 0) {
        perror("fa_igmp_leave failed.");
        fa_igmp_hdl_destroy(&igmphdl);
        return 0;
    }

    fa_igmp_hdl_destroy(&igmphdl);

    return 0;
}

