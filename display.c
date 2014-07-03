/*
/ Dateiname   : display.c
/ Versionsnr. : 1.0.0
/ Datum       : 15.01.2011 
/  
/ Autor		  : Pollin-Team
*/

 
#include <avr/io.h>
#include <util/delay.h>
#include "display.h"

 
 
/* -------------------------------------------------------------------------------------
   Initialisierungsroutine f�r das Display 
   Parametereinstellungen: 4 Bit Modus aktivieren                   0x02
  	      			       2 Zeilen, Zeichen 5x7                    0x28	
                           Display ein, Cursor aus, kein Blinken    0x0C 
                           Speicher inkrementieren, kein Scrollen   0x06
--------------------------------------------------------------------------------------*/ 
void InitDisplay(void)
{
    // Setze Port-Direction-Register f�r DATA4 bis DATA7 sowie RS und E auf Ausgang
    DDR_DISPLAY_DATA |= ((1<<BIT_DISPLAY_DATA4) | (1<<BIT_DISPLAY_DATA5) | (1<<BIT_DISPLAY_DATA6) | (1<<BIT_DISPLAY_DATA7)); 
    DDR_DISPLAY_RS   |= (1<<BIT_DISPLAY_RS);      
    DDR_DISPLAY_E    |= (1<<BIT_DISPLAY_E);       

 
    _delay_us(15000);											    // --- Warte 15 ms nach Power-On ---

   
   // Setze RS auf low um Daten ins Steuerregister zu schreiben
   PORT_DISPLAY_RS &= ~(1<<BIT_DISPLAY_RS);     				    // Setze RS auf 0; Steuerregister
 

   // Initialisierung erfolgt noch mit 8 Bit
   // Function set 0x03;
   PORT_DISPLAY_DATA |=  (1<<BIT_DISPLAY_DATA4);	    			// Setze DB4 auf 1
   PORT_DISPLAY_DATA |=  (1<<BIT_DISPLAY_DATA5);	    			// Setze DB5 auf 1
   PORT_DISPLAY_DATA &= ~(1<<BIT_DISPLAY_DATA6);					// Setze DB6 auf 0
   PORT_DISPLAY_DATA &= ~(1<<BIT_DISPLAY_DATA7);					// Setze DB7 auf 0

   PORT_DISPLAY_RS   &= ~(1<<BIT_DISPLAY_RS);				        // Setze RS  auf 0   


   // --- Enable-Puls f�r Daten�bernahme erzeugen ---
   PORT_DISPLAY_E |=  (1<<BIT_DISPLAY_E);
   _delay_us(10);                

   PORT_DISPLAY_E &= ~(1<<BIT_DISPLAY_E);
 
   _delay_us(4100);		      

 
   // Sende Kommando 4 Bit Modus zu aktivieren
   // Function set 0x02;
   PORT_DISPLAY_DATA &= ~(1<<BIT_DISPLAY_DATA4);	    			// Setze DB4 auf 0
   PORT_DISPLAY_DATA |=  (1<<BIT_DISPLAY_DATA5);	    			// Setze DB5 auf 1 
   PORT_DISPLAY_DATA &= ~(1<<BIT_DISPLAY_DATA6);	    			// Setze DB6 auf 0
   PORT_DISPLAY_DATA &= ~(1<<BIT_DISPLAY_DATA7);	    			// Setze DB7 auf 0   

   // --- Enable-Puls f�r Daten�bernahme erzeugen ---
   PORT_DISPLAY_E |=  (1<<BIT_DISPLAY_E);
   _delay_us(10);                

   PORT_DISPLAY_E &= ~(1<<BIT_DISPLAY_E);
   _delay_us(1000);
 
   WriteDisplayControl(0x28);								    	// 4Bit / 2 Zeilen / 5x7
   WriteDisplayControl(0x0C); 								    	// Display ein / Cursor aus / kein Blinken	
   WriteDisplayControl(0x06);										// inkrement / kein Scrollen
 
   ClearDisplay();
}



/* -------------------------------------------------------------------------------------
   Funktion :	      Sendet einen Befehl bzw Daten im 4-Bit-Modus an das Steuer oder
					  Datenregister des Displays entsprechend der Funktion WriteDisplayControl() 
					  oder WriteDisplayData() die diese Funktion aufruft.  
   Parameter�bergabe: Input     : data     Byte das an das Display gesendet werden soll
                      Return    : -
--------------------------------------------------------------------------------------*/ 
void WriteDisplay(unsigned char data)
{

   // l�scht zuerst die Daten die an den Portpins f�r das Display anliegen und
   // schiebt dann die Oberen vier Bits von Data nach Unten (auf PB0 bis PB3)
   // und sendet sie an das Display 
   PORT_DISPLAY_DATA &= ~((1<<BIT_DISPLAY_DATA4) | (1<<BIT_DISPLAY_DATA5) | (1<<BIT_DISPLAY_DATA6) | (1<<BIT_DISPLAY_DATA7));					
   PORT_DISPLAY_DATA |= (data>>4);	

   // --- Enable-Puls f�r Daten�bername erzeugen ---
   PORT_DISPLAY_E |=  (1<<BIT_DISPLAY_E);
   _delay_us(500);                
   PORT_DISPLAY_E &= ~(1<<BIT_DISPLAY_E);

   // l�scht zuerst die Daten die an den Portpins f�r das Display anliegen und
   // l�scht danach die Oberen vier Bits von Data und sendet dann die Unteren vier
   // Bits von Data (auf PB0 bis PB3) an das Display 
   PORT_DISPLAY_DATA &= ~((1<<BIT_DISPLAY_DATA4) | (1<<BIT_DISPLAY_DATA5) | (1<<BIT_DISPLAY_DATA6) | (1<<BIT_DISPLAY_DATA7));					
   PORT_DISPLAY_DATA |= (data & 0x0F);


   // --- Enable-Puls f�r Daten�bername erzeugen ---
   PORT_DISPLAY_E |=  (1<<BIT_DISPLAY_E);
   _delay_us(500);                
   PORT_DISPLAY_E &= ~(1<<BIT_DISPLAY_E);


}


 
/* -------------------------------------------------------------------------------------
   Funktion :		  Sendet einen Befehl im 4-Bit-Modus an das Steuerregister des Displays 
   Parameter�bergabe: Input     : data     Byte das an das Display gesendet werden soll
					  Return    : -
--------------------------------------------------------------------------------------*/ 
void WriteDisplayControl(unsigned char data)
{
   _delay_us(500);
 
   PORT_DISPLAY_RS &= ~(1<<BIT_DISPLAY_RS);        				// RS auf 0 setzen
   
   WriteDisplay(data);
}



