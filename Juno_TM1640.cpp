//////////////////////////////////////////////////////////////////////////////////
//  Juno TM1640 LED and KEY Library for AVR MCU 
//  Functions Definition File
//  Flyandance 2020 November 15  ||   © All rights reserved.
//////////////////////////////////////////////////////////////////////////////////

#include  "Juno_TM1640.h"

uint8_t TM1640_led[16]={ 0x66, 0x6D, 0x7D, 0x07, 
	0x3F, 0x06, 0x5B, 0x4F, 
	0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55};

const uint8_t digitMap[17] =  //7-Segments LED mapping
  {
  //HGFEDCBA  
  0b00111111, // 0  0x3F
  0b00000110, // 1  0x06
  0b01011011, // 2  0x5B
  0b01001111, // 3  0x4F
  0b01100110, // 4  0x66
  0b01101101, // 5  0x6D
  0b01111101, // 6  0x7D
  0b00000111, // 7  0x07
  0b01111111, // 8  0x7F
  0b01101111, // 9  0x6F
  
  //HGFEDCbA 
  0b01110111, // A  0x77 (10)
  0b01111100, // b  0x7C
  0b00111001, // C  0x39
  0b01011110, // d  0x5E
  0b01111011, // e  0x79
  0b01110001, // F  0x71 (15)
	0b10000000
  };

// Juno TM1640 Initialization 1-8 pwm LED brightness level
void Juno_TM1640_Init(uint8_t pwm){
  TM2W_IO_OUTPUT;
  TM2W_SCK_OUTPUT;	

  //Set brightness level
	TM1640_LEDbrightness(pwm);
	
	//Write initial data to TM1640
  TM1640_Write_burst(TM1640_led);
	
	//Clear TM1640 LED data
	//TM1640_clearLED();
}


// Left 7-segment (4-digit)
void TM1640_lNum ( uint16_t num){
    TM1640_led[4]= digitMap[num/100/10];  // 1234/100/10=1
    TM1640_led[5]= digitMap[num/100%10];  // 1234/100%10=2
    TM1640_led[6]= digitMap[num/10%10];   // 1234/10%10 =3
    TM1640_led[7]= digitMap[num%10];      // 1234%10    =4
	  //TM1640_Write_burst(TM1640_led);
}

// Right 7-segment (4-digit)
void TM1640_lHex ( uint16_t hex ){
	TM1640_led[4]= digitMap[hex/16/16/16];  // 0xabcd/(1+f)/(1+f)/(1+f)=0xa
	TM1640_led[5]= digitMap[hex/16/16%16];  // 0xabcd/(1+f)/(1+f)%(1+f)=0xb
	TM1640_led[6]= digitMap[hex/16%16];     // 0xabcd/(1+f)%(1+f)=0xc
	TM1640_led[7]= digitMap[hex%16];        // 0xabcd%(1+f)=0xd
	//TM1640_Write_burst(TM1640_led);
}


// Right 7-segment (4-digit)
void TM1640_rNum ( uint16_t num ){
    TM1640_led[0]= digitMap[num/100/10];  // 1234/100/10=1
    TM1640_led[1]= digitMap[num/100%10];  // 1234/100%10=2
    TM1640_led[2]= digitMap[num/10%10];   // 1234/10%10 =3
    TM1640_led[3]= digitMap[num%10];      // 1234%10    =4
		//TM1640_Write_burst(TM1640_led);
}

// Right 7-segment (4-digit)
void TM1640_rHex ( uint16_t hex ){
	TM1640_led[0]= digitMap[hex/16/16/16];  // 0xabcd/(1+f)/(1+f)/(1+f)=0xa
	TM1640_led[1]= digitMap[hex/16/16%16];  // 0xabcd/(1+f)/(1+f)%(1+f)=0xb
	TM1640_led[2]= digitMap[hex/16%16];     // 0xabcd/(1+f)%(1+f)=0xc
	TM1640_led[3]= digitMap[hex%16];        // 0xabcd%(1+f)=0xd
	//TM1640_Write_burst(TM1640_led);
}


// 8x8=64
void TM1640_matrix ( uint8_t input ){
	
	
	 for( uint8_t i=8; i<16; i++){
		TM1640_led[i]=0 ;
	  }
		
	if(input<63){	
	for( uint8_t i=0; i<input; i++){
		TM1640_led[8+i/8] |= (1<< (7- (i%8)) ) ;
	}
	}
	
}



//#######################################################
// Low Level Logics
//#######################################################
// Start Condition
void JUNO_2Wx_Start(void){
	TM2W_SCK_H;
  TM2W_IO_H;
	TM2W_IO_L;
  TM2W_SCK_L;
}

// Stop Condition
void JUNO_2Wx_Stop(void){
  TM2W_SCK_L;
  TM2W_IO_L;
  TM2W_SCK_H;
  TM2W_IO_H;
}

// Shift Out LSB First
void JUNO_2Wx_shiftData(uint8_t sData) {
	for( int8_t i=0;i<8;i++){
		TM2W_SCK_L;
		if ( sData & (1 << i) ) TM2W_IO_H;
		else TM2W_IO_L;
		TM2W_SCK_H;
	}
	TM2W_SCK_L;
}

// Burst write 16 bytes
void TM1640_Write_burst( uint8_t *data){
	
JUNO_2Wx_Start();
JUNO_2Wx_shiftData(0x40);
JUNO_2Wx_Stop();

JUNO_2Wx_Start();
JUNO_2Wx_shiftData(0xc0|0);

for( uint8_t i=0; i<16; i++){
JUNO_2Wx_shiftData(data[i]);
}

JUNO_2Wx_Stop();
}

// Clear all LED data
void TM1640_clearLED(){
	
	JUNO_2Wx_Start();
	JUNO_2Wx_shiftData(0x40);
	JUNO_2Wx_Stop();

	JUNO_2Wx_Start();
	JUNO_2Wx_shiftData(0xc0|0);

	for( uint8_t i=0; i<16; i++){
		JUNO_2Wx_shiftData(0);
	}

	JUNO_2Wx_Stop();
}

// Write 1 byte to a fixed address, start with address 0, end with 15
void TM1640_Write(uint8_t add,uint8_t data) {
  JUNO_2Wx_Start();
	JUNO_2Wx_shiftData(0x44);
	JUNO_2Wx_Stop();
	
	JUNO_2Wx_Start();
  JUNO_2Wx_shiftData(0xc0|add); 
  JUNO_2Wx_shiftData(data);
  JUNO_2Wx_Stop();
}


// LED brightness control (0-7)
void TM1640_LEDbrightness(uint8_t brightness){
	
	JUNO_2Wx_Start();
	JUNO_2Wx_shiftData(0x88 | brightness );
	JUNO_2Wx_Stop();
}
