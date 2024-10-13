#include <perf.h>
#include <uart.h>

#define reg(name)\
	({\
	unsigned int v;\
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
	clear("minstret");
	clear("mhpmcounter3");
	clear("mhpmcounter4");
	clear("mhpmcounter5");
	clear("mhpmcounter6");
	clear("mhpmcounter7");
	clear("mhpmcounter8");
	clear("mhpmcounter9");
}

void get_counters(struct counters *counters)
{
	counters->mcycle       = reg("mcycle");
	counters->minstret     = reg("minstret");
	counters->mhpmcounter3 = reg("mhpmcounter3");
	counters->mhpmcounter4 = reg("mhpmcounter4");
	counters->mhpmcounter5 = reg("mhpmcounter5");
	counters->mhpmcounter6 = reg("mhpmcounter6");
	counters->mhpmcounter7 = reg("mhpmcounter7");
	counters->mhpmcounter8 = reg("mhpmcounter8");
	counters->mhpmcounter9 = reg("mhpmcounter9");
}

void dump_perf_info(void)
{
	struct counters counters;
	get_counters(&counters);
	uart_printf("Retired instructions: %u\n"
	            "Cycles:               %u\n"
	            "IPC:                  %u\n",
	            counters.minstret, counters.mcycle,
	            counters.minstret / counters.mcycle);
}

struct counters counter_diff(struct counters *new, struct counters *old)
{
	struct counters res;
	res.minstret = new->minstret - old->minstret;
	res.mhpmcounter3 = new->mhpmcounter3 - old->mhpmcounter3;
	res.mhpmcounter4 = new->mhpmcounter4 - old->mhpmcounter4;
	res.mhpmcounter5 = new->mhpmcounter5 - old->mhpmcounter5;
	res.mhpmcounter6 = new->mhpmcounter6 - old->mhpmcounter6;
	res.mhpmcounter7 = new->mhpmcounter7 - old->mhpmcounter7;
	res.mhpmcounter8 = new->mhpmcounter8 - old->mhpmcounter8;
	res.mhpmcounter9 = new->mhpmcounter9 - old->mhpmcounter9;
	return res;
}
