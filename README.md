# Pollin-Spiel Lernkit #

**Dieses Projekt befindet sich noch in einem sehr frühen Entwicklungsstadium und wird wahrscheinlich noch aktualisiert!**

Dieses Programm dient als alternative Firmware für das Pollin Spiel und soll es Mikrocontroller-anfängern oder kompletten Programmiereinsteigern ermöglich schnell und einfach Programme für AVRs entwickeln.

## Abhängigkeiten ##
* avr-gcc
* avr-libc
* avrdude
* make

Getestet unter Archlinux mit AVR-GCC 4.8.2

## High-Level Funktionen ##
Das Hauptprogramm ist in pollinspiel.c. `init();` muss das Programm beginnen und `done();` beenden. Diese Funktionen kümmern sich um die komplette Initialisierung von Display und Hardwarekonfiguration (Buttons als Inputs). Ein hoher Ton kündigt die abgeschlossene Initialisierung an, ein tiefer Ton bedeutet das Ende des Programms.

* `void setled(uint8_t LED, uint8_t state);`
	- Leuchtdiode mit Bezeichnung LED auf state schalten
* `char getbutton(char button);`
	- Status von Knopf mit Bezeichnung button abfragen (1 = gedrückt / 0 = lose)
* `void sound(int freq, int duration);`
	- Ton mit Frequenz freq für duration Millisekunden abspielen.
	- Zu große Werte für freq und duration können zu Fehlfunktion führen, deshalb in Schleife packen
* `void waitms(int ms);`
	- Das Programm für ms Millisekunden pausieren. Wie `_delay_ms()`, aber nimmt auch Variablen.
* `void setledByNum(uint8_t lednum, uint8_t state);`
	- Wie setled, allerdings kann die LED auch mit einer Nummer angegeben werden
	- Die Nummer enstpricht der Bezeichnung der LED (LED3 --> 3)
* `void WriteDisplayString(char *data);`
	- Den String data auf dem Display ausgeben
* `void ClearDisplay(void);`
	- Den Displayinhalt löschen
* `void SetDisplayCursor(uint8_t y, uint8_t x);`
	- Den Displaycursor für WriteDisplayString auf y (Zeile), x (Zeichen) verschieben

### Low-Level ###
* `sbi(ADDR, BIT)`
	- Das Bit mit der Nummer BIT im Byte ADDR setzen  (auf 1)
* `cbi(ADDR, BIT)`
	- Das Bit mit der Nummer BIT im Byte ADDR löschen (auf 0)
* `gbi(ADDR, BIT)`
	- Gibt das Bit mit der Nummer BIT im Byte ADDR zurück
* `tbi(ADDR, BIT)`
	- Den Status des Bits BIT im Byte ADDR wechseln (0 zu 1 und 1 zu 0)

### Systimer ###
Die aktuelle Zeit in Millisekunden nach dem Systemstart kann ständig in `float SYSTMIME` verfügbar gemacht werden. Die Funktion ist allerdings standardmäßig deaktiviert, da ein dafür benötigtes Interrupt z.B. beim Abspielen von kontinuierlichen Tönen stört. Um sie zu aktivieren muss
```C
//#include "systimer.h"
```
in pollinspiel.h als auch in util.c zu
```C
#include "systimer.h"
```
abgeändert werden. Außerdem muss
```C
//systimer_init();
```
in der Funktion init() in util.c zu
```C
systimer_init();
```
abgeändert werden.

## Hardwarebezeichnungen

### LED Status: ###
* `LED_ON`  LED angeschaltet
* `LED_OFF` LED ausgeschaltet
Für Funktion setled und setledByNum `uint8_t state`.

### Buttons ###
* `BUTTON1`
* `BUTTON2`
* `BUTTON3`
* `BUTTON4`
* `BUTTON5`
Button 1-4 wie auf Platine, Button 5 ist Einschaltknopf.

### LEDs: ###
* `LED1`
* `LED2`
* `LED3`
* `LED4`
LEDs wie auf der Platine verzeichnet.

## Samples ##
Im Ordner samples/ sind Beispielprogramme enthalten, aktuell nur eines. Diese können 1:1 in pollinspiel.c kopiert werden.
* sample_zufallsgenerator.c
	- Beim Drücken der EIN-Taste (BUTTON5) leuchten die LEDs nacheinander im Kreis langsamer werdend auf
	- Nach einer Weile steht fest, welche LED zufällig an ist. Ein Piepsen ertönt.
	- Das Programm kann durch erneutes drücken der EIN-Taste neugestartet werden.
	- Display wird nicht verwendet.

## Lizenz ##
Die Dateien display.c, display.h sowie Teile von global.h stammen aus http://www.pollin.de/shop/downloads/D810148S.ZIP . Alle Rechte sind dem Autor vorbehalten.
Den gesamten weiteren Quelltext veröffentlich ich unter der LGPL.
