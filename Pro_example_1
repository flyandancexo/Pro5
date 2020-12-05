/*Prototype type 5 2020 Nov 11
TM1640 Example
*/

#include <inttypes.h>
#include <avr/io.h>

#define F_CPU 8000000UL  // 8 MHz
#include <util/delay.h>

#include "Juno_TM1640.h"

uint16_t left, right;

int main(void){
	
Juno_TM1640_Init(0); 

	
	while(1){
		
//#################
// 7-segment number
//#################
TM1640_rHex(left);   // hex number (range:0-0xffff)
TM1640_lNum(right);  // decimal number (range:0-9999)
//#################


//#################
// 8x8 Matrix effect
//#################
for( uint8_t i=0; i<4;i++){
	TM1640_led[8+i*2]^=0xff;
	TM1640_led[9+i*2]^=0xff;
};
//#################

//The actual shifting data to TM1640
//TM1640_led is an array of 16 bytes.
TM1640_Write_burst(TM1640_led);

_delay_ms(100);
left++; right++;
	 	 
	}//<<while
	
}//<<<<main

