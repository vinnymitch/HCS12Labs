;Vincent Mitchell - ECE 427
;Use this generic program for Shell
;In Dragon12+ RAM address is from $1000-3FFF 
;We use RAM addresses starting at $1000 for scratch pad (variables) and $3FFF for Stack 
        ABSENTRY Entry        ; for absolute assembly: mark this as application entry point
    
; Include derivative-specific definitions 
	INCLUDE 'mc9s12dp256.inc'     ;CPU used by Dragon12+ board
 
 
;----------------------USE $1000-$2FFF for Scratch Pad 
	ORG $1000
Count EQU $01  ; initial counter value 
R1 DS.W 1 ; memory storage for counter 
R2 DS.W 1 ; memory storage for counter 
R3 DS.W 1 ; memory storage for counter

;code section
        ORG   $4000     ;Flash ROM address for Dragon12+
Entry:
; ---------- Set-Up ---------- 
 	MOVB #$FF, DDRB      ;Port B to output
	MOVB #$FF, DDRP      ;Port P to output
	MOVB #$00, DDRH     ;Port H to input
	BSET DDRJ, %00000010 ;Bit 1 of DDRJ to 1
 	BCLR PTT, %11111111
 	BCLR PTH, %11111111

; ---------- Main Loop ---------- 
	MainLoop:   ;label
	BRSET PTH,%00000001,on
	BRCLR PTH,%00000001,off
	on:
	MOVB #%00000111, PTP ;right most display
	MOVB #$7D, PORTB ;6 on the 7 seg
	JSR Delay
	MOVB #%00001011, PTP ;second to the right
	MOVB #$67, PORTB ;9 on the 7 seg
	JSR Delay
	BRA MainLoop
	off: 
	MOVB #%00001111, PTP ;all displays off
	BRA MainLoop

; ---------- Subroutine ---------- 
  Delay: 
  MOVB #Count,R1  
  L1: 
    MOVB #Count,R2 
    L2: 
      MOVB #Count,R3 
      L3: 
         DEC R3 
         BNE L3 
      DEC R2 
      BNE L2 
    DEC R1 
    BNE L1
    RTS

;**************************************************************
;*                 Interrupt Vectors                          *
;**************************************************************
            ORG   $FFFE
            DC.W  Entry     ;Reset Vector. CPU wakes here and it is sent to start of the code at $4000
