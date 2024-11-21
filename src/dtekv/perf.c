#include <stdlib.h>
#include <io.h>
#include <perf.h>
#include <uart.h>

#define MAX_PROFILE_WINDOWS 32

static struct profile_window s_windows[MAX_PROFILE_WINDOWS] = { 0 };
static unsigned int s_window_count;

void clear_counters(void)
{
	csrw(mcycle, 0);
	csrw(minstret, 0);
	csrw(mhpmcounter3, 0);
	csrw(mhpmcounter4, 0);
	csrw(mhpmcounter5, 0);
	csrw(mhpmcounter6, 0);
	csrw(mhpmcounter7, 0);
	csrw(mhpmcounter8, 0);
	csrw(mhpmcounter9, 0);
	csrw(mcycleh, 0);
	csrw(minstreth, 0);
	csrw(mhpmcounter3h, 0);
	csrw(mhpmcounter4h, 0);
	csrw(mhpmcounter5h, 0);
	csrw(mhpmcounter6h, 0);
	csrw(mhpmcounter7h, 0);
	csrw(mhpmcounter8h, 0);
	csrw(mhpmcounter9h, 0);
}

void get_counters(struct counters *counters)
{
	counters->mcycle	= csrr(mcycle);
	counters->minstret	= csrr(minstret);
	counters->mhpmcounter3	= csrr(mhpmcounter3);
	counters->mhpmcounter4	= csrr(mhpmcounter4);
	counters->mhpmcounter5	= csrr(mhpmcounter5);
	counters->mhpmcounter6	= csrr(mhpmcounter6);
	counters->mhpmcounter7	= csrr(mhpmcounter7);
	counters->mhpmcounter8	= csrr(mhpmcounter8);
	counters->mhpmcounter9	= csrr(mhpmcounter9);
}

void dump_perf_info(void)
{
	struct counters counters;
	get_counters(&counters);
	uart_printf(	"Retired instructions: %u\n"
			"Cycles:               %u\n"
			"IPC:                  %u\n",
			counters.minstret, counters.mcycle,
			counters.minstret / counters.mcycle);
}

struct profile_window *create_new_profile_window(const char *name)
{
	if (s_window_count == MAX_PROFILE_WINDOWS)
	{
		uart_printf(	"error: could not create profile window '%s', "
				"reached max window count %d\n",
				name, MAX_PROFILE_WINDOWS);
		abort();
	}

	struct profile_window *win = &s_windows[s_window_count++];
	win->name = name;
	return win;
}

void profile_window_start(struct profile_window *win)
{
	get_counters(&win->offset);
}

void profile_window_end(struct profile_window *win)
{
	struct counters current;
	get_counters(&current);

	current.mcycle -= win->offset.mcycle;
	current.minstret -= win->offset.minstret;
	current.mhpmcounter3 -= win->offset.mhpmcounter3;
	current.mhpmcounter4 -= win->offset.mhpmcounter4;
	current.mhpmcounter5 -= win->offset.mhpmcounter5;
	current.mhpmcounter6 -= win->offset.mhpmcounter6;
	current.mhpmcounter7 -= win->offset.mhpmcounter7;
	current.mhpmcounter8 -= win->offset.mhpmcounter8;
	current.mhpmcounter9 -= win->offset.mhpmcounter9;

	long long mcycle = win->average.mcycle * win->times;
	long long minstret = win->average.minstret * win->times;
	long long mhpmcounter3 = win->average.mhpmcounter3 * win->times;
	long long mhpmcounter4 = win->average.mhpmcounter4 * win->times;
	long long mhpmcounter5 = win->average.mhpmcounter5 * win->times;
	long long mhpmcounter6 = win->average.mhpmcounter6 * win->times;
	long long mhpmcounter7 = win->average.mhpmcounter7 * win->times;
	long long mhpmcounter8 = win->average.mhpmcounter8 * win->times;
	long long mhpmcounter9 = win->average.mhpmcounter9 * win->times;

	mcycle += current.mcycle;
	minstret += current.minstret;
	mhpmcounter3 += current.mhpmcounter3;
	mhpmcounter4 += current.mhpmcounter4;
	mhpmcounter5 += current.mhpmcounter5;
	mhpmcounter6 += current.mhpmcounter6;
	mhpmcounter7 += current.mhpmcounter7;
	mhpmcounter8 += current.mhpmcounter8;
	mhpmcounter9 += current.mhpmcounter9;

	win->times++;

	mcycle /= win->times;
	minstret /= win->times;
	mhpmcounter3 /= win->times;
	mhpmcounter4 /= win->times;
	mhpmcounter5 /= win->times;
	mhpmcounter6 /= win->times;
	mhpmcounter7 /= win->times;
	mhpmcounter8 /= win->times;
	mhpmcounter9 /= win->times;

	win->average.mcycle = mcycle;
	win->average.minstret = minstret;
	win->average.mhpmcounter3 = mhpmcounter3;
	win->average.mhpmcounter4 = mhpmcounter4;
	win->average.mhpmcounter5 = mhpmcounter5;
	win->average.mhpmcounter6 = mhpmcounter6;
	win->average.mhpmcounter7 = mhpmcounter7;
	win->average.mhpmcounter8 = mhpmcounter8;
	win->average.mhpmcounter9 = mhpmcounter9;
}

static void print_profile_window_info(struct profile_window *win)
{
	uart_printf("%s:\n", win->name);
	uart_printf("    Cycles: %d\n", win->average.mcycle);
	uart_printf("    Instructions: %d\n", win->average.minstret);
	uart_printf("    IPC: %d\n", win->average.minstret / win->average.mcycle);
	uart_printf("\n");
}

void print_all_profile_window_info(void)
{
	for (int i = 0; i < s_window_count; i++)
	{
		print_profile_window_info(&s_windows[i]);
	}
}
