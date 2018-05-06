#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "cpu.h"

struct cpu_load
{
        uint64_t user;
        uint64_t nice;
        uint64_t system;
        uint64_t idle;
};

int32_t get_cpu_freq(void)
{
        FILE *fp;
        char buffer[256];
        char *match;
        size_t bytes_read;
        int32_t clock_speed;

        fp = fopen("/proc/cpuinfo", "r");
        bytes_read = fread(buffer, 1, sizeof(buffer), fp);
        fclose(fp);

        buffer[bytes_read] = '\0';

        match = strstr(buffer, "cpu MHz");
        if(match == NULL)
                return -1;

        sscanf(match, "cpu MHz : %" SCNi32, &clock_speed);

        return (clock_speed);
}

int32_t get_cpu_temp(void)
{
        FILE *fp;
        uint32_t temperature;

        fp = fopen(CPU_TEMP_FILE, "r");

        if(fp == NULL)
        {
                fprintf(stderr, "CPU_TEMP_FILE config wrong");
                temperature = -1;
        }
        else
        {
                fscanf(fp, "%" SCNi32, &temperature);
                temperature /= 1000;
        }

        fclose(fp);

        return (temperature);
}

int32_t get_cpu_usage(void)
{
        FILE *fp;
        int32_t cpu_usage;
        uint64_t tmp;

        static struct cpu_load load_old;
        struct cpu_load load;

        fp = fopen("/proc/stat", "r");

        fscanf(fp, "%*s %" SCNu64 "%" SCNu64 "%" SCNu64 "%" SCNu64, &load.user,
               &load.nice, &load.system, &load.idle);

        fclose(fp);

        if(load_old.user == 0)
        {
                cpu_usage = 0;
        }
        else
        {
                tmp = (load.user + load.nice + load.system) -
                      (load_old.user + load_old.nice + load_old.system);

                cpu_usage = (100 * tmp) / ((tmp + load.idle) - load_old.idle);
        }

        load_old = load;

        return (cpu_usage);
}
