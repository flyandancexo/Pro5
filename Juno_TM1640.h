//////////////////////////////////////////////////////////////////////////////////
//  Juno TM1640 LED and KEY Library for AVR MCU 
//  Functions Declaration Header File
//  Flyandance 2020 November 15  ||   © All rights reserved.
//////////////////////////////////////////////////////////////////////////////////


#include <avr/io.h>

#ifndef  Juno_TM1640_H
#define  Juno_TM1640_H

#include  "Juno_TM1640_PIN_DEF.h"

/////////////////////////////////////////
//    Pin Definition                   // 
/////////////////////////////////////////

#define TM2W_IO_OUTPUT TM2W_IO_DDR|=BITSELECT(TM1640_IO_PIN)
#define TM2W_IO_L  TM2W_IO_PORT&=~BITSELECT(TM1640_IO_PIN)
#define TM2W_IO_H TM2W_IO_PORT|=BITSELECT(TM1640_IO_PIN)

#define TM2W_SCK_OUTPUT TM2W_SCK_DDR|=BITSELECT(TM1640_SCK_PIN) 
#define TM2W_SCK_L  TM2W_SCK_PORT&=~BITSELECT(TM1640_SCK_PIN) 
#define TM2W_SCK_H TM2W_SCK_PORT|=BITSELECT(TM1640_SCK_PIN) 

#define BITSELECT(a) (1<<a)
             
			 
/////////////////////////////////////////
//    Juno TM1640 - Command            // 
/////////////////////////////////////////		 
			 
#define TM1640_PWM(p)  JUNO_2W_shiftData(0x88|(p) )
#define TM1640_LED_out() TM1640_Write_burst(&TM1640_led[0])

#define TM_HEX 16
#define TM_DEC 10

/////////////////////////////////////////
//    Juno TM1640 - Flyandance         // 
/////////////////////////////////////////

extern uint8_t TM1640_led[16];
extern const uint8_t digitMap[17];

void Juno_TM1640_Init(uint8_t);

void JUNO_2Wx_Start(void);
void JUNO_2Wx_Stop(void);
void JUNO_2Wx_shiftData(uint8_t sData);


void TM1640_Write_burst( uint8_t *data);
void TM1640_Write(uint8_t,uint8_t);
void TM1640_clearLED(void);
void TM1640_LEDbrightness(uint8_t);

//write encoded data to TM1640
void TM1640_lNum ( uint16_t);
void TM1640_lHex ( uint16_t);
void TM1640_rNum ( uint16_t);
void TM1640_rHex ( uint16_t);
void TM1640_matrix ( uint8_t);

/////////////////////////////////////////
//    Juno PINS Marcos                 // 
/////////////////////////////////////////

#if defined TM1640_IO_PORTA
#define TM2W_IO_PORT PORTA
#define TM2W_IO_DDR DDRA
#define TM2W_IO_DATA PINA
#endif

#if defined TM1640_IO_PORTB
#define TM2W_IO_PORT PORTB
#define TM2W_IO_DDR DDRB
#define TM2W_IO_DATA PINB
#endif

#if defined TM1640_IO_PORTC
#define TM2W_IO_PORT PORTC
#define TM2W_IO_DDR DDRC
#define TM2W_IO_DATA PINC
#endif

#if defined TM1640_IO_PORTD
#define TM2W_IO_PORT PORTD
#define TM2W_IO_DDR DDRD
#define TM2W_IO_DATA PIND
#endif

#if defined TM1640_IO_PORTE
#define TM2W_IO_PORT PORTE
#define TM2W_IO_DDR DDRE
#define TM2W_IO_DATA PINE
#endif

#if defined TM1640_IO_PORTF
#define TM2W_IO_PORT PORTF
#define TM2W_IO_DDR DDRF
#define TM2W_IO_DATA PINF
#endif

#if defined TM1640_IO_PORTG
#define TM2W_IO_PORT PORTG
#define TM2W_IO_DDR DDRG
#define TM2W_IO_DATA PING
#endif

#if defined TM1640_SCK_PORTA
#define TM2W_SCK_PORT PORTA
#define TM2W_SCK_DDR DDRA
#endif

#if defined TM1640_SCK_PORTB
#define TM2W_SCK_PORT PORTB
#define TM2W_SCK_DDR DDRB
#endif

#if defined TM1640_SCK_PORTC
#define TM2W_SCK_PORT PORTC
#define TM2W_SCK_DDR DDRC
#endif

#if defined TM1640_SCK_PORTD
#define TM2W_SCK_PORT PORTD
#define TM2W_SCK_DDR DDRD
#endif

#if defined TM1640_SCK_PORTE
#define TM2W_SCK_PORT PORTE
#define TM2W_SCK_DDR DDRE
#endif

#if defined TM1640_SCK_PORTF
#define TM2W_SCK_PORT PORTF
#define TM2W_SCK_DDR DDRF
#endif

#if defined TM1640_SCK_PORTG
#define TM2W_SCK_PORT PORTG
#define TM2W_SCK_DDR DDRG
#endif

#endif
