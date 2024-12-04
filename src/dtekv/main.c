#include <button.h>
#include <perf.h>
#include <perf_json.h>
#include <qmath.h>
#include <rast.h>
#include <switch.h>
#include <vga.h>

#define PROFILE_FRAMES	500

static unsigned char	(*cb)[WIDTH * HEIGHT];
static qval_t		zb[WIDTH * HEIGHT];

static void display_func(void)
{
	PROFILE_WINDOW_START(frame);

	PROFILE_WINDOW_START(zbuf_clear);

	/* clear depth buffer */
	for (int i = 0; i < sizeof(zb) / sizeof*(zb); i++)
	{
		zb[i] = QMAX;
	}

	PROFILE_WINDOW_END(zbuf_clear);

	PROFILE_WINDOW_START(swap);

	/* wait for buffer swap */
	vga_finish();

	PROFILE_WINDOW_END(swap);

	PROFILE_WINDOW_START(cbuf_clear);

	/* clear color buffer */
	for (int i = 0; i < sizeof(*cb) / sizeof*(*cb); i += 4)
	{
		__asm__ ("sw zero, %0;" : "=m"(*(int *)&(*cb)[i]));
	}

	PROFILE_WINDOW_END(cbuf_clear);

	/* draw model */
	draw_model(*g_model, g_model_xfm, *cb, zb);

	PROFILE_WINDOW_END(frame);

	/* handle input */
	{
		static int mdl_selected = 0;

		if (button_get())
		{
			if (!mdl_selected)
			{
				model_select
				(
					(model_current() + 1) % model_count()
				);
			}
			mdl_selected = 1;
		}
		else
		{
			mdl_selected = 0;
		}
	}
	{
		int sw = switch_get_all();

		if (sw & (1 << 0))
		{
			g_model_xfm->y = qadd(g_model_xfm->y, QVAL(-0.02));
		}
		if (sw & (1 << 1))
		{
			g_model_xfm->y = qadd(g_model_xfm->y, QVAL( 0.02));
		}
		if (sw & (1 << 2))
		{
			g_model_xfm->p = qadd(g_model_xfm->p, QVAL( 0.02));
		}
		if (sw & (1 << 3))
		{
			g_model_xfm->p = qadd(g_model_xfm->p, QVAL(-0.02));
		}
		if (sw & (1 << 4))
		{
			g_model_xfm->r = qadd(g_model_xfm->r, QVAL( 0.02));
		}
		if (sw & (1 << 5))
		{
			g_model_xfm->r = qadd(g_model_xfm->r, QVAL(-0.02));
		}
		if (sw & (1 << 6))
		{
			g_model_xfm->s = qadd(g_model_xfm->s, QVAL( 0.01));
		}
		if (sw & (1 << 7))
		{
			g_model_xfm->s = qadd(g_model_xfm->s, QVAL(-0.01));
		}
	}

	/* swap buffer */
	cb = vga_swap();
}

static void rast_main(int argc, char *argv[])
{
	cb = vga_get_buf();

	for (;;)
	{
		display_func();

#ifdef PROFILE_ENABLE
		static int frame_count;

		frame_count++;

		if (frame_count == PROFILE_FRAMES)
		{
			print_all_profile_windows_json();

			break;
		}
#endif
	}
}

int main(int argc, char *argv[])
{
	rast_main(argc, argv);
}
