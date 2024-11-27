#include <stddef.h>
#include <perf.h>

/*
 * Dummy implementations for profiling on host system.
 */

void clear_counters(void)
{
}

void get_counters(struct counters *counters)
{
	(void) counters;
}

void dump_perf_info(void)
{
}

struct profile_window *create_new_profile_window(const char *name)
{
	(void) name;
	return NULL;
}

void profile_window_start(struct profile_window *win)
{
	(void) win;
}

void profile_window_end(struct profile_window *win)
{
	(void) win;
}

void print_all_profile_window_info(void (*print)(struct profile_window *))
{
}

