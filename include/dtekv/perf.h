#ifndef PERF_H
#define PERF_H

#include <stdint.h>

struct counters {
	uint64_t mcycle;
	uint64_t minstret;
};

void clear_counters(void);
void get_counters(struct counters *counters);
void dump_perf_info(void);

#endif
