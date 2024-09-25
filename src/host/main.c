#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <model.h>
#include <qmath.h>
#include <rast.h>
#include <uart.h>

int qprint(qval_t v)
{
	char s[32];
	int n;

	n = qsnprint(v, s, sizeof(s));
	fputs(s, stdout);

	return n;
}

int qprintln(qval_t v)
{
	int n = qprint(v);

	fputc('\n', stdout);

	return n + 1;
}

#define SCALE		4

static GLuint		fbo;
static GLuint		tex;
static unsigned char	cb[WIDTH * HEIGHT];
static qval_t		zb[WIDTH * HEIGHT];
static char		keys[256];

static void display_func(void)
{
	for (int i = 0; i < sizeof(cb) / sizeof*(cb); i++)
	{
		cb[i] = 0;
	}

	for (int i = 0; i < sizeof(zb) / sizeof*(zb); i++)
	{
		zb[i] = QMAX;
	}

	draw_model(g_model, &g_model_xfm, cb, zb);

	if (keys[GLUT_KEY_LEFT])
	{
		g_model_xfm.y = qadd(g_model_xfm.y, QVAL(-0.02));
	}
	if (keys[GLUT_KEY_RIGHT])
	{
		g_model_xfm.y = qadd(g_model_xfm.y, QVAL( 0.02));
	}
	if (keys[GLUT_KEY_UP])
	{
		g_model_xfm.p = qadd(g_model_xfm.p, QVAL( 0.02));
	}
	if (keys[GLUT_KEY_DOWN])
	{
		g_model_xfm.p = qadd(g_model_xfm.p, QVAL(-0.02));
	}
	if (keys[','])
	{
		g_model_xfm.r = qadd(g_model_xfm.r, QVAL( 0.02));
	}
	if (keys['.'])
	{
		g_model_xfm.r = qadd(g_model_xfm.r, QVAL(-0.02));
	}
	if (keys['+'])
	{
		g_model_xfm.s = qadd(g_model_xfm.s, QVAL( 0.1));
	}
	if (keys['-'])
	{
		g_model_xfm.s = qadd(g_model_xfm.s, QVAL(-0.1));
	}

	{
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(	GL_TEXTURE_2D, 0, GL_RGB,
				WIDTH, HEIGHT, 0, GL_RGB,
				GL_UNSIGNED_BYTE_3_3_2, cb);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
		glFramebufferTexture2D(	GL_READ_FRAMEBUFFER,
					GL_COLOR_ATTACHMENT0,
					GL_TEXTURE_2D, tex, 0);
		glBlitFramebuffer(	0, 0, WIDTH, HEIGHT,
					0, 0, WIDTH * SCALE, HEIGHT * SCALE,
					GL_COLOR_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

		glutSwapBuffers();
		glutPostRedisplay();
	}
}

static void keyboard_func(unsigned char key, int x, int y)
{
	if (key >= 'a' && key <= 'z')
	{
		key = key + ('A' - 'a');
	}

	keys[key] = 1;

	if (key == 27)
	{
		glutLeaveMainLoop();
	}
}

static void keyboard_up_func(unsigned char key, int x, int y)
{
	if (key >= 'a' && key <= 'z')
	{
		key = key + ('A' - 'a');
	}

	keys[key] = 0;
}

static void special_func(int key, int x, int y)
{
	keys[key] = 1;
}

static void special_up_func(int key, int x, int y)
{
	keys[key] = 0;
}

static void rast_main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutSetOption(	GLUT_ACTION_ON_WINDOW_CLOSE,
			GLUT_ACTION_CONTINUE_EXECUTION);

	glutInitWindowSize(WIDTH * SCALE, HEIGHT * SCALE);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("");

	glewInit();

	glGenTextures(1, &tex);
	glGenFramebuffers(1, &fbo);

	glutDisplayFunc(display_func);
	glutKeyboardFunc(keyboard_func);
	glutKeyboardUpFunc(keyboard_up_func);
	glutSpecialFunc(special_func);
	glutSpecialUpFunc(special_up_func);

	glutMainLoop();
}

int main(int argc, char *argv[])
{
	float vbad = NAN;
	float emax = 0;

	uart_printf("hello, the number forty-three is %d!\n", 43);
	uart_printf("main is at %p, in case you were wondering.\nargc is %d.\n", main, argc);
	uart_printf("QPI is %q, and thats %s.\n", QPI, "pretty good");
	uart_printf("this is a backslash: \\, and this is a precent sign: %%.\n");

	for (qval_t i = QVAL(0); i < QVAL(256); i++)
	{
		qval_t q = qsqrt(i);
		float f = sqrtf(QTOF(i));
		float e = QTOF(q) - f;

		if (fabsf(e) > fabsf(emax))
		{
			vbad = QTOF(i);
			emax = e;
		}
	}

	printf("largest error: %+g (for input %g)\n", emax, vbad);

	{
		qval_t f = QVAL(1);
		qval_t v = QVAL(0);

		for (int i = 1; i <= 10; i++)
		{
			v = qadd(v, qdiv(QVAL(1), f));
			f = qmul(f, QINT(i));
		}

		qprintln(v);
	}

	rast_main(argc, argv);
}
