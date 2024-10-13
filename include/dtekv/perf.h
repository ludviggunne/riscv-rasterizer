#ifndef PERF_H
#define PERF_H

#include <stdint.h>

struct counters {
#define REGISTER(x) uint64_t x;
#include <hwc.h>
#undef REGISTER
};

void clear_counters(void);
void get_counters(struct counters *counters);
void dump_perf_info(void);

#endif
