#ifndef PERF_H
#define PERF_H

/* Types and functions for dealing with hardware counters and profiling. */

/*
 * Holds values obtained from hardware counters
 */
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

/*
 * Represents the average counter values in a window of time,
 * for example a frame or a function.
 */
struct profile_window {
	struct counters average;
	struct counters offset;
	unsigned int times;
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
 * Start measuring.
 */
void profile_window_start(struct profile_window *win);

/*
 * Stop measuring and update average.
 */
void profile_window_end(struct profile_window *win);

/*
 * Display information about all profile windows over uart.
 */
void print_all_profile_window_info(void);
/*
 * Convenience macro to create a profile window.
 */
#define PROFILE_WINDOW_START(name) \
	static struct profile_window *__pwin_ ## name = \
		__pwin_ ## name = create_new_profile_window(#name); \
	profile_window_start(__pwin_ ## name);

/*
 * Used with PROFILE_WINDOW_START to end the window.
 */
#define PROFILE_WINDOW_END(name) \
	profile_window_end(__pwin_ ## name);

#endif
