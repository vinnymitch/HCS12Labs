#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


unsigned int i;
unsigned int b1;
unsigned int t1;
unsigned int val;
unsigned int s1; 

void blink(unsigned int);
void timer(unsigned int);
void sound(unsigned int);

void main(void) {
  DDRB = 0xFF; //LED PORT TO OUTPUT
  DDRJ = 0xFF; //PORT J to output
  DDRT = 0x20; //Bit 5 PORT T to output for Speakers
  PTJ = 0x00;  //Enable LEDS with PORT J
  DDRP = 0x0F; //Enable Port P to turn off 7 segs
  PTP = 0xFF;  //Turn off 7 Segs
  DDRH = 0x00; //DDRH as input
  TSCR1 = 0x90;  //timer enable, CPU clears flags 
  TSCR2 = 0x07;  //no interrupt, prescaler=128
  TIOS = TIOS | 0b00000001; //Channel 0 to output capture 
  TCTL2 = 0b00000000; //TCTL2 toggle port 2 on match 

  
  for(;;) {
  
  blink(7);
  sound(100000);
  
  }
}

void timer(unsigned int t)
{

for(val=0; val<t; val++) 
{ 
	int t1 = TCNT;
	t1 = TCNT + val; //add desired delay 
	TC0 = t1; //store value in the desired TC register
	while(!(TFLG1 & TFLG1_C0F_MASK)); 
}
}

void blink(unsigned int b)
{

for(b1=0; b1<b; b1++)
{

  PORTB=0xFF;
  timer(500);
  PORTB=0x00;
  timer(500);
}
}

void sound(unsigned int s)
{
	for(s1=0; s1<s; s1++)
{
	PTT = 0b00100000;
	timer(10);
	PTT = 0b00000000;
	timer(10);
}
}
