Pro 5 Pinout

+++++++++++++++++++++++++++++++++++++++++++++++++++++
TM1640 Din-> D1; Sclk-> D0
G1-G4==> Left 7-segment
G5-G8==> Right 7-segment
G9-G16=> 8x8 Matrix
+++++++++++++++++++++++++++++++++++++++++++++++++++++

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
3 Buttons--> C6
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
AT24, LM75, PCF8563--> I2C(C4[SDA], C5[SCL])
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Sound Level (Mic OpAmp Vout) --> C7
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

=====================================================
LED Control --> D3 (OC2B) Timer2
USB Control --> D5 (OC0B) Timer0 
LED & USB Current Sense --> C0 (INA180N-(A2-50X)- 0.10hm - 2 order RC filter)
0.444V measured at Vout with a voltage drop of 8.9mV on the 0.1ohm resistor. 50 times amplification!
A=V/R = 0.0089/0.1=0.08A or 89mA ( with OCR2B equals to 50 ) 

35mV measured at Vout with a voltage drop of 0.7mV on the 0.1ohm resistor. 50 times amplification, slightly Off!
A=V/R = 0.0007/0.1=0.007A or 7mA ( with OCR2B equals to 1 )

A= V/5 = 0.444V/5=0.089mA

Expected result - AVR 1.1V reference, 8-bit (0-255)
0.444/1.1*256= 103
0.035/1.1*256= 8

At 4k PWM frequency, it will take about 125us (1/4k*2) for the filters to stabilize. 

ADC took 13 cycles for one conversion, 
@ 8000000Hz, the time for 1 conversion = 1/ 8000000/13=9ns

125us/9ns= 1250/9= 138

c= 1/4000/(2*3.14*1000) = 20nf

Math conversion: the Art of basic algebra 
0.444/1.1*256= 103
103/256*1.1= 0.442 *1000 / 5 = 88 mA
103/256/5 *1.1 *1000 =88 mA
103/256 *1.1 *200 =88 mA
103/256*220 =88 mA
103*220/256 =88 mA
103*55/64 =88 mA  

>>> ADC* 55/64 = mA <<< 
=====================================================

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
Battery Switch --> D7
Battery Charger Switch --> D2 (active LOW)

Battery Voltage Check  --> C3
Battery Charger Current--> C1 (LM358 - 0.5-Ohm - V=5*I)

Mega Load (3x51-ohm (1W) parallel = 17-Ohms (3W) --> D6 (OC0A) Timer0 (For battery)
P=R*I^2 --> I= sq(3/17)=0.42A max

Mega Load Current--> C2 (LM358 - 0.5-Ohm - V=5*I - 2 order RC filter)
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
