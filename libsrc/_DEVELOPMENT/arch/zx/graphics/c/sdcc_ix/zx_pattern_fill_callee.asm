
; int zx_pattern_fill_callee(uint x, uint y, void *pattern, uint depth)

SECTION code_clib
SECTION code_arch

PUBLIC _zx_pattern_fill_callee, l0_zx_pattern_fill_callee

EXTERN asm_zx_pattern_fill

_zx_pattern_fill_callee:

   pop af
   pop hl
   exx
   pop bc
   exx
   pop de
   pop bc
   push af

l0_zx_pattern_fill_callee:

   exx
   ld a,c
   exx
   ld h,a
   
   push ix
   call asm_zx_pattern_fill
   pop ix
   
   ret
