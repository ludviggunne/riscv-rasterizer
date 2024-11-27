#include <json.h>
#include <perf.h>
#include <uart.h>

static void print_profile_window_json(struct profile_window *win,
                                      unsigned int index,
                                      unsigned int nwins)
{
	uart_printf("    {\n"
	            "        \"name\": %s,\n"
		    "        \"runs\": %lu,\n"
	            "        \"mcycle\": %lu,\n"
	            "        \"minstret\": %lu,\n"
	            "        \"mhpmcounter3\": %lu,\n"
	            "        \"mhpmcounter4\": %lu,\n"
	            "        \"mhpmcounter5\": %lu,\n"
	            "        \"mhpmcounter6\": %lu,\n"
	            "        \"mhpmcounter7\": %lu,\n"
	            "        \"mhpmcounter8\": %lu,\n"
	            "        \"mhpmcounter9\": %lu\n"
	            "     }%s\n",
	            win->name,
	            win->nruns,
		    win->acc.mcycle,
		    win->acc.minstret,
		    win->acc.mhpmcounter3,
		    win->acc.mhpmcounter4,
		    win->acc.mhpmcounter5,
		    win->acc.mhpmcounter6,
		    win->acc.mhpmcounter7,
		    win->acc.mhpmcounter8,
		    win->acc.mhpmcounter9,
		    index < nwins - 1 ? "," : "");
}

void print_all_profile_windows_json(void)
{
	uart_printf("[\n");
	print_all_profile_window_info(print_profile_window_json);
	uart_printf("]\n");
}
