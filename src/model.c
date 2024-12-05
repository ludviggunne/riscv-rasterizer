/* By: Ludvig Gunne Lindström */
#include <model.h>
#include <qmath.h>

#include <models.c>

#ifndef DEFAULT_MODEL
# define DEFAULT_MODEL	0
#endif

#if defined(__GNUC__)
# pragma GCC diagnostic ignored "-Woverride-init"
#elif defined(__clang__)
# pragma clang diagnostic ignored "-Winitializer-overrides"
#endif

static xfm_t model_xfm[NUM_MODELS] =
{
	/* default transform */
	[0 ... NUM_MODELS - 1] =
	{
		.s = QVAL(1),
		.t = { QVAL(0), QVAL(0), QVAL(25) },
	},

	/* specific transforms */
	[MODELNUM_teapot] =
	{
		.s = QVAL(6),
		.t = { QVAL(0), QVAL(-10), QVAL(25) },
	},
	[MODELNUM_rat ... MODELNUM_rat_lofi] =
	{
		.s = QVAL(2),
		.t = { QVAL(0), QVAL(-10), QVAL(25) },
		.y = QPIHALF,
	},
	[MODELNUM_modern] =
	{
		.s = QVAL(0.02),
		.t = { QVAL(0), QVAL(0), QVAL(25) },
	},
	[MODELNUM_torus] =
	{
		.s = QVAL(0.05),
		.t = { QVAL(0), QVAL(0), QVAL(25) },
	},
	[MODELNUM_skull] =
	{
		.s = QVAL(4),
		.t = { QVAL(0), QVAL(0), QVAL(25) },
	},
	[MODELNUM_riscv] =
	{
		.s = QVAL(4),
		.t = { QVAL(0), QVAL(0), QVAL(25) },
	},
};

static int	model_num	= DEFAULT_MODEL;

model_t **	g_model		= &models[DEFAULT_MODEL];
xfm_t *		g_model_xfm	= &model_xfm[DEFAULT_MODEL];

int model_count(void)
{
	return NUM_MODELS;
}

int model_current(void)
{
	return model_num;
}

void model_select(int num)
{
	model_num = num;

	g_model = &models[model_num];
	g_model_xfm = &model_xfm[model_num];
}
