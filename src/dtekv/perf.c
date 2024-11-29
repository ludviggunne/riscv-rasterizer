#include <stdlib.h>
#include <io.h>
#include <irq.h>
#include <perf.h>
#include <uart.h>

#define MAX_PROFILE_WINDOWS	32

static struct profile_window	s_windows[MAX_PROFILE_WINDOWS];
static unsigned int		s_window_count;

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
	/* FIXME: Race condition.
	 * The low part of a csr can roll over inbetween reading the hi part
	 * and the lo part.
	 */

	counters->mcycle = csrr(mcycleh);
	counters->minstret = csrr(minstreth);
	counters->mhpmcounter3 = csrr(mhpmcounter3h);
	counters->mhpmcounter4 = csrr(mhpmcounter4h);
	counters->mhpmcounter5 = csrr(mhpmcounter5h);
	counters->mhpmcounter6 = csrr(mhpmcounter6h);
	counters->mhpmcounter7 = csrr(mhpmcounter7h);
	counters->mhpmcounter8 = csrr(mhpmcounter8h);
	counters->mhpmcounter9 = csrr(mhpmcounter9h);

	counters->mcycle <<= 32;
	counters->minstret <<= 32;
	counters->mhpmcounter3 <<= 32;
	counters->mhpmcounter4 <<= 32;
	counters->mhpmcounter5 <<= 32;
	counters->mhpmcounter6 <<= 32;
	counters->mhpmcounter7 <<= 32;
	counters->mhpmcounter8 <<= 32;
	counters->mhpmcounter9 <<= 32;

	counters->mcycle |= csrr(mcycle);
	counters->minstret |= csrr(minstret);
	counters->mhpmcounter3 |= csrr(mhpmcounter3);
	counters->mhpmcounter4 |= csrr(mhpmcounter4);
	counters->mhpmcounter5 |= csrr(mhpmcounter5);
	counters->mhpmcounter6 |= csrr(mhpmcounter6);
	counters->mhpmcounter7 |= csrr(mhpmcounter7);
	counters->mhpmcounter8 |= csrr(mhpmcounter8);
	counters->mhpmcounter9 |= csrr(mhpmcounter9);
}

struct profile_window *create_new_profile_window(const char *name)
{
	if (s_window_count == MAX_PROFILE_WINDOWS)
	{
		uart_printf("error: could not create profile window '%s', "
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
	get_counters(&win->off);
}

void profile_window_end(struct profile_window *win)
{
	struct counters current;
	get_counters(&current);

	current.mcycle -= win->off.mcycle;
	current.minstret -= win->off.minstret;
	current.mhpmcounter3 -= win->off.mhpmcounter3;
	current.mhpmcounter4 -= win->off.mhpmcounter4;
	current.mhpmcounter5 -= win->off.mhpmcounter5;
	current.mhpmcounter6 -= win->off.mhpmcounter6;
	current.mhpmcounter7 -= win->off.mhpmcounter7;
	current.mhpmcounter8 -= win->off.mhpmcounter8;
	current.mhpmcounter9 -= win->off.mhpmcounter9;

	int irqf = irq_save();

	win->acc.mcycle += current.mcycle;
	win->acc.minstret += current.minstret;
	win->acc.mhpmcounter3 += current.mhpmcounter3;
	win->acc.mhpmcounter4 += current.mhpmcounter4;
	win->acc.mhpmcounter5 += current.mhpmcounter5;
	win->acc.mhpmcounter6 += current.mhpmcounter6;
	win->acc.mhpmcounter7 += current.mhpmcounter7;
	win->acc.mhpmcounter8 += current.mhpmcounter8;
	win->acc.mhpmcounter9 += current.mhpmcounter9;

	irq_restore(irqf);

	win->nruns++;
}

static void default_print_callback(struct profile_window *win, unsigned int index, unsigned int nwins)
{
	(void) index;
	(void) nwins;

	uart_printf("%s:\n", win->name);
	uart_printf("    mcycle:       %lu\n", win->acc.mcycle);
	uart_printf("    minstret:     %lu\n", win->acc.minstret);
	uart_printf("    mhpmcounter3: %lu\n", win->acc.mhpmcounter3);
	uart_printf("    mhpmcounter4: %lu\n", win->acc.mhpmcounter4);
	uart_printf("    mhpmcounter5: %lu\n", win->acc.mhpmcounter5);
	uart_printf("    mhpmcounter6: %lu\n", win->acc.mhpmcounter6);
	uart_printf("    mhpmcounter7: %lu\n", win->acc.mhpmcounter7);
	uart_printf("    mhpmcounter8: %lu\n", win->acc.mhpmcounter8);
	uart_printf("    mhpmcounter9: %lu\n", win->acc.mhpmcounter9);
	uart_printf("\n");
}

void print_all_profile_window_info(pw_print_callback_t print_callback)
{
	if (print_callback)
	{
		for (int i = 0; i < s_window_count; i++)
		{
			print_callback(&s_windows[i], i, s_window_count);
		}
	}
	else
	{
		print_all_profile_window_info(default_print_callback);
	}
}
