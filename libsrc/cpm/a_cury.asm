;
;       Small C+ Runtime Library
;
;       CP/M functions
;
;       CPM Plus "userf" custom Amstrad calls, for Amstrad CPC & PCW and ZX Spectrum +3
;
;
;       $Id: a_cury.asm,v 1.2 2016/11/03 09:25:27 stefano Exp $
;

	SECTION code_clib

	PUBLIC	a_cury
	
	EXTERN	subuserf
	INCLUDE	"amstrad_userf.def"

a_cury:
	call subuserf
	defw TE_ASK
	ld l,h
	ld h,0
	ret

