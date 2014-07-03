#ifndef _DISPLAY_H
#define _DISPLAY_H

/*
/ Dateiname   : display.h
/ Versionsnr. : 1.0.0
/ Datum       : 15.01.2011 
/  
/ Autor		  : Pollin-Team
*/

void InitDisplay(void);
void WriteDisplay(unsigned char data);
void WriteDisplayControl(unsigned char data);
void WriteDisplayData(unsigned char data);
void WriteDisplayString(char *data);
void ClearDisplay(void);
void SleepDisplay(void);
void SetDisplayCursor(uint8_t x, uint8_t y);
void UploadCustomCharacter(uint8_t addr, uint8_t *data);
void WriteCustomCharacter(uint8_t addr);

 
// Display Befehle
#define CLEAR_DISPLAY            0x01
#define CURSOR_HOME              0x02

 
// Pinbelegung des Display an verwendete µC-Pins anpassen
#define PORT_DISPLAY_DATA     PORTB
#define PORT_DISPLAY_RS       PORTA
#define PORT_DISPLAY_E        PORTA
#define DDR_DISPLAY_DATA      DDRB
#define DDR_DISPLAY_RS        DDRA
#define DDR_DISPLAY_E         DDRA
#define BIT_DISPLAY_DATA4     0
#define BIT_DISPLAY_DATA5     1
#define BIT_DISPLAY_DATA6     2
#define BIT_DISPLAY_DATA7     3
#define BIT_DISPLAY_RS        1
#define BIT_DISPLAY_E         0                 



#endif
