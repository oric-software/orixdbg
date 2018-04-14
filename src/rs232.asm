#include "../orix/src/include/orix.h"
#include "../orix/src/include/macro.h"
#include "../orix/src/include/6551.h"
#include "../orix/src/include/keyboard.h"
/*
    *=$1000-20
; include header
  .byt $01,$00	      	; non-C64 marker like o65 format
  .byt "o", "r", "i"      ; "ori" MAGIC number :$6f, $36, $35 like o65 format
  .byt $01                ; version of this header
cpu_mode
  .byt $00                ; CPU see below for description
language_type
  .byt $00	             ; reserved in the future, it will define if it's a Hyperbasic file, teleass file, forth file 
  .byt $00                ; reserved
  .byt $00		            ; reserved
  .byt $00	              ; operating system id for telemon $00 means telemon 3.0 version
  .byt $00	              ; reserved
	.byt $00                ; reserved
type_of_file
	.byt %01001001                   ; Auto, direct, data for stratsed, sedoric, ftdos compatibility
	.byt <start_adress,>start_adress ; loading adress
	.byt <EndOfMemory,>EndOfMemory   ; end of loading adress
	.byt <start_adress,>start_adress ; starting adress
 
start_adress
 
	*=$1000
  */
/*  
#define ACIADR $031C
#define ACIASR $031D ; STATUS REGISTER
#define ACIACR $031E ; control register
#define ACIACT $031F
*/



_send_byte_rs232
.(
  lda   #$41
  BRK_ORIX(XSOUT)
  rts
.)
  
_print_hexa:
    pha
    CPUTC("#")
    pla

    BRK_ORIX(XHEXA)
    sty save
    
    BRK_ORIX(XWR0)
    lda save
    BRK_ORIX(XWR0)
    rts 
  
wait:
.(
    ldy #$00
loop2    
    ldx #$00
loop1
   
    inx
    bne loop1
    iny
    bne loop2
.)    
    rts
_rs232_console
 loop
  BRK_ORIX(XCONSO)
  jmp loop
  rts
save
.byt 0


  