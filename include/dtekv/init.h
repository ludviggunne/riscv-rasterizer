#ifndef INIT_H
#define INIT_H

#define __INITLVL_IRQ	0

#define DEFINE_INITCALL(lvl, fn) \
	__DEFINE_INITCALL_1_(__INITLVL_ ## lvl, fn)

#define __DEFINE_INITCALL_1_(lvl, fn) \
	__DEFINE_INITCALL_2_(lvl, fn)

#define __DEFINE_INITCALL_2_(lvl, fn) \
	static void __initcall_ ## lvl ## _fn_ ## fn(void); \
	__attribute__ ((section (".init." #lvl), used)) \
	static void (*__initcall_ ## lvl ## _ptr_ ## fn)(void) = \
	&__initcall_ ## lvl ## _fn_ ## fn; \
	static void __initcall_ ## lvl ## _fn_ ## fn(void)

#endif
