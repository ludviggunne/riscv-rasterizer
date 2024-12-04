#include <model.h>
#include <qmath.h>

#include <cube.c>
#include <teapot.c>
#include <rat.c>
#include <rat_lofi.c>
#include <modern.c>
#include <torus.c>
#include <skull.c>
#include <riscv.c>

#ifndef DEFAULT_MODEL
#define DEFAULT_MODEL 0
#endif

static model_t *model[] =
{
	&cube_model,
	&teapot_model,
	&rat_model,
	&rat_lofi_model,
	&modern_model,
	&torus_model,
	&skull_model,
	&riscv_model,
};

static xfm_t model_xfm[] =
{
	{
		.s = QVAL(1),
		.t = { QVAL(0), QVAL(0), QVAL(25) },
	},
	{
		.s = QVAL(6),
		.t = { QVAL(0), QVAL(-10), QVAL(25) },
	},
	{
		.s = QVAL(2),
		.t = { QVAL(0), QVAL(-10), QVAL(25) },
		.y = QPIHALF,
	},
	{
		.s = QVAL(2),
		.t = { QVAL(0), QVAL(-10), QVAL(25) },
		.y = QPIHALF,
	},
	{
		.s = QVAL(0.02),
		.t = { QVAL(0), QVAL(0), QVAL(25) },
	},
	{
		.s = QVAL(0.05),
		.t = { QVAL(0), QVAL(0), QVAL(25) },
	},
	{
		.s = QVAL(4),
		.t = { QVAL(0), QVAL(0), QVAL(25) },
	},
	{
		.s = QVAL(4),
		.t = { QVAL(0), QVAL(0), QVAL(25) },
	},
};

static int	model_num	= DEFAULT_MODEL;

model_t **	g_model		= &model[DEFAULT_MODEL];
xfm_t *		g_model_xfm	= &model_xfm[DEFAULT_MODEL];

int model_count(void)
{
	return sizeof(model) / sizeof*(model);
}

int model_current(void)
{
	return model_num;
}

void model_select(int num)
{
	model_num = num;

	g_model = &model[model_num];
	g_model_xfm = &model_xfm[model_num];
}
