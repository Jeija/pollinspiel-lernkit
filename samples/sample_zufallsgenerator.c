/**
 * Diesen code direkt in main.c kopieren zum ausprobieren.
 *
 * Eine Art Würfel mit 4 möglichen Zufallszuständen.
 */

uint8_t led = LED1;
while(1)
{
	// Warten bis der Button 5 gedrückt wird
	int randnum = 0;
	while(!getbutton(BUTTON5))
		randnum++;

	// Falls schon ein Durchgang gemacht wurde, vorheriges Ergebnis löschen
	setled(led, LED_OFF);

	// "Lichtball" mit zufälliger Geschwindigkeit (delay) einwerfen
	led = LED1;
	int delay = randnum % 200;

	// "Lichtball" läuft herum bis er pro LED länger als 500ms braucht. Dabei wird er verlangsamt.
	while(delay < 500)
	{
		// Nächste LED anschalten
		setled(led, LED_OFF);
		led++;
		if (led > 4) led = 1;
		setled(led, LED_ON);

		// Ball verlangsamen und warten
		delay += 10;
		waitms(delay);

		// "Knacken" abspielen
		tbi(PORTD, BUZZER);
	}

	// Ergebnis eingeloggt, sound abspielen
	sound(1000, 500);
}
