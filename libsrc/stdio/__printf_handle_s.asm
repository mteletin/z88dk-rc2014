
	MODULE	__printf_handle_s
	SECTION code_clib
	PUBLIC	__printf_handle_s
	EXTERN	__printf_loop
	EXTERN	__printf_print_aligned
	EXTERN	get_16bit_ap_parameter
	EXTERN	strlen

__printf_handle_s:
        push    hl              ;save format string
        call    get_16bit_ap_parameter  ;de=new ap, hl=string to print
        push    de              ;save ap
        ld      a,h
        or      l
        jr      nz, printstr
        ld      hl,nullstr
printstr:
        push    hl              ;save string
        call    strlen          ;exits hl=length
        ex      de,hl           ;de=length
        pop     bc              ;get string back
        call    __printf_print_aligned
printstr_end:
        pop     de              ;ap
        pop     hl              ;fmt
        jp      __printf_loop

	SECTION	rodata_clib
nullstr:
	defm	"(null)"	
	defb	0
