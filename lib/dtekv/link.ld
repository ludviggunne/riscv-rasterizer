OUTPUT_FORMAT("elf32-littleriscv", "elf32-bigriscv", "elf32-littleriscv")
OUTPUT_ARCH(riscv)

ENTRY(_reset)

SECTIONS
{
	. = 0;

	.mvec		: { KEEP (*(.mvec .mvec.*)) }

	.text		: { *(.text .text.* .gnu.linkonce.t.*) }

	.init		:
	{
		__init_0_start = . ;
		KEEP(*(.init.0))
		__init_0_end = . ;
	}

	.rodata		: { *(.rodata .rodata.* .gnu.linkonce.r.*) }

	.data		: { *(.data .data.* .gnu.linkonce.d.*) }

	__global_pointer$ = ALIGN (16) + 0x7F0 ;
	.sdata		: { *(.sdata .sdata.* .gnu.linkonce.s.*) }

	. = ALIGN (4) ;
	__bss_start = . ;
	.sbss		: { *(.sbss .sbss.* .gnu.linkonce.sb.*) *(.scommon) }
	.bss		: { *(.bss .bss.* .gnu.linkonce.b.*) *(COMMON) }
	. = ALIGN (4) ;
	__bss_end = . ;

	_end = . ;

	.debug			0	: { *(.debug) }
	.line			0	: { *(.line) }
	.debug_srcinfo		0	: { *(.debug_srcinfo) }
	.debug_sfnames		0	: { *(.debug_sfnames) }
	.debug_aranges		0	: { *(.debug_aranges) }
	.debug_pubnames		0	: { *(.debug_pubnames) }
	.debug_info		0	: { *(.debug_info .gnu.linkonce.wi.*) }
	.debug_abbrev		0	: { *(.debug_abbrev) }
	.debug_line		0	: { *(.debug_line .debug_line.* .debug_line_end) }
	.debug_frame		0	: { *(.debug_frame) }
	.debug_str		0	: { *(.debug_str) }
	.debug_loc		0	: { *(.debug_loc) }
	.debug_macinfo		0	: { *(.debug_macinfo) }
	.debug_weaknames	0	: { *(.debug_weaknames) }
	.debug_funcnames	0	: { *(.debug_funcnames) }
	.debug_typenames	0	: { *(.debug_typenames) }
	.debug_varnames		0	: { *(.debug_varnames) }
	.debug_pubtypes		0	: { *(.debug_pubtypes) }
	.debug_ranges		0	: { *(.debug_ranges) }
	.debug_addr		0	: { *(.debug_addr) }
	.debug_line_str		0	: { *(.debug_line_str) }
	.debug_loclists		0	: { *(.debug_loclists) }
	.debug_macro		0	: { *(.debug_macro) }
	.debug_names		0	: { *(.debug_names) }
	.debug_rnglists		0	: { *(.debug_rnglists) }
	.debug_str_offsets	0	: { *(.debug_str_offsets) }
	.debug_sup		0	: { *(.debug_sup) }
	.gnu.attributes		0	: { KEEP (*(.gnu.attributes)) }

	/DISCARD/	: { *(*) }
}
