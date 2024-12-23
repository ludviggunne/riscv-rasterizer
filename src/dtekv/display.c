#include <display_io.h>
#include <qmath.h>

static unsigned char display_chrtbl[256] =
{
	[' '] = 0b11111111,

	['0'] = 0b11000000,
	['1'] = 0b11111001,
	['2'] = 0b10100100,
	['3'] = 0b10110000,
	['4'] = 0b10011001,
	['5'] = 0b10010010,
	['6'] = 0b10000010,
	['7'] = 0b11111000,
	['8'] = 0b10000000,
	['9'] = 0b10010000,

	['-'] = 0b10111111,

	['A'] = 0b10001000,
	['B'] = 0b10000011,
	['C'] = 0b11000110,
	['D'] = 0b10100001,
	['E'] = 0b10000110,
	['F'] = 0b10001110,
	['G'] = 0b11000010,
	['H'] = 0b10001001,
	['I'] = 0b11001111,
	['J'] = 0b11100001,
	['K'] = 0b11101010,
	['L'] = 0b11000111,
	['M'] = 0b11011100,
	['N'] = 0b10101011,
	['O'] = 0b10100011,
	['P'] = 0b10001100,
	['Q'] = 0b10011000,
	['R'] = 0b10101111,
	['S'] = 0b10010010,
	['T'] = 0b10000111,
	['U'] = 0b11000001,
	['V'] = 0b11110011,
	['W'] = 0b11010101,
	['X'] = 0b11101011,
	['Y'] = 0b10010001,
	['Z'] = 0b10110111,

	['a'] = 0b10001000,
	['b'] = 0b10000011,
	['c'] = 0b11000110,
	['d'] = 0b10100001,
	['e'] = 0b10000110,
	['f'] = 0b10001110,
	['g'] = 0b11000010,
	['h'] = 0b10001001,
	['i'] = 0b11001111,
	['j'] = 0b11100001,
	['k'] = 0b11101010,
	['l'] = 0b11000111,
	['m'] = 0b11011100,
	['n'] = 0b10101011,
	['o'] = 0b10100011,
	['p'] = 0b10001100,
	['q'] = 0b10011000,
	['r'] = 0b10101111,
	['s'] = 0b10010010,
	['t'] = 0b10000111,
	['u'] = 0b11000001,
	['v'] = 0b11110011,
	['w'] = 0b11010101,
	['x'] = 0b11101011,
	['y'] = 0b10010001,
	['z'] = 0b10110111,
};

void display_char(int pos, int c)
{
	if (c & 0x80)
	{
		c = (display_chrtbl[c ^ 0x80] ^ 0x80);
	}
	else
	{
		c = display_chrtbl[c];
	}

	DISPLAY_BASE[(5 - pos) * 4] = c;
}

void display_qval(int pos, qval_t v)
{
	char s[8];
	int p = 0;

	qsnprint(v, s, sizeof(s));

	for (int i = 0; i < pos; i++)
	{
		display_char(i, ' ');
	}

	for (int i = pos; i < 6; i++)
	{
		if (s[p] == '\0')
		{
			display_char(i, ' ');
		}
		else if (s[p + 1] == '.')
		{
			display_char(i, s[p] | 0x80);
			p = p + 2;
		}
		else
		{
			display_char(i, s[p]);
			p = p + 1;
		}
	}
}
