#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "display.h"
#include "global.h"
#include "util.h"
//#include "systimer.h"

char getbutton(char button)
{
	return gbi(PIND, button);
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

void waitms(int ms)
{
	for (int i = 0; i <= ms; ++i)
		_delay_ms(1);
}

void init(void)
{
	DDRD  |= ((1<<BUZZER) | (1<<DISPLAY_POWER));
	DDRD  &= ~((1<<BUTTON1) | (1<<BUTTON2) | (1<<BUTTON3) | (1<<BUTTON4) | (1<<BUTTON5));

	PORTD |=  (1<<DISPLAY_POWER);
	PORTD &= ~((1<<BUTTON1) | (1<<BUTTON2) | (1<<BUTTON3) | (1<<BUTTON4) | (1<<BUTTON5));

	DDRB  |=  (1<<DISPLAY_Vo);
	PORTB |=  (1<<DISPLAY_Vo);

	InitDisplay();
	//systimer_init();

	sound(2000, 50);
	_delay_ms(100);
}

void done(void)
{
	sound(500, 50);
	while(1);
}

void setled(uint8_t LED, uint8_t state)
{
	if (state)
	{
		sbi(LED_DDR,  LED);
		sbi(LED_PORT, LED);
	}
	else
	{
		cbi(LED_DDR,  LED);
		cbi(LED_PORT, LED);
	}
}

void setledByNum(uint8_t lednum, uint8_t state)
{
	uint8_t led;

	if (lednum == 1) led = 0;
	if (lednum == 2) led = 1;
	if (lednum == 3) led = 3;
	if (lednum == 4) led = 4;

	setled(led, state);
}
