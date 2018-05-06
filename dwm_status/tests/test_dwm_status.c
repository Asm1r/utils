
#include <unity.h>

#include "config.h"

#include "common.h"
#include "memory.h"
#include "net.h"

#include "alsa.h"
#include "alsa.c"

void test_get_alsa_volume(void)
{

	TEST_ASSERT_INT64_WITHIN(50, 50, get_alsa_volume());
}

#include "cpu.h"
#include "cpu.c"

void test_get_cpu_freq(void)
{
	TEST_ASSERT_GREATER_THAN(0, get_cpu_freq());
}

void test_get_cpu_temp(void)
{
	TEST_ASSERT_INT32_WITHIN(70, 50, get_cpu_temp());
}

void test_get_cpu_usage(void)
{
	TEST_ASSERT_INT32_WITHIN(50, 50, get_cpu_usage());
}

#include "memory.h"
#include "memory.c"

void test_get_ram_cache(void)
{
	TEST_ASSERT_GREATER_OR_EQUAL_INT32(0, get_ram_cache());
}

void test_get_ram_usage(void)
{
	TEST_ASSERT_GREATER_THAN_INT64(0, get_ram_usage());
}


int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_get_cpu_freq);
	RUN_TEST(test_get_cpu_temp);
	RUN_TEST(test_get_ram_cache);
	RUN_TEST(test_get_ram_usage);

	return UNITY_END();
}

