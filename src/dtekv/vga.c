#include <vga_io.h>

static int vga_current = 1;

void *vga_get_buf(void)
{
	return VGA_MEM[vga_current];
}

void *vga_swap(void)
{
	VGA_BACK = vga_get_buf();
	VGA_FRONT = 0;

	vga_current = vga_current ^ 1;

	return vga_get_buf();
}

void vga_finish(void)
{
	while (VGA_STATUS & 1)
	{
	}
}
