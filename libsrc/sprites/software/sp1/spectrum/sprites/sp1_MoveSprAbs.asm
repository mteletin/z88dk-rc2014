; void sp1_MoveSprAbs(struct sp1_ss *s, struct sp1_Rect *clip, uchar *frame, uchar row, uchar col, uchar vrot, uchar hrot)
; CALLER linkage for function pointers

PUBLIC sp1_MoveSprAbs

EXTERN sp1_MoveSprAbs_callee
EXTERN ASMDISP_SP1_MOVESPRABS_CALLEE

.sp1_MoveSprAbs

   pop af
   pop de
   pop bc
   ld b,e
   pop de
   pop hl
   ld d,l
   pop hl
   pop iy
   pop ix
   push hl
   push hl
   push hl
   push hl
   push de
   push bc
   push de
   push af

   jp sp1_MoveSprAbs_callee + ASMDISP_SP1_MOVESPRABS_CALLEE
