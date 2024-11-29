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

void print_all_profile_window_info(pw_print_callback_t print_callback)
{
	(void) print_callback;
}

