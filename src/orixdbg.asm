#include "../orix/src/include/orix.h"
#include "../orix/src/include/macro.h"
#include "../orix/src/include/6551.h"
#include "../orix/src/include/keyboard.h"

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
/*  
#define ACIADR $031C
#define ACIASR $031D ; STATUS REGISTER
#define ACIACR $031E ; control register
#define ACIACT $031F
*/  
  PRINT(str_menu)
 
 start_commandline
    BRK_ORIX(XRDW0)       ; read keyboard
    bmi start_commandline    ; don't receive any specials chars (that is the case when funct key is used : it needs to be fixed in bank 7 in keyboard management
    cmp #"1"
    beq start_console
    cmp #"2"
    beq dump_acia    
    
    cmp #KEY_ESC
    beq exit
    jmp start_commandline
start_console
    jsr CONSOLE 
    jmp start_commandline
dump_acia
    jsr dump_acia_register
 exit
    rts
  ;lda   $232T
dump_acia_register  

  RETURN_LINE
  PRINT(str_ACIACR)

  lda ACIACR
  jsr _print_hexa

  
  RETURN_LINE
  PRINT(str_ACIASR)

  lda ACIASR
  jsr _print_hexa

  
loop

  RETURN_LINE
  jsr wait
/*
  PRINT(str_ACIADR)
  lda ACIADR
  BRK_ORIX(XHEXA)
  BRK_ORIX(XWR0)    
  RETURN_LINE
  */
 ; rts
  lda   #<str
  ldy   #>str
  BRK_TELEMON(XWSTR0)

  lda   #$41
  BRK_TELEMON(XSOUT)
  jmp loop
  
  /*
	lda #XKBD
	BRK_TELEMON(XOP0)
  
  lda     #XRSS ; Setup keyboard on channel 0
  BRK_TELEMON(XOP0)
loop	
  lda     #$41
	BRK_TELEMON(XWR0) 
  jmp loop
  */
	rts
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
CONSOLE    
  BRK_ORIX(XCONSO)
  rts

str_menu:
.asc "1 Read RS232 input and displays",$0A,$0D
.asc "2 Output ACIA registers",$0A,$0D
.asc "3 Send 'A' 20 times",$0A,$0D,0
    
  
save    
.byt 0  
str    
.asc "RS232 sending ... ",$0A,$0D,0   
str_ACIACR
  .asc "_ACIACR : ",0  
str_ACIASR
  .asc "_ACIASR : ",0  
str_ACIADR
  .asc "_ACIADR : ",0    
EndOfMemory

