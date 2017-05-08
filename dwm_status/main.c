#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <X11/Xlib.h>

#include "cpu.h"
#include "memory.h"
#include "net.h"
#include "alsa.h"
#include "config.h"



int main(int argc, const char *argv[])
{
        (void)argc;
        (void)argv;

        Display *dpy;
        char msg[100];

        dpy = XOpenDisplay(NULL);

        struct net_bandwidth speed;
        struct tm tm;
        time_t t;

        do
        {
                speed = get_network_speed();
                t = time(NULL);
                tm = *localtime(&t);

                sprintf(msg, "freq: %dMHz "
                             "temp: %" PRIu32 "C "
                             "cpu: %d%% "
                             "ram: %" PRIi64 "MB "
                             "U: %" PRIu32 "kB D: %" PRIu32 "kB "
                             "V: %" PRIi64 "%% "
                             "%02d.%02d. %02d:%02d\n",
                        get_cpu_freq(), get_cpu_temp(), get_cpu_usage(),
                        get_ram_usage(), speed.up, speed.down,
                        get_alsa_volume(), tm.tm_mday, tm.tm_mon + 1,
                        tm.tm_hour, tm.tm_min);

		XStoreName(dpy, DefaultRootWindow(dpy), msg);
		XSync(dpy, False);

        } while(!sleep(DELAY));

        XCloseDisplay(dpy);

        printf("Something happened!");

        return 0;
}
