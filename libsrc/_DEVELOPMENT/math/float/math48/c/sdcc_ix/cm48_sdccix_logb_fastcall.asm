
; float logb(float x) __z88dk_fastcall

SECTION code_clib
SECTION code_fp_math48

PUBLIC cm48_sdccix_logb_fastcall

EXTERN cm48_sdccixp_dx2m48, am48_logb, cm48_sdccixp_m482d

cm48_sdccix_logb_fastcall:

   call cm48_sdccixp_dx2m48
   
   call am48_logb
   
   jp cm48_sdccixp_m482d