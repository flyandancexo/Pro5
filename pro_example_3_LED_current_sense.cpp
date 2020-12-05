// LED brightness increases with PWM, and the measured current is output to right LED.
// left led is for PWM value.

// 8-bit ADC - Single Conversion Mode
//ADCSRA - ADC control and status register A
#define JUNO_ADC_CLOCK 7   // 1-7;  F_CPU/ 2-4-8-16-32-64-128

//ADMUX - ADC multiplexer selection register
#define JUNO_ADC_REF 3     // 0-1-3 ; 0=AREF Pin; 1=VCC; 3=Internal 1.1V Voltage Reference
#define ADC_MODE 1         // 0-1; 0=10-bit mode; 1=8-bit;
#define JUNO_ADC_CHANNEL 0 // 0-7 ADC channels; 8=Temperature Sensor; 14= 1.1V (VBG); 15=0V (GND);

#define sf 10

//#####################################################################

#include <inttypes.h>
#include <avr/io.h>

#define F_CPU 8000000UL  // 8 MHz
#include <util/delay.h>

#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "Juno_TM1640.h"

volatile uint8_t newADC;

int main(void){
	
	Juno_TM1640_Init(1);


	
	ADMUX =  (JUNO_ADC_REF<<6) | (ADC_MODE<<5) | JUNO_ADC_CHANNEL;
	ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADIE) | JUNO_ADC_CLOCK;
	sei();

	//D3 (OC2B) Timer2 - PWM frequency= 8000000/256/8= 3906Hz or 4kHz
	TCCR2A= (1<<COM2B1) | (1<<WGM21) | (1<<WGM20);
	TCCR2B= (1<<CS21);
	DDRD |= (1<<3);

	OCR2B=0;

	uint16_t ms=0, delay=0;

	//uint8_t max=0;

	uint8_t sw=0;
	uint8_t swt=0;

	uint8_t tog=0;

	uint8_t Level=0;
	volatile uint16_t total=0;
	uint8_t ampere[sf];
	uint8_t i=0;
	
	while(1){
		
		TM1640_lNum(OCR2B);
		
		if(delay>=100) {
			TM1640_rNum(Level*55/64); //convert to mA
			delay=0;
		}

		//if(ADCH>max) max=ADCH;
		
		if(newADC==1){
			total -= ampere[i];
			ampere[i]=ADCH;
			total += ampere[i];
			i++;
			if( i==sf){ i=0;}
			
			Level=total/sf;
			TM1640_matrix(Level/4);
			
			if(total>255*sf) total=0;
			newADC=0;
		}
		
		
		
		
		if(tog==1){
			sw=1; OCR2B=1;
		}
		else{
			sw=0;
		}
		
		// 1/4k= 250us loop  0.00025s
		if( TIFR2 & (1<<TOV2)){
			delay++;
			
			ms++;
			if(ms>=17000) { tog^=1; ms=0;}
			
			swt++;
			if(swt>=120) {  if(sw==0)OCR2B++;  swt=0; }
			
			
			TIFR2|= (1<<TOV2);
		}
		
		
		TM1640_Write_burst(TM1640_led);
		
	}//<<while
	
}//<<<<main


ISR(ADC_vect){
	newADC=1;
	ADCSRA|= (1<<ADSC);
}
