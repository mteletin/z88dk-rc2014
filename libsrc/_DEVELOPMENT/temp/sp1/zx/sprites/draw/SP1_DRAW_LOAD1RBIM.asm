
; DRAW LOAD SPRITE 1 BYTE DEFINITION ROTATED, RIGHT BORDER WITH IMPLIED MASK
; 04.2006 aralbrec, Sprite Pack v3.0
; sinclair spectrum version

INCLUDE "clib_target_cfg.asm"

SECTION code_clib
SECTION code_temp_sp1

PUBLIC _SP1_DRAW_LOAD1RBIM

EXTERN _SP1_DRAW_LOAD1LBIM
EXTERN SP1RETSPRDRAW

; following data segment copied into struct sp1_cs

   ld de,0
   nop
   ld hl,0
   call _SP1_DRAW_LOAD1RBIM
   
; following draw code called by way of SP1UpdateNow
;
;  a = hor rot table
; bc = graphic disp
; de = graphic def ptr
; hl = left graphic def ptr
;
; 64 + 8*54 - 6 + 10 = 500 cycles

_SP1_DRAW_LOAD1RBIM:

   cp SP1V_ROTTBL/256
   jp z, SP1RETSPRDRAW

   add hl,bc
   ex de,hl
   ld h,a
   ld l,$ff
   ld c,(hl)
   inc h
   
   ;  h = shift table
   ;  c = constant mask
   ; de = sprite def (graph only)

_SP1Load1RBIMRotate:

   jp _SP1_DRAW_LOAD1LBIM + 13
