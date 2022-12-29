;Vincent Mitchell - ECE 427
;Use this generic program for Shell
;In Dragon12+ RAM address is from $1000-3FFF 
;We use RAM addresses starting at $1000 for scratch pad (variables) and $3FFF for Stack 
        ABSENTRY Entry        ; for absolute assembly: mark this as application entry point
    
; Include derivative-specific definitions 
	INCLUDE 'mc9s12dp256.inc'     ;CPU used by Dragon12+ board
 
 
;----------------------USE $1000-$2FFF for Scratch Pad 
	ORG $1000
Count EQU $1
R1 DS.W 1 ; memory storage for counter 
R2 DS.W 1 ; memory storage for counter 
R3 DS.W 1 ; memory storage for counter
D0 DS.B 1  ; storage for hex division digit 0
D1 DS.B 1  ; storage for hex division digit 1
D2 DS.B 1  ; storage for hex division digit 2
Codes DC.B  $3F,$06,$5B,$4F,$66,$6D,$7D,$07,$7F,$6F
;code section
        ORG   $4000     ;Flash ROM address for Dragon12+
Entry:
; ---------- Set-Up ---------- 
 	MOVB #$FF, DDRB ;PortB to output for LEDs
 	MOVB #$FF, DDRP ;Port P to output for 7 Seg
	BSET DDRJ, %00000010 ;Bit 1 of DDRJ to 1 
 	MOVB #$00, DDRH ;PortH to input
 	MOVB #$00, PTJ  ;00 to port J
 	BCLR PTT, %11111111
 	BCLR PTH, %11111111

 	

; ---------- Main Loop ---------- 
	MainLoop:   ;label
	BRSET PTH,%00000000 ,on
	BRCLR PTH,%00000001 ,off
	on:
	JSR Hex
	CLRA
	CLRB
	LDX #Codes
	LDAB D2
	LDAA B,X
	MOVB #%00001101, PTP
	STAA PORTB
	
	JSR Delay
	CLRA
	CLRB
	LDX #Codes
	LDAB D1
	LDAA B,X
	MOVB #%00001011, PTP
	STAA PORTB
	
	JSR Delay
	CLRA
	CLRB
	LDAB D0
	LDAA B,X
	MOVB #%00000111, PTP
	STAA PORTB
  
  JSR Delay
MOVB #%00000000, PORTB
	BRA MainLoop
	
	
	off:
	MOVB #%00001111, PTP
	BRA MainLoop
	
; ---------- Subroutine ----------
  Hex: 
  LDD PTH
	LDX #10
	IDIV
	STAB D0 ; store remainder in D0
  
  XGDX
  LDX #10
  IDIV
  STAB D1
  
  XGDX
  LDX #10
  IDIV
  STAB D2
  RTS
  
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
