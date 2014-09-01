;=================================================================================================
;  			syscall.asm			Bill Liang	2014-8-29
;=================================================================================================
%include	"sconst.inc"

_NR_get_ticks		equ	0		;要与global.c中的sys_call_table对应
_NR_write		equ	1
INT_VECTOR_SYS_CALL	equ	0x90

global	get_ticks
global	write

bits	32
[section .text]

;=================================================================================================
;	int get_ticks();
;=================================================================================================
get_ticks:
	mov	eax, _NR_get_ticks
	int	INT_VECTOR_SYS_CALL
	ret

;=================================================================================================
;	void write(char* buf, int len);
;=================================================================================================
write:
	mov	eax, _NR_write
	mov	ebx, [esp + 4]
	mov	ecx, [esp + 8]
	int	INT_VECTOR_SYS_CALL
	ret
