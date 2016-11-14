;	Sprinter fcntl library
;
;	$Id: fdgetpos.asm,v 1.3 2016/03/13 18:14:13 dom Exp $
;


		SECTION	  code_clib
                PUBLIC    fdgetpos

;int fgetpos(int fd, long *dump)
;
;Dumps in dump the file position, and returns 0 if all went well


.fdgetpos
	pop	bc
	pop	de	;dump
	pop	hl	;fd
	push	hl
	push	de
	push	bc
	push	ix	;save callers
	push	de	;save it for later
	ld	a,l
	ld	hl,0
	ld	ix,0
	ld	b,1	;from current position
	ld	c,$15	;MOVE_FP
	rst	$10
	pop	de	;where to store it
	jr	nc,fdgetpos_ret
	ld	hl,-1
	pop	ix
	ret
.fdgetpos_ret
	ex	de,hl
	ld	(hl),e
	inc	hl
	ld	(hl),d
	inc	hl
	push	ix
	pop	de
	ld	(hl),e
	inc	hl
	ld	(hl),d
	ld	hl,0	;all ok
	pop	ix
	ret

