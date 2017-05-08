#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

#include <sys/sysinfo.h>

static inline int64_t get_ram_cache(void);

static inline int64_t get_ram_cache(void)
{
        char buf[60];
        FILE *fp;
        int64_t cached;

        fp = fopen("/proc/meminfo", "r");

        while(fgets(buf, sizeof(buf), fp) != NULL)
        {
                if(sscanf(buf, "Cached: %" SCNi64 "%*s\n", &cached) == 1)
                        break;
        }
        fclose(fp);

        return cached;
}

int64_t get_ram_usage(void)
{
	struct sysinfo info;
	sysinfo(&info);
	int64_t retval;

	retval = info.freeram + info.bufferram + (1024 * get_ram_cache());

	return (retval / (1024 * 1024));
}

