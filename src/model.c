#include <model.h>
#include <qmath.h>
#include <vmath.h>

#define MODEL	3

#if MODEL == 0
# define CUBE_IMPL
# include <cube.h>
model_t *g_model = &cube_model;
#elif MODEL == 1
# define TEAPOT_IMPL
# include <teapot.h>
model_t *g_model = &teapot_model;
#elif MODEL == 2
# define RAT_IMPL
# include <rat.h>
model_t *g_model = &rat_model;
#elif MODEL == 3
# define RAT_LOFI_IMPL
# include <rat_lofi.h>
model_t *g_model = &rat_lofi_model;
#elif MODEL == 4
# define MODERN_IMPL
# include <modern.h>
model_t *g_model = &modern_model;
#elif MODEL == 5
# define TORUS_IMPL
# include <torus.h>
model_t *g_model = &torus_model;
#endif

xfm_t g_model_xfm =
{
	.r = QZERO,
	.p = QZERO,
	.y = QZERO,
#if MODEL == 0
	.s = QVAL(1),
#elif MODEL == 1
	.s = QVAL(6),
#elif MODEL == 2 || MODEL == 3
	.s = QVAL(1),
#elif MODEL == 4
	.s = QVAL(0.01),
#elif MODEL == 5
	.s = QVAL(0.05),
#endif
	.t = { QZERO, QZERO, QVAL(25) },
};
