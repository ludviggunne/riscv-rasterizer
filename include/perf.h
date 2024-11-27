#ifndef PERF_H
#define PERF_H

/* Types and functions for dealing with hardware counters and profiling. */

/*
 * Holds values obtained from hardware counters
 */
struct counters
{
	unsigned long long mcycle;
	unsigned long long minstret;
	unsigned long long mhpmcounter3;
	unsigned long long mhpmcounter4;
	unsigned long long mhpmcounter5;
	unsigned long long mhpmcounter6;
	unsigned long long mhpmcounter7;
	unsigned long long mhpmcounter8;
	unsigned long long mhpmcounter9;
};

/*
 * Holds the accumulated counter values in a window of time,
 * for example a frame or a function.
 */
struct profile_window
{
	/* Total accumulated values */
	struct counters acc;
	/* The value fo the counters at the start of the window */
	struct counters off;
	/* Number of runs */
	unsigned long long nruns;
	/* Name of the window, for example 'Frame' */
	const char *name;
};

/*
 * Clear hardware counters.
 */
void clear_counters(void);

/*
 * Obtain the current values of the hardware counters.
 */
void get_counters(struct counters *counters);

/*
 * Create a new profile window with name `name`.
 */
struct profile_window *create_new_profile_window(const char *name);

/*
 * Start window.
 */
void profile_window_start(struct profile_window *win);

/*
 * Stop window.
 */
void profile_window_end(struct profile_window *win);

/*
 * Display information about all profile windows over UART.
 */
void print_all_profile_window_info(void (*print)(struct profile_window *, unsigned int, unsigned int));

/*
 * Convenience macro to create a profile window.
 */
#define PROFILE_WINDOW_START(name) \
	static struct profile_window *__pwin_ ## name; \
	if (__pwin_ ## name == NULL) \
	{ \
		__pwin_ ## name = create_new_profile_window(#name); \
	} \
	profile_window_start(__pwin_ ## name);

/*
 * Used with PROFILE_WINDOW_START to end the window.
 */
#define PROFILE_WINDOW_END(name) \
	profile_window_end(__pwin_ ## name);

#endif
