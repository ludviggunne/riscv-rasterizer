/* By: Ludvig Gunne Lindström */

#include <perf.h>
#include <uart.h>

static void print_profile_window_json(struct profile_window *win,
                                      unsigned int index,
                                      unsigned int nwins)
{
	uart_printf("    {\n"
	            "        \"name\": \"%s\",\n"
	            "        \"runs\": \"%x\",\n"
	            "        \"mcycle\": \"%x\",\n"
	            "        \"minstret\": \"%x\",\n"
	            "        \"mhpmcounter3\": \"%x\",\n"
	            "        \"mhpmcounter4\": \"%x\",\n"
	            "        \"mhpmcounter5\": \"%x\",\n"
	            "        \"mhpmcounter6\": \"%x\",\n"
	            "        \"mhpmcounter7\": \"%x\",\n"
	            "        \"mhpmcounter8\": \"%x\",\n"
	            "        \"mhpmcounter9\": \"%x\"\n"
	            "    }%s\n",
	            win->name,
	            &win->nruns,
	            &win->acc.mcycle,
	            &win->acc.minstret,
	            &win->acc.mhpmcounter3,
	            &win->acc.mhpmcounter4,
	            &win->acc.mhpmcounter5,
	            &win->acc.mhpmcounter6,
	            &win->acc.mhpmcounter7,
	            &win->acc.mhpmcounter8,
	            &win->acc.mhpmcounter9,
	            /* fiffigt */
	            index < nwins - 1 ? "," : "");
}

void print_all_profile_windows_json(void)
{
	uart_printf("# PROFILE START\n"
	            "[\n");
	print_all_profile_window_info(print_profile_window_json);
	uart_printf("]\n"
	            "# PROFILE END\n");
}
