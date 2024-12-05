#include <button.h>
#include <display.h>
#include <perf.h>
#include <perf_json.h>
#include <qmath.h>
#include <rast.h>
#include <switch.h>
#include <timer.h>
#include <vga.h>

#if defined(PROFILE_ENABLE) && !defined(PROFILE_FRAMES)
# define PROFILE_FRAMES	500
#endif

static unsigned char	(*cb)[WIDTH * HEIGHT];
static qval_t		zb[WIDTH * HEIGHT];
static int		frame_count;

static void display_func(void)
{
	PROFILE_WINDOW_START(frame);

	PROFILE_WINDOW_START(zbuf_clear);

	/* clear depth buffer */
	for (int i = 0; i < sizeof(zb) / sizeof*(zb); i += 16)
	{
		zb[i +  0] = QMAX;
		zb[i +  1] = QMAX;
		zb[i +  2] = QMAX;
		zb[i +  3] = QMAX;
		zb[i +  4] = QMAX;
		zb[i +  5] = QMAX;
		zb[i +  6] = QMAX;
		zb[i +  7] = QMAX;
		zb[i +  8] = QMAX;
		zb[i +  9] = QMAX;
		zb[i + 10] = QMAX;
		zb[i + 11] = QMAX;
		zb[i + 12] = QMAX;
		zb[i + 13] = QMAX;
		zb[i + 14] = QMAX;
		zb[i + 15] = QMAX;
	}

	PROFILE_WINDOW_END(zbuf_clear);

	PROFILE_WINDOW_START(swap);

	/* wait for buffer swap */
	vga_finish();

	PROFILE_WINDOW_END(swap);

	PROFILE_WINDOW_START(cbuf_clear);

	/* clear color buffer */
	for (int i = 0; i < sizeof(*cb) / sizeof(int); i += 16)
	{
		/* this is written in assembly to prevent the compiler from
		 * emitting a call to memset, which we don't have */
		__asm__
		(
			"sw zero,  0(%0);"
			"sw zero,  4(%0);"
			"sw zero,  8(%0);"
			"sw zero, 12(%0);"
			"sw zero, 16(%0);"
			"sw zero, 20(%0);"
			"sw zero, 24(%0);"
			"sw zero, 28(%0);"
			"sw zero, 32(%0);"
			"sw zero, 36(%0);"
			"sw zero, 40(%0);"
			"sw zero, 44(%0);"
			"sw zero, 48(%0);"
			"sw zero, 52(%0);"
			"sw zero, 56(%0);"
			"sw zero, 60(%0);"
			:: "r"(&((int *) cb)[i])
			: "memory"
		);
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

	frame_count++;
}

static void rast_main(int argc, char *argv[])
{
	cb = vga_get_buf();

	for (;;)
	{
		display_func();

#ifdef PROFILE_ENABLE
		if (frame_count == PROFILE_FRAMES)
		{
			print_all_profile_windows_json();

			break;
		}
#endif
	}
}

static void timer_fn(void)
{
	static int v[5];
	static int p;

	v[p] = frame_count;
	p = (p + 1) % 5;

	display_qval(qdiv(QINT(frame_count - v[p]), QINT(5)));
}

int main(int argc, char *argv[])
{
	timer_start(1000, 1, timer_fn);
	rast_main(argc, argv);
}
