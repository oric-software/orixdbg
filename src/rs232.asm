#include "../orix/src/include/orix.h"
#include "../orix/src/include/macro.h"
#include "../orix/src/include/6551.h"
#include "../orix/src/include/keyboard.h"



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


  