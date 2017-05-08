#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "net.h"

struct net_bandwidth get_network_speed(void)
{
        static uint64_t recieve_old;
        static uint64_t transmit_old;

        struct net_bandwidth retval;

        FILE *fp;
        char buffer[512];
        char *match;
        size_t bytes_read;
        uint64_t recieve_now;
        uint64_t transmit_now;

        fp = fopen("/proc/net/dev", "r");

        bytes_read = fread(buffer, 1, sizeof(buffer), fp);
        fclose(fp);

        buffer[bytes_read] = '\0';
        match = strstr(buffer, NET_IFACE);

        sscanf(match, NET_IFACE ": %" SCNu64
                                " %*ld %*ld %*ld %*ld %*ld %*ld %*ld %" SCNu64,
               &recieve_now, &transmit_now);

        if(recieve_old == 0)
        {
                retval.up = 0;
                retval.down = 0;
        }
        else
        {
                retval.down = (recieve_now - recieve_old) / 1024 / DELAY;
                retval.up = (transmit_now - transmit_old) / 1024 / DELAY;
        }

        recieve_old = recieve_now;
        transmit_old = transmit_now;

        return (retval);
}

