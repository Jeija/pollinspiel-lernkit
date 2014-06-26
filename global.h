#ifndef _GLOBAL_H
#define _GLOBAL_H

/*
/ Mikrocontroller :
/                                   ATtiny2313
/                              ---------------------  
/                             |                     |
/                   <---PA2---|1(/RESET/dW)   VCC 20|
/           TASTER1 <---PD0---|2(RXD)   (UCSK/SCL)19|---PB7--> ISP Programmer
/           TASTER2 <---PD1---|3(TXD)    (MISO/DO)18|---PB6--> ISP Programmer
/        DISPLAY_RS <---PA1---|4(XTAL2) (./DI/SDA)17|---PB5--> ISP Programmer
/        DISPLAY_E  <---PA0---|5(XTAL1)     (OC1B)16|---PB4--> DISPLAY_Vo
/        EIN_TASTER <---PD2---|6(CKOUT/XCK) (OC1A)15|---PB3--> DISPLAY_DB7
/           TASTER3 <---PD3---|7(INT1)      (OC0A)14|---PB2--> DISPLAY_DB6
/           TASTER4 <---PD4---|8(T0)        (AIN1)13|---PB1--> DISPLAY_DB5
/            SUMMER <---PD5---|9(OC0B/T1)   (AIN0)12|---PB0--> DISPLAY_DB4
/                             |10 GND        (ICP)11|---PD6--> DISPLAY_POWER
/                              ---------------------
/
/ Fuse-Bits: --- für internen Clock ---
/            CKSEL3..0   0100   (1 bedeutet unprogrammiert)
/            SUT1..0     10
/            CKDIV8      0
/
/
/ Frequenz : 1.000.000 Hz   (Grundeinstellung für die Taktfrequenz der CPU bei Werksauslieferung)
/
/ Display  : Die Ansteuerung des HD44780 kompatiblen Display-Controllers
/            erfolgt im 4-Bit-Interfacemodus. Dabei sind folgende Port-Pins
/            des µC mit den Pins des Display-Moduls verfunden.
/            PB0->DB4; PB1->DB5; PB2->DB6; PB3->DB7; PA0->E; PA1->RS;
/             
/ Ports    : Taster  : PD0 -> TASTER1
/                      PD1 -> TASTER2
/                      PD3 -> TASTER3
/                      PD4 -> TASTER4
/                      PD2 -> EIN_TASTER
/            LED     : PD0 -> LED1
/                      PD1 -> LED2
/                      PD3 -> LED3
/                      PD4 -> LED4
/            Summer  : PD5 -> SUMMER
/            Display : PB0 -> DB4
/                      PB1 -> DB5
/                      PB2 -> DB6
/                      PB3 -> DB7
/                      PA0 -> E
/                      PA1 -> RS
*/

#define LED_PORT	PORTD
#define LED_DDR		DDRD
#define BUZZER		5             // Port PD5
#define DISPLAY_Vo	4             // Port PB4
#define DISPLAY_POWER	6             // Port PD6


#define TIMER0_OVR      1
#define TIMER1_OVR      2


#define F_CPU           1000000UL     // Systemtakt 1 MHz

#define sbi(ADDR, BIT) ((ADDR |=  (1<<BIT)))
#define cbi(ADDR, BIT) ((ADDR &= ~(1<<BIT)))
#define gbi(ADDR, BIT) ((ADDR &   (1<<BIT)))
#define tbi(ADDR, BIT) ((ADDR ^=  (1<<BIT)))

#endif
