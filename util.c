#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

//#include "systimer.h"
#include "display.h"
#include "global.h"
#include "util.h"

/*
	Funktionen für main.c - Hardware steuern
*/
Button_state getbutton(Button_id button)
{
	// Hardware: Vom Platinenaufdruck = interne Bezeichnung auf das PORTD-bit umrechnen
	uint8_t button_bit;
	if (button == BUTTON1) button_bit = 0;
	if (button == BUTTON2) button_bit = 1;
	if (button == BUTTON3) button_bit = 3;
	if (button == BUTTON4) button_bit = 4;
	if (button == BUTTON5) button_bit = 2;

	// Status des Tasters lesen
	return gbi(PIND, button_bit);
}

void sound(int freq, int duration)
{
	int nops = F_CPU / freq / 8;
	int count = (duration / 20) * (freq / 50);

	for (int i=0; i <= count; ++i)
	{
		for (int j = 0; j <= nops; ++j) asm("nop");
		tbi(PORTD, BUZZER);
	}

	cbi(PORTD, BUZZER);
}

void setled(LED_id led, LED_state state)
{
	// Hardware: Vom Platinenaufdruck = interne Bezeichnung auf das PORTD-bit umrechnen
	uint8_t led_bit;
	if (led == LED1) led_bit = 0;
	if (led == LED2) led_bit = 1;
	if (led == LED3) led_bit = 3;
	if (led == LED4) led_bit = 4;

	if (state)
	{
		sbi(LED_DDR,  led_bit);
		sbi(LED_PORT, led_bit);
	}
	else
	{
		cbi(LED_DDR,  led_bit);
		cbi(LED_PORT, led_bit);
	}
}

void waitms(int ms)
{
	for (int i = 0; i <= ms; ++i)
		_delay_ms(1);
}

/*
	init() und done() Funktionen
	Zu verwenden, wenn statt die main.c die pollinspiel.c - Datei für eigene Programme genutzt
	werden (Fortgeschrittener Modus).
*/

void init(void)
{
	// LCD
	sbi(DDRD, DISPLAY_POWER);
	sbi(PORTD, DISPLAY_POWER);
	sbi(DDRB, DISPLAY_Vo);
	InitDisplay();

	// Buzzer
	sbi(DDRD, BUZZER);
	//systimer_init();

	sound(2000, 50);
	_delay_ms(100);
}

void done(void)
{
	sound(500, 50);
	while(1);
}
