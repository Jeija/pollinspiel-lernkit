#ifndef _SYSTIMER_H
#define _SYSTIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include "global.h"

#define TIMER_PRESC		1024
#define TIMER_PRESC_1024	0b00000101

float SYSTIME;

// Timer
void systimer_init(void)
{
	sei();
	TCCR0B = TIMER_PRESC_1024;
	sbi(TIMSK, TOIE0); // Timer interrupt enable
}

ISR(TIMER0_OVF_vect)
{
	SYSTIME += ((256. * TIMER_PRESC) / F_CPU );
}

#endif
