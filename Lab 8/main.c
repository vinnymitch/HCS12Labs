#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


unsigned int i;
unsigned int x=0x80;
unsigned int y;
unsigned int b1;

void blink(unsigned int);
void flash(unsigned int);
void MSDelay(unsigned int);
void main(void) {
  DDRB = 0xFF; //LED PORT TO OUTPUT
  DDRJ = 0xFF; //PORT J to output
  PTJ = 0x00;  //Enable LEDS with PORT J
  DDRP = 0x0F;
  PTP = 0xFF;  //Turn off 7 Segs
  DDRH = 0x00; //DDRH as input
  
  for(;;)
  {
   unsigned int switches;
   switches=PTH&0xF0; 
  	if((PTH&0x01)==0)
  	{
  	blink(switches); //Blink = the binary number inputted on sw3-sw0
  	}
 	else
 	{
 	flash(8); //Flashes through all 8 LEDS once, will need to play if u want continuous
 	}
  }
}

void flash(unsigned int k) {
 
 for(i=0;i<k; i++);
 {	
 y = x >> 1;
 x=y;
 PORTB=y;
 MSDelay(250);
 
 }
 
 {
 	
 }
}

void MSDelay(unsigned int t) 
{ 
 unsigned int i; 
 unsigned int j; 
  
 for(i=0;i<t;i++) 
  for(j=0;j<2020;j++); 
}

void blink(unsigned int b)
{

for(b1=0; b1<b; b1++)
{

  PORTB=0xFF;
  MSDelay(1000);
  PORTB=0x00;
  MSDelay(1000);

}
}
