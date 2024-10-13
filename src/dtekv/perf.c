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
	clear("mcycle");
	clear("mcycleh");
	clear("minstret");
	clear("minstreth");
}

void get_counters(struct counters *counters)
{
	counters->mcycle = (uint64_t)reg("mcycle") &
	                   ((uint64_t)reg("mcycleh") << 32);
	counters->minstret = (uint64_t)reg("minstret") &
	                   ((uint64_t)reg("minstreth") << 32);
}

void dump_perf_info(void)
{
	struct counters counters;
	get_counters(&counters);
	uart_printf("Retired instructions: %ull\n"
	            "Cycles:               %ull\n"
	    	    "IPC:                  %ull\n\n",
	    	    counters.minstret, counters.mcycle,
	    	    counters.minstret / counters.mcycle);
}
