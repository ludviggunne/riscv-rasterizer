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

struct profile_window {
	struct counters average;
	struct counters offset;
	unsigned int times;
	const char *name;
};

void clear_counters(void);
void get_counters(struct counters *counters);
void dump_perf_info(void);

struct profile_window *create_new_profile_window(const char *name);
void profile_window_start(struct profile_window *win);
void profile_window_end(struct profile_window *win);
void print_all_profile_window_info(void);

#define PROFILE_WINDOW_START(name)\
	static struct profile_window *__pwin_##name = \
		__pwin_##name = create_new_profile_window(#name);\
	profile_window_start(__pwin_##name);

#define PROFILE_WINDOW_END(name)\
	profile_window_end(__pwin_##name);

#endif
