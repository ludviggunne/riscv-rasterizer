#include <perf.h>
#include <uart.h>

#define reg(name)\
	({\
	uint32_t v;\
	asm volatile (\
	"csrr %0, " name "\n"\
	: "=r" (v));\
	v;\
	})

#define clear(reg)\
	asm volatile (\
	"csrw " reg ", zero\n"\
	)

void clear_counters(void)
{
#define REGISTER(x) clear(#x); clear(#x "h");
#include <hwc.h>
#undef REGISTER
}

void get_counters(struct counters *counters)
{
#define REGISTER(x) counters->x = (uint64_t)reg(#x) | ((uint64_t)reg(#x "h") << 32);
#include <hwc.h>
#undef REGISTER
}

void dump_perf_info(void)
{
	struct counters counters;
	get_counters(&counters);
	uart_printf("Retired instructions: %ull\n"
	            "Cycles:               %ull\n",
	            counters.minstret, counters.mcycle);
}
