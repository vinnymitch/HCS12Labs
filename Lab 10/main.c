#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


unsigned int i;
unsigned int t1;
unsigned int val;

void timer(unsigned int);


void main(void) {
  DDRT = 0xFF; //Bit 0 PORT T to output for Speakers
  TSCR1 = 0x90;  //timer enable, CPU clears flags 
  TSCR2 = 0x06;  //no interrupt, prescaler=64
  TIOS = TIOS | 0b00100000; //Channel 5 to output capture 
  TCTL1 = 0b00000100; //TCTL1 toggle port 5 on match 

  
  for(;;) {
  
  timer(444);
  
  }
}

void timer(unsigned int t)
{

for(val=0; val<t; val++) 
{ 
	int t1 = TCNT;
	t1 = TCNT + val; //add desired delay 
	TC5 = t1; //store value in the desired TC register
	while(!(TFLG1 & TFLG1_C5F_MASK)); 
}
}
