# Pollin-Spiel Lernkit #

Dieses Programm dient als alternative Firmware für das Pollin Spiel und soll es Mikrocontroller-anfängern oder kompletten Programmiereinsteigern ermöglich schnell und einfach Programme für AVRs entwickeln.

## Abhängigkeiten ##
* avr-gcc
* avr-libc
* avrdude
* make

Getestet unter Archlinux mit AVR-GCC 4.9.0

## High-Level Funktionen ##
Das Hauptprogramm ist in main.c . Ohne die Implementierung einer main() - Funktion kann direkt mit dem Verwenden der unten gegebenen Funktionen zum erstellen eines eigenen Programms begonnen werden.

Im fortgeschrittenen Modus kann die pollinspiel.c als Hauptprogramm verwendet werden. Dabei wird die Zeile `#include "main.c"` durch eigenen Quellcode ersetzt. Hierbei muss `init();` das Programm beginnen und `done();` beenden. Diese Funktionen kümmern sich um die komplette Initialisierung von Display und Hardwarekonfiguration (Buttons als Inputs). Ein hoher Ton kündigt die abgeschlossene Initialisierung an, ein tiefer Ton bedeutet das Ende des Programms. Bei Verwendung der main.c geschieht all dies automatisch.

* `void setled(LED_id LED, LED_state state);`
	- Leuchtdiode mit Bezeichnung LED auf state schalten
	- LED_id: LED1 - LED4 oder einfach direkt Zahlen (1-4)
	- LED_state: LED_on oder LED_off oder einfach direkt 1 (an) oder 0 (aus)
	- Die Zahlen stimmen mit denen, die auf der Platine aufgedruckt sind, überein
* `Button_state getbutton(Button_id button);`
	- Status von Knopf mit Bezeichnung button abfragen
	- Button_id: BUTTON1 - BUTTON5 oder einfach direkt Zahlen (1-5)
	- Button_state (return-Wert): BUTTON_PRESSED für gedrückt oder einfach 1 bzw. BUTTON_RELEASED = 0
	- Die Zahlen stimmen mit denen, die auf der Platine aufgedruckt sind, überein
* `void sound(int freq, int duration);`
	- Ton mit Frequenz freq für duration Millisekunden abspielen.
	- Zu große Werte für freq und duration können zu Fehlfunktion führen, deshalb in Schleife packen
* `void waitms(int ms);`
	- Das Programm für ms Millisekunden pausieren. Wie `_delay_ms()`, aber nimmt auch Variablen.

### LCD ###
* `void WriteDisplayString(char *data);`
	- Den String data auf dem Display ausgeben
* `void ClearDisplay(void);`
	- Den Displayinhalt löschen
* `void SetDisplayCursor(uint8_t x, uint8_t y);`
	- Den Displaycursor für WriteDisplayString auf x (Zeichenreihe), y (Zeile) verschieben
* `void UploadCustomCharacter(uint8_t addr, uint8_t *data)`
	- Ein custom character an die Adresse "addr" (0-7) aufs LCD hochladen. Der Upload muss am Anfang des Programms vorgenommen werden!
	- Das byte-array "data" beschreibt das aussehen des custom character. Ein guter Generator findet sich hierfür unter http://www.quinapalus.com/hd44780udg.html . Um Das dort erstellte Bild zu verwenden, muss der Code unter "In hex" in ein uint8_t-Array hineinkopiert werden.
	- Siehe auch sample/sample_customcharacters.c
* `WriteCustomCharacter(uint8_t addr)`
	- Ein mit `UploadCustomCharacter` auf "addr" hochgeladenes Bild aufs Display schreiben.
b
## Low-Level ##
* `sbi(ADDR, BIT)`
	- Das Bit mit der Nummer BIT im Byte ADDR setzen  (auf 1)
* `cbi(ADDR, BIT)`
	- Das Bit mit der Nummer BIT im Byte ADDR löschen (auf 0)
* `gbi(ADDR, BIT)`
	- Gibt das Bit mit der Nummer BIT im Byte ADDR zurück
* `tbi(ADDR, BIT)`
	- Den Status des Bits BIT im Byte ADDR wechseln (0 zu 1 und 1 zu 0)

## Systimer ##
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

## Samples ##
Im Ordner samples/ sind Beispielprogramme enthalten, aktuell nur eines. Diese können 1:1 in pollinspiel.c kopiert werden.
* sample_zufallsgenerator.c
	- Beim Drücken der EIN-Taste (BUTTON5) leuchten die LEDs nacheinander im Kreis langsamer werdend auf
	- Nach einer Weile steht fest, welche LED zufällig an ist. Ein Piepsen ertönt.
	- Das Programm kann durch erneutes drücken der EIN-Taste neugestartet werden.
	- Display wird nicht verwendet.
* sample_reaction_game.c
	- Der Spieler muss rechtzeitig den Taster bei der LED drücken, die aufleuchtet.
	- Dabei erhöht sich die Spielgeschwindigkeit immer weiter.
	- Am Ende wird das Ergebnis auf dem LCD-Display angezeigt.
	- Mit dem Taster 5 wird das Spiel (neu)gestartet.

## Lizenz ##
Die Dateien display.c, display.h sowie Teile von global.h stammen aus http://www.pollin.de/shop/downloads/D810148S.ZIP . Alle Rechte sind dem Autor vorbehalten.
Den gesamten weiteren Quelltext veröffentlich ich unter der LGPL.
