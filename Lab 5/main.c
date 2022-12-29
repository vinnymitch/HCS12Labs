;Vincent Mitchell - ECE 427
;Use this generic program for Shell
;In Dragon12+ RAM address is from $1000-3FFF 
;We use RAM addresses starting at $1000 for scratch pad (variables) and $3FFF for Stack 
        ABSENTRY Entry        ; for absolute assembly: mark this as application entry point
    
; Include derivative-specific definitions 
	INCLUDE 'mc9s12dp256.inc'     ;CPU used by Dragon12+ board
 
 
;----------------------USE $1000-$2FFF for Scratch Pad 
	ORG $1000
Count EQU $7F 
R1 DS.W 1 ; memory storage for counter 
R2 DS.W 1 ; memory storage for counter 
R3 DS.W 1 ; memory storage for counter
D0 DC.B 1  ; storage for hex division digit 0
D1 DS.B 1  ; storage for hex division digit 1
D2 DS.B 1  ; storage for hex division digit 2

;code section
        ORG   $4000     ;Flash ROM address for Dragon12+
Entry:
; ---------- Set-Up ---------- 
	LDS #$4000
 	MOVB #$FF, DDRB ;PortB to output for LEDs
	MOVB #$FF, DDRJ ;PortJ to output 
 	MOVB #$00, DDRH ;PortH to input
 	MOVB #$00, PTJ  ;00 to port J
 	

; ---------- Main Loop ---------- 
	MainLoop:   ;label
	BRSET PTH,%00000000 ,on
	BRCLR PTH,%00000001 ,off
	on:
	JSR Hex
	MOVB #$00, PORTB
	LDAB D0
	STAB PORTB
	
	JSR Delay
	MOVB #$00, PORTB
	LDAB D1
	STAB PORTB
	JSR Delay
	
	MOVB #$00, PORTB
	LDAB D2
	STAB PORTB
  JSR Delay	
  MOVB #$00, PORTB	 
	BRA MainLoop
	off:
	BRA MainLoop
	
; ---------- Subroutine ----------
  Hex: 
  LDD PTH
	LDX #$A
	IDIV
	STAB D0 ; store remainder in D0
  
  XGDX
  LDX #$A
  IDIV
  STAB D1
  
  XGDX
  LDX #$A
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
