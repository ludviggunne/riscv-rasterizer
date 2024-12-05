/* By: Tommy Bergman */
#define INITCALL_CASE(lvl) \
	extern void (*__init_ ## lvl ## _start)(void); \
	extern void (*__init_ ## lvl ## _end)(void); \
	case lvl: \
	{ \
		void (**fn)(void) = &__init_ ## lvl ## _start; \
		void (**end)(void) = &__init_ ## lvl ## _end; \
		while (fn != end) \
		{ \
			(*fn++)(); \
		} \
		break; \
	}

void __do_initcalls(int lvl)
{
	switch (lvl)
	{
		INITCALL_CASE(0)
	}
}