/* -------------------------------------------------------------------------------------
   Funktion :		  Sendet Daten im 4-Bit-Modus an das Datenregister des Displays 
   Parameter�bergabe: Input     : data     Byte das an das Display gesendet werden soll
                      Return    : -
--------------------------------------------------------------------------------------*/ 
void WriteDisplayData(unsigned char data)
{
   _delay_us(500);
 
   PORT_DISPLAY_RS |=  (1<<BIT_DISPLAY_RS);      					// RS auf 1 setzen
 
   WriteDisplay(data);
}



/* -------------------------------------------------------------------------------------
   Funktion :         Diese Routine l�scht den am Display angezeigten Text 
   Parameter�bergabe: Input     : - 
                      Return    : -
--------------------------------------------------------------------------------------*/ 
void ClearDisplay(void)
{
   WriteDisplayControl(CLEAR_DISPLAY);

   _delay_us(5000); 
}


/* -------------------------------------------------------------------------------------
   Funktion :         Diese Routine positioniert den Cursor in der Zeile y (1..2) und
					  Spalte x (0..8) 
   Parameter�bergabe: Input     : y           Zeile  (1..2) 
                                  x           Spalte (0..8)
                      Return    : -
--------------------------------------------------------------------------------------*/ 
void SetDisplayCursor(unsigned char x, unsigned char y)
{
    unsigned char tmp; 

    if(y==1)
		tmp=0x80+0x00+x;     // 1. Zeile
    else 
		tmp=0x80+0x40+x;     // 2. Zeile
  
    WriteDisplayControl(tmp);
}
 

/* -------------------------------------------------------------------------------------
   Funktion :   	  Diese Routine sendet einen String an das Display  
   Parameter�bergabe: Input     : *data       der zu sendende Text 
                      Return    : -
--------------------------------------------------------------------------------------*/ 
void WriteDisplayString(char *data)
{
    while(*data)
    {
        WriteDisplayData(*data);
        data++;
    }
}



/* -------------------------------------------------------------------------------------
   Funktion :              Diese Funktion setzt die Pins des �C die f�r die Ansteuerung 
                           des Displays ben�tigt werden, w�hrend des Sleep-Modus des �C,
                           in einen hochohmigen Zustand und tragen somit zur Engergieeinsparung 
						   im Sleep-Modus bei.
   Parametereinstellungen: Input     : - 
						   Return    : -
--------------------------------------------------------------------------------------*/ 
void SleepDisplay(void)
{
    // Setze Port-Direction-Register f�r DATA4 bis DATA7 sowie RS und E auf Eingang
    DDR_DISPLAY_DATA &= ~((1<<BIT_DISPLAY_DATA4) | (1<<BIT_DISPLAY_DATA5) | (1<<BIT_DISPLAY_DATA6) | (1<<BIT_DISPLAY_DATA7)); 
    DDR_DISPLAY_RS   &= ~(1<<BIT_DISPLAY_RS);      
    DDR_DISPLAY_E    &= ~(1<<BIT_DISPLAY_E);       

    // Setze Port-Pins auf Low-Pegel f�r DATA4 bis DATA7 sowie RS und E
    PORT_DISPLAY_DATA &= ~((1<<BIT_DISPLAY_DATA4) | (1<<BIT_DISPLAY_DATA5) | (1<<BIT_DISPLAY_DATA6) | (1<<BIT_DISPLAY_DATA7)); 
    PORT_DISPLAY_RS   &= ~(1<<BIT_DISPLAY_RS);      
    PORT_DISPLAY_E    &= ~(1<<BIT_DISPLAY_E);       
}


// Ab hier: (c) Florian Euchner, Datum: 03.07.14
/* -------------------------------------------------------------------------------------
   Funktion: Diese Routine schreibt einen custom character in den CGRAM
   Parameter�bergabe: Input     : addr: Die Adresse des zu schreibenden custom character,
					von 0-7
				: data: 8 bytes, die das Aussehen des custom character
					beschreiben (binary 1=on, binary 0=off)
                      Return    : -
--------------------------------------------------------------------------------------*/ 
void UploadCustomCharacter(uint8_t addr, uint8_t *data)
{
	WriteDisplayControl(0x40 + addr*8);
	for (uint8_t i = 0; i < 8; i++)
		WriteDisplayData(data[i]);
	WriteDisplayControl(0x02);
}

/* -------------------------------------------------------------------------------------
   Funktion: Diese Routine l�dt einen custom character aus dem CGRAM aufs LCD
   Parameter�bergabe: Input     : addr: Die Adresse des zu schreibenden custom character,
					von 0-7
                      Return    : -
--------------------------------------------------------------------------------------*/ 
void WriteCustomCharacter(uint8_t addr)
{
	WriteDisplayData(addr);
}
