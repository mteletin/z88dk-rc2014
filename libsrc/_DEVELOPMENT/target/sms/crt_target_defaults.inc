
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; crt target defaults ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

IF __CRTDEF = -1

   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
   ;; user supplied crt defaults ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
   
   INCLUDE "crtdef.inc"

ENDIF

IF __CRTDEF = 0

   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
   ;; sms standard model ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

   defc TAR__crt_org_code              = 0
   defc TAR__crt_org_data              = 0xc000
   defc TAR__crt_org_bss               = -1

   defc TAR__crt_model                 = 1
   
   defc TAR__register_sp               = 0xdff8
   defc TAR__crt_stack_size            = 256
      
   defc TAR__crt_initialize_bss        = 1
   
   defc TAR__crt_include_preamble      = 0

   defc TAR__crt_enable_streams        = 0
   
   defc TAR__crt_enable_commandline    = 0
   defc TAR__crt_enable_restart        = 1
   defc TAR__crt_enable_close          = 1
   
   defc TAR__crt_enable_eidi           = 0x10
   defc TAR__crt_on_exit               = 0x10001
   
   defc TAR__crt_enable_rst            = 0
   defc TAR__crt_enable_nmi            = 0
   
   ; clib defaults
   
   defc TAR__clib_exit_stack_size      = 0
   defc TAR__clib_quickexit_stack_size = 0
   
   defc TAR__clib_malloc_heap_size     = 0
   defc TAR__clib_stdio_heap_size      = 0
   
   defc TAR__clib_balloc_table_size    = 0
   
   defc TAR__clib_fopen_max            = 0
   defc TAR__clib_open_max             = 0

ENDIF

;; end crt target defaults ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
