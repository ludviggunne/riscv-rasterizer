#ifndef PERF_H
#define PERF_H

struct counters {
	unsigned int mcycle;
	unsigned int minstret;
	unsigned int mhpmcounter3;
	unsigned int mhpmcounter4;
	unsigned int mhpmcounter5;
	unsigned int mhpmcounter6;
	unsigned int mhpmcounter7;
	unsigned int mhpmcounter8;
	unsigned int mhpmcounter9;
};

void clear_counters(void);
void get_counters(struct counters *counters);
void dump_perf_info(void);
struct counters counter_diff(struct counters *new, struct counters *old);

#endif
